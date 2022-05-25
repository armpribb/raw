#include "convert.h"
#include "log.h"
#include "parse.h"

int main(int argc, char *argv[]) {
  logger log{};

  const auto parser = parse::get_parser(log.queue());
  const auto config = parser->do_parse(argc, argv);
  const auto converter = convert::get_converter(config, log.queue());

  log.print_queued();

  converter->run();

  return 0;
}
