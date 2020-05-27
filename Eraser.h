#ifndef PENCIL_DURABILITY_ERASER_H
#define PENCIL_DURABILITY_ERASER_H

#include <string>

namespace PencilDurability {
    class Eraser {
    public:
        explicit Eraser(int durability);
        char erase(char character);

    private:
        int durability;
    };
}

#endif //PENCIL_DURABILITY_ERASER_H
