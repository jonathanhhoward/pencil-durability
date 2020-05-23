#ifndef PENCIL_DURABILITY_PENCIL_H
#define PENCIL_DURABILITY_PENCIL_H

#include <string>
#include <string_view>
#include "Point.h"

namespace PencilDurability {
    class Pencil {
    public:
        explicit Pencil(int initPointDurability = 100, int length = 100);
        void writeTextToPaper(std::string_view instruction, std::string& paper);
        void eraseTextFromPaper(std::string text, std::string& paper);
        void insertTextToPaper(std::string text, std::string& paper);
        void sharpen();

    private:
        std::string writeTextFrom(std::string_view instruction);
        Point point;
        int length;
    };
}

#endif //PENCIL_DURABILITY_PENCIL_H
