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

        WHEN("the text is not found") {
            pencil.eraseTextFromPaper("duck", paper);

            THEN("the paper is not changed") {
                CHECK(paper == "How much wood would a woodchuck chuck if a woodchuck could chuck wood?");
            }
        }
    }
}

SCENARIO("pencils can insert text to paper")
{
    GIVEN("a pencil and paper with erasures") {
        Pencil pencil;
        std::string paper{ "An       a day keeps the doctor away" };

        WHEN("the pencil writes to empty space") {
            pencil.insertTextToPaper("onion", paper);

            THEN("the empty space is filled in with the new text") {
                CHECK(paper == "An onion a day keeps the doctor away");
            }
        }
    }
}

SCENARIO("pencil points degrade with use")
{
    GIVEN("a pencil point with no durability remaining") {
        Pencil pencil{ 0 };
        std::string paper;

        WHEN("the pencil writes with a dull point") {
            pencil.writeTextToPaper("text", paper);

            THEN("it only writes spaces") {
                CHECK(paper == "    ");
            }
        }
    }

    GIVEN("a pencil point with durability remaining") {
        Pencil pencil{ 4 };
        std::string paper;

        WHEN("the pencil writes a lowercase letter") {
            pencil.writeTextToPaper("texts", paper);

            THEN("the point durability degrades by one") {
                CHECK(paper == "text ");
            }
        }

        WHEN("the pencil writes an uppercase letter") {
            pencil.writeTextToPaper("Text", paper);

            THEN("the point durability degrades by two") {
                CHECK(paper == "Tex ");
            }
        }

        WHEN("the remaining point durability is one") {
            pencil.writeTextToPaper("tex Mex", paper);

            THEN("an uppercase letter may still be written") {
                CHECK(paper == "tex M  ");
            }
        }

        WHEN("the pencil writes whitespace") {
            pencil.writeTextToPaper("te \nxt", paper);

            THEN("the point does not degrade") {
                CHECK(paper == "te \nxt");
            }
        }
    }
}
