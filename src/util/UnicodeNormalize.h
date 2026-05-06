// Copyright (c) 2026 Leon J. Lee
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <string>
#include <string_view>

namespace vtplayer
{

/// 한글 자모(NFD)를 미리 조합된 음절(NFC)로 변환한다.
/// 다른 코드포인트는 그대로 통과시키므로, macOS HFS+/APFS가
/// 노출하는 NFD 형태의 한글 파일명을 화면에 표시하기 직전에
/// 정규화하기 위한 용도로 사용한다.
std::string toNfc(std::string_view str);

/// 표시 폭(셀 단위) 기준으로 문자열을 잘라낸다. 한글·CJK처럼
/// 전각 문자가 차지하는 2셀을 정확히 반영하며, UTF-8 멀티바이트
/// 시퀀스를 절대 중간에 자르지 않는다. 잘림이 발생하면 ellipsis를
/// 덧붙이고, 최종 결과의 표시 폭은 maxWidth를 넘지 않는다.
std::string truncateToWidth(std::string_view str, int maxWidth,
                            std::string_view ellipsis = "..");

} // namespace vtplayer
