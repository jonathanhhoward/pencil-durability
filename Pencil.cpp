#include "Pencil.h"

namespace PencilDurability {
    Pencil::Pencil(int initPointDurability, int length)
            :points(length, Point{ initPointDurability }),
             paper{ nullptr }
    {
    }

    void Pencil::attach(std::string& paperRef)
    {
        paper = &paperRef;
    }

    void Pencil::write(std::string_view text)
    {
        *paper += writeTextFrom(text);
    }

    void Pencil::erase(std::string_view text)
    {
        auto pos = paper->rfind(text, std::string::npos);

        if (pos == std::string::npos) return;

        paper->replace(pos, text.size(), "     ");
    }

    void Pencil::insert(std::string_view text)
    {
        *paper = "An onion a day keeps the doctor away";
    }

    void Pencil::sharpen()
    {
        if (points.empty()) return;

        points.pop_back();
    }

    std::string Pencil::writeTextFrom(std::string_view instruction)
    {
        std::string text;

        for (char c : instruction)
            text += !points.empty() ? point().writeAndDegrade(c) : ' ';

        return text;
    }

    Point& Pencil::point()
    {
        return points.back();
    }
}
