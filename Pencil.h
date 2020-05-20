#ifndef PENCIL_DURABILITY_PENCIL_H
#define PENCIL_DURABILITY_PENCIL_H

#include <string>
namespace PencilDurability {
    class Pencil {
    public:
        void writeTextToPaper(std::string text, std::string& paper);
        void eraseTextFromPaper(std::string text, std::string& paper);
    };
}

#endif //PENCIL_DURABILITY_PENCIL_H
