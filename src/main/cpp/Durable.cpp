/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "Durable.h"

namespace PencilDurability {
    Durable::Durable(int durability)
            :durability{ durability } { }

    bool Durable::isDegraded() const
    {
        return durability <= 0;
    }

    void Durable::degradeBy(int count)
    {
        durability -= count;
    }

    Point::Point(int durability)
            :Durable{ durability }
    {
    }

    char Point::write(char character)
    {
        const char space = ' ';

        if (isDegraded())
            return space;

        if (isSpace(character))
            return character;

        degradeUsing(character);
        return character;
    }

    char Point::overwrite(char current, char replacement)
    {
        const char space = ' ';
        const char newline = '\n';
        const char overwrite = '@';

        if (isDegraded() || replacement == space)
            return current;

        if (replacement != newline)
            degradeUsing(replacement);

        return isSpace(current) ? replacement : overwrite;
    }

    void Point::degradeUsing(char character)
    {
        if (isUpper(character))
            degradeBy(2);
        else
            degradeBy(1);
    }

    Eraser::Eraser(int durability)
            :Durable{ durability }
    {
    }

    char Eraser::erase(char character)
    {
        const char space = ' ';

        if (isDegraded())
            return character;

        if (!isSpace(character))
            degradeBy(1);

        return space;
    }
}
