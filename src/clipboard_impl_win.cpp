#include "clipboard_impl.h"

#include <Windows.h>
#include <nowide/convert.hpp>
#include <nowide/iostream.hpp>

namespace output {
void clipboard_impl::copy_to_clipboard(const std::string &str) const {
  auto wstr = nowide::widen(str);

  HWND handle = nullptr;
  if (!OpenClipboard(handle)) {
    return;
  }

  const auto buffer_size = wstr.size() * sizeof(TCHAR);

  HGLOBAL copy_handle = GlobalAlloc(GMEM_MOVEABLE, buffer_size + sizeof(TCHAR));
  if (copy_handle == nullptr) {
    CloseClipboard();
    return;
  }

  auto copy_buffer = (LPTSTR)GlobalLock(copy_handle);
  memcpy(copy_buffer, wstr.c_str(), buffer_size);
  copy_buffer[wstr.size()] = 0;
  GlobalUnlock(copy_handle);

  if (!SetClipboardData(CF_UNICODETEXT, copy_handle)) {
    nowide::cerr << "Cannot copy to clipboard!\n";
  }

  CloseClipboard();
}
} // namespace output
