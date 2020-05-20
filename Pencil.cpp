#include "Pencil.h"

namespace PencilDurability {
    void Pencil::writeTextToPaper(std::string text, std::string& paper)
    {
        paper += text;
    }

    void Pencil::eraseTextFromPaper(std::string text, std::string& paper)
    {
        paper = "How much wood would a woodchuck chuck if a woodchuck could       wood?";
    }
}
