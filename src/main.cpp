#include <nowide/args.hpp>

#include "convert.h"
#include "parse.h"
#include "print.h"

using Printer = print::engine;

int main(int argc, char *argv[]) {

  nowide::args _(argc, argv);

  Printer printer{};

  const auto parser = parse::get_parser(printer.get_queue_func());

  const auto config = parser->do_parse(argc, argv);

  const auto converter =
      convert::get_converter(config, printer.get_queue_func());

  printer.print_queued();

  converter->run();

  return 0;
}
