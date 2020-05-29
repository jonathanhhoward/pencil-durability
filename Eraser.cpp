#include "Eraser.h"

namespace PencilDurability {
    Eraser::Eraser(int durability)
            :durability{ durability }
    {
    }

    char Eraser::erase(char character)
    {
        if (isWorn())
            return character;

        if (!isSpace(character))
            --durability;

        return ' ';
    }

    bool Eraser::isWorn() const
    {
        return durability <= 0;
    }
}
