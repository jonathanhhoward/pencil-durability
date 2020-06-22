#include "catch.hpp"

#include <string>
#include "Pencil.h"
#include "Writer.h"

using namespace PencilDurability;

TEST_CASE("a writer writes on paper with a pencil")
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
