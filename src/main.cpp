#include "converter.h"
#include "formatter.h"
#include "input_adapter.h"
#include "output_adapter.h"

#include <nowide/args.hpp>

int main(int argc, char *argv[]) {

  nowide::args a(argc, argv);

  // input::from_console input{};
  input::from_file input{{"text.txt"}};
  format::engine formatter{};
  output::to_console output{};

  const auto cnv = converter(input, formatter, output);

  while (cnv.proceed())
    ;

  return 0;
}
