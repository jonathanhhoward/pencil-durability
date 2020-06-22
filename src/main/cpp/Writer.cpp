#include "Writer.h"

namespace PencilDurability {
    Writer::Writer(std::string& mediumRef, Pencil& pencilRef)
            :medium{ &mediumRef },
             pencil{ pencilRef }
    {
    }

    void Writer::writeAppend(std::string_view text)
    {
        *medium += pencil.write(text);
    }

    void Writer::writeFill(std::string_view text)
    {
        const std::string doubleSpace{ "  " };
        auto pos = medium->find(doubleSpace);

        if (isNotFound(pos))
            return;

        std::string padText = isBeginMedium(pos) ? std::string{ text } : ' ' + std::string{ text };
        std::string context = medium->substr(pos, padText.size());
        medium->replace(pos, padText.size(), pencil.overwrite(context, padText));
    }

    void Writer::erase(std::string_view text)
    {
        auto pos = medium->rfind(text);

        if (isNotFound(pos))
            return;

        medium->replace(pos, text.size(), pencil.erase(text));
    }

    void Writer::changeMedium(std::string& mediumRef)
    {
        medium = &mediumRef;
    }
}
