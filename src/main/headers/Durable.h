/**
 * (C) Copyright 2020, by Jonathan Howard
 *
 * A Durable object has an initial durability value that degrades with use.
 */

#ifndef PENCIL_DURABILITY_DURABLE_H
#define PENCIL_DURABILITY_DURABLE_H

#include "helpers.h"

namespace PencilDurability {
    class Durable {
    public:
        explicit Durable(int durability);

    protected:
        [[nodiscard]] bool isDegraded() const;
        void degradeBy(int count);

    private:
        int durability;
    };

    class Point : public Durable {
    public:
        explicit Point(int durability);
        char write(char character);
        char overwrite(char current, char replacement);

    private:
        void degradeUsing(char character);
    };

    class Eraser : public Durable {
    public:
        explicit Eraser(int durability);
        char erase(char character);
    };
}

#endif //PENCIL_DURABILITY_DURABLE_H
