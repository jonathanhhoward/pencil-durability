/**
 * (C) Copyright 2020, by Jonathan Howard
 *
 * An Eraser has durability that degrades as it erases characters.
 */

#ifndef PENCIL_DURABILITY_ERASER_H
#define PENCIL_DURABILITY_ERASER_H

#include "helpers.h"

namespace PencilDurability {
    class Eraser {
    public:
        explicit Eraser(int durability);
        char erase(char character);

    private:
        bool isWorn() const;
        void degrade();
        int durability;
    };
}

#endif //PENCIL_DURABILITY_ERASER_H
