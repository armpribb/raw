#include "convert.h"
#include "parse.h"

#include <nowide/args.hpp>
#include <nowide/iostream.hpp>

int main(int argc, char *argv[]) {

  nowide::args _(argc, argv);

  parse::engine parser{};

  parser.do_parse(argc, argv);

  if (parser.is_valid_non_help_cmd()) {
    const auto input = parser.get_input();
    const auto format = parser.get_format();
    const auto output = parser.get_output();

    const auto cnv = converter(*input, *format, *output);

    while (cnv.proceed())
      ;
  }

  parser.print_output();

  return 0;
}
