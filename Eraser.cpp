/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "Eraser.h"

namespace PencilDurability {
    Eraser::Eraser(int durability)
            :durability{ durability }
    {
    }

    char Eraser::erase(char character)
    {
        const char space = ' ';

        if (isWorn())
            return character;

        if (!isSpace(character))
            degrade();

        return space;
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
