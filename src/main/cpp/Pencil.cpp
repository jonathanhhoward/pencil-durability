/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "Pencil.h"

namespace PencilDurability {
    Pencil::Pencil(int pointDurability, std::size_t length, int eraserDurability)
            :points(length, DurablePoint{ pointDurability }),
             eraser{ eraserDurability }
    {
        if (points.empty())
            points.emplace_back(DurablePoint{ 0 });
        point = &points.back();
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

    std::string Pencil::erase(std::string_view text)
    {
        std::string str;

        for (auto i = text.rbegin(); i != text.rend(); ++i)
            str = eraser.erase(*i) + str;

        return str;
    }

    void Pencil::sharpen()
    {
        if (points.size() == 1)
            return;

        points.pop_back();
        point = &points.back();
    }
}
