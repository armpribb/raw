#include "output.h"

#include "clipboard_impl.h"

namespace output {

void write_to_clipboard(const std::string &str) { copy_to_clipboard(str); }

void write_to_clipboard(const std::string &str, const stream_provider_v2 &ios) {
  if (copy_to_clipboard(str)) {
    if (ios.prompt.get() != nullptr) {
      ios.info << "(hit enter to continue)";
      ios.prompt.get()->get();
    }
    ios.info << "<result copied to clipboard>\n\n";
  } else {
    ios.err << "<failed to copy result to clipboard>\n";
  }
}

void write_to_stream(const std::string &str, const stream_provider_v2 &ios) {
  ios.info << "< ";
  ios.out << str << "\n";
}

} // namespace output