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

        if (isRemaining()) {
            charToWrite = c;
            if (std::isupper(c, std::locale("C")))
                degrade();
            degrade();
        }
        else
            charToWrite = ' ';

        return charToWrite;
    }
}
