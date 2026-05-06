// Copyright (c) 2026 Leon J. Lee
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "VisualizerView.h"

#include <ventty/art/AsciiArt.h>

namespace vtplayer
{

    void VisualizerView::setVisualizer(std::unique_ptr<Visualizer> vis)
    {
        _vis = std::move(vis);
        if (_vis)
            _vis->setTheme(_theme);
    }

    void VisualizerView::update(AudioEngine const &engine)
    {
        if (_vis)
            _vis->update(engine);
    }

    void VisualizerView::draw(ventty::Window &window)
    {
        auto const &r = rect();

        // Left + right borders
        ventty::Style borderStyle{_theme.border, _theme.background};
        for (int y = 0; y < r.height; ++y)
        {
            window.putChar(r.x, r.y + y, ventty::DOUBLE_BOX.v, borderStyle);
            window.putChar(r.x + r.width - 1, r.y + y, ventty::DOUBLE_BOX.v, borderStyle);
        }

        // Visualizer fills the full inner area
        int cx = r.x + 2;
        int cw = r.width - 4;
        if (_vis)
        {
            _vis->draw(window, cx, r.y, cw, r.height);
        }
    }

} // namespace vtplayer
