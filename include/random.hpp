#pragma once
#include <fmt/format.h>
#include <random>
#include <stdexcept>

namespace catify {
// Returns a randomly seeded rng
std::mt19937_64 get_rng() {
    std::random_device rd;
    auto seed = std::seed_seq {rd(), rd(), rd(), rd(), rd(), rd()};
    return std::mt19937_64(seed);
}
// Gets two distinct integers in the range [0, max). It has the precondition
// that max >= 2
auto get_distinct_pair(size_t max) {
    if (max <= 1) {
        throw std::invalid_argument(fmt::format(
            "Error in get_distinct_pair: can't get two distinct integers in "
            "range [0, {})",
            max));
    }
    auto rng = get_rng();
    std::uniform_int_distribution<size_t> dist1(0, max - 1);
    std::uniform_int_distribution<size_t> dist2(0, max - 2);
    size_t first = dist1(rng);
    size_t second = dist2(rng);

    // Second is shifted so that it becomes first + 1 when it's greater or equal
    // to first. This has the effect of ensuring second is from the distribution
    // {[0, first - 1], [first + 1, max - 1]}
    if (second >= first) {
        second += 1;
    }
    return std::pair {first, second};
}
} // namespace catify
