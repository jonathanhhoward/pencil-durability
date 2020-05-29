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

    bool isTextNotFound(std::size_t searchResult)
    {
        return searchResult == std::string::npos;
    }

    void Pencil::insert(std::string_view text)
    {
        checkPaper();

        auto pos = paper->find("  ");

        if (isTextNotFound(pos)) return;

        auto off = (pos == 0) ? pos : pos + 1;

        paper->replace(off, text.size(), buildInsertString(text, off));
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

        for (char c : text)
            str += points.empty() ? ' ' : point().extract(c);

        return str;
    }

    std::string Pencil::buildEraseString(std::string_view text)
    {
        std::string str;

        for (auto i = text.rbegin(); i != text.rend(); ++i)
            str.insert(0, std::string{ eraser.erase(*i) });

        return str;
    }

    std::string Pencil::buildInsertString(std::string_view text, std::size_t off)
    {
        std::string str;

        for (std::size_t i = 0; i < text.size(); ++i)
            str += (paper->at(off + i) == ' ') ? text[i] : '@';

        return str;
    }

    Point& Pencil::point()
    {
        return points.back();
    }
}
