// Copyright (c) 2026 Leon J. Lee
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "Theme.h"

#include <ventty/widget/Widget.h>

namespace vtplayer
{

class HeaderBar : public ventty::Widget
{
public:
    void setTheme(Theme const & theme) { _theme = theme; }

    void draw(ventty::Window & window) override;

private:
    Theme _theme;
};

} // namespace vtplayer
