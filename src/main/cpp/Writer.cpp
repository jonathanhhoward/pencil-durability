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

    void Writer::appendToMedium(std::string_view text)
    {
        *medium += pencil->write(text);
    }

    void Writer::fillInMedium(std::string_view text)
    {
        const std::string doubleSpace{ "  " };
        const auto pos = medium->find(doubleSpace);

        if (isNotFound(pos))
            return;

        std::string newText = padText(pos, std::string{ text });
        std::string oldText = medium->substr(pos, newText.size());
        medium->replace(pos, newText.size(), pencil->overwrite(oldText, newText));
    }

    void Writer::eraseFromMedium(std::string_view text)
    {
        const auto pos = medium->rfind(text);

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
