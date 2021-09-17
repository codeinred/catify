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
}
