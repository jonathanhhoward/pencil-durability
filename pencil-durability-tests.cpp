#include "catch.hpp"
#include <string>
#include "Pencil.h"

using namespace PencilDurability;

SCENARIO("pencils can write text to paper")
{
    GIVEN("a pencil and paper") {
        Pencil pencil;
        std::string paper;
        pencil.attach(paper);

        WHEN("the pencil writes text") {
            THEN("the paper reflects the text that was written") {
                pencil.write("She sells sea shells");

                CHECK(paper == "She sells sea shells");

                AND_WHEN("additional text is written") {
                    THEN("the text is appended to existing text on the paper") {
                        pencil.write(" down by the sea shore");

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
        pencil.attach(paper);

        WHEN("a pencil erases text from the paper") {
            THEN("the last occurrence of the text is replaced with blank spaces") {
                pencil.erase("chuck");

                CHECK(paper == "How much wood would a woodchuck chuck if a woodchuck could       wood?");

                AND_WHEN("when the text matches a substring") {
                    THEN("the substring is replaced with blank spaces") {
                        pencil.erase("chuck");

                        CHECK(paper == "How much wood would a woodchuck chuck if a wood      could       wood?");
                    }
                }
            }
        }

        WHEN("the text is not found") {
            THEN("the paper is not changed") {
                pencil.erase("duck");

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
        pencil.attach(paper);

        WHEN("the pencil writes to empty space") {
            THEN("the empty space is filled in with the new text") {
                pencil.insert("onion");

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
        pencil.attach(paper);

        WHEN("the pencil writes with a dull point") {
            THEN("it only writes spaces") {
                pencil.write("text");

                CHECK(paper == "    ");
            }
        }
    }

    GIVEN("a pencil point with durability remaining") {
        Pencil pencil{ 4 };
        std::string paper;
        pencil.attach(paper);

        WHEN("the pencil writes a lowercase letter") {
            THEN("the point durability degrades by one") {
                pencil.write("texts");

                CHECK(paper == "text ");
            }
        }

        WHEN("the pencil writes an uppercase letter") {
            THEN("the point durability degrades by two") {
                pencil.write("Text");

                CHECK(paper == "Tex ");
            }
        }

        WHEN("the remaining point durability is one") {
            THEN("an uppercase letter may still be written") {
                pencil.write("tex Mex");

                CHECK(paper == "tex M  ");
            }
        }

        WHEN("the pencil writes whitespace") {
            THEN("the point does not degrade") {
                pencil.write("te \nxt");

                CHECK(paper == "te \nxt");
            }
        }
    }
}

SCENARIO("a pencil can be sharpened")
{
    GIVEN("a pencil with point durability and length") {
        Pencil pencil(4, 2);
        std::string paper;
        pencil.attach(paper);

        WHEN("a dull pencil is sharpened") {
            THEN("its point durability is restored and the length is shortened by one") {
                pencil.write("Text");

                CHECK(paper == "Tex ");

                pencil.sharpen();
                pencil.write("Text");

                CHECK(paper == "Tex Tex ");

                AND_WHEN("no length remains") {
                    THEN("the pencil cannot be sharpened") {
                        pencil.sharpen();
                        pencil.write("Text");

                        CHECK(paper == "Tex Tex     ");
                    }
                }
            }
        }
    }
}

SCENARIO("the pencil eraser degrades with use")
{
    GIVEN("a pencil eraser with no durability remaining") {
        Pencil pencil{ 100, 100, 0 };
        std::string paper{ "text" };
        pencil.attach(paper);

        WHEN("the eraser is used") {
            THEN("it will not erase") {
                pencil.erase("text");

                CHECK(paper == "text");
            }
        }
    }
}
