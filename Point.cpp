#include "Point.h"

namespace PencilDurability {
    Point::Point(int durability)
            :durability{ durability }
    {
    }

    char Point::write(char character)
    {
        const char space = ' ';

        if (isDull())
            return space;

        if (isSpace(character))
            return character;

        degradeUsing(character);
        return character;
    }

    bool Point::isDull() const
    {
        return durability <= 0;
    }

    void Point::degradeUsing(char character)
    {
        if (isUpper(character))
            durability -= 2;
        else
            --durability;
    }
}
