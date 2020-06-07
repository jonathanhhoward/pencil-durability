/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "Pencil.h"

namespace PencilDurability {
    Pencil::Pencil(int pointDurability, std::size_t length, int eraserDurability)
            :points{ length, DurablePoint{ pointDurability }},
             eraser{ eraserDurability },
             medium{ nullptr }
    {
    }

    void Pencil::attach(std::string& mediumRef)
    {
        medium = &mediumRef;
    }

    void Pencil::writeAppend(std::string_view text)
    {
        if (isMediumNotAttached())
            return;

        *medium += buildAppendString(text);
    }

    void Pencil::writeFill(std::string_view text)
    {
        if (isMediumNotAttached())
            return;

        const std::string doubleSpace{ "  " };
        auto pos = medium->find(doubleSpace);

        if (isNotFound(pos))
            return;

        auto off = isBeginMedium(pos) ? 0 : 1;
        medium->replace(pos + off, text.size(), buildFillString(text, pos + off));
    }

    void Pencil::erase(std::string_view text)
    {
        if (isMediumNotAttached())
            return;

        auto pos = medium->rfind(text);

        if (isNotFound(pos))
            return;

        medium->replace(pos, text.size(), buildEraseString(text));
    }

    void Pencil::sharpen()
    {
        if (points.empty())
            return;

        points.pop_back();
    }

    bool Pencil::isMediumNotAttached()
    {
        return !medium;
    }

    std::string Pencil::buildAppendString(std::string_view text)
    {
        std::string str;
        const char space = ' ';

        for (char c : text)
            str += points.empty() ? space : points.back().write(c);

        return str;
    }

    std::string Pencil::buildFillString(std::string_view text, std::size_t off)
    {
        std::string str;

        for (std::size_t i = 0; i < text.size(); ++i) {
            const char current = medium->at(off + i);
            str += points.empty() ? current : points.back().overwrite(current, text[i]);
        }

        return str;
    }

    std::string Pencil::buildEraseString(std::string_view text)
    {
        std::string str;

        for (auto i = text.rbegin(); i != text.rend(); ++i)
            pushFront(str, eraser.erase(*i));

        return str;
    }
}
