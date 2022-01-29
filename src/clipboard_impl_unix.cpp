#include "clipboard_impl.h"

#include <clip.h>

namespace output {
void clipboard_impl::copy_to_clipboard(const std::string &str) const {
    clip::set_text(str);
}
} // namespace output
