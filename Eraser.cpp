#include "Eraser.h"

namespace PencilDurability {
    Eraser::Eraser(int durability)
            :durability{ durability }
    {
    }

    char Eraser::erase(char character)
    {
        if (durability <= 0)
            return character;

        if (!isSpace(character))
            --durability;

        return ' ';
    }
}
