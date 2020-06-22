#include "catch.hpp"

#include <string>
#include "Pencil.h"
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
            writer.writeAppend("text");

            writer.changeMedium(paper2);
            writer.writeAppend("TEXT");

            THEN("it should reflect the text on the respective paper") {
                CHECK(paper1 == "text");
                CHECK(paper2 == "TEXT");
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
            writer.writeAppend("She sells sea shells");

            THEN("the text should be reflected on the paper") {
                CHECK(paper == "She sells sea shells");

                AND_WHEN("additional text is written") {
                    writer.writeAppend(" down by the sea shore");

                    THEN("the text should append to existing text on the paper") {
                        CHECK(paper == "She sells sea shells down by the sea shore");
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
            writer.writeFill("onion");

            THEN("it should fill the first occurrence of empty space with a single space before the text") {
                CHECK(paper == "An onion a day       the doctor away");

                AND_WHEN("the writer fills again") {
                    writer.writeFill("onion");

                    THEN("it should fill the next empty space") {
                        CHECK(paper == "An onion a day onion the doctor away");
                    }
                }
            }
        }

        WHEN("the writer fills at the start of the paper") {
            paper = "   apple a day keeps the doctor away";
            writer.writeFill("An");

            THEN("it should not put a space before the text") {
                CHECK(paper == "An apple a day keeps the doctor away");
            }
        }

        WHEN("the text to fill is larger than the space") {
            paper = "An       a day keeps the doctor away";
            writer.writeFill("artichoke");

            THEN("it should not resize the space and should replace overwritten characters with '@'") {
                CHECK(paper == "An artich@k@ay keeps the doctor away");
            }
        }

        WHEN("there is no erasure") {
            paper = "An apple a day keeps the doctor away";
            writer.writeFill("onion");

            THEN("it should not change the paper") {
                CHECK(paper == "An apple a day keeps the doctor away");
            }
        }

        WHEN("overwriting a character with whitespace") {
            paper = "An apple   day keeps the doctor away";
            writer.writeFill("An apple\n");

            THEN("it should not change the character") {
                CHECK(paper == "An apple And@@p@@eps the doctor away");
            }
        }

        WHEN("overwriting whitespace with whitespace") {
            paper = "  \n\n";
            writer.writeFill(" \n \n");

            THEN("it should not change whitespace") {
                CHECK(paper == "  \n\n");
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
            writer.erase("chuck");

            THEN("it should replace the last occurrence of the text with blank spaces") {
                CHECK(paper == "How much wood would a woodchuck chuck if a woodchuck could       wood?");

                AND_WHEN("when the text matches a substring") {
                    writer.erase("chuck");

                    THEN("it should replace the substring blank spaces") {
                        CHECK(paper == "How much wood would a woodchuck chuck if a wood      could       wood?");
                    }
                }
            }
        }

        WHEN("the writer erases text that is not found") {
            writer.erase("duck");

            THEN("it should not change the paper") {
                CHECK(paper == "How much wood would a woodchuck chuck if a woodchuck could chuck wood?");
            }
        }
    }
}
