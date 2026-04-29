// Copyright (c) 2026 Leon J. Lee
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Oscilloscope.h"

#include <algorithm>

namespace vtplayer
{

    void Oscilloscope::update(AudioEngine const &engine)
    {
        engine.getSamples(_samples.data(), static_cast<int>(_samples.size()));
    }

    void Oscilloscope::draw(ventty::Window &window, int x, int y, int w, int h)
    {
        if (w <= 0 || h <= 0)
            return;

        int const N = static_cast<int>(_samples.size());
        ventty::Style traceStyle{_theme.visBarMid, _theme.background};
        ventty::Style axisStyle{_theme.visBarLow, _theme.background};

        int midRow = h / 2;
        for (int col = 0; col < w; ++col)
            window.putChar(x + col, y + midRow, U'─', axisStyle);

        int const denom = std::max(1, w - 1);
        for (int col = 0; col < w; ++col)
        {
            int idx = (col * (N - 1)) / denom;
            float s = std::clamp(_samples[idx], -1.0f, 1.0f);
            // s = +1 → top row, s = -1 → bottom row
            int row = static_cast<int>((1.0f - (s + 1.0f) * 0.5f) * (h - 1) + 0.5f);
            row = std::clamp(row, 0, h - 1);
            window.putChar(x + col, y + row, U'•', traceStyle);
        }
    }

} // namespace vtplayer
