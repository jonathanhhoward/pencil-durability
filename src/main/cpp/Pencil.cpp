/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "Pencil.h"

namespace PencilDurability {
    Pencil::Pencil(int pointDurability, std::size_t length, int eraserDurability)
            :points{ length, DurablePoint{ pointDurability }},
             point{ nullptr },
             eraser{ eraserDurability },
             medium{ nullptr }
    {
        point = setPoint();
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

        *medium += buildAppendString(text);
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
        medium->replace(pos, padText.size(), buildFillString(context, padText));
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
        point = setPoint();
    }

    std::string Pencil::buildAppendString(std::string_view text)
    {
        std::string str;

        for (char c : text)
            str += point->write(c);

        return str;
    }

    std::string Pencil::buildFillString(std::string_view context, std::string_view text)
    {
        std::string str;

        for (std::size_t i = 0; i < text.size(); ++i)
            str += point->overwrite(context[i], text[i]);

        return str;
    }

    std::string Pencil::buildEraseString(std::string_view text)
    {
        std::string str;

        for (auto i = text.rbegin(); i != text.rend(); ++i)
            str = eraser.erase(*i) + str;

        return str;
    }

    DurablePoint* Pencil::setPoint()
    {
        return points.empty() ? new DurablePoint{ 0 } : &points.back();
    }
}
