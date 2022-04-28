#include <nowide/args.hpp>

#include "convert.h"
#include "parse.h"
#include "print.h"

using Converter = convert::engine;
using Parser = parse::engine;
using Printer = print::engine;

int main(int argc, char *argv[]) {

  nowide::args _(argc, argv);

  Printer printer{};

  Parser parser{printer.get_queue_func()};

  const auto config = parser.do_parse(argc, argv);

  Converter converter{config, printer.get_queue_func()};

  printer.print_queued();

  converter.run();

  return 0;
}
