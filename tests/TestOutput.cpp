#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Special/OutputComponent.hpp"
#include "../Special/TrueComponent.hpp"
#include "../Special/FalseComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(OutputComponentTests, InitialState, .init = redirect_all_stdout)
{
    OutputComponent output;
    cr_assert_eq(output.compute(1), UNDEFINED, "Output must be initialized to UNDEFINED");
}

Test(OutputComponentTests, ComputeWithoutLink, .init = redirect_all_stdout)
{
    OutputComponent output;
    cr_assert_eq(output.compute(1), UNDEFINED, "Output without link must return UNDEFINED");
}

Test(OutputComponentTests, ComputeWithTrueComponent, .init = redirect_all_stdout)
{
    OutputComponent output;
    TrueComponent trueComp;
    
    output.setLink(1, trueComp, 1);
    cr_assert_eq(output.compute(1), TRUE, "Output linked to TRUE component must return TRUE");
}

Test(OutputComponentTests, ComputeWithFalseComponent, .init = redirect_all_stdout)
{
    OutputComponent output;
    FalseComponent falseComp;
    
    output.setLink(1, falseComp, 1);
    cr_assert_eq(output.compute(1), FALSE, "Output linked to FALSE component must return FALSE");
}

Test(OutputComponentTests, ComputeInvalidPin, .init = redirect_all_stdout)
{
    OutputComponent output;
    cr_assert_any_throw(output.compute(999), "Computing an invalid pin should throw an exception");
}

Test(OutputComponentTests, ComputeInvalidPin2, .init = redirect_all_stdout)
{
    OutputComponent output;
    try {
        output.compute(2);
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Pin not found", "Exception message should be 'Pin not found' when computing a wrong pin");
    }
}
