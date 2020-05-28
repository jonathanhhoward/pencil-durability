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

        *paper = "An onion a day keeps the doctor away";
    }

    void Pencil::sharpen()
    {
        if (points.size() == 1) return;

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
            str += point().extract(c);

        return str;
    }

    std::string Pencil::buildEraseString(std::string_view text)
    {
        std::string str;

        for (auto i = text.rbegin(); i != text.rend(); ++i)
            str.insert(0, std::string{ eraser.erase(*i) });

        return str;
    }

    Point& Pencil::point()
    {
        return points.back();
    }
}
