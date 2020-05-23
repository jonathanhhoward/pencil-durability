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
            THEN("the paper reflects the text that was written") {
                pencil.writeTextToPaper("She sells sea shells", paper);

                CHECK(paper == "She sells sea shells");

                AND_WHEN("additional text is written") {
                    THEN("the text is appended to existing text on the paper") {
                        pencil.writeTextToPaper(" down by the sea shore", paper);

                        CHECK(paper == "She sells sea shells down by the sea shore");
                    }
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
            THEN("the last occurrence of the text is replaced with blank spaces") {
                pencil.eraseTextFromPaper("chuck", paper);

                CHECK(paper == "How much wood would a woodchuck chuck if a woodchuck could       wood?");

                AND_WHEN("when the text matches a substring") {
                    THEN("the substring is replaced with blank spaces") {
                        pencil.eraseTextFromPaper("chuck", paper);

                        CHECK(paper == "How much wood would a woodchuck chuck if a wood      could       wood?");
                    }
                }
            }
        }

        WHEN("the text is not found") {
            THEN("the paper is not changed") {
                pencil.eraseTextFromPaper("duck", paper);

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
            THEN("the empty space is filled in with the new text") {
                pencil.insertTextToPaper("onion", paper);

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
            THEN("it only writes spaces") {
                pencil.writeTextToPaper("text", paper);

                CHECK(paper == "    ");
            }
        }
    }

    GIVEN("a pencil point with durability remaining") {
        Pencil pencil{ 4 };
        std::string paper;

        WHEN("the pencil writes a lowercase letter") {
            THEN("the point durability degrades by one") {
                pencil.writeTextToPaper("texts", paper);

                CHECK(paper == "text ");
            }
        }

        WHEN("the pencil writes an uppercase letter") {
            THEN("the point durability degrades by two") {
                pencil.writeTextToPaper("Text", paper);

                CHECK(paper == "Tex ");
            }
        }

        WHEN("the remaining point durability is one") {
            THEN("an uppercase letter may still be written") {
                pencil.writeTextToPaper("tex Mex", paper);

                CHECK(paper == "tex M  ");
            }
        }

        WHEN("the pencil writes whitespace") {
            THEN("the point does not degrade") {
                pencil.writeTextToPaper("te \nxt", paper);

                CHECK(paper == "te \nxt");
            }
        }
    }
}

SCENARIO("a pencil can be sharpened")
{
    GIVEN("a pencil with point durability and length") {
        Pencil pencil(4, 1);
        std::string paper;

        WHEN("a dull pencil is sharpened") {
            THEN("its point durability is restored and the length is shortened by one") {
                pencil.writeTextToPaper("Text", paper);

                CHECK(paper == "Tex ");

                pencil.sharpen();
                pencil.writeTextToPaper("Text", paper);

                CHECK(paper == "Tex Tex ");

                AND_WHEN("no length remains") {
                    THEN("the pencil cannot be sharpened") {
                        pencil.sharpen();
                        pencil.writeTextToPaper("Text", paper);

                        CHECK(paper == "Tex Tex     ");
                    }
                }
            }
        }
    }
}
