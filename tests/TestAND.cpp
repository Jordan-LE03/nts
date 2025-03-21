#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Elementary/ANDComponent.hpp"
#include "../Special/TrueComponent.hpp"
#include "../Special/FalseComponent.hpp"
#include "../Special/InputComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ANDComponentTests, InitialState, .init = redirect_all_stdout)
{
    ANDComponent andComponent;
    for (int pin = 1; pin <= 3; pin++) {
        cr_assert_eq(andComponent.compute(pin), UNDEFINED, "Pins must be UNDEFINED at creation.");
    }
}

Test(ANDComponentTests, ComputeWithTrueComponents, .init = redirect_all_stdout)
{
    ANDComponent andComponent;
    TrueComponent input1, input2;
    
    andComponent.setLink(1, input1, 1);
    andComponent.setLink(2, input2, 1);
    cr_assert_eq(andComponent.compute(3), TRUE, "AND gate output must be TRUE when both inputs are TRUE");
}

Test(ANDComponentTests, ComputeWithFalseComponents, .init = redirect_all_stdout)
{
    ANDComponent andComponent;
    FalseComponent input1, input2;
    
    andComponent.setLink(1, input1, 1);
    andComponent.setLink(2, input2, 1);
    cr_assert_eq(andComponent.compute(3), FALSE, "AND gate output must be FALSE when both inputs are FALSE");
}

Test(ANDComponentTests, ComputeWithMixedInputs, .init = redirect_all_stdout)
{
    ANDComponent andComponent;
    TrueComponent true_input;
    FalseComponent false_input;
    
    andComponent.setLink(1, true_input, 1);
    andComponent.setLink(2, false_input, 1);
    cr_assert_eq(andComponent.compute(3), FALSE, "AND gate output must be FALSE when one input is TRUE and other is FALSE");
}

Test(ANDComponentTests, ComputeWithOneInputMissing, .init = redirect_all_stdout)
{
    ANDComponent andComponent;
    TrueComponent true_input;
    
    andComponent.setLink(1, true_input, 1);
    cr_assert_eq(andComponent.compute(3), UNDEFINED, "AND gate output must be UNDEFINED when one input is not connected");
}

Test(ANDComponentTests, ComputeInvalidPin, .init = redirect_all_stdout)
{
    ANDComponent andComponent;
    cr_assert_any_throw(andComponent.compute(999), "Computing an invalid pin should throw an exception");
}

Test(ANDComponentTests, ComputeInvalidPin2, .init = redirect_all_stdout)
{
    ANDComponent andComponent;
    try {
        andComponent.compute(4);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found", "Exception message should be 'Pin not found' when computing a wrong pin");
    }
}

Test(ANDComponentTests, LinkToInvalidPin, .init = redirect_all_stdout)
{
    ANDComponent andComponent;
    TrueComponent true_input;

    try {
        andComponent.setLink(1, true_input, 2);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found", "Exception message should be 'Pin not found' when linking to a wrong pin");
    }
}

Test(ANDComponentTests, LinkInvalidPin, .init = redirect_all_stdout)
{
    ANDComponent andComponent;
    TrueComponent true_input;

    try {
        andComponent.setLink(999, true_input, 1);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found", "Exception message should be 'Pin not found' when linking a wrong pin");
    }
}

Test(ANDComponentTests, InputPinComputation, .init = redirect_all_stdout)
{
    ANDComponent andComponent;
    TrueComponent input;
    
    andComponent.setLink(1, input, 1);
    cr_assert_eq(andComponent.compute(1), TRUE, "Input pin 1 should return the value of its linked component");
}

Test(ANDComponentTests, ComputeWithUndefinedComponents, .init = redirect_all_stdout)
{
    ANDComponent andComponent;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;

    andComponent.setLink(1, true_input, 1);
    andComponent.setLink(2, undefined_input, 1);
    cr_assert_eq(andComponent.compute(3), UNDEFINED, "AND gate output must be UNDEFINED with TRUE and UNDEFINED inputs");

    andComponent.setLink(1, false_input, 1);
    andComponent.setLink(2, undefined_input, 1);
    cr_assert_eq(andComponent.compute(3), FALSE, "AND gate output must be FALSE with FALSE and UNDEFINED inputs");

    andComponent.setLink(1, undefined_input, 1);
    andComponent.setLink(2, true_input, 1);
    cr_assert_eq(andComponent.compute(3), UNDEFINED, "AND gate output must be UNDEFINED with UNDEFINED and TRUE inputs");

    andComponent.setLink(1, undefined_input, 1);
    andComponent.setLink(2, false_input, 1);
    cr_assert_eq(andComponent.compute(3), FALSE, "AND gate output must be FALSE with UNDEFINED and FALSE inputs");

    andComponent.setLink(1, undefined_input, 1);
    andComponent.setLink(2, undefined_input, 1);
    cr_assert_eq(andComponent.compute(3), UNDEFINED, "AND gate output must be UNDEFINED with both UNDEFINED inputs");
}
