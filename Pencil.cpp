#include "Pencil.h"

namespace PencilDurability {
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
}
