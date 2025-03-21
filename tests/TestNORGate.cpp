#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <criterion/redirect.h>
#include "../Gates/NORGate.hpp"
#include "../Special/TrueComponent.hpp"
#include "../Special/FalseComponent.hpp"
#include "../Special/InputComponent.hpp"
#include "../Special/OutputComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(NORGateTests, InitialState, .init = redirect_all_stdout)
{
    NORGate nor_gate;
    for (std::size_t pin = 1; pin <= 13; pin++) {
        if (pin == 7)
            continue;
        cr_assert_eq(nor_gate.compute(pin), UNDEFINED);
    }
}

Test(NORGateTests, FirstGateCompute, .init = redirect_all_stdout)
{
    NORGate nor_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    nor_gate.setLink(1, true_input, 1);
    nor_gate.setLink(2, true_input, 1);
    cr_assert_eq(nor_gate.compute(3), FALSE);
    
    nor_gate.setLink(1, false_input, 1);
    nor_gate.setLink(2, true_input, 1);
    cr_assert_eq(nor_gate.compute(3), FALSE);
    
    nor_gate.setLink(1, false_input, 1);
    nor_gate.setLink(2, false_input, 1);
    cr_assert_eq(nor_gate.compute(3), TRUE);
    
    nor_gate.setLink(1, undefined_input, 1);
    nor_gate.setLink(2, true_input, 1);
    cr_assert_eq(nor_gate.compute(3), FALSE);
    
    nor_gate.setLink(1, undefined_input, 1);
    nor_gate.setLink(2, false_input, 1);
    cr_assert_eq(nor_gate.compute(3), UNDEFINED);
}

Test(NORGateTests, SecondGateCompute, .init = redirect_all_stdout)
{
    NORGate nor_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    nor_gate.setLink(5, true_input, 1);
    nor_gate.setLink(6, true_input, 1);
    cr_assert_eq(nor_gate.compute(4), FALSE);
    
    nor_gate.setLink(5, false_input, 1);
    nor_gate.setLink(6, false_input, 1);
    cr_assert_eq(nor_gate.compute(4), TRUE);
    
    nor_gate.setLink(5, undefined_input, 1);
    nor_gate.setLink(6, false_input, 1);
    cr_assert_eq(nor_gate.compute(4), UNDEFINED);
}

Test(NORGateTests, ThirdGateCompute, .init = redirect_all_stdout)
{
    NORGate nor_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    nor_gate.setLink(8, true_input, 1);
    nor_gate.setLink(9, false_input, 1);
    cr_assert_eq(nor_gate.compute(10), FALSE);
    
    nor_gate.setLink(8, false_input, 1);
    nor_gate.setLink(9, false_input, 1);
    cr_assert_eq(nor_gate.compute(10), TRUE);
    
    nor_gate.setLink(8, undefined_input, 1);
    nor_gate.setLink(9, false_input, 1);
    cr_assert_eq(nor_gate.compute(10), UNDEFINED);
}

Test(NORGateTests, FourthGateCompute, .init = redirect_all_stdout)
{
    NORGate nor_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;
    
    nor_gate.setLink(12, true_input, 1);
    nor_gate.setLink(13, false_input, 1);
    cr_assert_eq(nor_gate.compute(11), FALSE);
    
    nor_gate.setLink(12, false_input, 1);
    nor_gate.setLink(13, false_input, 1);
    cr_assert_eq(nor_gate.compute(11), TRUE);
    
    nor_gate.setLink(12, undefined_input, 1);
    nor_gate.setLink(13, false_input, 1);
    cr_assert_eq(nor_gate.compute(11), UNDEFINED);
}

Test(NORGateTests, InputPinCompute, .init = redirect_all_stdout)
{
    NORGate nor_gate;
    TrueComponent true_input;
    FalseComponent false_input;
    InputComponent undefined_input;

    nor_gate.setLink(13, true_input, 1);
    cr_assert_eq(nor_gate.compute(13), TRUE);
}

Test(NORGateTests, InvalidPins, .init = redirect_all_stdout)
{
    NORGate nor_gate;
    
    try {
        nor_gate.compute(7);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found");
    }
    
    try {
        nor_gate.compute(14);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found");
    }
}

