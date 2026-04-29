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

} // namespace vtplayer
