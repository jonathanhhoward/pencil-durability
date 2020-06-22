/**
 * (C) Copyright 2020, by Jonathan Howard
 *
 * This is my original solution to the Pencil Durability Kata for Pillar Technology
 * which describes a Pencil that has durability that degrades with use. A Pencil works
 * directly on any medium that holds a string.
 *
 * https://github.com/PillarTechnology/kata-pencil-durability
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
        ~Pencil();
        void attachRequired(std::string& mediumRef);
        void writeAppend(std::string_view text);
        void writeFill(std::string_view text);
        void erase(std::string_view text);
        void sharpen();

        std::string buildAppendString(std::string_view text);
        std::string buildFillString(std::string_view context, std::string_view text);
    private:
        std::string buildEraseString(std::string_view text);
        [[nodiscard]] DurablePoint* newPoint();
        std::vector<DurablePoint> points;
        DurablePoint* point;
        DurableEraser eraser;
        std::string* medium;
    };
}

#endif //PENCIL_DURABILITY_PENCIL_H
