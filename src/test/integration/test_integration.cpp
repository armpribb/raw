#include <gtest/gtest.h>

#include <array>
#include <ranges>
#include <sstream>
#include <string_view>

#include "convert.h"
#include "log.h"

namespace {
constexpr std::string_view test_input_1{"Hello, World!"};
constexpr std::string_view test_input_2{"what's up, yo!?"};
constexpr std::string_view test_input_3{"äöü"};

constexpr std::string_view output_delimiter{"\n"};

template <size_t Size>
void check_expected_output(const std::array<std::string_view, Size> &expected,
                           const std::ostringstream &output) {
  auto expected_it = expected.begin();

  for (const auto out : std::views::split(output.str(), output_delimiter)) {
    if (expected_it == expected.end()) {
      EXPECT_TRUE(std::string_view(out.begin(), out.end()).empty());
      continue;
    }
    EXPECT_EQ(*expected_it, std::string_view(out.begin(), out.end()));
    ++expected_it;
  }
}
} // namespace

class IntegrationTest : public ::testing::Test {
protected:
  std::ostringstream mock_cerr{};
  std::stringstream mock_cin{};
  std::ostringstream mock_cout{};
  std::ostringstream mock_secondary_cout{};
  stream_provider ios{mock_cerr, mock_cin, mock_cout, mock_secondary_cout};
};

TEST_F(IntegrationTest, DefaultFormatVerboseNoInput) {
  parse_result prs{.format = {},
                   .input = input_type::console,
                   .output = output_type::console,
                   .verbose = true};

  logger log{mock_cout};
  auto converter = convert::get_converter(prs, ios, log.queue());

  log.print_queued();

  converter->run();

  constexpr std::array<std::string_view, 3> expected{
      "format: 48 65 6c 6c 6f 2c 20 57 6f 72 6c 64 21 (\"Hello, World!\")",
      "input: console", "output: console"};

  check_expected_output(expected, mock_cout);
}

TEST_F(IntegrationTest, FormatHexUpperCommaSpaceVerboseNoInput) {
  parse_result prs{.format = {},
                   .input = input_type::console,
                   .output = output_type::console,
                   .verbose = true};

  prs.format.use_hex_prefix = true;
  prs.format.use_uppercase = true;
  prs.format.byte_separator = ", ";

  logger log{mock_cout};
  auto converter = convert::get_converter(prs, ios, log.queue());

  log.print_queued();

  converter->run();

  constexpr std::array<std::string_view, 3> expected{
      "format: 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x57, 0x6F, 0x72, "
      "0x6C, 0x64, 0x21 (\"Hello, World!\")",
      "input: console", "output: console"};

  check_expected_output(expected, mock_cout);
}

TEST_F(IntegrationTest, DefaultFormatWithInput) {
  parse_result prs{.format = {},
                   .input = input_type::console,
                   .output = output_type::console,
                   .verbose = false};

  auto converter = convert::get_converter(prs, ios);

  mock_cin << test_input_1 << "\n";
  mock_cin << test_input_2 << "\n";
  mock_cin << test_input_3 << "\n";

  converter->run();

  constexpr std::array<std::string_view, 3> expected{
      "48 65 6c 6c 6f 2c 20 57 6f 72 6c 64 21",
      "77 68 61 74 27 73 20 75 70 2c 20 79 6f 21 3f", "c3 a4 c3 b6 c3 bc"};

  check_expected_output(expected, mock_cout);
}

TEST_F(IntegrationTest, Dummy) {
  format_config fmt{.use_hex_prefix = false,
                    .use_uppercase = false,
                    .n_byte_group = 1,
                    .byte_separator = " "};
  parse_result prs{.format = fmt,
                   .input = input_type::console,
                   .output = output_type::console,
                   .verbose = false};

  logger log{mock_cout};
  auto converter = convert::get_converter(prs, ios, log.queue());

  mock_cin << test_input_1 << "\n";
  mock_cin << test_input_2 << "\n";
  mock_cin << test_input_3 << "\n";

  log.print_queued();

  converter->run();

  std::cout << mock_cin.str() << std::endl;

  for (const auto word : std::views::split(mock_cout.str(), output_delimiter)) {
    std::cout << std::string_view(word.begin(), word.end()) << "\n";
  }

  EXPECT_TRUE(mock_cerr.str().empty());
  EXPECT_FALSE(mock_cout.str().empty());
}
