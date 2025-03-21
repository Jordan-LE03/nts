#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Special/FalseComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(FalseComponentTests, InitialState, .init = redirect_all_stdout)
{
    FalseComponent falseComp;
    cr_assert_eq(falseComp.compute(1), FALSE, "False component must be initialized to FALSE");
}

Test(FalseComponentTests, ComputeAlwaysFalse, .init = redirect_all_stdout)
{
    FalseComponent falseComp;
    falseComp.simulate(1);
    cr_assert_eq(falseComp.compute(1), FALSE, "False component must always return FALSE after simulation");
    
    falseComp.simulate(2);
    cr_assert_eq(falseComp.compute(1), FALSE, "False component must always return FALSE after multiple simulations");
}

Test(FalseComponentTests, ComputeInvalidPin, .init = redirect_all_stdout)
{
    FalseComponent falseComp;
    cr_assert_any_throw(falseComp.compute(999), "Computing an invalid pin should throw an exception");
}

Test(FalseComponentTests, ComputeInvalidPin2, .init = redirect_all_stdout)
{
    FalseComponent falseComp;
    try {
        falseComp.compute(2);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found", "Exception message should be 'Pin not found' when computing a wrong pin");
    }
}
