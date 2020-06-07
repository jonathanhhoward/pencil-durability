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
        setPoint();
    }

    Pencil::~Pencil()
    {
        if (points.empty())
            delete point;
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
        setPoint();
    }

    bool Pencil::isMediumNotAttached()
    {
        return !medium;
    }

    std::string Pencil::buildAppendString(std::string_view text)
    {
        std::string str;

        for (char c : text)
            str += point->write(c);

        return str;
    }

    std::string Pencil::buildFillString(std::string_view text, std::size_t off)
    {
        std::string str;

        for (std::size_t i = 0; i < text.size(); ++i)
            str += point->overwrite(medium->at(i + off), text[i]);

        return str;
    }

    std::string Pencil::buildEraseString(std::string_view text)
    {
        std::string str;

        for (auto i = text.rbegin(); i != text.rend(); ++i)
            str = eraser.erase(*i) + str;

        return str;
    }

    void Pencil::setPoint()
    {
        point = points.empty() ? new DurablePoint{ 0 } : &points.back();
    }
}
