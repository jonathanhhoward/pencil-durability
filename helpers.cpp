#include "helpers.h"

namespace PencilDurability {
    bool isSpace(char c)
    {
        return std::isspace(c, std::locale{ "C" });
    }

    bool isUpper(char c)
    {
        return std::isupper(c, std::locale{ "C" });
    }

    bool isTextNotFound(std::size_t searchResult)
    {
        return searchResult == std::string::npos;
    }

    bool isStartOfPaper(std::size_t searchResult)
    {
        return searchResult == 0;
    }
}
