#include "Writer.h"

namespace PencilDurability {
    void Writer::writeAppend(std::string_view text)
    {
        medium += pencil.buildAppendString(text);
    }
}
