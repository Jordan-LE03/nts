#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <criterion/redirect.h>
#include <fstream>
#include "../Advanced/LoggerComponent.hpp"
#include "../Special/TrueComponent.hpp"
#include "../Special/FalseComponent.hpp"
#include "../Special/ClockComponent.hpp"
#include "../Special/InputComponent.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(LoggerComponentTest, InitialState, .init = redirect_all_stdout)
{
    LoggerComponent logger;

    for (int pin = 1; pin <= 10; pin++) {
        cr_assert_eq(logger.compute(pin), UNDEFINED, "Pins must be UNDEFINED at creation.");
    }
}

Test(LoggerComponentTest, basicWorkingLoggerComponent, .init = redirect_all_stdout)
{
    LoggerComponent logger;
    TrueComponent in_001;
    TrueComponent in_002;
    TrueComponent in_004;
    TrueComponent in_008;
    TrueComponent in_016;
    TrueComponent in_032;
    TrueComponent in_064;
    TrueComponent in_128;
    ClockComponent clock;
    FalseComponent inhibit;
    
    in_001.setLink(1, logger, 1);
    in_002.setLink(1, logger, 2);
    in_004.setLink(1, logger, 3);
    in_008.setLink(1, logger, 4);
    in_016.setLink(1, logger, 5);
    in_032.setLink(1, logger, 6);
    in_064.setLink(1, logger, 7);
    in_128.setLink(1, logger, 8);
    clock.setLink(1, logger, 9);
    inhibit.setLink(1, logger, 10);

    clock.setValue(nts::FALSE);
    clock.simulate(1);
    logger.simulate(1);
    clock.simulate(1);
    logger.simulate(1);

    std::ifstream file("./log.bin", std::ios::binary);

    cr_assert(file, "ERROR: file log.bin not found but should be present.");

    std::vector<unsigned char> content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    cr_assert(!content.empty(), "ERROR: log.bin is empty, expected data.");

    unsigned char lastChar = content.back();
    cr_assert_eq(lastChar, 255, "The last char in the log.bin file must be 255.");
}

Test(LoggerComponentTest, checkStringInLogFile, .init = redirect_all_stdout)
{
    LoggerComponent logger;
    InputComponent input;
    TrueComponent input2;
    InputComponent input3;
    FalseComponent inhibit;
    ClockComponent clock;

    input.setValue(TRUE);
    clock.setValue(FALSE);

    input.simulate(1);

    inhibit.setLink(1, logger, 10);
    input.setLink(1, logger, 1);
    input2.setLink(1, logger, 7);
    input3.setLink(1, logger, 2);
    clock.setLink(1, logger, 9);

    for (unsigned int simulation = 1; simulation <= 10; simulation++) {
        clock.simulate(1);
        logger.simulate(1);
    }

    input.setValue(FALSE);
    input3.setValue(TRUE);

    input.simulate(1);
    input3.simulate(1);

    for (unsigned int simulation = 1; simulation <= 10; simulation++) {
        clock.simulate(1);
        logger.simulate(1);
    }

    std::ifstream file("./log.bin", std::ios::binary);
    cr_assert(file, "ERROR: file log.bin not found but should be present.");

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    cr_assert(!content.empty(), "ERROR: log.bin is empty, expected data.");

    std::string expectedSubstring = "AAAAA";
    cr_assert(content.find(expectedSubstring) != std::string::npos, "Expected string 'AAAAA' not found in log.bin.");

    std::string expectedSubstring2 = "BBBBB";
    cr_assert(content.find(expectedSubstring2) != std::string::npos, "Expected string 'BBBBB' not found in log.bin.");
}
