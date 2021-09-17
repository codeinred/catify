#pragma once
#include <array>
#include <cstddef>
#include <string_view>

namespace catify {
// Returns the size of the first matching suffix. If none match, returns 0
constexpr size_t check_suffix(std::string_view line, auto const& range) {
    for (std::string_view ending : range) {
        if (line.ends_with(ending))
            return ending.size();
    }
    return 0;
}

// Removes suffixes in the range `endings` from line
constexpr auto sanitize_ending(std::string_view line, auto const& endings)
    -> std::string_view {
    while (size_t ending_len = check_suffix(line, endings)) {
        line.remove_suffix(ending_len);
    }
    return line;
}


constexpr std::array emoji_endings = {"🐈"sv, "😌"sv, "💅"sv, "💕"sv, "💖"sv};
constexpr std::array endings_to_sanitize = {
    " "sv, "🐈"sv, "😌"sv, "💅"sv, "💕"sv, "💖"sv};
} // namespace catify
