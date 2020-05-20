#include "catch.hpp"
#include <string>
#include "Pencil.h"

using namespace PencilDurability;

SCENARIO("pencils can write text to paper")
{
    GIVEN("a pencil and paper") {
        Pencil pencil;
        std::string paper;

        WHEN("the pencil writes text") {
            pencil.writeTextToPaper("She sells sea shells", paper);

            THEN("the paper reflects the text that was written") {
                CHECK(paper == "She sells sea shells");
            }

            WHEN("additional text is written") {
                pencil.writeTextToPaper(" down by the sea shore", paper);

                THEN("the text is appended to existing text on the paper") {
                    CHECK(paper == "She sells sea shells down by the sea shore");
                }
            }
        }
    }
}

SCENARIO("pencils can erase text from paper")
{
    GIVEN("a pencil and paper with text") {
        Pencil pencil;
        std::string paper{ "How much wood would a woodchuck chuck if a woodchuck could chuck wood?" };

        WHEN("a pencil erases text from the paper") {
            pencil.eraseTextFromPaper("chuck", paper);

            THEN("the last occurrence of the text is replaced with blank spaces") {
                CHECK(paper == "How much wood would a woodchuck chuck if a woodchuck could       wood?");
            }

            WHEN("when the text matches a substring") {
                pencil.eraseTextFromPaper("chuck", paper);

                THEN("the substring is replaced with blank spaces") {
                    CHECK(paper == "How much wood would a woodchuck chuck if a wood      could       wood?");
                }
            }
        }
    }
}
