#include "helpers.h"

namespace PencilDurability {
    bool isSpace(char c)
    {
        return std::isspace(c, std::locale{ "C" });
    }
}
