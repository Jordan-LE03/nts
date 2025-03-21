#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Special/InputComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(InputComponentTests, InitialState, .init = redirect_all_stdout)
{
    InputComponent input;
    cr_assert_eq(input.compute(1), UNDEFINED, "Input must be initialized to UNDEFINED");
}

Test(InputComponentTests, SetValueWithoutSimulation, .init = redirect_all_stdout)
{
    InputComponent input;

    input.setValue(UNDEFINED);
    cr_assert_eq(input.compute(1), UNDEFINED, "After setValue(UNDEFINED), compute() must return UNDEFINED without simulation");

    input.setValue(TRUE);
    cr_assert_eq(input.compute(1), UNDEFINED, "After setValue(TRUE), compute() must return UNDEFINED without simulation");
    
    input.setValue(FALSE);
    cr_assert_eq(input.compute(1), UNDEFINED, "After setValue(FALSE), compute() must return UNDEFINED without simulation");
}

Test(InputComponentTests, SetValueWithSimulation, .init = redirect_all_stdout)
{
    InputComponent input;
    
    input.setValue(UNDEFINED);
    input.simulate(1);
    cr_assert_eq(input.compute(1), UNDEFINED, "After setValue(UNDEFINED) & simulation, compute() must be UNDEFINED");

    input.setValue(TRUE);
    input.simulate(1);
    cr_assert_eq(input.compute(1), TRUE, "After setValue(TRUE) & simulation, compute() must be TRUE");

    input.setValue(FALSE);
    input.simulate(1);
    cr_assert_eq(input.compute(1), FALSE, "After setValue(FALSE) & simulation, compute() must be FALSE");
}

Test(InputComponentTests, SimulationWithoutSetValue, .init = redirect_all_stdout)
{
    InputComponent input;
    input.simulate(1);
    cr_assert_eq(input.compute(1), UNDEFINED, "Without setValue() & simulation, compute() must be UNDEFINED");
}

Test(InputComponentTests, ComputeInvalidPin, .init = redirect_all_stdout)
{
    InputComponent input;
    cr_assert_any_throw(input.compute(999), "Computing an invalid pin should throw an exception");
}

Test(InputComponentTests, ComputeInvalidPin2, .init = redirect_all_stdout)
{
    InputComponent input;
    try {
        input.compute(2);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found", "Exception message should be 'Pin not found' when computing a wrong pin");
    }
}
