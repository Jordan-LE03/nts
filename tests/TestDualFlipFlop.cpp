#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <criterion/redirect.h>
#include <cstdio>

#include "../Advanced/DualFlipFlop.hpp"
#include "../AllComponents.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}


Test(DualFlipFlopTests, InitialState, .init=redirect_all_stdout)
{
    DualFlipFlop d;
    for (unsigned int pin = 1; pin <= 13; pin++) {
        if (pin == 7)
            continue;
        cr_assert_eq(d.compute(pin), UNDEFINED, "Pins must be UNDEFINED at creation.");
    }
}

Test(DualFlipFlopTests, BasicTestFirstFlipFlop)
{
    DualFlipFlop dflipflop;
    ClockComponent c;
    InputComponent d;
    InputComponent r;
    InputComponent s;
    OutputComponent q1;
    OutputComponent q2;

    c.setValue(FALSE);
    d.setValue(FALSE);
    r.setValue(FALSE);
    s.setValue(FALSE);

    d.simulate(1);
    r.simulate(1);
    s.simulate(1);

    dflipflop.setLink(1, q1, 1);
    dflipflop.setLink(2, q2, 1);
    dflipflop.setLink(3, c, 1);
    dflipflop.setLink(4, r, 1);
    dflipflop.setLink(5, d, 1);
    dflipflop.setLink(6, s, 1);

    dflipflop.simulate(1);
    c.simulate(1);
    c.simulate(1);
    dflipflop.simulate(1);

    cr_assert_eq(dflipflop.compute(3), TRUE);
    cr_assert_eq(dflipflop.compute(4), FALSE);
    cr_assert_eq(dflipflop.compute(5), FALSE);
    cr_assert_eq(dflipflop.compute(6), FALSE);
    cr_assert_eq(dflipflop.compute(1), FALSE);
    cr_assert_eq(dflipflop.compute(2), TRUE);
}
