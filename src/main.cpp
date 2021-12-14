#include "converter.h"
#include "format.h"
#include "input_adapter.h"
#include "output_adapter.h"

#include <nowide/args.hpp>

int main(int argc, char *argv[]) {

  nowide::args a(argc, argv);

  input::from_console input{};
  format::engine formatter{};
  output::to_clipboard output{};

  const auto cnv = converter(input, formatter, output);

  while (cnv.proceed())
    ;

  return 0;
}
