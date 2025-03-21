#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <fstream>
#include "../Parsing/Parser.hpp"
#include "../Component.hpp"

using namespace nts;

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static void createValidFile(const std::string& filename)
{
    std::ofstream file(filename);
    file << ".chipsets:\n";
    file << "input i0\n";
    file << "input i1\n";
    file << "input i2\n";
    file << "\n";
    file << "4081 and0\n";
    file << "output out\n";
    file << "\n";
    file << ".links:\n";
    file << "i0:1 and0:1\n";
    file << "i1:1 and0:2\n";
    file << "and0:3 and0:5\n";
    file << "\n";
    file << "i2:1 and0:6\n";
    file << "and0:4 out:1\n";
    file.close();
}

static void createFileWithComments(const std::string& filename)
{
    std::ofstream file(filename);
    file << "# This is a comment\n";
    file << ".chipsets: # Section chipsets\n";
    file << "input i0 # First input\n";
    file << "# Comment between lines\n";
    file << "input i1\n";
    file << ".links:\n";
    file << "# Another comment between lines\n";
    file << "i0:1 i1:1 # Link between inputs\n";
    file.close();
}

static void createInvalidFile(const std::string& filename)
{
    std::ofstream file(filename);
    file << ".chipsets:\n";
    file << "invalid_type comp1\n";
    file.close();
}

Test(ParserTests, ValidFile, .init = redirect_all_stdout)
{
    Circuit circuit;
    createValidFile("test_valid.nts");
    Parser parser(circuit, "test_valid.nts");
    
    parser.parse();
    auto& components = circuit.getComponents();
    
    cr_assert_eq(components.size(), 5);
    cr_assert(components.find("i0") != components.end());
    cr_assert(components.find("i1") != components.end());
    cr_assert(components.find("i2") != components.end());
    cr_assert(components.find("and0") != components.end());
    cr_assert(components.find("out") != components.end());
    
    remove("test_valid.nts");
}

Test(ParserTests, FileWithComments, .init = redirect_all_stdout)
{
    Circuit circuit;
    createFileWithComments("test_comments.nts");
    Parser parser(circuit, "test_comments.nts");
    
    parser.parse();
    auto& components = circuit.getComponents();
    
    cr_assert_eq(components.size(), 2);
    cr_assert(components.find("i0") != components.end());
    cr_assert(components.find("i1") != components.end());
    
    remove("test_comments.nts");
}

Test(ParserTests, InvalidComponentType, .init = redirect_all_stdout)
{
    Circuit circuit;
    createInvalidFile("test_invalid.nts");
    Parser parser(circuit, "test_invalid.nts");
    
    try {
        parser.parse();
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception& e) {
        cr_assert_str_eq(e.what(), "Component not found: invalid_type");
    }
    
    remove("test_invalid.nts");
}

Test(ParserTests, FileNotFound, .init = redirect_all_stdout)
{
    Circuit circuit;
    Parser parser(circuit, "nonexistent.nts");
    
    try {
        parser.parse();
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception& e) {
        cr_assert_str_eq(e.what(), "File not found: nonexistent.nts");
    }
}

Test(ParserTests, DuplicateComponentName, .init = redirect_all_stdout)
{
    std::ofstream file("test_duplicate.nts");
    file << ".chipsets:\n";
    file << "input i0\n";
    file << "input i0\n";
    file.close();
    
    Circuit circuit;
    Parser parser(circuit, "test_duplicate.nts");
    
    try {
        parser.parse();
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception& e) {
        cr_assert_str_eq(e.what(), "Parsing error: Name already exists 'i0'");
    }
    
    remove("test_duplicate.nts");
}

Test(ParserTests, InvalidLinkPin1Value, .init = redirect_all_stdout)
{
    std::ofstream file("test_invalid_pin1.nts");
    file << ".chipsets:\n";
    file << "input i0\n";
    file << "input i1\n";
    file << ".links:\n";
    file << "i0:abc i1:1\n";
    file.close();
    
    Circuit circuit;
    Parser parser(circuit, "test_invalid_pin1.nts");
    
    try {
        parser.parse();
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception& e) {
        cr_assert_str_eq(e.what(), "Parsing error: Invalid pin value for 'i0'");
    }
    
    remove("test_invalid_pin1.nts");
}

