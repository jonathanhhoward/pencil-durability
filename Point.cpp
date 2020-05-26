#include "Point.h"
#include <locale>

namespace PencilDurability {
    Point::Point(int durability)
            :durability{ durability }
    {
    }

    char Point::extract(char character)
    {
        if (isDull())
            return ' ';

        if (std::isspace(character, std::locale("C")))
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
        if (std::isupper(character, std::locale("C")))
            durability -= 2;
        else
            --durability;
    }
}
