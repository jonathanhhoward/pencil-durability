/**
 * (C) Copyright 2020, by Jonathan Howard
 */

#include "catch.hpp"
#include "Writer.h"

using namespace PencilDurability;

SCENARIO("a writer uses many sheets of paper")
{
    GIVEN("multiple sheets of paper") {
        Pencil pencil;
        std::string paper1;
        std::string paper2;
        Writer writer{ paper1, pencil };

        WHEN("the writer writes text to different papers") {
            writer.appendToMedium("text");

            writer.reassignMedium(paper2);
            writer.appendToMedium("TEXT");

            THEN("it should reflect the text on the respective paper") {
                REQUIRE(paper1 == "text");
                REQUIRE(paper2 == "TEXT");
            }
        }
    }
}

SCENARIO("a writer uses many pencils")
{
    GIVEN("multiple pencils") {
        Pencil pencil{ 4 };
        Pencil pencil2;
        std::string paper;
        Writer writer{ paper, pencil };

        WHEN("the writer changes pencils") {
            writer.appendToMedium("text");
            writer.reassignPencil(pencil2);
            writer.appendToMedium(" text");

            THEN("it should continue to write with the same paper") {
                REQUIRE(paper == "text text");
            }
        }
    }
}

SCENARIO("a writer writes on paper with a pencil")
{
    GIVEN("a pencil and paper") {
        Pencil pencil;
        std::string paper;
        Writer writer{ paper, pencil };

        WHEN("the writer writes text to paper with a pencil") {
            writer.appendToMedium("She sells sea shells");

            THEN("the text should be reflected on the paper") {
                REQUIRE(paper == "She sells sea shells");

                AND_WHEN("additional text is written") {
                    writer.appendToMedium(" down by the sea shore");

                    THEN("the text should append to existing text on the paper") {
                        REQUIRE(paper == "She sells sea shells down by the sea shore");
                    }
                }
            }
        }
    }
}

SCENARIO("a writer can fill the space where text was erased from paper")
{
    GIVEN("a pencil and paper with erasures") {
        Pencil pencil;
        std::string paper;
        Writer writer{ paper, pencil };

        WHEN("the writer fills empty space") {
            paper = "An       a day       the doctor away";
            writer.fillInMedium("onion");

            THEN("it should fill the first occurrence of empty space with a single space before the text") {
                REQUIRE(paper == "An onion a day       the doctor away");

                AND_WHEN("the writer fills again") {
                    writer.fillInMedium("onion");

                    THEN("it should fill the next empty space") {
                        REQUIRE(paper == "An onion a day onion the doctor away");
                    }
                }
            }
        }

        WHEN("the writer fills at the start of the paper") {
            paper = "   apple a day keeps the doctor away";
            writer.fillInMedium("An");

            THEN("it should not put a space before the text") {
                REQUIRE(paper == "An apple a day keeps the doctor away");
            }
        }

        WHEN("the text to fill is larger than the space") {
            paper = "An       a day keeps the doctor away";
            writer.fillInMedium("artichoke");

            THEN("it should not resize the space and should replace overwritten characters with '@'") {
                REQUIRE(paper == "An artich@k@ay keeps the doctor away");
            }
        }

        WHEN("there is no erasure") {
            paper = "An apple a day keeps the doctor away";
            writer.fillInMedium("onion");

            THEN("it should not change the paper") {
                REQUIRE(paper == "An apple a day keeps the doctor away");
            }
        }
    }
}

SCENARIO("a writer can erase text from paper")
{
    GIVEN("a pencil and paper with text") {
        Pencil pencil;
        std::string paper{ "How much wood would a woodchuck chuck if a woodchuck could chuck wood?" };
        Writer writer{ paper, pencil };

        WHEN("a writer erases text from the paper") {
            writer.eraseFromMedium("chuck");

            THEN("it should replace the last occurrence of the text with blank spaces") {
                REQUIRE(paper == "How much wood would a woodchuck chuck if a woodchuck could       wood?");

                AND_WHEN("when the text matches a substring") {
                    writer.eraseFromMedium("chuck");

                    THEN("it should replace the substring blank spaces") {
                        REQUIRE(paper == "How much wood would a woodchuck chuck if a wood      could       wood?");
                    }
                }
            }
        }

        WHEN("the writer erases text that is not found") {
            writer.eraseFromMedium("duck");

            THEN("it should not change the paper") {
                REQUIRE(paper == "How much wood would a woodchuck chuck if a woodchuck could chuck wood?");
            }
        }
    }
}