Test(ParserTests, InvalidLinkPin2Value, .init = redirect_all_stdout)
{
    std::ofstream file("test_invalid_pin2.nts");
    file << ".chipsets:\n";
    file << "input i0\n";
    file << "input i1\n";
    file << ".links:\n";
    file << "i0:1 i1:abc\n";
    file.close();
    
    Circuit circuit;
    Parser parser(circuit, "test_invalid_pin2.nts");
    
    try {
        parser.parse();
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception& e) {
        cr_assert_str_eq(e.what(), "Parsing error: Invalid pin value for 'i1'");
    }
    
    remove("test_invalid_pin2.nts");
}

Test(ParserTests, InvalidLinkPin2Value2, .init = redirect_all_stdout)
{
    std::ofstream file("test_invalid_pin3.nts");
    file << ".chipsets:\n";
    file << "input i0\n";
    file << "input i1\n";
    file << ".links:\n";
    file << "i0:1 i1:5\n";
    file.close();
    
    Circuit circuit;
    Parser parser(circuit, "test_invalid_pin3.nts");
    
    try {
        parser.parse();
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception& e) {
        cr_assert_str_eq(e.what(), "Pin not found");
    }
    
    remove("test_invalid_pin3.nts");
}

Test(ParserTests, UnknownComponentInLinks, .init = redirect_all_stdout)
{
    std::ofstream file("test_unknown.nts");
    file << ".chipsets:\n";
    file << "input i0\n";
    file << ".links:\n";
    file << "i0:1 unknown:1\n";
    file.close();
    
    Circuit circuit;
    Parser parser(circuit, "test_unknown.nts");
    
    try {
        parser.parse();
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception& e) {
        cr_assert_str_eq(e.what(), "Parsing error: Unknow component name 'unknown'");
    }
    
    remove("test_unknown.nts");
}

Test(ParserTests, ChipsetWithoutName, .init = redirect_all_stdout)
{
    std::ofstream file("test_no_name.nts");
    file << ".chipsets:\n";
    file << "input\n";  // Type without name
    file.close();
    
    Circuit circuit;
    Parser parser(circuit, "test_no_name.nts");
    
    try {
        parser.parse();
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception& e) {
        cr_assert_str_eq(e.what(), "Parsing error: Missing name for 'input'");
    }
    
    remove("test_no_name.nts");
}

Test(ParserTests, NonExistentComponentInLinks, .init = redirect_all_stdout)
{
    std::ofstream file("test_nonexistent_link.nts");
    file << ".chipsets:\n";
    file << "input in1\n";
    file << ".links:\n";
    file << "nonexistent:1 in1:1\n";
    file.close();
    
    Circuit circuit;
    Parser parser(circuit, "test_nonexistent_link.nts");
    
    try {
        parser.parse();
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception& e) {
        cr_assert_str_eq(e.what(), "Parsing error: Unknow component name 'nonexistent'");
    }
    
    remove("test_nonexistent_link.nts");
}

Test(ParserTests, MissingSecondComponentInLinks, .init = redirect_all_stdout)
{
    std::ofstream file("test_missingsecondcomponent_link.nts");
    file << ".chipsets:\n";
    file << "input in1\n";
    file << "output out1\n";
    file << ".links:\n";
    file << "in1:1\n";
    file << "in1:1 out1:1\n";
    file.close();
    
    Circuit circuit;
    Parser parser(circuit, "test_missingsecondcomponent_link.nts");
    
    try {
        parser.parse();
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception& e) {
        cr_assert_str_eq(e.what(), "Parsing error: Missing target to link with 'in1'");
    }
    
    remove("test_missingsecondcomponent_link.nts");
}

Test(ParserTests, InvalidTest, .init = redirect_all_stdout)
{
    std::ofstream file("test_invalidtext.nts");
    file << "InvalidText\n";
    file << ".chipsets:\n";
    file << "input in1\n";
    file << "output out1\n";
    file << ".links:\n";
    file << "in1:1\n";
    file << "in1:1 out1:1\n";
    file.close();
    
    Circuit circuit;
    Parser parser(circuit, "test_invalidtext.nts");
    
    try {
        parser.parse();
        cr_assert_fail("Expected exception not thrown");
    } catch (const std::exception& e) {
        cr_assert_str_eq(e.what(), "Parsing error: Unknow instruction 'InvalidText'");
    }
    
    remove("test_invalidtext.nts");
}
