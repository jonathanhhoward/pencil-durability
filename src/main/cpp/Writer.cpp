#include "Writer.h"

namespace PencilDurability {
    void Writer::writeAppend(std::string_view text)
    {
        medium += pencil.buildAppendString(text);
    }

    void Writer::writeFill(std::string_view text)
    {
        const std::string doubleSpace{ "  " };
        auto pos = medium.find(doubleSpace);

        if (isNotFound(pos))
            return;

        std::string padText = isBeginMedium(pos) ? std::string{ text } : ' ' + std::string{ text };
        std::string context = medium.substr(pos, padText.size());
        medium.replace(pos, padText.size(), pencil.buildFillString(context, padText));
    }
}
