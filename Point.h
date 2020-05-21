#ifndef PENCIL_DURABILITY_POINT_H
#define PENCIL_DURABILITY_POINT_H

namespace PencilDurability {
    class Point {
    public:
        explicit Point(int initDurability);

        bool isRemaining() const;
        void degrade();

        int durability;
    };
}

#endif //PENCIL_DURABILITY_POINT_H
