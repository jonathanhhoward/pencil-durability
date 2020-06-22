#ifndef PENCIL_DURABILITY_WRITER_H
#define PENCIL_DURABILITY_WRITER_H

#include "Pencil.h"

namespace PencilDurability {
    struct Writer {
        void writeAppend(std::string_view text);
        void writeFill(std::string_view text);
        std::string& medium;
        Pencil& pencil;
    };
}

#endif //PENCIL_DURABILITY_WRITER_H
