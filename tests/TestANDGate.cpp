#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Gates/ANDGate.hpp"
#include "../Special/TrueComponent.hpp"
#include "../Special/FalseComponent.hpp"
#include "../Special/InputComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ANDGateTests, InitialState, .init = redirect_all_stdout)
{
    ANDGate and_gate;
    for (std::size_t pin = 1; pin <= 13; pin++) {
        if (pin == 7)
            continue;
        cr_assert_eq(and_gate.compute(pin), UNDEFINED, "Pins must be UNDEFINED at creation."); 
    }
}

Test(ANDGateTests, FirstGateCompute, .init = redirect_all_stdout)
{
    ANDGate and_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    
    // Test TRUE & TRUE = TRUE
    and_gate.setLink(1, true_input, 1);
    and_gate.setLink(2, true_input, 1);
    cr_assert_eq(and_gate.compute(3), TRUE);
    
    // Test TRUE & FALSE = FALSE
    and_gate.setLink(2, false_input, 1);
    cr_assert_eq(and_gate.compute(3), FALSE);
}

Test(ANDGateTests, SecondGateCompute, .init = redirect_all_stdout)
{
    ANDGate and_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    
    // Test TRUE & TRUE = TRUE
    and_gate.setLink(5, true_input, 1);
    and_gate.setLink(6, true_input, 1);
    cr_assert_eq(and_gate.compute(4), TRUE);
    
    // Test TRUE & FALSE = FALSE
    and_gate.setLink(6, false_input, 1);
    cr_assert_eq(and_gate.compute(4), FALSE);
}

Test(ANDGateTests, ThirdGateCompute, .init = redirect_all_stdout)
{
    ANDGate and_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    
    // Test TRUE & TRUE = TRUE
    and_gate.setLink(8, true_input, 1);
    and_gate.setLink(9, true_input, 1);
    cr_assert_eq(and_gate.compute(10), TRUE);
    
    // Test TRUE & FALSE = FALSE
    and_gate.setLink(9, false_input, 1);
    cr_assert_eq(and_gate.compute(10), FALSE);
}

Test(ANDGateTests, FourthGateCompute, .init = redirect_all_stdout)
{
    ANDGate and_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    
    // Test TRUE & TRUE = TRUE
    and_gate.setLink(12, true_input, 1);
    and_gate.setLink(13, true_input, 1);
    cr_assert_eq(and_gate.compute(11), TRUE);
    
    // Test TRUE & FALSE = FALSE
    and_gate.setLink(13, false_input, 1);
    cr_assert_eq(and_gate.compute(11), FALSE);
}

Test(ANDGateTests, InvalidPins, .init = redirect_all_stdout)
{
    ANDGate and_gate;
    
    // Test pin 7 (invalid)
    cr_assert_any_throw(and_gate.compute(7), "Computing pin 7 should throw an exception");
    
    // Test out of range pin
    cr_assert_any_throw(and_gate.compute(14), "Computing pin 14 should throw an exception");
    
    try {
        and_gate.compute(7);
        cr_assert_fail("Expected exception not thrown for pin 7");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Cannot compute pin 7");
    }
}

Test(ANDGateTests, ConstructorPinInitialization, .init = redirect_all_stdout)
{
    ANDGate and_gate;
    auto pins = and_gate.getPins();
    
    cr_assert_eq(pins.size(), 12, "AND gate should have exactly 12 pins");
    for (int i = 1; i <= 13; i++) {
        if (i != 7) {
            cr_assert(pins.find(i) != pins.end(), "Pin %d should be present", i);
        }
    }
}

Test(ANDGateTests, InputPinsComputation, .init = redirect_all_stdout)
{
    ANDGate and_gate;
    TrueComponent true_input;
    
    and_gate.setLink(1, true_input, 1);
    cr_assert_eq(and_gate.compute(1), TRUE, "Input pin should return the value of its linked component");
}

