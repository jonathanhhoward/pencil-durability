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
}
