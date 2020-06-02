/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "catch.hpp"
#include <string>
#include "Pencil.h"

using namespace PencilDurability;

SCENARIO("pencils are made independent of paper")
{
    GIVEN("a pencil and paper") {
        Pencil pencil;
        std::string paper;

        WHEN("the pencil writes without paper attached") {
            pencil.write("text");

            THEN("no text is appended") {
                CHECK(paper.empty());
            }
        }

        WHEN("the pencil erases without paper attached") {
            paper = "text";
            pencil.erase("text");

            THEN("no text is erased") {
                CHECK(paper == "text");
            }
        }

        WHEN("the pencil fills empty space without paper attached") {
            paper = "text      text";
            pencil.fillErased("text");

            THEN("the space is not filled") {
                CHECK(paper == "text      text");
            }
        }
    }

    GIVEN("a pencil and multiple papers") {
        Pencil pencil;
        std::string paper1;
        std::string paper2;

        WHEN("the pencil writes with different papers attached") {
            pencil.attach(paper1);
            pencil.write("text");

            pencil.attach(paper2);
            pencil.write("TEXT");

            THEN("the text will be reflected on the respective paper") {
                CHECK(paper1 == "text");
                CHECK(paper2 == "TEXT");
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

SCENARIO("pencils can fill the space where text was erased from paper")
{
    GIVEN("a pencil and paper with erasures") {
        Pencil pencil;
        std::string paper;
        pencil.attach(paper);

        WHEN("the pencil fills empty space") {
            paper = "An       a day       the doctor away";
            pencil.fillErased("onion");

            THEN("the first occurrence of empty space is filled in with a single space before the text") {
                CHECK(paper == "An onion a day       the doctor away");

                AND_WHEN("the pencil fills again") {
                    pencil.fillErased("onion");

                    THEN("the next empty space is filled in") {
                        CHECK(paper == "An onion a day onion the doctor away");
                    }
                }
            }
        }

        WHEN("the pencil fills at the start of the paper") {
            paper = "   apple a day keeps the doctor away";
            pencil.fillErased("An");

            THEN("there is no space before the text") {
                CHECK(paper == "An apple a day keeps the doctor away");
            }
        }

        WHEN("the text to fill is larger than the space") {
            paper = "An       a day keeps the doctor away";
            pencil.fillErased("artichoke");

            THEN("the space does not resize and overwritten characters will be replaced with '@'") {
                CHECK(paper == "An artich@k@ay keeps the doctor away");
            }
        }

        WHEN("there is no erasure") {
            paper = "An apple a day keeps the doctor away";
            pencil.fillErased("onion");

            THEN("the nothing gets filled") {
                CHECK(paper == "An apple a day keeps the doctor away");
            }
        }

        WHEN("overwriting with a space") {
            paper = "An apple   day keeps the doctor away";
            pencil.fillErased("An apple");

            THEN("text overwritten by the space is unchanged") {
                CHECK(paper == "An apple And@@p@@eps the doctor away");
            }
        }

        WHEN("overwriting with a newline") {
            paper = "   apple a day keeps the doctor away";
            pencil.fillErased("An\n\n");

            THEN("spaces become newline and text becomes '@'") {
                CHECK(paper == "An\n@pple a day keeps the doctor away");
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

        WHEN("the pencil fills with a dull point") {
            paper = "one     three";
            pencil.fillErased("twenty");

            THEN("the paper is not altered") {
                CHECK(paper == "one     three");
            }
        }
    }

    GIVEN("a pencil point with durability remaining") {
        Pencil pencil1{ 4 };
        std::string paper1;
        pencil1.attach(paper1);

        Pencil pencil2{ 4 };
        std::string paper2{ "text      text" };
        pencil2.attach(paper2);

        WHEN("the pencil writes a lowercase letter") {
            pencil1.write("texts");
            pencil2.fillErased("texts");

            THEN("the point durability degrades by one") {
                CHECK(paper1 == "text ");
                CHECK(paper2 == "text text text");
            }
        }

        WHEN("the pencil writes an uppercase letter") {
            pencil1.write("Text");
            pencil2.fillErased("Text");

            THEN("the point durability degrades by two") {
                CHECK(paper1 == "Tex ");
                CHECK(paper2 == "text Tex  text");
            }
        }

        WHEN("the remaining point durability is one") {
            pencil1.write("texMex");
            pencil2.fillErased("texMex");

            THEN("an uppercase letter may still be written") {
                CHECK(paper1 == "texM  ");
                CHECK(paper2 == "text texM text");
            }
        }

        WHEN("the pencil writes whitespace") {
            pencil1.write("te \nxt");
            pencil2.fillErased("te \nxt");

            THEN("the point does not degrade") {
                CHECK(paper1 == "te \nxt");
                CHECK(paper2 == "text te \nx@ext");
            }
        }
    }
}

SCENARIO("a pencil can be sharpened")
{
    GIVEN("a pencil with no length remaining") {
        Pencil pencil1{ 100, 0 };
        std::string paper1;
        pencil1.attach(paper1);

        Pencil pencil2{ 100, 0 };
        std::string paper2{ "text      text" };
        pencil2.attach(paper2);

        WHEN("the pencil is instructed to sharpen") {
            pencil1.sharpen();
            pencil1.write("text");

            pencil2.sharpen();
            pencil2.fillErased("text");

            THEN("it does not sharpen") {
                CHECK(paper1 == "    ");
                CHECK(paper2 == "text      text");
            }
        }
    }

    GIVEN("a pencil with point durability and length") {
        Pencil pencil1{ 4, 2 };
        std::string paper1;
        pencil1.attach(paper1);

        Pencil pencil2{ 4, 2 };
        std::string paper2{ "Tex             Tex" };
        pencil2.attach(paper2);

        WHEN("a dull pencil is sharpened") {
            pencil1.write("Text");
            CHECK(paper1 == "Tex ");
            pencil1.sharpen();
            pencil1.write("Text");

            pencil2.fillErased("Text");
            CHECK(paper2 == "Tex Tex         Tex");
            pencil2.sharpen();
            pencil2.fillErased("Text");

            THEN("its point durability is restored and the length is shortened by one") {
                CHECK(paper1 == "Tex Tex ");
                CHECK(paper2 == "Tex Tex Tex     Tex");

                AND_WHEN("no length remains") {
                    pencil1.sharpen();
                    pencil1.write("Texting");

                    pencil2.sharpen();
                    pencil2.fillErased("texting");

                    THEN("the pencil writes spaces") {
                        CHECK(paper1 == "Tex Tex        ");
                    } AND_THEN("the pencil does not fill or overwrite") {
                        CHECK(paper2 == "Tex Tex Tex     Tex");
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
