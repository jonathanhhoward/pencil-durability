/**
 * (C) Copyright 2020, by Jonathan Howard
 *
 * A Pencil has durability that degrades with use.
 */

#ifndef PENCIL_DURABILITY_PENCIL_H
#define PENCIL_DURABILITY_PENCIL_H

#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>
#include "Durable.h"
#include "helpers.h"

namespace PencilDurability {
    class Pencil {
    public:
        // defaults approximate typical #2 pencil
        explicit Pencil(int pointDurability = 3000, std::size_t length = 40, int eraserDurability = 1000);
        std::string write(std::string_view text);
        std::string overwrite(std::string_view oldText, std::string_view newText);
        std::string erase(std::string_view text);
        void sharpen();

    private:
        std::vector<DurablePoint> points;
        DurablePoint* point;
        DurableEraser eraser;
    };
}

#endif //PENCIL_DURABILITY_PENCIL_H
