#ifndef PENCIL_DURABILITY_POINT_H
#define PENCIL_DURABILITY_POINT_H

namespace PencilDurability {
    class Point {
    public:
        explicit Point(int durability);
        char extract(char character);

    private:
        bool isDull() const;
        void degradeUsing(char character);
        int durability;
    };
}

#endif //PENCIL_DURABILITY_POINT_H
