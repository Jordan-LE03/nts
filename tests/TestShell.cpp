#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "../Shell/Shell.hpp"
#include "../Special/InputComponent.hpp"
#include "../Special/OutputComponent.hpp"
#include "../Special/ClockComponent.hpp"
#include <thread>
#include <chrono>
#include <signal.h>
#include <unistd.h>

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(ShellTests, DisplayCommand, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;

    components["input1"] = std::make_unique<InputComponent>();
    components["output1"] = std::make_unique<OutputComponent>();
    components["clock1"] = std::make_unique<ClockComponent>();
    Shell shell (components);

    shell.executeCommand("display");

    std::string expected = "tick: 0\ninput(s):\n  clock1: U\n  input1: U\noutput(s):\n  output1: U\n";

    cr_assert_stdout_eq_str(expected.c_str());
}

Test(ShellTests, DisplayCommandAfterSetValue, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;

    components["input1"] = std::make_unique<InputComponent>();
    components["output1"] = std::make_unique<OutputComponent>();
    components["clock1"] = std::make_unique<ClockComponent>();
    auto *clock = dynamic_cast<ClockComponent *>(components["clock1"].get());
    auto *output = dynamic_cast<OutputComponent *>(components["output1"].get());

    clock->setLink(1, *output, 1);
    Shell shell (components);

    shell.executeCommand("input1=0");
    shell.executeCommand("clock1=1");
    shell.executeCommand("simulate");
    shell.executeCommand("display");

    std::string expected = "tick: 1\ninput(s):\n  clock1: 1\n  input1: 0\noutput(s):\n  output1: 1\n";

    cr_assert_stdout_eq_str(expected.c_str());
}

Test(ShellTests, SimulateCommand, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;

    components["input1"] = std::make_unique<InputComponent>();
    components["clock1"] = std::make_unique<ClockComponent>();

    Shell shell (components);

    auto *input = dynamic_cast<InputComponent*>(components["input1"].get());
    auto *clock = dynamic_cast<ClockComponent*>(components["clock1"].get());

    input->setValue(TRUE);
    clock->setValue(TRUE);

    shell.executeCommand("simulate");

    cr_assert_eq(shell.getTick(), 1);
}

Test(ShellTests, SetInputValue, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;

    components["input1"] = std::make_unique<InputComponent>();
    Shell shell (components);
    auto *input = dynamic_cast<InputComponent*>(components["input1"].get());

    shell.executeCommand("input1=1");
    cr_assert_eq(input->compute(), UNDEFINED);
    shell.executeCommand("simulate");
    cr_assert_eq(input->compute(), TRUE);

    shell.executeCommand("input1=0");
    cr_assert_eq(input->compute(), TRUE);
    shell.executeCommand("simulate");
    cr_assert_eq(input->compute(), FALSE);

    shell.executeCommand("input1=U");
    cr_assert_eq(input->compute(), FALSE);
    shell.executeCommand("simulate");
    cr_assert_eq(input->compute(), UNDEFINED);
}

Test(ShellTests, SetClockValue, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;

    components["clock1"] = std::make_unique<ClockComponent>();
    auto *clock = dynamic_cast<ClockComponent*>(components["clock1"].get());
    Shell shell (components);

    shell.executeCommand("clock1=1");
    shell.executeCommand("simulate");
    cr_assert_eq(clock->compute(), TRUE);

    shell.executeCommand("clock1=0");
    shell.executeCommand("simulate");
    cr_assert_eq(clock->compute(), FALSE);

    shell.executeCommand("clock1=U");
    shell.executeCommand("simulate");
    cr_assert_eq(clock->compute(), UNDEFINED);
}

Test(ShellTests, SetTooLowValue, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;
    auto *clock = dynamic_cast<ClockComponent*>(components["clock1"].get());
    Shell shell (components);

    shell.executeCommand("clock1=-5");
    cr_assert_stderr_eq_str("Invalid value: -5\n");
}

Test(ShellTests, SetTooHighValue, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;
    auto *clock = dynamic_cast<ClockComponent*>(components["clock1"].get());
    Shell shell (components);

    shell.executeCommand("clock1=5");
    cr_assert_stderr_eq_str("Invalid value: 5\n");
}

Test(ShellTests, SetInvalidValue, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;
    auto *clock = dynamic_cast<ClockComponent*>(components["clock1"].get());
    Shell shell (components);

    shell.executeCommand("clock1=abc");
    cr_assert_stderr_eq_str("Invalid value: abc\n");
}

Test(ShellTests, InvalidCommand, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;
    Shell shell (components);

    shell.executeCommand("invalid");
    cr_assert_stderr_eq_str("Unknow command: invalid\n");
}

Test(ShellTests, InvalidComponent, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;
    Shell shell (components);

    shell.executeCommand("nonexistent=1");
    cr_assert_stderr_eq_str("Unknow component name: nonexistent\n");
}

Test(ShellTests, EmptyCommand, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;
    Shell shell (components);

    shell.executeCommand("");
    shell.executeCommand("   ");
    shell.executeCommand("\t");

    cr_assert_stdout_eq_str("");
}

Test(ShellTests, ExitCommand, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;
    Shell shell (components);

    bool result = shell.executeCommand("exit");
    cr_assert_eq(result, false);
}

Test(ShellTests, RunCommand, .init = redirect_all_stdout)
{
    std::stringstream input;
    input << "display\nexit\n";
    std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

    std::map<std::string, std::unique_ptr<IComponent>> components;
    components["input1"] = std::make_unique<InputComponent>();
    components["output1"] = std::make_unique<OutputComponent>();
    Shell shell(components);

    shell.run();

    std::cin.rdbuf(oldCin);

    std::string expected = "> tick: 0\ninput(s):\n  input1: U\noutput(s):\n  output1: U\n> ";
    cr_assert_stdout_eq_str(expected.c_str());
}

Test(ShellTests, RunCommandWithEOF, .init = redirect_all_stdout)
{
    std::stringstream input;
    input << "display" << (char)EOF;
    std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

    std::map<std::string, std::unique_ptr<IComponent>> components;
    components["input1"] = std::make_unique<InputComponent>();
    Shell shell(components);

    shell.run();

    std::cin.rdbuf(oldCin);

    std::string expected = "> ";
    cr_assert_stdout_eq_str(expected.c_str());
}

Test(ShellTests, LoopCommand, .init = redirect_all_stdout)
{
    std::map<std::string, std::unique_ptr<IComponent>> components;
    components["input1"] = std::make_unique<InputComponent>();
    components["output1"] = std::make_unique<OutputComponent>();
    Shell shell(components);

    std::thread sigintThread([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        kill(getpid(), SIGINT);
    });

    shell.executeCommand("loop");
    
    sigintThread.join();

    std::string expected = "tick: 1\ninput(s):\n  input1: U\noutput(s):\n  output1: U\n\n";
    cr_assert_stdout_eq_str(expected.c_str());
}
