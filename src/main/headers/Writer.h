/**
 * (C) Copyright 2020, by Jonathan Howard
 *
 * This is my original solution to the Pencil Durability Kata for Pillar Technology
 * which describes a Pencil that has durability that degrades with use.
 *
 * https://github.com/PillarTechnology/kata-pencil-durability
 */

#ifndef PENCIL_DURABILITY_WRITER_H
#define PENCIL_DURABILITY_WRITER_H

#include "Pencil.h"

namespace PencilDurability {
    class Writer {
    public:
        Writer(std::string& mediumRef, Pencil& pencilRef);
        void appendMedium(std::string_view text);
        void fillMedium(std::string_view text);
        void eraseMedium(std::string_view text);
        void reassignMedium(std::string& mediumRef);
        void reassignPencil(Pencil& pencilRef);
    private:
        std::string* medium;
        Pencil* pencil;
    };
}

#endif //PENCIL_DURABILITY_WRITER_H
