#ifndef PENCIL_DURABILITY_POINT_H
#define PENCIL_DURABILITY_POINT_H

namespace PencilDurability {
    class Point {
    public:
        explicit Point(int initDurability);

        char writeAndDegrade(char charToWrite);

        int durability;

    private:
        bool isDull() const;
        void degrade(char c);
    };
}

#endif //PENCIL_DURABILITY_POINT_H
