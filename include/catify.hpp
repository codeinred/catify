#pragma once
#include <string_view>
#include <cstddef>

namespace catify {
constexpr size_t ends_with(std::string_view line, auto const& range) {
    for (std::string_view ending : range) {
        if (line.ends_with(ending))
            return ending.size();
    }
    return 0;
}

// Removes suffixes in the range `endings` from line
constexpr auto sanitize_ending(std::string_view line, auto const& endings)
    -> std::string_view {
    while (size_t ending_len = ends_with(line, endings)) {
        line.remove_suffix(ending_len);
    }
    return line;
}
}
