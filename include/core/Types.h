#ifndef TYPES_H
#define TYPES_H

#include <filesystem>

namespace Core {
    using FilePath = std::filesystem::path;
    using AssetPath = std::string_view;
    using TextureId = unsigned int;

    constexpr unsigned int DEFAULT_CAPACITY = 128;

    constexpr unsigned int MAX_QUADS = 10000;
    constexpr unsigned int MAX_VERTICES = MAX_QUADS * 4;
    constexpr unsigned int MAX_INDICES = MAX_QUADS * 6;
    constexpr unsigned int MAX_TEXTURES = 10000;
}

#endif //TYPES_H