#include "Pencil.h"
#include <locale>

namespace PencilDurability {
    Pencil::Pencil(int point, int length, int eraser)
            :points(length, Point{ point }),
             eraser{ eraser },
             paper{ nullptr }
    {
    }

    void Pencil::attach(std::string& paperRef)
    {
        paper = &paperRef;
    }

    void Pencil::write(std::string_view text)
    {
        *paper += buildString(text);
    }

    void Pencil::erase(std::string_view text)
    {
        if (!eraser) return;

        auto pos = paper->rfind(text, std::string::npos);

        if (pos == std::string::npos) return;

        std::string erased{ text };
        for (int i = 0; i < erased.size(); ++i) {
            if (!eraser) break;
            auto off = erased.size() - 1 - i;
            if (std::isspace(erased[off], std::locale("C"))) continue;
            erased.replace(off, 1, " ");
            --eraser;
        }

        paper->replace(pos, text.size(), erased);
    }

    void Pencil::insert(std::string_view text)
    {
        *paper = "An onion a day keeps the doctor away";
    }

    void Pencil::sharpen()
    {
        if (points.size() == 1) return;

        points.pop_back();
    }

    std::string Pencil::buildString(std::string_view text)
    {
        std::string str;

        for (char c : text)
            str += point().extract(c);

        return str;
    }

    Point& Pencil::point()
    {
        return points.back();
    }
}
