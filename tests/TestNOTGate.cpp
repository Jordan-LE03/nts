#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Gates/NOTGate.hpp"
#include "../Special/TrueComponent.hpp"
#include "../Special/FalseComponent.hpp"
#include "../Special/InputComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(NOTGateTests, InitialState, .init = redirect_all_stdout)
{
    NOTGate not_gate;
    for (std::size_t pin = 1; pin <= 13; pin++) {
        if (pin == 7)
            continue;
        cr_assert_eq(not_gate.compute(pin), UNDEFINED);
    } 
}

Test(NOTGateTests, FirstGateCompute, .init = redirect_all_stdout)
{
    NOTGate not_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    not_gate.setLink(1, true_input, 1);
    cr_assert_eq(not_gate.compute(2), FALSE);
    
    not_gate.setLink(1, false_input, 1);
    cr_assert_eq(not_gate.compute(2), TRUE);
    
    not_gate.setLink(1, undefined_input, 1);
    cr_assert_eq(not_gate.compute(2), UNDEFINED);
}

Test(NOTGateTests, SecondGateCompute, .init = redirect_all_stdout)
{
    NOTGate not_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    not_gate.setLink(3, true_input, 1);
    cr_assert_eq(not_gate.compute(4), FALSE);
    
    not_gate.setLink(3, false_input, 1);
    cr_assert_eq(not_gate.compute(4), TRUE);
    
    not_gate.setLink(3, undefined_input, 1);
    cr_assert_eq(not_gate.compute(4), UNDEFINED);
}

Test(NOTGateTests, ThirdGateCompute, .init = redirect_all_stdout)
{
    NOTGate not_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    not_gate.setLink(5, true_input, 1);
    cr_assert_eq(not_gate.compute(6), FALSE);
    
    not_gate.setLink(5, false_input, 1);
    cr_assert_eq(not_gate.compute(6), TRUE);
    
    not_gate.setLink(5, undefined_input, 1);
    cr_assert_eq(not_gate.compute(6), UNDEFINED);
}

Test(NOTGateTests, FourthGateCompute, .init = redirect_all_stdout)
{
    NOTGate not_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    not_gate.setLink(9, true_input, 1);
    cr_assert_eq(not_gate.compute(8), FALSE);
    
    not_gate.setLink(9, false_input, 1);
    cr_assert_eq(not_gate.compute(8), TRUE);
    
    not_gate.setLink(9, undefined_input, 1);
    cr_assert_eq(not_gate.compute(8), UNDEFINED);
}

Test(NOTGateTests, FifthGateCompute, .init = redirect_all_stdout)
{
    NOTGate not_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    not_gate.setLink(11, true_input, 1);
    cr_assert_eq(not_gate.compute(10), FALSE);
    
    not_gate.setLink(11, false_input, 1);
    cr_assert_eq(not_gate.compute(10), TRUE);
    
    not_gate.setLink(11, undefined_input, 1);
    cr_assert_eq(not_gate.compute(10), UNDEFINED);
}

Test(NOTGateTests, SixthGateCompute, .init = redirect_all_stdout)
{
    NOTGate not_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    not_gate.setLink(13, true_input, 1);
    cr_assert_eq(not_gate.compute(12), FALSE);
    
    not_gate.setLink(13, false_input, 1);
    cr_assert_eq(not_gate.compute(12), TRUE);
    
    not_gate.setLink(13, undefined_input, 1);
    cr_assert_eq(not_gate.compute(12), UNDEFINED);
}

Test(NOTGateTests, InputPinCompute, .init = redirect_all_stdout)
{
    NOTGate not_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;

    not_gate.setLink(13, true_input, 1);
    cr_assert_eq(not_gate.compute(13), TRUE);
}

Test(NOTGateTests, InvalidPins, .init = redirect_all_stdout)
{
    NOTGate not_gate;
    
    try {
        not_gate.compute(7);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Cannot compute pin 7");
    }
    
    try {
        not_gate.compute(14);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found");
    }
}

Test(NOTGateTests, ConstructorPinInitialization, .init = redirect_all_stdout)
{
    NOTGate not_gate;
    auto pins = not_gate.getPins();
    
    cr_assert_eq(pins.size(), 12);
    for (int i = 1; i <= 13; i++) {
        if (i != 7) {
            cr_assert(pins.find(i) != pins.end(), "Pin %d should be present", i);
        }
    }
}
