#include <nowide/args.hpp>

#include "parse.h"

int main(int argc, char *argv[]) {

  nowide::args _(argc, argv);

  parse::engine parser{};

  parser.do_parse(argc, argv);

  auto converter = parser.get_converter();

  parser.print_output();

  converter.run();

  return 0;
}
