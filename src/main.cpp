#include "convert.h"
#include "log.h"
#include "parse.h"
#include "stream_io.h"

#include <nowide/iostream.hpp>

int main(int argc, char *argv[]) {
  logger log{nowide::cout};
  // stream_provider ios{nowide::cerr, nowide::cin, nowide::cout};

  const auto parser = parse::get_parser(log.queue());
  const auto config = parser->do_parse_v2(argc, argv);
  const auto converter = convert::get_converter_v2(config);

  log.print_queued();

  converter->run();

  return 0;
}