Test(ANDGateTests, FirstGateComputeWithUndefined, .init = redirect_all_stdout)
{
    ANDGate and_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    // Test TRUE & UNDEFINED = UNDEFINED
    and_gate.setLink(1, true_input, 1);
    and_gate.setLink(2, undefined_input, 1);
    cr_assert_eq(and_gate.compute(3), UNDEFINED);
    
    // Test FALSE & UNDEFINED = FALSE
    and_gate.setLink(1, false_input, 1);
    and_gate.setLink(2, undefined_input, 1);
    cr_assert_eq(and_gate.compute(3), FALSE);
    
    // Test UNDEFINED & TRUE = UNDEFINED
    and_gate.setLink(1, undefined_input, 1);
    and_gate.setLink(2, true_input, 1);
    cr_assert_eq(and_gate.compute(3), UNDEFINED);
    
    // Test UNDEFINED & FALSE = FALSE
    and_gate.setLink(1, undefined_input, 1);
    and_gate.setLink(2, false_input, 1);
    cr_assert_eq(and_gate.compute(3), FALSE);
    
    // Test UNDEFINED & UNDEFINED = UNDEFINED
    and_gate.setLink(1, undefined_input, 1);
    and_gate.setLink(2, undefined_input, 1);
    cr_assert_eq(and_gate.compute(3), UNDEFINED);
}

Test(ANDGateTests, SecondGateComputeWithUndefined, .init = redirect_all_stdout)
{
    ANDGate and_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    // Test TRUE & UNDEFINED = UNDEFINED
    and_gate.setLink(5, true_input, 1);
    and_gate.setLink(6, undefined_input, 1);
    cr_assert_eq(and_gate.compute(4), UNDEFINED);
    
    // Test FALSE & UNDEFINED = FALSE
    and_gate.setLink(5, false_input, 1);
    and_gate.setLink(6, undefined_input, 1);
    cr_assert_eq(and_gate.compute(4), FALSE);
    
    // Test UNDEFINED & TRUE = UNDEFINED
    and_gate.setLink(5, undefined_input, 1);
    and_gate.setLink(6, true_input, 1);
    cr_assert_eq(and_gate.compute(4), UNDEFINED);
    
    // Test UNDEFINED & FALSE = FALSE
    and_gate.setLink(5, undefined_input, 1);
    and_gate.setLink(6, false_input, 1);
    cr_assert_eq(and_gate.compute(4), FALSE);
}

Test(ANDGateTests, ThirdGateComputeWithUndefined, .init = redirect_all_stdout)
{
    ANDGate and_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    // Test TRUE & UNDEFINED = UNDEFINED
    and_gate.setLink(8, true_input, 1);
    and_gate.setLink(9, undefined_input, 1);
    cr_assert_eq(and_gate.compute(10), UNDEFINED);
    
    // Test FALSE & UNDEFINED = FALSE
    and_gate.setLink(8, false_input, 1);
    and_gate.setLink(9, undefined_input, 1);
    cr_assert_eq(and_gate.compute(10), FALSE);
    
    // Test UNDEFINED & TRUE = UNDEFINED
    and_gate.setLink(8, undefined_input, 1);
    and_gate.setLink(9, true_input, 1);
    cr_assert_eq(and_gate.compute(10), UNDEFINED);
    
    // Test UNDEFINED & FALSE = FALSE
    and_gate.setLink(8, undefined_input, 1);
    and_gate.setLink(9, false_input, 1);
    cr_assert_eq(and_gate.compute(10), FALSE);
}

Test(ANDGateTests, FourthGateComputeWithUndefined, .init = redirect_all_stdout)
{
    ANDGate and_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    // Test TRUE & UNDEFINED = UNDEFINED
    and_gate.setLink(12, true_input, 1);
    and_gate.setLink(13, undefined_input, 1);
    cr_assert_eq(and_gate.compute(11), UNDEFINED);
    
    // Test FALSE & UNDEFINED = FALSE
    and_gate.setLink(12, false_input, 1);
    and_gate.setLink(13, undefined_input, 1);
    cr_assert_eq(and_gate.compute(11), FALSE);
    
    // Test UNDEFINED & TRUE = UNDEFINED
    and_gate.setLink(12, undefined_input, 1);
    and_gate.setLink(13, true_input, 1);
    cr_assert_eq(and_gate.compute(11), UNDEFINED);
    
    // Test UNDEFINED & FALSE = FALSE
    and_gate.setLink(12, undefined_input, 1);
    and_gate.setLink(13, false_input, 1);
    cr_assert_eq(and_gate.compute(11), FALSE);
}
