#include "Point.h"
#include <locale>

namespace PencilDurability {
    Point::Point(int initDurability)
            :durability{ initDurability }
    {
    }

    char Point::writeAndDegrade(char charToWrite)
    {
        const char SPACE = ' ';

        if (isDull()) return SPACE;

        degrade(charToWrite);

        return charToWrite;
    }

    bool Point::isDull() const
    {
        return durability == 0;
    }

    void Point::degrade(char c)
    {
        std::locale loc("C");

        if (std::isspace(c, loc)) return;

        if (std::isupper(c, loc))
            durability -= 2;
        else
            --durability;
    }
}
