/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "Durable.h"

namespace PencilDurability {
    DurableBase::DurableBase(int durability)
            :durability{ durability } { }

    bool DurableBase::isDegraded() const
    {
        return durability <= 0;
    }

    void DurableBase::degradeBy(int count)
    {
        durability -= count;
    }

    DurablePoint::DurablePoint(int durability)
            :DurableBase{ durability }
    {
    }

    char DurablePoint::write(char character)
    {
        const char space = ' ';

        if (isDegraded())
            return space;

        if (isSpace(character))
            return character;

        degradeUsing(character);
        return character;
    }

    char DurablePoint::overwrite(char current, char replacement)
    {
        const char overwrite = '@';

        if (isDegraded() || isSpace(replacement))
            return current;

        degradeUsing(replacement);

        return isSpace(current) ? replacement : overwrite;
    }

    void DurablePoint::degradeUsing(char character)
    {
        if (isUpper(character))
            degradeBy(2);
        else
            degradeBy(1);
    }

    DurableEraser::DurableEraser(int durability)
            :DurableBase{ durability }
    {
    }

    char DurableEraser::erase(char character)
    {
        const char space = ' ';

        if (isDegraded())
            return character;

        if (!isSpace(character))
            degradeBy(1);

        return space;
    }
}
