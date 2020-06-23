/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "pencil-durability-utils.h"

namespace PencilDurability {
    bool isSpace(char c)
    {
        return std::isspace(c, std::locale{ "C" });
    }

    bool isUpper(char c)
    {
        return std::isupper(c, std::locale{ "C" });
    }

    bool isNotFound(std::size_t searchResult)
    {
        return searchResult == std::string::npos;
    }

    bool isBeginMedium(std::size_t searchResult)
    {
        return searchResult == 0;
    }
}
