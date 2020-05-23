#include "Pencil.h"

namespace PencilDurability {
    Pencil::Pencil(int initPointDurability, int length)
            :point{ initPointDurability }
    {
    }

    void Pencil::writeTextToPaper(std::string_view instruction, std::string& paper)
    {
        paper += writeTextFrom(instruction);
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

    void Pencil::sharpen()
    {
        point.sharpen();
    }

    std::string Pencil::writeTextFrom(std::string_view instruction)
    {
        std::string text;

        for (char c : instruction)
            text += point.writeAndDegrade(c);

        return text;
    }
}
