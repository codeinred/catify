#pragma once
#include <constants.hpp>
#include <filesys.hpp>
#include <random.hpp>
#include <sanitization.hpp>

namespace catify {
int catify(fs::path const& p) {
    std::string contents = read_all(p);

    auto [e1, e2] = get_distinct_pair(emoji_endings.size());

    std::string_view ending1 = emoji_endings.at(e1);
    std::string_view ending2 = emoji_endings.at(e2);
    std::string_view sv = contents;

    for (size_t start = 0; start < sv.size();) {
        size_t end = sv.find('\n', start);
        auto line = sv.substr(start, end - start);
        if (line.size() == 0 || line[0] == '#') {
            start = end + 1;
            continue;
        }
        line = sanitize_ending(line, endings_to_sanitize);

        cfile file(p, "w");
        file.fwrite(sv.substr(0, start));
        file.fwrite(line);
        file.fwrite(" ");
        file.fwrite(ending1);
        file.fwrite(ending2);
        file.fwrite(sv.substr(end));
        return 0;
    }

    fmt::print("Could not find suitable point in file to put the cat.\n");
    return 1;
}
} // namespace catify
