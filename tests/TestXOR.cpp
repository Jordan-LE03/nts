#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Elementary/XORComponent.hpp"
#include "../Special/TrueComponent.hpp"
#include "../Special/FalseComponent.hpp"
#include "../Special/InputComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(XORComponentTests, InitialState, .init = redirect_all_stdout)
{
    XORComponent xor_gate;
    for (int pin = 1; pin <= 3; pin++)
        cr_assert_eq(xor_gate.compute(pin), UNDEFINED, "Pins must be UNDEFINED at creation.");
}

Test(XORComponentTests, ComputeWithTrueComponents, .init = redirect_all_stdout)
{
    XORComponent xor_gate;
    TrueComponent input1, input2;
    
    xor_gate.setLink(1, input1, 1);
    xor_gate.setLink(2, input2, 1);
    cr_assert_eq(xor_gate.compute(3), FALSE, "XOR gate output must be FALSE when both inputs are TRUE");
}

Test(XORComponentTests, ComputeWithFalseComponents, .init = redirect_all_stdout)
{
    XORComponent xor_gate;
    FalseComponent input1, input2;
    
    xor_gate.setLink(1, input1, 1);
    xor_gate.setLink(2, input2, 1);
    cr_assert_eq(xor_gate.compute(3), FALSE, "XOR gate output must be FALSE when both inputs are FALSE");
}

Test(XORComponentTests, ComputeWithMixedInputs, .init = redirect_all_stdout)
{
    XORComponent xor_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    
    xor_gate.setLink(1, true_input, 1);
    xor_gate.setLink(2, false_input, 1);
    cr_assert_eq(xor_gate.compute(3), TRUE, "XOR gate output must be TRUE when inputs are different");
}

Test(XORComponentTests, ComputeWithOneInputMissing, .init = redirect_all_stdout)
{
    XORComponent xor_gate;
    TrueComponent true_input;
    
    xor_gate.setLink(1, true_input, 1);
    cr_assert_eq(xor_gate.compute(3), UNDEFINED, "XOR gate output must be UNDEFINED when one input is not connected");
}

Test(XORComponentTests, ComputeInputPins, .init = redirect_all_stdout)
{
    XORComponent xor_gate;
    TrueComponent input1;
    FalseComponent input2;
    
    xor_gate.setLink(1, input1, 1);
    xor_gate.setLink(2, input2, 1);
    cr_assert_eq(xor_gate.compute(1), TRUE, "Input pin 1 should return TRUE when connected to TRUE component");
    cr_assert_eq(xor_gate.compute(2), FALSE, "Input pin 2 should return FALSE when connected to FALSE component");
}

Test(XORComponentTests, ComputeInvalidPin, .init = redirect_all_stdout)
{
    XORComponent xor_gate;
    cr_assert_any_throw(xor_gate.compute(999), "Computing an invalid pin should throw an exception");
}

Test(XORComponentTests, ComputeInvalidPin2, .init = redirect_all_stdout)
{
    XORComponent xor_gate;
    try {
        xor_gate.compute(4);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found", "Exception message should be 'Pin not found' when computing a wrong pin");
    }
}

Test(XORComponentTests, ConstructorPinInitialization, .init = redirect_all_stdout)
{
    XORComponent xor_gate;
    auto pins = xor_gate.getPins();
    
    cr_assert_eq(pins.size(), 3, "XOR gate should have exactly 3 pins");
    cr_assert(pins.find(1) != pins.end(), "Pin 1 should be present");
    cr_assert(pins.find(2) != pins.end(), "Pin 2 should be present");
    cr_assert(pins.find(3) != pins.end(), "Pin 3 should be present");
}

Test(XORComponentTests, ComputeWithUndefinedComponents, .init = redirect_all_stdout)
{
    XORComponent xor_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;

    xor_gate.setLink(1, true_input, 1);
    xor_gate.setLink(2, undefined_input, 1);
    cr_assert_eq(xor_gate.compute(3), UNDEFINED);

    xor_gate.setLink(1, false_input, 1);
    xor_gate.setLink(2, undefined_input, 1);
    cr_assert_eq(xor_gate.compute(3), UNDEFINED);

    xor_gate.setLink(1, undefined_input, 1);
    xor_gate.setLink(2, true_input, 1);
    cr_assert_eq(xor_gate.compute(3), UNDEFINED);

    xor_gate.setLink(1, undefined_input, 1);
    xor_gate.setLink(2, false_input, 1);
    cr_assert_eq(xor_gate.compute(3), UNDEFINED);

    xor_gate.setLink(1, undefined_input, 1);
    xor_gate.setLink(2, undefined_input, 1);
    cr_assert_eq(xor_gate.compute(3), UNDEFINED);
}
