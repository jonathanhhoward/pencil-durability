/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#ifndef PENCIL_DURABILITY_UTILS_H
#define PENCIL_DURABILITY_UTILS_H

#include <cstddef>
#include <locale>
#include <string>
#include <string_view>
#include <vector>

namespace PencilDurability {
    bool isSpace(char c);
    bool isUpper(char c);
    bool isNotFound(std::size_t searchResult);
    std::string padText(bool isPad, const std::string& text);
}

#endif //PENCIL_DURABILITY_UTILS_H
