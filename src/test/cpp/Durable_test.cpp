#include "catch.hpp"
#include "Durable.h"

using namespace PencilDurability;

TEST_CASE("a point writes a character")
{
    DurablePoint point{ 10 };

    SECTION("it should return the character it is passed") {
        REQUIRE(point.write('x') == 'x');
    }
}

TEST_CASE("a point overwrites with a character")
{
    DurablePoint point{ 10 };

    SECTION("it should replace whitespace with a character") {
        REQUIRE(point.overwrite(' ', 'x') == 'x');
        REQUIRE(point.overwrite('\n', 'x') == 'x');
    }

    SECTION("it should not replace a character with whitespace") {
        REQUIRE(point.overwrite('x', ' ') == 'x');
        REQUIRE(point.overwrite('x', '\n') == 'x');
    }

    SECTION("it should not replace different whitespace") {
        REQUIRE(point.overwrite(' ', '\n') == ' ');
        REQUIRE(point.overwrite('\n', ' ') == '\n');
    }

    SECTION("it should replace different characters with @") {
        REQUIRE(point.overwrite('a', 'b') == '@');
    }
}

TEST_CASE("a point with durability of 0")
{
    DurablePoint point{ 0 };

    SECTION("it should write spaces") {
        REQUIRE(point.write('x') == ' ');
    }

    SECTION("it should not overwrite") {
        REQUIRE(point.overwrite('x', 'y') == 'x');
    }
}

TEST_CASE("a point with durability of 1")
{
    DurablePoint point1{ 1 };
    DurablePoint point2{ 1 };

    SECTION("it should write one letter then spaces") {
        REQUIRE(point1.write('a') == 'a');
        REQUIRE(point1.write('a') == ' ');
        REQUIRE(point2.write('A') == 'A');
        REQUIRE(point2.write('A') == ' ');
    }

    SECTION("it should overwrite with one letter then not overwrite") {
        REQUIRE(point1.overwrite(' ', 'a') == 'a');
        REQUIRE(point1.overwrite(' ', 'a') == ' ');
        REQUIRE(point2.overwrite(' ', 'A') == 'A');
        REQUIRE(point2.overwrite(' ', 'A') == ' ');
    }

    SECTION("it should overwrite with another letter and then not overwrite") {
        REQUIRE(point1.overwrite('a', 'b') == '@');
        REQUIRE(point1.overwrite('a', 'b') == 'a');
        REQUIRE(point2.overwrite('A', 'B') == '@');
        REQUIRE(point2.overwrite('A', 'B') == 'A');
    }

    SECTION("it should not degrade by writing whitespace") {
        REQUIRE(point1.write(' ') == ' ');
        REQUIRE(point1.write('\n') == '\n');
        REQUIRE(point1.write('x') == 'x');
        REQUIRE(point1.write('x') == ' ');
    }

    SECTION("it should not degrade by overwriting with whitespace") {
        REQUIRE(point1.overwrite(' ', ' ') == ' ');
        REQUIRE(point1.overwrite(' ', '\n') == ' ');
        REQUIRE(point1.overwrite('\n', ' ') == '\n');
        REQUIRE(point1.overwrite('\n', '\n') == '\n');
        REQUIRE(point1.overwrite('x', ' ') == 'x');
        REQUIRE(point1.overwrite('x', '\n') == 'x');
        REQUIRE(point1.overwrite(' ', 'x') == 'x');
        REQUIRE(point1.overwrite(' ', 'x') == ' ');
    }
}

TEST_CASE("a point with durability of 2")
{
    DurablePoint point{ 2 };

    SECTION("it should write 2 lowercase then spaces") {
        REQUIRE(point.write('a') == 'a');
        REQUIRE(point.write('a') == 'a');
        REQUIRE(point.write('a') == ' ');
    }

    SECTION("it should write 1 uppercase then spaces") {
        REQUIRE(point.write('A') == 'A');
        REQUIRE(point.write('A') == ' ');
    }

    SECTION("it should overwrite with 2 lowercase then not overwrite") {
        REQUIRE(point.overwrite(' ', 'a') == 'a');
        REQUIRE(point.overwrite(' ', 'a') == 'a');
        REQUIRE(point.overwrite(' ', 'a') == ' ');
    }

    SECTION("it should overwrite with 1 uppercase then not overwrite") {
        REQUIRE(point.overwrite(' ', 'A') == 'A');
        REQUIRE(point.overwrite(' ', 'A') == ' ');
    }
}

TEST_CASE("an eraser should turn non-space into space")
{
    DurableEraser eraser{ 10 };

    REQUIRE(eraser.erase('x') == ' ');
    REQUIRE(eraser.erase('\n') == ' ');
}

TEST_CASE("an eraser with durability of 0")
{
    DurableEraser eraser{ 0 };

    SECTION("it should not turn non-space into space") {
        REQUIRE(eraser.erase('x') == 'x');
        REQUIRE(eraser.erase('\n') == '\n');
    }
}

TEST_CASE("an eraser with durability of 1")
{
    DurableEraser eraser{ 1 };

    SECTION("it should turn one character into space") {
        REQUIRE(eraser.erase('x') == ' ');
        REQUIRE(eraser.erase('x') == 'x');
    }

    SECTION("it should not degrade by erasing whitespace") {
        REQUIRE(eraser.erase(' ') == ' ');
        REQUIRE(eraser.erase('\n') == ' ');
        REQUIRE(eraser.erase('x') == ' ');
        REQUIRE(eraser.erase('x') == 'x');
    }
}
