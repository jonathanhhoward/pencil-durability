#ifndef PENCIL_DURABILITY_PENCIL_H
#define PENCIL_DURABILITY_PENCIL_H

#include <string>
namespace PencilDurability {
    class Pencil {
    public:
        Pencil() = default;
        explicit Pencil(int initPointDurability);
        void writeTextToPaper(std::string text, std::string& paper);
        void eraseTextFromPaper(std::string text, std::string& paper);
        void insertTextToPaper(std::string text, std::string& paper);

        int pointDurability;
    };
}

#endif //PENCIL_DURABILITY_PENCIL_H