Test(NORGateTests, ConstructorPinInitialization, .init = redirect_all_stdout)
{
    NORGate nor_gate;
    auto pins = nor_gate.getPins();
    
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

Test(NORGateTests, OneInputIsNotLinkedInFirstGate, .init = redirect_all_stdout)
{
    NORGate nor_gate1;
    NORGate nor_gate2;
    TrueComponent input;
    TrueComponent input2;

    input.setLink(1, nor_gate1, 1);
    cr_assert_eq(nor_gate1.compute(1), TRUE);
    cr_assert_eq(nor_gate1.compute(2), UNDEFINED);
    cr_assert_eq(nor_gate1.compute(3), FALSE);

    input2.setLink(1, nor_gate2, 2);
    cr_assert_eq(nor_gate2.compute(1), UNDEFINED);
    cr_assert_eq(nor_gate2.compute(2), TRUE);
    cr_assert_eq(nor_gate2.compute(3), FALSE);
}

Test(NORGateTests, OneInputIsNotLinkedInSecondGate, .init = redirect_all_stdout)
{
    NORGate nor_gate1;
    NORGate nor_gate2;
    TrueComponent input;
    TrueComponent input2;

    input.setLink(1, nor_gate1, 5);
    cr_assert_eq(nor_gate1.compute(5), TRUE);
    cr_assert_eq(nor_gate1.compute(6), UNDEFINED);
    cr_assert_eq(nor_gate1.compute(4), FALSE);

    input2.setLink(1, nor_gate2, 6);
    cr_assert_eq(nor_gate2.compute(5), UNDEFINED);
    cr_assert_eq(nor_gate2.compute(6), TRUE);
    cr_assert_eq(nor_gate2.compute(4), FALSE);
}

Test(NORGateTests, OneInputIsNotLinkedInThirdGate, .init = redirect_all_stdout)
{
    NORGate nor_gate1;
    NORGate nor_gate2;
    TrueComponent input;
    TrueComponent input2;

    input.setLink(1, nor_gate1, 8);
    cr_assert_eq(nor_gate1.compute(8), TRUE);
    cr_assert_eq(nor_gate1.compute(9), UNDEFINED);
    cr_assert_eq(nor_gate1.compute(10), FALSE);

    input2.setLink(1, nor_gate2, 9);
    cr_assert_eq(nor_gate2.compute(8), UNDEFINED);
    cr_assert_eq(nor_gate2.compute(9), TRUE);
    cr_assert_eq(nor_gate2.compute(10), FALSE);
}

Test(NORGateTests, OneInputIsNotLinkedInFourthGate, .init = redirect_all_stdout)
{
    NORGate nor_gate1;
    NORGate nor_gate2;
    TrueComponent input;
    TrueComponent input2;

    input.setLink(1, nor_gate1, 12);
    cr_assert_eq(nor_gate1.compute(12), TRUE);
    cr_assert_eq(nor_gate1.compute(13), UNDEFINED);
    cr_assert_eq(nor_gate1.compute(11), FALSE);

    input2.setLink(1, nor_gate2, 13);
    cr_assert_eq(nor_gate2.compute(12), UNDEFINED);
    cr_assert_eq(nor_gate2.compute(13), TRUE);
    cr_assert_eq(nor_gate2.compute(11), FALSE);
}

Test(NORGateTests, FlipFlopRSFalseFalse)
{
    NORGate g_nor;
    InputComponent s;
    InputComponent r;

    g_nor.setLink(1, s, 1);
    g_nor.setLink(5, r, 1);
    g_nor.setLink(2, g_nor, 4);
    g_nor.setLink(6, g_nor, 3);

    s.setValue(FALSE);
    r.setValue(FALSE);
    s.simulate(1);
    r.simulate(1);

    cr_assert_eq(g_nor.compute(3), UNDEFINED);
    cr_assert_eq(g_nor.compute(4), UNDEFINED);
}

Test(NORGateTests, FlipFlopRSFalseTrue)
{
    NORGate g_nor;
    InputComponent s;
    InputComponent r;

    g_nor.setLink(1, s, 1);
    g_nor.setLink(5, r, 1);
    g_nor.setLink(2, g_nor, 4);
    g_nor.setLink(6, g_nor, 3);

    s.setValue(FALSE);
    r.setValue(TRUE);
    s.simulate(1);
    r.simulate(1);
    cr_assert_eq(g_nor.compute(3), FALSE);
    cr_assert_eq(g_nor.compute(4), TRUE);
}

Test(NORGateTests, FlipFlopRSTrueFalse)
{
    NORGate g_nor;
    InputComponent s;
    InputComponent r;

    g_nor.setLink(1, s, 1);
    g_nor.setLink(5, r, 1);
    g_nor.setLink(2, g_nor, 4);
    g_nor.setLink(6, g_nor, 3);

    s.setValue(TRUE);
    r.setValue(FALSE);
    s.simulate(1);
    r.simulate(1);
    cr_assert_eq(g_nor.compute(3), UNDEFINED);
    cr_assert_eq(g_nor.compute(4), UNDEFINED);
}

Test(NORGateTests, FlipFlopRSTrueTrue)
{
    NORGate g_nor;
    InputComponent s;
    InputComponent r;

    g_nor.setLink(1, s, 1);
    g_nor.setLink(5, r, 1);
    g_nor.setLink(2, g_nor, 4);
    g_nor.setLink(6, g_nor, 3);

    s.setValue(TRUE);
    r.setValue(TRUE);
    s.simulate(1);
    r.simulate(1);
    cr_assert_eq(g_nor.compute(3), UNDEFINED);
    cr_assert_eq(g_nor.compute(4), UNDEFINED);
}
