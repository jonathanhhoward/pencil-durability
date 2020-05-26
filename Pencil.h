#ifndef PENCIL_DURABILITY_PENCIL_H
#define PENCIL_DURABILITY_PENCIL_H

#include <string>
#include <string_view>
#include <vector>
#include "Point.h"

namespace PencilDurability {
    class Pencil {
    public:
        explicit Pencil(int initPointDurability = 100, int length = 100);
        void attach(std::string& paperRef);
        void write(std::string_view text);
        void erase(std::string_view text);
        void insert(std::string_view text);
        void sharpen();

    private:
        std::string buildString(std::string_view text);
        Point& point();
        std::vector<Point> points;
        std::string* paper;
    };
}

#endif //PENCIL_DURABILITY_PENCIL_H
