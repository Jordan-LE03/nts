#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Special/ClockComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ClockComponentTests, InitialState, .init = redirect_all_stdout) {
    ClockComponent clock;
    cr_assert_eq(clock.compute(), UNDEFINED, "Clock must be initialised to UNDEFINED");
}

Test(ClockComponentTests, SetValueWithoutSimulation, .init = redirect_all_stdout) {
    ClockComponent clock;

    clock.setValue(UNDEFINED);
    cr_assert_eq(clock.compute(), UNDEFINED, "After setValue(UNDEFINED), compute() must return UNDEFINED without simulation");

    clock.setValue(TRUE);
    cr_assert_eq(clock.compute(), UNDEFINED, "After setValue(TRUE), compute() must return UNDEFINED without simulation");
    
    clock.setValue(FALSE);
    cr_assert_eq(clock.compute(), UNDEFINED, "After setValue(FALSE), compute() must return UNDEFINED without simulation");
}

Test(ClockComponentTests, SetValueWithSimulation, .init = redirect_all_stdout) {
    ClockComponent clock;
    clock.setValue(UNDEFINED);
    clock.simulate(1);
    cr_assert_eq(clock.compute(), UNDEFINED, "After setValue(UNDEFINED) & simulation, compute() must be UNDEFINED");

    clock.setValue(TRUE);
    clock.simulate(1);
    cr_assert_eq(clock.compute(), TRUE, "After setValue(TRUE) & simulation, compute() must be TRUE");

    clock.setValue(FALSE);
    clock.simulate(1);
    cr_assert_eq(clock.compute(), FALSE, "After setValue(FALSE) & simulation, compute() must be FALSE");
}

Test(ClockComponentTests, SimulationWithoutSetValue, .init = redirect_all_stdout) {
    ClockComponent clock;
    clock.simulate(1);
    cr_assert_eq(clock.compute(), UNDEFINED, "Without setValue() & simulation, compute() must be UNDEFINED");
}

Test(ClockComponentTests, ComputeInvalidPin, .init = redirect_all_stdout) {
    ClockComponent clock;
    cr_assert_any_throw(clock.compute(999), "Computing an invalid pin should throw an exception");
}

Test(ClockComponentTests, ComputeInvalidPin2, .init = redirect_all_stdout) {
    ClockComponent clock;
    try {
        clock.compute(2);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found", "Exception message should be 'Pin not found' when computing a wrong pin");
    }
}
