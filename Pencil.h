#ifndef PENCIL_DURABILITY_PENCIL_H
#define PENCIL_DURABILITY_PENCIL_H

#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>
#include "Point.h"
#include "Eraser.h"

namespace PencilDurability {
    class Pencil {
    public:
        explicit Pencil(int point = 100, std::size_t length = 100, int eraser = 100);
        void attach(std::string& paperRef);
        void write(std::string_view text);
        void erase(std::string_view text);
        void insert(std::string_view text);
        void sharpen();

    private:
        void checkPaper();
        std::string buildWriteString(std::string_view text);
        std::string buildEraseString(std::string_view text);
        Point& point();
        std::vector<Point> points;
        Eraser eraser;
        std::string* paper;
    };

    bool isTextNotFound(std::size_t searchResult);
}

#endif //PENCIL_DURABILITY_PENCIL_H
