#include <catify.hpp>

namespace fs = std::filesystem;

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

    return catify::catify(file);
}
