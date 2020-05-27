#include "Eraser.h"
#include <locale>

namespace PencilDurability {
    Eraser::Eraser(int durability)
            :durability{ durability }
    {
    }

    char Eraser::erase(char character)
    {
        if (!durability)
            return character;

        if (!std::isspace(character, std::locale("C")))
            --durability;

        return ' ';
    }
}
