// Copyright (c) 2026 Leon J. Lee
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "UnicodeNormalize.h"

#include <ventty/core/Utf8.h>

#include <vector>

namespace vtplayer
{

namespace
{

// Hangul Jamo (conjoining) → Hangul Syllables 알고리즘
// (Unicode 표준 부속서 §3.12 Hangul Composition).
constexpr char32_t kLBase  = 0x1100;
constexpr char32_t kVBase  = 0x1161;
constexpr char32_t kTBase  = 0x11A7;
constexpr char32_t kSBase  = 0xAC00;
constexpr int      kLCount = 19;
constexpr int      kVCount = 21;
constexpr int      kTCount = 28;

inline bool isL(char32_t c) { return c >= kLBase && c < kLBase + kLCount; }
inline bool isV(char32_t c) { return c >= kVBase && c < kVBase + kVCount; }
// T_idx 0 == "no trailing"; conjoining T occupies kTBase+1 .. kTBase+27.
inline bool isT(char32_t c) { return c > kTBase && c < kTBase + kTCount; }

} // namespace

std::string toNfc(std::string_view str)
{
    auto cps = ventty::toCodepoints(str);
    std::vector<char32_t> out;
    out.reserve(cps.size());

    for (size_t i = 0; i < cps.size();)
    {
        char32_t const c = cps[i];
        if (isL(c) && i + 1 < cps.size() && isV(cps[i + 1]))
        {
            int const lIdx = static_cast<int>(c - kLBase);
            int const vIdx = static_cast<int>(cps[i + 1] - kVBase);
            int       tIdx = 0;
            size_t    step = 2;
            if (i + 2 < cps.size() && isT(cps[i + 2]))
            {
                tIdx = static_cast<int>(cps[i + 2] - kTBase);
                step = 3;
            }
            char32_t const syllable = kSBase
                                    + ((lIdx * kVCount) + vIdx) * kTCount
                                    + tIdx;
            out.push_back(syllable);
            i += step;
        }
        else
        {
            out.push_back(c);
            ++i;
        }
    }

    return ventty::fromCodepoints(out);
}

std::string truncateToWidth(std::string_view str, int maxWidth,
                            std::string_view ellipsis)
{
    if (maxWidth <= 0) return {};

    int const totalW = ventty::stringWidth(str);
    if (totalW <= maxWidth) return std::string(str);

    int const ellipsisW = ventty::stringWidth(ellipsis);
    bool useEllipsis = ellipsisW <= maxWidth;
    int budget = useEllipsis ? (maxWidth - ellipsisW) : maxWidth;

    std::string out;
    out.reserve(str.size());
    int width = 0;
    size_t pos = 0;
    while (pos < str.size())
    {
        size_t const prev = pos;
        char32_t const cp = ventty::decode(str, pos);
        int const cpW = ventty::displayWidth(cp);
        if (width + cpW > budget) { pos = prev; break; }
        out.append(str.data() + prev, pos - prev);
        width += cpW;
    }
    if (useEllipsis) out.append(ellipsis);
    return out;
}

} // namespace vtplayer
