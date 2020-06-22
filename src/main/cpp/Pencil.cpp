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

    void Pencil::attachRequired(std::string& mediumRef)
    {
        medium = &mediumRef;
    }

    void Pencil::writeAppend(std::string_view text)
    {
        if (!medium)
            return;

        *medium += write(text);
    }

    void Pencil::writeFill(std::string_view text)
    {
        if (!medium)
            return;

        const std::string doubleSpace{ "  " };
        auto pos = medium->find(doubleSpace);

        if (isNotFound(pos))
            return;

        std::string padText = isBeginMedium(pos) ? std::string{ text } : ' ' + std::string{ text };
        std::string context = medium->substr(pos, padText.size());
        medium->replace(pos, padText.size(), overwrite(context, padText));
    }

    void Pencil::erase(std::string_view text)
    {
        if (!medium)
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
