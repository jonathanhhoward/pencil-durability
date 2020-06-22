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

SCENARIO("a pencil can be sharpened")
{
    GIVEN("a pencil with no length remaining") {
        Pencil pencil1{ 100, 0 };
        std::string paper1;
        pencil1.attachRequired(paper1);

        Pencil pencil2{ 100, 0 };
        std::string paper2{ "text      text" };
        pencil2.attachRequired(paper2);

        WHEN("the pencil is instructed to sharpen") {
            pencil1.sharpen();
            pencil1.writeAppend("text");

            pencil2.sharpen();
            pencil2.writeFill("text");

            THEN("it should not sharpen") {
                CHECK(paper1 == "    ");
                CHECK(paper2 == "text      text");
            }
        }
    }

    GIVEN("a pencil with point durability and length") {
        Pencil pencil1{ 4, 2 };
        std::string paper1;
        pencil1.attachRequired(paper1);

        Pencil pencil2{ 4, 2 };
        std::string paper2{ "Tex             Tex" };
        pencil2.attachRequired(paper2);

        WHEN("a dull pencil is sharpened") {
            pencil1.writeAppend("Text");
            CHECK(paper1 == "Tex ");
            pencil1.sharpen();
            pencil1.writeAppend("Text");

            pencil2.writeFill("Text");
            CHECK(paper2 == "Tex Tex         Tex");
            pencil2.sharpen();
            pencil2.writeFill("Text");

            THEN("it should restore the point durability and shorten the length by one") {
                CHECK(paper1 == "Tex Tex ");
                CHECK(paper2 == "Tex Tex Tex     Tex");

                AND_WHEN("no length remains") {
                    pencil1.sharpen();
                    pencil1.writeAppend("Texting");

                    pencil2.sharpen();
                    pencil2.writeFill("texting");

                    THEN("it should write spaces") {
                        CHECK(paper1 == "Tex Tex        ");
                    } AND_THEN("it should not change the paper") {
                        CHECK(paper2 == "Tex Tex Tex     Tex");
                    }
                }
            }
        }
    }
}

SCENARIO("the pencil eraser degrades with use")
{
    GIVEN("a pencil eraser with durability remaining") {
        Pencil pencil{ 100, 100, 5 };
        std::string paper{ "Buffalo Bill" };
        pencil.attachRequired(paper);

        WHEN("the eraser is used") {
            pencil.erase("Buffalo Bill");

            THEN("it should remove characters in reverse order one durability point each not counting spaces") {
                CHECK(paper == "Buffal      ");
            }
        }
    }
}
