// Copyright (c) 2026 Leon J. Lee
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "PlaylistRepository.h"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <system_error>

namespace vtplayer
{

std::filesystem::path PlaylistRepository::defaultDirectory()
{
    char const * home = std::getenv("HOME");
    if (!home) return {};
    return std::filesystem::path(home) / ".config" / "ventty-player" / "playlists";
}

std::filesystem::path PlaylistRepository::defaultPlaylistPath()
{
    auto dir = defaultDirectory();
    if (dir.empty()) return {};
    return dir / "default.m3u";
}

bool PlaylistRepository::ensureDirectory()
{
    auto dir = defaultDirectory();
    if (dir.empty()) return false;

    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    return !ec;
}

Playlist PlaylistRepository::ensureDefault()
{
    auto path = defaultPlaylistPath();
    ensureDirectory();

    if (!std::filesystem::exists(path))
    {
        Playlist empty(path);
        empty.save();
        return empty;
    }

    if (auto loaded = Playlist::load(path))
    {
        return std::move(*loaded);
    }
    return Playlist(path);
}

std::filesystem::path PlaylistRepository::newUntitledPath()
{
    auto dir = defaultDirectory();
    ensureDirectory();

    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &now);
#else
    localtime_r(&now, &tm);
#endif

    char stamp[32];
    std::strftime(stamp, sizeof(stamp), "%Y%m%d-%H%M%S", &tm);

    auto candidate = dir / (std::string("untitled-") + stamp + ".m3u");
    int suffix = 1;
    while (std::filesystem::exists(candidate))
    {
        candidate = dir / (std::string("untitled-") + stamp + "-" + std::to_string(suffix) + ".m3u");
        ++suffix;
    }
    return candidate;
}

} // namespace vtplayer
