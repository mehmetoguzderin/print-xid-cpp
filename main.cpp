#include <fstream>
#include <iostream>
#include <sstream>
#include <unicodelib.h>
#include <unicodelib_encodings.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::wcout << "No file path provided.\n";
    return 1;
  }
  std::wifstream wifs(argv[1]);
  std::wstringstream wss;
  wss << wifs.rdbuf();
  auto wstring = wss.str();
  auto u32string = unicode::to_utf32(wstring);
  auto nfcstring = unicode::to_nfc(u32string);
  bool start = true;
  for (auto &ch : nfcstring) {
    if (start) {
      if (!(unicode::is_xid_start(ch) || ch == char32_t('_'))) {
        std::wcout << "Invalid start\n";
        return 1;
      }
      start = false;
    } else {
      if (!(unicode::is_xid_continue(ch))) {
        std::wcout << "Invalid continue\n";
        return 1;
      }
    }
  }
  std::wcout << "\n";
  return 0;
}