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
            degrade();

        return ' ';
    }

    bool Eraser::isWorn() const
    {
        return durability <= 0;
    }

    void Eraser::degrade()
    {
        --durability;
    }
}
