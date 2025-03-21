#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Component.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(CircuitTests, CreateBasicComponents, .init = redirect_all_stdout)
{
    Circuit circuit;

    auto input = circuit.createComponent("input");
    cr_assert_not_null(input.get());

    auto output = circuit.createComponent("output");
    cr_assert_not_null(output.get());

    auto clock = circuit.createComponent("clock");
    cr_assert_not_null(clock.get());

    auto true_comp = circuit.createComponent("true");
    cr_assert_not_null(true_comp.get());

    auto false_comp = circuit.createComponent("false");
    cr_assert_not_null(false_comp.get());
}

Test(CircuitTests, CreateLogicGates, .init = redirect_all_stdout)
{
    Circuit circuit;

    auto and_gate = circuit.createComponent("and");
    cr_assert_not_null(and_gate.get());

    auto or_gate = circuit.createComponent("or");
    cr_assert_not_null(or_gate.get());

    auto xor_gate = circuit.createComponent("xor");
    cr_assert_not_null(xor_gate.get());

    auto not_gate = circuit.createComponent("not");
    cr_assert_not_null(not_gate.get());
}

Test(CircuitTests, Create4000Series, .init = redirect_all_stdout)
{
    Circuit circuit;

    auto c4001 = circuit.createComponent("4001");
    cr_assert_not_null(c4001.get());

    auto c4011 = circuit.createComponent("4011");
    cr_assert_not_null(c4011.get());

    auto c4030 = circuit.createComponent("4030");
    cr_assert_not_null(c4030.get());

    auto c4069 = circuit.createComponent("4069");
    cr_assert_not_null(c4069.get());

    auto c4071 = circuit.createComponent("4071");
    cr_assert_not_null(c4071.get());

    auto c4081 = circuit.createComponent("4081");
    cr_assert_not_null(c4081.get());
}

Test(CircuitTests, InvalidComponent, .init = redirect_all_stdout)
{
    Circuit circuit;

    try {
        auto invalid = circuit.createComponent("invalid");
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception &e) {
        cr_assert_str_eq(e.what(), "Component not found: invalid");
    }
}

Test(CircuitTests, GetComponents, .init = redirect_all_stdout)
{
    Circuit circuit;
    auto &components = circuit.getComponents();
    
    cr_assert_eq(components.size(), 0, "Initial components map should be empty");
    
    components["input"] = circuit.createComponent("input");
    cr_assert_eq(components.size(), 1, "Components map should have one element");
    cr_assert_not_null(components["input"].get());
}
