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

    cfile file(p, "w");
    for (size_t start = 0; start < sv.size();) {
        size_t end = sv.find('\n', start);
        auto line = sv.substr(start, end - start);
        if (line.size() == 0 || line[0] == '#') {
            start = end + 1;
            continue;
        }
        line = sanitize_ending(line, endings_to_sanitize);

        file.fwrite(sv.substr(0, start));
        file.fwrite(line);
        file.fwrite(" ");
        file.fwrite(ending1);
        file.fwrite(ending2);
        file.fwrite(sv.substr(end));
        return 0;
    }
    // If it can't find one, it just adds the emojis to the beginning
    // This is used so git commit with no message still works
    file.fwrite(ending1);
    file.fwrite(ending2);
    file.fwrite(contents);

    return 0;
}
} // namespace catify
