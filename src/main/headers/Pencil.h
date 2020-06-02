/**
 * (C) Copyright 2020, by Jonathan Howard
 *
 * This is my original solution to the Pencil Durability Kata for Pillar Technology
 * which describes a Pencil with a Point and an Eraser that degrades when it writes
 * text, erases text, and fills in erased text. A Pencil works with any medium that
 * holds a string, and it makes changes directly to that string.
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
#include "Point.h"
#include "Eraser.h"
#include "helpers.h"

namespace PencilDurability {
    class Pencil {
    public:
        // defaults approximate typical #2 pencil
        explicit Pencil(int point = 3000, std::size_t length = 40, int eraser = 1000);
        // using the pencil without attaching a medium throws an exception
        void attach(std::string& mediumRef);
        void write(std::string_view text);
        void erase(std::string_view text);
        void fillErased(std::string_view text);
        void sharpen();

    private:
        void checkMediumExists();
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
