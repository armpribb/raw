#include "clipboard_impl.h"

#include <Windows.h>

namespace output {
void clipboard_impl::copy_to_clipboard(const std::string &str) const {
  HWND handle;
  OpenClipboard(handle);
  // . . .
  CloseClipboard();
}
} // namespace output