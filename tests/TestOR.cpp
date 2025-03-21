#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Elementary/ORComponent.hpp"
#include "../Special/TrueComponent.hpp"
#include "../Special/FalseComponent.hpp"
#include "../Special/InputComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ORComponentTests, InitialState, .init = redirect_all_stdout)
{
    ORComponent orComponent;
    for (std::size_t pin = 1; pin <= 3; pin++)
        cr_assert_eq(orComponent.compute(pin), UNDEFINED, "Pins must be UNDEFINED at creation.");
}

Test(ORComponentTests, ComputeWithTrueComponents, .init = redirect_all_stdout)
{
    ORComponent orComponent;
    TrueComponent input1, input2;
    
    orComponent.setLink(1, input1, 1);
    orComponent.setLink(2, input2, 1);
    cr_assert_eq(orComponent.compute(3), TRUE, "OR gate output must be TRUE when both inputs are TRUE");
}

Test(ORComponentTests, ComputeWithFalseComponents, .init = redirect_all_stdout)
{
    ORComponent orComponent;
    FalseComponent input1, input2;
    
    orComponent.setLink(1, input1, 1);
    orComponent.setLink(2, input2, 1);
    cr_assert_eq(orComponent.compute(3), FALSE, "OR gate output must be FALSE when both inputs are FALSE");
}

Test(ORComponentTests, ComputeWithMixedInputs, .init = redirect_all_stdout)
{
    ORComponent orComponent;
    TrueComponent true_input;
    FalseComponent false_input;
    
    orComponent.setLink(1, true_input, 1);
    orComponent.setLink(2, false_input, 1);
    cr_assert_eq(orComponent.compute(3), TRUE, "OR gate output must be TRUE when one input is TRUE and other is FALSE");
}

Test(ORComponentTests, ComputeWithOneInputMissing, .init = redirect_all_stdout)
{
    ORComponent orComponent;
    TrueComponent true_input;
    
    orComponent.setLink(1, true_input, 1);
    cr_assert_eq(orComponent.compute(3), UNDEFINED, "OR gate output must be UNDEFINED when one input is not connected");
}

Test(ORComponentTests, ComputeInputPins, .init = redirect_all_stdout)
{
    ORComponent orComponent;
    TrueComponent input1;
    FalseComponent input2;
    
    orComponent.setLink(1, input1, 1);
    orComponent.setLink(2, input2, 1);
    cr_assert_eq(orComponent.compute(1), TRUE, "Input pin 1 should return TRUE when connected to TRUE component");
    cr_assert_eq(orComponent.compute(2), FALSE, "Input pin 2 should return FALSE when connected to FALSE component");
}

Test(ORComponentTests, ComputeInvalidPin, .init = redirect_all_stdout)
{
    ORComponent orComponent;
    cr_assert_any_throw(orComponent.compute(999), "Computing an invalid pin should throw an exception");
}

Test(ORComponentTests, ComputeInvalidPin2, .init = redirect_all_stdout)
{
    ORComponent orComponent;
    try {
        orComponent.compute(4);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found", "Exception message should be 'Pin not found' when computing a wrong pin");
    }
}

Test(ORComponentTests, ConstructorPinInitialization, .init = redirect_all_stdout)
{
    ORComponent orComponent;
    auto pins = orComponent.getPins();
    
    cr_assert_eq(pins.size(), 3, "OR gate should have exactly 3 pins");
    cr_assert(pins.find(1) != pins.end(), "Pin 1 should be present");
    cr_assert(pins.find(2) != pins.end(), "Pin 2 should be present");
    cr_assert(pins.find(3) != pins.end(), "Pin 3 should be present");
}

Test(ORComponentTests, ComputeWithUndefinedComponents, .init = redirect_all_stdout)
{
    ORComponent orComponent;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;

    orComponent.setLink(1, true_input, 1);
    orComponent.setLink(2, undefined_input, 1);
    cr_assert_eq(orComponent.compute(3), TRUE);

    orComponent.setLink(1, false_input, 1);
    orComponent.setLink(2, undefined_input, 1);
    cr_assert_eq(orComponent.compute(3), UNDEFINED);

    orComponent.setLink(1, undefined_input, 1);
    orComponent.setLink(2, true_input, 1);
    cr_assert_eq(orComponent.compute(3), TRUE);

    orComponent.setLink(1, undefined_input, 1);
    orComponent.setLink(2, false_input, 1);
    cr_assert_eq(orComponent.compute(3), UNDEFINED);

    orComponent.setLink(1, undefined_input, 1);
    orComponent.setLink(2, undefined_input, 1);
    cr_assert_eq(orComponent.compute(3), UNDEFINED);
}
