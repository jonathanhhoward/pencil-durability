/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#ifndef PENCIL_DURABILITY_HELPERS_H
#define PENCIL_DURABILITY_HELPERS_H

#include <cstddef>
#include <locale>
#include <string>

namespace PencilDurability {
    bool isSpace(char c);
    bool isUpper(char c);
    bool isNotFound(std::size_t searchResult);
    bool isStartOfPaper(std::size_t searchResult);
}

#endif //PENCIL_DURABILITY_HELPERS_H
