/**
 * (C) Copyright 2020, by Jonathan Howard
 *
 * A Point has durability that degrades as it writes or overwrites characters.
 */

#ifndef PENCIL_DURABILITY_POINT_H
#define PENCIL_DURABILITY_POINT_H

#include "helpers.h"

namespace PencilDurability {
    class Point {
    public:
        explicit Point(int durability);
        char write(char character);
        char overwrite(char current, char next);

    private:
        bool isDull() const;
        void degradeUsing(char character);
        int durability;
    };
}

#endif //PENCIL_DURABILITY_POINT_H
