#pragma once
#include <random>
#include <stdexcept>
#include <fmt/core.h>

namespace catify {
// Returns a randomly seeded rng
std::mt19937_64 get_rng() {
    std::random_device rd;
    auto seed = std::seed_seq {rd(), rd(), rd(), rd(), rd(), rd()};
    return std::mt19937_64(seed);
}
// Gets two distinct integers in the range [0, max)
auto get_distinct_pair(size_t max) {
    if (max <= 1) {
        throw std::invalid_argument(fmt::format(
            "Error in get_distinct_pair: can't get two distinct integers in "
            "range [0, {})",
            max));
    }
    auto rng = get_rng();
    std::uniform_int_distribution<size_t> dist(0, max - 1);
    size_t first = dist(rng);
    size_t second;
    do {
        second = dist(rng);
    } while (second == first);
    return std::pair {first, second};
}
} // namespace catify
