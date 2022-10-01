#include <gtest/gtest.h>

#include "convert_impl.h"
#include "mock_format.h"
#include "mock_input.h"
#include "mock_output.h"

namespace test_data {
const std::string some_test_string{"blubber"};
const std::string other_test_string{"schwabbel"};
const std::vector<uint8_t> some_test_vector{0xde, 0xad, 0xbe, 0xef};
const std::vector<uint8_t> other_test_vector{0xba, 0xd4, 0xf0, 0x0f};
} // namespace test_data

class ConvertTest : public ::testing::Test {
protected:
  std::ostringstream mock_cerr{};
  std::stringstream mock_cin{};
  std::ostringstream mock_cout{};
  stream_provider ios{mock_cerr, mock_cin, mock_cout};
};

TEST_F(ConvertTest, NoInput_RunDoesntRunForever) {
  const auto converter = convert::get_converter({}, ios);
  converter->run();
  // if we reach this, we are good
  EXPECT_TRUE(true);
}

TEST_F(ConvertTest, EmptyInput_ProceedReturnsFalse) {
  std::vector<uint8_t> input_inject{};
  auto input = std::make_unique<input::mock>(input_inject);
  const convert::engine converter(format::get_format_engine({}),
                                  std::move(input),
      output::get_output_adapter({}, set_none), ios);
  ASSERT_FALSE(converter.proceed());
}

TEST_F(ConvertTest, NonEmptyInput_ProceedReturnsTrue) {
  std::vector<uint8_t> input_inject{test_data::some_test_vector};

  auto input = std::make_unique<input::mock>(input_inject);
  const convert::engine converter(format::get_format_engine({}),
                                  std::move(input),
      output::get_output_adapter({}, set_none), ios);

  ASSERT_TRUE(converter.proceed());

  input_inject.clear();
  ASSERT_FALSE(converter.proceed());
}

TEST_F(ConvertTest, EmptyInput_NothingFormatted_NothingPassedToOutut) {
  std::vector<uint8_t> input_inject{};
  std::string format_inject{test_data::some_test_string};

  std::vector<uint8_t> format_read{0xff, 0xff, 0xff, 0xff};
  std::string output_read{};

  auto input = std::make_unique<input::mock>(input_inject);
  auto formatter = std::make_unique<format::mock>(format_inject, format_read);
  auto output = std::make_unique<output::mock>(output_read);

  const convert::engine converter(std::move(formatter), std::move(input),
                                  std::move(output), ios);

  converter.run();

  ASSERT_FALSE(format_read.empty());
  ASSERT_TRUE(output_read.empty());
}

TEST_F(ConvertTest, InputPassedToFormatter_FormatPassedToOutput) {
  std::vector<uint8_t> input_inject{test_data::some_test_vector};
  std::string format_inject{test_data::some_test_string};

  std::vector<uint8_t> format_read{};
  std::string output_read{};

  auto input = std::make_unique<input::mock>(input_inject);
  auto formatter = std::make_unique<format::mock>(format_inject, format_read);
  auto output = std::make_unique<output::mock>(output_read);

  const convert::engine converter(std::move(formatter), std::move(input),
                                  std::move(output), ios);

  EXPECT_TRUE(converter.proceed());
  ASSERT_EQ(test_data::some_test_vector, format_read);
  ASSERT_EQ(test_data::some_test_string, output_read);

  output_read.clear();
  format_inject = test_data::other_test_string;
  EXPECT_TRUE(converter.proceed());
  ASSERT_EQ(test_data::other_test_string, output_read);

  input_inject = test_data::other_test_vector;
  format_inject.clear();
  EXPECT_TRUE(converter.proceed());
  ASSERT_EQ(test_data::other_test_vector, format_read);
  ASSERT_TRUE(output_read.empty());
}

TEST_F(ConvertTest, VerboseOutputAsExpected) {
  std::vector<std::string> verbose_output{};

  auto print_function = [&verbose_output](const std::string &str) {
    verbose_output.push_back(str);
  };

  const auto converter =
      convert::get_converter({.verbose = true}, ios, print_function);

  ASSERT_EQ(3, verbose_output.size());
  ASSERT_EQ("format: 0xDU, 0xMM, 0xYF, 0xOR, 0xMA, 0xT! (\"Hello, World!\")",
            verbose_output[0]);
  ASSERT_EQ("input: mock", verbose_output[1]);
  ASSERT_EQ("output: mock", verbose_output[2]);
}
