#include "Point.h"
#include <locale>

namespace PencilDurability {
    Point::Point(int initDurability)
            :durability{ initDurability }
    {
    }

    bool Point::isRemaining() const
    {
        return durability != 0;
    }

    void Point::degrade()
    {
        --durability;
    }

    char Point::write(char c)
    {
        char charToWrite;
        std::locale loc("C");

        if (isRemaining()) {
            charToWrite = c;
            if (std::isspace(c, loc))
                return charToWrite;
            if (std::isupper(c, loc))
                degrade();
            degrade();
        }
        else
            charToWrite = ' ';

        return charToWrite;
    }
}
