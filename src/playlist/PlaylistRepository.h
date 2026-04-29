// Copyright (c) 2026 Leon J. Lee
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "Playlist.h"

#include <filesystem>
#include <string>

namespace vtplayer
{

/// Manages the playlist directory (~/.config/ventty-player/playlists) and bootstraps
/// the default playlist when the user hasn't opened one yet.
class PlaylistRepository
{
public:
    /// Base directory for playlist files. Derived from $HOME like Config::defaultPath().
    static std::filesystem::path defaultDirectory();

    /// Canonical path to the bootstrap playlist (`<defaultDirectory>/default.m3u`).
    static std::filesystem::path defaultPlaylistPath();

    /// Create the directory if it does not exist. Safe to call repeatedly.
    static bool ensureDirectory();

    /// Ensure `default.m3u` exists (creating an empty one if not) and return the loaded playlist.
    /// Used as a fallback when Config.playlistCurrentPath is missing or points at a deleted file.
    static Playlist ensureDefault();

    /// Generate a unique path for a new untitled playlist inside the default directory.
    static std::filesystem::path newUntitledPath();
};

} // namespace vtplayer
