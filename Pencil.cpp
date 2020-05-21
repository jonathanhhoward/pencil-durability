#include "Pencil.h"
#include <locale>

namespace PencilDurability {
    Pencil::Pencil(int initPointDurability)
            :point{ initPointDurability }
    {
    }

    void Pencil::writeTextToPaper(std::string text, std::string& paper)
    {
        std::string letters;
        std::locale loc("C");

        for (char c : text) {
            if (point.isRemaining()) {
                letters += c;
                if (std::isupper(c, loc))
                    point.degrade();
                point.degrade();
            }
            else
                letters += ' ';
        }

        paper += letters;
    }

    void Pencil::eraseTextFromPaper(std::string text, std::string& paper)
    {
        auto pos = paper.rfind(text, std::string::npos);

        if (pos == std::string::npos) return;

        paper.replace(pos, text.size(), "     ");
    }

    void Pencil::insertTextToPaper(std::string text, std::string& paper)
    {
        paper = "An onion a day keeps the doctor away";
    }
}
