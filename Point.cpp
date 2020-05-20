#include "Point.h"

namespace PencilDurability {
    Point::Point(int initDurability)
            :durability{ initDurability }
    {
    }

    bool Point::isRemaining() const
    {
        return durability != 0;
    }
}
