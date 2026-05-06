// Copyright (c) 2026 Leon J. Lee
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "Theme.h"
#include "../audio/AudioEngine.h"
#include "../visualizer/Visualizer.h"

#include <ventty/widget/Widget.h>

#include <memory>

namespace vtplayer
{

    class VisualizerView : public ventty::Widget
    {
    public:
        void setTheme(Theme const &theme)
        {
            _theme = theme;
            if (_vis)
                _vis->setTheme(theme);
        }

        /// Set the active visualizer implementation.
        void setVisualizer(std::unique_ptr<Visualizer> vis);

        /// Call each frame with latest audio samples.
        void update(AudioEngine const &engine);

        void draw(ventty::Window &window) override;

    private:
        Theme _theme;
        std::unique_ptr<Visualizer> _vis;
    };

} // namespace vtplayer
