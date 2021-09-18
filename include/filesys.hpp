#pragma once
#include <cerrno>
#include <cstdio>
#include <filesystem>
#include <fmt/core.h>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

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
    // Deleted to prevent accidental copies resulting in double-frees
    cfile(cfile const&) = delete;
    cfile(cfile&& cf) noexcept
      : fileptr(std::exchange(cf.fileptr, nullptr)) {}

    // This allows you to avoid checking if the file is the same as itself
    // Self-assignment can only be done by doing `f = std::move(f)`, which
    // will create a new cfile, resulting in f.fileptr being made null. Then,
    // when the assignment occurs, tihs null value will be replaced with the
    // original value.
    cfile& operator=(cfile f) {
        std::swap(fileptr, f.fileptr);
        return *this;
    }

    operator FILE*() const { return fileptr; }

    // Closes the fileptr, no questions asked.
    ~cfile() noexcept {
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
