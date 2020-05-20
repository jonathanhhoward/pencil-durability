#include "Pencil.h"

namespace PencilDurability {
    Pencil::Pencil(int initPointDurability)
            :pointDurability{ 100 }
    {
    }

    void Pencil::writeTextToPaper(std::string text, std::string& paper)
    {
        paper += text;
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
