#include "clipboard_impl.h"

#include <clip.h>

namespace output {
bool copy_to_clipboard(const std::string &str) { return clip::set_text(str); }
} // namespace output
