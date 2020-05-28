#include "catch.hpp"
#include <string>
#include "Pencil.h"

using namespace PencilDurability;

SCENARIO("pencils are made independent of paper")
{
    GIVEN("a pencil and no paper") {
        Pencil pencil;

        WHEN("the pencil is used without paper") {
            THEN("the pencil throws an exception") {
                REQUIRE_THROWS_WITH(pencil.write("text"), "invalid reference to paper");
                REQUIRE_THROWS_WITH(pencil.erase("text"), "invalid reference to paper");
                REQUIRE_THROWS_WITH(pencil.insert("text"), "invalid reference to paper");
            }
        }
    }
}

SCENARIO("pencils can write text to paper")
{
    GIVEN("a pencil and paper") {
        Pencil pencil;
        std::string paper;
        pencil.attach(paper);

        WHEN("the pencil writes text") {
            pencil.write("She sells sea shells");

            THEN("the paper reflects the text that was written") {
                CHECK(paper == "She sells sea shells");

                AND_WHEN("additional text is written") {
                    pencil.write(" down by the sea shore");

                    THEN("the text is appended to existing text on the paper") {
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
            pencil.erase("chuck");

            THEN("the last occurrence of the text is replaced with blank spaces") {
                CHECK(paper == "How much wood would a woodchuck chuck if a woodchuck could       wood?");

                AND_WHEN("when the text matches a substring") {
                    pencil.erase("chuck");

                    THEN("the substring is replaced with blank spaces") {
                        CHECK(paper == "How much wood would a woodchuck chuck if a wood      could       wood?");
                    }
                }
            }
        }

        WHEN("the text is not found") {
            pencil.erase("duck");

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
        std::string paper{ "An       a day       the doctor away" };
        pencil.attach(paper);

        WHEN("the pencil writes to empty space") {
            pencil.insert("onion");

            THEN("the first empty space is filled in with a single space before the insertion") {
                CHECK(paper == "An onion a day       the doctor away");
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
            pencil.write("text");

            THEN("it only writes spaces") {
                CHECK(paper == "    ");
            }
        }
    }

    GIVEN("a pencil point with durability remaining") {
        Pencil pencil{ 4 };
        std::string paper;
        pencil.attach(paper);

        WHEN("the pencil writes a lowercase letter") {
            pencil.write("texts");

            THEN("the point durability degrades by one") {
                CHECK(paper == "text ");
            }
        }

        WHEN("the pencil writes an uppercase letter") {
            pencil.write("Text");

            THEN("the point durability degrades by two") {
                CHECK(paper == "Tex ");
            }
        }

        WHEN("the remaining point durability is one") {
            pencil.write("tex Mex");

            THEN("an uppercase letter may still be written") {
                CHECK(paper == "tex M  ");
            }
        }

        WHEN("the pencil writes whitespace") {
            pencil.write("te \nxt");

            THEN("the point does not degrade") {
                CHECK(paper == "te \nxt");
            }
        }
    }
}

SCENARIO("a pencil can be sharpened")
{
    GIVEN("a pencil with no length remaining") {
        Pencil pencil{ 100, 0 };
        std::string paper;
        pencil.attach(paper);

        WHEN("the pencil is instructed to sharpen") {
            pencil.sharpen();
            pencil.write("text");

            THEN("it does not sharpen") {
                CHECK(paper == "    ");
            }
        }
    }

    GIVEN("a pencil with point durability and length") {
        Pencil pencil{ 4, 2 };
        std::string paper;
        pencil.attach(paper);

        WHEN("a dull pencil is sharpened") {
            pencil.write("Text");

            CHECK(paper == "Tex ");

            pencil.sharpen();
            pencil.write("Text");

            THEN("its point durability is restored and the length is shortened by one") {
                CHECK(paper == "Tex Tex ");

                AND_WHEN("no length remains") {
                    pencil.sharpen();
                    pencil.write("Text");

                    THEN("the pencil writes spaces") {
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
            pencil.erase("text");

            THEN("it will not erase") {
                CHECK(paper == "text");
            }
        }
    }

    GIVEN("a pencil eraser with durability remaining") {
        Pencil pencil{ 100, 100, 5 };
        std::string paper{ "Buffalo Bill" };
        pencil.attach(paper);

        WHEN("the eraser is used") {
            pencil.erase("Buffalo Bill");

            THEN("it removes characters in reverse order one durability point each not counting spaces") {
                CHECK(paper == "Buffal      ");
            }
        }
    }
}
