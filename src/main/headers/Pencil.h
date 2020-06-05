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
        // a Pencil needs a medium to do its work
        void attach(std::string& mediumRef);
        void write(std::string_view text);
        void erase(std::string_view text);
        void fillSpace(std::string_view text);
        void sharpen();

    private:
        bool isMediumNotAttached();
        std::string buildWriteString(std::string_view text);
        std::string buildEraseString(std::string_view text);
        std::string buildFillString(std::string_view text, std::size_t off);
        Point& point();
        std::vector<Point> points;
        Eraser eraser;
        std::string* medium;
    };
}

#endif //PENCIL_DURABILITY_PENCIL_H
