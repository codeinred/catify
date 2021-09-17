#include <array>
#include <exception>
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <random>
#include <vector>

namespace fs = std::filesystem;

std::string read_all(fs::path const& p, std::fstream& file) {
    std::string buffer(fs::file_size(p), '\0');
    file.read(buffer.data(), buffer.size());
    return buffer;
}

int catify(fs::path const& p) {
    std::fstream file(p);
    std::string contents = read_all(p, file);
    using std::string_view_literals::operator""sv;

    constexpr std::array endings = {"🐈"sv, "😌"sv, "💅"sv, "💕"sv, "💖"sv};

    std::random_device rd;

    std::string_view ending1 = endings[rd() % endings.size()];
    std::string_view ending2;
    do {
        ending2 = endings[rd() % endings.size()];
    } while (ending2 == ending1);

    std::string_view sv = contents;

    for (size_t start = 0; start < sv.size();) {
        size_t end = sv.find('\n', start);
        auto line = sv.substr(start, end - start);
        if (line.size() == 0 || line[0] == '#') {
            start = end + 1;
            continue;
        }

        file.seekp(end);
        file << ' ' << ending1 << ending2;
        file << sv.substr(end);
        return 0;
    }

    fmt::print("Could not find suitable point in file to put the cat.\n");
    return 1;
}
int main(int argc, char** argv) {


    if (argc == 1) {
        fmt::print("Error: no file specified.\n");
        return 1;
    }
    auto file = fs::path(argv[1]);

    if (!fs::exists(file)) {
        fmt::print("Error: file '{}' doesn't exist.\n", argv[1]);
        return 1;
    }

    return catify(file);
}
