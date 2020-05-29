#include "Pencil.h"

namespace PencilDurability {
    Pencil::Pencil(int point, std::size_t length, int eraser)
            :points{ length, Point{ point }},
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
        checkPaper();

        *paper += buildWriteString(text);
    }

    void Pencil::erase(std::string_view text)
    {
        checkPaper();

        auto pos = paper->rfind(text);

        if (isTextNotFound(pos)) return;

        paper->replace(pos, text.size(), buildEraseString(text));
    }

    void Pencil::insert(std::string_view text)
    {
        checkPaper();

        const std::string doubleSpace{ "  " };

        auto pos = paper->find(doubleSpace);

        if (isTextNotFound(pos)) return;

        auto off = isStartOfPaper(pos) ? 0 : 1;

        paper->replace(pos + off, text.size(), buildInsertString(text, pos + off));
    }

    void Pencil::sharpen()
    {
        if (points.empty()) return;

        points.pop_back();
    }

    void Pencil::checkPaper()
    {
        if (!paper) throw std::runtime_error{ "invalid reference to paper" };
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

    std::string Pencil::buildInsertString(std::string_view text, std::size_t off)
    {
        std::string str;
        const char overwrite = '@';

        for (std::size_t i = 0; i < text.size(); ++i)
            str += isSpace(paper->at(off + i)) ? text[i] : overwrite;

        return str;
    }

    Point& Pencil::point()
    {
        return points.back();
    }
}
