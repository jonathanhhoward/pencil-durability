/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "Pencil.h"

namespace PencilDurability {
    Pencil::Pencil(int point, std::size_t length, int eraser)
            :points{ length, Point{ point }},
             eraser{ eraser },
             medium{ nullptr }
    {
    }

    void Pencil::attach(std::string& mediumRef)
    {
        medium = &mediumRef;
    }

    void Pencil::write(std::string_view text)
    {
        checkMediumExists();

        *medium += buildWriteString(text);
    }

    void Pencil::erase(std::string_view text)
    {
        checkMediumExists();

        auto pos = medium->rfind(text);

        if (isNotFound(pos)) return;

        medium->replace(pos, text.size(), buildEraseString(text));
    }

    void Pencil::fillErased(std::string_view text)
    {
        checkMediumExists();

        const std::string doubleSpace{ "  " };
        auto pos = medium->find(doubleSpace);

        if (isNotFound(pos)) return;

        auto off = isStartOfPaper(pos) ? 0 : 1;
        medium->replace(pos + off, text.size(), buildOverwriteString(text, pos + off));
    }

    void Pencil::sharpen()
    {
        if (points.empty()) return;

        points.pop_back();
    }

    void Pencil::checkMediumExists()
    {
        if (!medium) throw std::runtime_error{ "invalid reference to medium" };
    }

    std::string Pencil::buildWriteString(std::string_view text)
    {
        std::string str;
        const char space = ' ';

        for (char c : text)
            str += points.empty() ? space : point().write(c);

        return str;
    }

    std::string Pencil::buildEraseString(std::string_view text)
    {
        std::string str;
        const std::size_t front = 0;

        for (auto i = text.rbegin(); i != text.rend(); ++i)
            str.insert(front, std::string{ eraser.erase(*i) });

        return str;
    }

    std::string Pencil::buildOverwriteString(std::string_view text, std::size_t off)
    {
        std::string str;

        for (std::size_t i = 0; i < text.size(); ++i) {
            const char current = medium->at(off + i);
            str += points.empty() ? current : point().overwrite(current, text[i]);
        }

        return str;
    }

    Point& Pencil::point()
    {
        return points.back();
    }
}
