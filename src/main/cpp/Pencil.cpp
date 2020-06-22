/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "Pencil.h"

namespace PencilDurability {
    Pencil::Pencil(int pointDurability, std::size_t length, int eraserDurability)
            :points(length, DurablePoint{ pointDurability }),
             point{ newPoint() },
             eraser{ eraserDurability },
             medium{ nullptr }
    {
    }

    Pencil::~Pencil()
    {
        if (points.empty())
            delete point;
    }

    void Pencil::sharpen()
    {
        if (points.empty())
            return;

        points.pop_back();
        point = newPoint();
    }

    std::string Pencil::write(std::string_view text)
    {
        std::string str;

        for (char c : text)
            str += point->write(c);

        return str;
    }

    std::string Pencil::overwrite(std::string_view oldText, std::string_view newText)
    {
        std::string str;

        for (std::size_t i = 0; i < newText.size(); ++i)
            str += point->overwrite(oldText[i], newText[i]);

        return str;
    }

    std::string Pencil::buildEraseString(std::string_view text)
    {
        std::string str;

        for (auto i = text.rbegin(); i != text.rend(); ++i)
            str = eraser.erase(*i) + str;

        return str;
    }

    DurablePoint* Pencil::newPoint()
    {
        return points.empty() ? new DurablePoint{ 0 } : &points.back();
    }
}
