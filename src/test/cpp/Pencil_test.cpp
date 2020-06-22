/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "catch.hpp"

#include <string>
#include "Pencil.h"

using namespace PencilDurability;

TEST_CASE("a pencil writes a string")
{
    Pencil pencil;

    SECTION("it should return the string it receives") {
        REQUIRE(pencil.write("text") == "text");
    }
}

TEST_CASE("a pencil overwrites with a string")
{
    Pencil pencil;

    SECTION("it should replace characters in a string according to DurablePoint") {
        REQUIRE(pencil.overwrite("texting    ", "tex mex\nmix") == "@@@t@@@ mix");
    }
}

TEST_CASE("the pencil point degrades with use")
{
    Pencil pencil1{ 4 };
    Pencil pencil2{ 4 };

    SECTION("it should write from the left until it goes dull") {
        REQUIRE(pencil1.write("Text") == "Tex ");
        REQUIRE(pencil2.overwrite("    ", "Text") == "Tex ");
    }
}

TEST_CASE("a pencil can be sharpened")
{
    SECTION("constructing a pencil with length 0") {
        Pencil pencil{ 100, 0 };

        SECTION("it should only write spaces") {
            REQUIRE(pencil.write("text") == "    ");
        }

        SECTION("it should not overwrite") {
            REQUIRE(pencil.overwrite("    ", "text") == "    ");
        }
    }

    SECTION("a dull pencil with length 2") {
        Pencil pencil{ 4, 2 };

        REQUIRE(pencil.write("Text") == "Tex ");

        SECTION("sharpening it should restore the point durability and shorten the length to 1") {
            pencil.sharpen();
            REQUIRE(pencil.write("Text") == "Tex ");

            SECTION("it should not sharpen again") {
                pencil.sharpen();
                REQUIRE(pencil.write("text") == "    ");
            }
        }
    }
}

TEST_CASE("the pencil eraser degrades with use")
{
    Pencil pencil{ 100, 100, 5 };

    SECTION("it should remove characters in reverse order one durability point each not counting spaces") {
        REQUIRE(pencil.erase("Buffalo Bill") == "Buffal      ");
    }
}
