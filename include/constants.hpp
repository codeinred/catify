#pragma once
#include <array>
#include <string_view>

namespace catify {
using std::string_view_literals::operator""sv;

constexpr std::array emoji_endings = {"🐈"sv, "😌"sv, "💅"sv, "💕"sv, "💖"sv};
constexpr std::array endings_to_sanitize =
    {" "sv, "🐈"sv, "😌"sv, "💅"sv, "💕"sv, "💖"sv};
} // namespace catify
