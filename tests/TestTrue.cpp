#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Special/TrueComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(TrueComponentTests, InitialState, .init = redirect_all_stdout)
{
    TrueComponent trueComp;
    cr_assert_eq(trueComp.compute(1), TRUE, "True component must be initialized to TRUE");
}

Test(TrueComponentTests, ComputeAlwaysTrue, .init = redirect_all_stdout)
{
    TrueComponent trueComp;
    trueComp.simulate(1);
    cr_assert_eq(trueComp.compute(1), TRUE, "True component must always return TRUE after simulation");
    
    trueComp.simulate(2);
    cr_assert_eq(trueComp.compute(1), TRUE, "True component must always return TRUE after multiple simulations");
}

Test(TrueComponentTests, ComputeInvalidPin, .init = redirect_all_stdout)
{
    TrueComponent trueComp;
    cr_assert_any_throw(trueComp.compute(999), "Computing an invalid pin should throw an exception");
}

Test(TrueComponentTests, ComputeInvalidPin2, .init = redirect_all_stdout)
{
    TrueComponent trueComp;
    try {
        trueComp.compute(2);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found", "Exception message should be 'Pin not found' when computing a wrong pin");
    }
}
