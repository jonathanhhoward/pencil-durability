/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "Writer.h"

namespace PencilDurability {
    Writer::Writer(std::string& mediumRef, Pencil& pencilRef)
            :medium{ &mediumRef },
             pencil{ &pencilRef }
    {
    }

    void Writer::appendMedium(std::string_view text)
    {
        *medium += pencil->write(text);
    }

    void Writer::fillMedium(std::string_view text)
    {
        const std::string doubleSpace{ "  " };
        auto pos = medium->find(doubleSpace);

        if (isNotFound(pos))
            return;

        std::string padText = isBeginMedium(pos) ? std::string{ text } : ' ' + std::string{ text };
        std::string context = medium->substr(pos, padText.size());
        medium->replace(pos, padText.size(), pencil->overwrite(context, padText));
    }

    void Writer::eraseMedium(std::string_view text)
    {
        auto pos = medium->rfind(text);

        if (isNotFound(pos))
            return;

        medium->replace(pos, text.size(), pencil->erase(text));
    }

    void Writer::reassignMedium(std::string& mediumRef)
    {
        medium = &mediumRef;
    }

    void Writer::reassignPencil(Pencil& pencilRef)
    {
        pencil = &pencilRef;
    }
}
