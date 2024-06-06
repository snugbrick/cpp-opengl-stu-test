#include <Windows.h>
#include <iostream>


typedef int (*AddFunc)();

int main() {
  HINSTANCE dllFir = LoadLibrary("dllFir.dll");
  if (dllFir != NULL) {
    AddFunc printHello = (AddFunc)GetProcAddress(dllFir, "printHello");
    if (printHello != NULL) {
      printHello();
    } else {
      std::cerr << "Failed to get function address" << std::endl;
    }
    FreeLibrary(dllFir);
  } else {
    std::cerr << "Failed to load DLL" << std::endl;
  }

  return 0;
}