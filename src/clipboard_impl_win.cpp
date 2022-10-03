#include "clipboard_impl.h"

#include <Windows.h>
#include <nowide/convert.hpp>

namespace output {

bool copy_to_clipboard(const std::string &str) {
  auto wstr = nowide::widen(str);

  HWND handle = nullptr;
  if (!OpenClipboard(handle)) {
    return false;
  }

  const auto buffer_size = wstr.size() * sizeof(TCHAR);

  HGLOBAL copy_handle = GlobalAlloc(GMEM_MOVEABLE, buffer_size + sizeof(TCHAR));
  if (copy_handle == nullptr) {
    CloseClipboard();
    return false;
  }

  auto copy_buffer = (LPTSTR)GlobalLock(copy_handle);
  memcpy(copy_buffer, wstr.c_str(), buffer_size);
  copy_buffer[wstr.size()] = 0;
  GlobalUnlock(copy_handle);

  bool success = true;
  if (!SetClipboardData(CF_UNICODETEXT, copy_handle)) {
    success = false;
  }

  CloseClipboard();

  return success;
}

} // namespace output
