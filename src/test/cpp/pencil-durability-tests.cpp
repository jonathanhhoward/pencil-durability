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
            pencil.writeAppend("text");

            THEN("it should not append text") {
                CHECK(paper.empty());
            }
        }

        WHEN("the pencil erases without paper attached") {
            paper = "text";
            pencil.erase("text");

            THEN("it should not erase text") {
                CHECK(paper == "text");
            }
        }

        WHEN("the pencil fills empty space without paper attached") {
            paper = "text      text";
            pencil.writeFill("text");

            THEN("it should not fill text") {
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
            pencil.writeAppend("text");

            pencil.attach(paper2);
            pencil.writeAppend("TEXT");

            THEN("it should write text on the respective paper") {
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
            pencil.writeAppend("She sells sea shells");

            THEN("it should write the text to the paper") {
                CHECK(paper == "She sells sea shells");

                AND_WHEN("additional text is written") {
                    pencil.writeAppend(" down by the sea shore");

                    THEN("it should append to existing text on the paper") {
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

            THEN("it should replace the last occurrence of the text with blank spaces") {
                CHECK(paper == "How much wood would a woodchuck chuck if a woodchuck could       wood?");

                AND_WHEN("when the text matches a substring") {
                    pencil.erase("chuck");

                    THEN("it should replace the substring blank spaces") {
                        CHECK(paper == "How much wood would a woodchuck chuck if a wood      could       wood?");
                    }
                }
            }
        }

        WHEN("the text is not found") {
            pencil.erase("duck");

            THEN("it should not change the paper") {
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
            pencil.writeFill("onion");

            THEN("it should fill the first occurrence of empty space with a single space before the text") {
                CHECK(paper == "An onion a day       the doctor away");

                AND_WHEN("the pencil fills again") {
                    pencil.writeFill("onion");

                    THEN("it should fill the next empty space") {
                        CHECK(paper == "An onion a day onion the doctor away");
                    }
                }
            }
        }

        WHEN("the pencil fills at the start of the paper") {
            paper = "   apple a day keeps the doctor away";
            pencil.writeFill("An");

            THEN("it should not put a space before the text") {
                CHECK(paper == "An apple a day keeps the doctor away");
            }
        }

        WHEN("the text to fill is larger than the space") {
            paper = "An       a day keeps the doctor away";
            pencil.writeFill("artichoke");

            THEN("it should not resize the space and should replace overwritten characters with '@'") {
                CHECK(paper == "An artich@k@ay keeps the doctor away");
            }
        }

        WHEN("there is no erasure") {
            paper = "An apple a day keeps the doctor away";
            pencil.writeFill("onion");

            THEN("it should not change the paper") {
                CHECK(paper == "An apple a day keeps the doctor away");
            }
        }

        WHEN("overwriting a character with a space") {
            paper = "An apple   day keeps the doctor away";
            pencil.writeFill("An apple");

            THEN("it should not change the character") {
                CHECK(paper == "An apple And@@p@@eps the doctor away");
            }
        }

        WHEN("overwriting a character with a newline") {
            paper = "   apple a day keeps the doctor away";
            pencil.writeFill("An\n\n");

            THEN("it should change a space to a newline and text to '@'") {
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
            pencil.writeAppend("text");

            THEN("it should write spaces") {
                CHECK(paper == "    ");
            }
        }

        WHEN("the pencil fills with a dull point") {
            paper = "one     three";
            pencil.writeFill("twenty");

            THEN("it should not change the paper") {
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
            pencil1.writeAppend("texts");
            pencil2.writeFill("texts");

            THEN("it should degrade the point durability by one") {
                CHECK(paper1 == "text ");
                CHECK(paper2 == "text text text");
            }
        }

        WHEN("the pencil writes an uppercase letter") {
            pencil1.writeAppend("Text");
            pencil2.writeFill("Text");

            THEN("it should degrade the point durability by two") {
                CHECK(paper1 == "Tex ");
                CHECK(paper2 == "text Tex  text");
            }
        }

        WHEN("the remaining point durability is one") {
            pencil1.writeAppend("texMex");
            pencil2.writeFill("texMex");

            THEN("it should still write an uppercase letter") {
                CHECK(paper1 == "texM  ");
                CHECK(paper2 == "text texM text");
            }
        }

        WHEN("the pencil writes whitespace") {
            pencil1.writeAppend("te \nxt");
            pencil2.writeFill("te \nxt");

            THEN("it should not degrade the point") {
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
        pencil1.attach(paper1);

        Pencil pencil2{ 4, 2 };
        std::string paper2{ "Tex             Tex" };
        pencil2.attach(paper2);

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
    GIVEN("a pencil eraser with no durability remaining") {
        Pencil pencil{ 100, 100, 0 };
        std::string paper{ "text" };
        pencil.attach(paper);

        WHEN("the eraser is used") {
            pencil.erase("text");

            THEN("it should not erase") {
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

            THEN("it should remove characters in reverse order one durability point each not counting spaces") {
                CHECK(paper == "Buffal      ");
            }
        }
    }
}
