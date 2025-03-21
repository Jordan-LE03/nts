#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Gates/ORGate.hpp"
#include "../Special/TrueComponent.hpp"
#include "../Special/FalseComponent.hpp"
#include "../Special/InputComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ORGateTests, InitialState, .init = redirect_all_stdout)
{
    ORGate or_gate;
    for (std::size_t pin = 1; pin <= 13; pin++) {
        if (pin == 7)
            continue;
        cr_assert_eq(or_gate.compute(pin), UNDEFINED);
    }
}

Test(ORGateTests, FirstGateCompute, .init = redirect_all_stdout)
{
    ORGate or_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    or_gate.setLink(1, true_input, 1);
    or_gate.setLink(2, true_input, 1);
    cr_assert_eq(or_gate.compute(3), TRUE);
    
    or_gate.setLink(1, false_input, 1);
    or_gate.setLink(2, true_input, 1);
    cr_assert_eq(or_gate.compute(3), TRUE);
    
    or_gate.setLink(1, false_input, 1);
    or_gate.setLink(2, false_input, 1);
    cr_assert_eq(or_gate.compute(3), FALSE);
    
    or_gate.setLink(1, undefined_input, 1);
    or_gate.setLink(2, true_input, 1);
    cr_assert_eq(or_gate.compute(3), TRUE);
    
    or_gate.setLink(1, undefined_input, 1);
    or_gate.setLink(2, false_input, 1);
    cr_assert_eq(or_gate.compute(3), UNDEFINED);
}

Test(ORGateTests, SecondGateCompute, .init = redirect_all_stdout)
{
    ORGate or_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    or_gate.setLink(5, true_input, 1);
    or_gate.setLink(6, true_input, 1);
    cr_assert_eq(or_gate.compute(4), TRUE);
    
    or_gate.setLink(5, false_input, 1);
    or_gate.setLink(6, false_input, 1);
    cr_assert_eq(or_gate.compute(4), FALSE);
    
    or_gate.setLink(5, undefined_input, 1);
    or_gate.setLink(6, false_input, 1);
    cr_assert_eq(or_gate.compute(4), UNDEFINED);
}

Test(ORGateTests, ThirdGateCompute, .init = redirect_all_stdout)
{
    ORGate or_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    or_gate.setLink(8, true_input, 1);
    or_gate.setLink(9, false_input, 1);
    cr_assert_eq(or_gate.compute(10), TRUE);
    
    or_gate.setLink(8, false_input, 1);
    or_gate.setLink(9, false_input, 1);
    cr_assert_eq(or_gate.compute(10), FALSE);
    
    or_gate.setLink(8, undefined_input, 1);
    or_gate.setLink(9, false_input, 1);
    cr_assert_eq(or_gate.compute(10), UNDEFINED);
}

Test(ORGateTests, FourthGateCompute, .init = redirect_all_stdout)
{
    ORGate or_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    or_gate.setLink(12, true_input, 1);
    or_gate.setLink(13, false_input, 1);
    cr_assert_eq(or_gate.compute(11), TRUE);
    
    or_gate.setLink(12, false_input, 1);
    or_gate.setLink(13, false_input, 1);
    cr_assert_eq(or_gate.compute(11), FALSE);
    
    or_gate.setLink(12, undefined_input, 1);
    or_gate.setLink(13, false_input, 1);
    cr_assert_eq(or_gate.compute(11), UNDEFINED);
}

Test(ORGateTests, InputPinCompute, .init = redirect_all_stdout)
{
    ORGate or_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    
    or_gate.setLink(1, true_input, 1);
    or_gate.setLink(2, false_input, 1);
    cr_assert_eq(or_gate.compute(1), TRUE);
    cr_assert_eq(or_gate.compute(2), FALSE);
}

Test(ORGateTests, InvalidPins, .init = redirect_all_stdout)
{
    ORGate or_gate;
    
    try {
        or_gate.compute(7);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Cannot compute pin 7");
    }
    
    try {
        or_gate.compute(14);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found");
    }
}

Test(ORGateTests, ConstructorPinInitialization, .init = redirect_all_stdout)
{
    ORGate or_gate;
    auto pins = or_gate.getPins();
    
    cr_assert_eq(pins.size(), 12);
    cr_assert(pins.find(1) != pins.end());
    cr_assert(pins.find(2) != pins.end());
    cr_assert(pins.find(3) != pins.end());
    cr_assert(pins.find(4) != pins.end());
    cr_assert(pins.find(5) != pins.end());
    cr_assert(pins.find(6) != pins.end());
    cr_assert(pins.find(8) != pins.end());
    cr_assert(pins.find(9) != pins.end());
    cr_assert(pins.find(10) != pins.end());
    cr_assert(pins.find(11) != pins.end());
    cr_assert(pins.find(12) != pins.end());
    cr_assert(pins.find(13) != pins.end());
}
