#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Elementary/NOTComponent.hpp"
#include "../Special/TrueComponent.hpp"
#include "../Special/FalseComponent.hpp"
#include "../Special/InputComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(NOTComponentTests, InitialState, .init = redirect_all_stdout)
{
    NOTComponent not_gate;
    for (std::size_t pin = 1; pin <= 2; pin++)
        cr_assert_eq(not_gate.compute(pin), UNDEFINED, "Pins must be UNDEFINED at creation.");
}

Test(NOTComponentTests, ComputeWithTrueComponent, .init = redirect_all_stdout)
{
    NOTComponent not_gate;
    TrueComponent input;
    
    not_gate.setLink(1, input, 1);
    cr_assert_eq(not_gate.compute(2), FALSE, "NOT gate output must be FALSE when input is TRUE");
}

Test(NOTComponentTests, ComputeWithFalseComponent, .init = redirect_all_stdout)
{
    NOTComponent not_gate;
    FalseComponent input;
    
    not_gate.setLink(1, input, 1);
    cr_assert_eq(not_gate.compute(2), TRUE, "NOT gate output must be TRUE when input is FALSE");
}

Test(NOTComponentTests, ComputeWithoutLink, .init = redirect_all_stdout)
{
    NOTComponent not_gate;
    cr_assert_eq(not_gate.compute(2), UNDEFINED, "NOT gate output must be UNDEFINED when input is not connected");
}

Test(NOTComponentTests, ComputeInputPin, .init = redirect_all_stdout)
{
    NOTComponent not_gate;
    TrueComponent input;
    
    not_gate.setLink(1, input, 1);
    cr_assert_eq(not_gate.compute(1), TRUE, "Input pin should return the value of its linked component");
}

Test(NOTComponentTests, ComputeInvalidPin, .init = redirect_all_stdout)
{
    NOTComponent not_gate;
    cr_assert_any_throw(not_gate.compute(999), "Computing an invalid pin should throw an exception");
}

Test(NOTComponentTests, ComputeInvalidPin2, .init = redirect_all_stdout)
{
    NOTComponent not_gate;
    try {
        not_gate.compute(3);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found", "Exception message should be 'Pin not found' when computing a wrong pin");
    }
}

Test(NOTComponentTests, ConstructorPinInitialization, .init = redirect_all_stdout)
{
    NOTComponent not_gate;
    auto pins = not_gate.getPins();
    
    cr_assert_eq(pins.size(), 2, "NOT gate should have exactly 2 pins");
    cr_assert(pins.find(1) != pins.end(), "Pin 1 should be present");
    cr_assert(pins.find(2) != pins.end(), "Pin 2 should be present");
}

Test(NOTComponentTests, ComputeWithUndefinedComponent, .init = redirect_all_stdout)
{
    NOTComponent not_gate;
    InputComponent undefined_input;

    not_gate.setLink(1, undefined_input, 1);
    cr_assert_eq(not_gate.compute(2), UNDEFINED, "NOT gate output must be UNDEFINED when input is UNDEFINED");

    undefined_input.simulate(1);
    cr_assert_eq(not_gate.compute(2), UNDEFINED, "NOT gate output must stay UNDEFINED after simulation");

    undefined_input.setValue(TRUE);
    undefined_input.simulate(1);
    cr_assert_eq(not_gate.compute(2), FALSE, "NOT gate output must be FALSE when input becomes TRUE");

    undefined_input.setValue(UNDEFINED);
    undefined_input.simulate(1);
    cr_assert_eq(not_gate.compute(2), UNDEFINED, "NOT gate output must return to UNDEFINED when input becomes UNDEFINED");
}
