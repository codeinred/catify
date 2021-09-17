#pragma once
#include <cerrno>
#include <cstdio>
#include <filesystem>
#include <fmt/core.h>
#include <stdexcept>
#include <string>
#include <string_view>

namespace catify {
namespace fs = std::filesystem;

class cfile {
    FILE* fileptr = nullptr;
    void check(const char* filename, const char* mode) {
        int error_code = errno;
        if (fileptr == nullptr) {
            throw std::runtime_error(fmt::format(
                "Unable to open '{}' with mode '{}'. Error code: {}",
                filename,
                mode,
                error_code));
        }
    }

   public:
    cfile() = default;
    cfile(fs::path const& p, const char* mode)
      : fileptr(fopen(p.c_str(), mode)) {
        check(p.c_str(), mode);
    }

    operator FILE*() const { return fileptr; }
    ~cfile() {
        if (fileptr) {
            fclose(fileptr);
        }
    }

    size_t fwrite(std::string_view sv) {
        return std::fwrite(sv.data(), 1, sv.size(), fileptr);
    }
    size_t fread(char* dest, size_t count) {
        return std::fread(dest, 1, count, fileptr);
    }
};

std::string read_all(fs::path const& p) {
    size_t size = fs::file_size(p);
    std::string buffer(size, '\0');
    cfile file(p, "r");
    size_t amount_read = file.fread(buffer.data(), buffer.size());
    if (amount_read != size) {
        throw std::runtime_error(fmt::format(
            "Couldn't read entire file. Expected {} bytes, but was only able "
            "to read {} bytes.",
            size,
            amount_read));
    }
    return buffer;
}

} // namespace catify
