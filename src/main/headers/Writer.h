#ifndef PENCIL_DURABILITY_WRITER_H
#define PENCIL_DURABILITY_WRITER_H

#include "Pencil.h"

namespace PencilDurability {
    class Writer {
    public:
        Writer(std::string& mediumRef, Pencil& pencilRef);
        void writeAppend(std::string_view text);
        void writeFill(std::string_view text);
        void erase(std::string_view text);
        void changeMedium(std::string& mediumRef);
    private:
        std::string* medium;
        Pencil& pencil;
    };
}

#endif //PENCIL_DURABILITY_WRITER_H
