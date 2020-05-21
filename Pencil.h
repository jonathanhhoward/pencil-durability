#ifndef PENCIL_DURABILITY_PENCIL_H
#define PENCIL_DURABILITY_PENCIL_H

#include <string>
#include <string_view>
#include "Point.h"

namespace PencilDurability {
    class Pencil {
    public:
        explicit Pencil(int initPointDurability);
        void writeTextToPaper(std::string_view instruction, std::string& paper);
        void eraseTextFromPaper(std::string text, std::string& paper);
        void insertTextToPaper(std::string text, std::string& paper);

        Point point;

    private:
        std::string writeTextFrom(std::string_view instruction);
    };
}

#endif //PENCIL_DURABILITY_PENCIL_H
