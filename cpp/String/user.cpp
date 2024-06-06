#include "String.h"
#include <cstring>
#include <iostream>
#include <string.h>

using namespace std;
auto main() -> decltype(114 + 514) {
  {
    String newStr("use newStr constructor");
    cout << newStr.checkStrNum() << endl;

    String newStr2("use newStr2 constructor");
    cout << newStr2.checkStrNum() << endl;

    String newStr3("use newStr3 constructor");
    cout << newStr3.checkStrNum() << endl;

    String newStr4("use newStr4 constructor"); // c9r :)
    cout << newStr4.checkStrNum() << endl;
    for (int i = 0; i < newStr4.checkLen(); i++) {
      cout << *(newStr4.getString() + i);
    }
    cout << endl;
  }
  {
    String newStr5("hi im john5");
    cout << newStr5.checkStrNum() << endl;

    String ne2Str6 = newStr5;
    cout << ne2Str6.checkStrNum() << endl;
  }
  cout << "here is end" << endl;
  return 0;
}

int String::String_Num = 0;

String::String(const char *s) : lenPlus(strlen(s) + 1) { // member init list
  len = strlen(s);
  _stringBody = new char[len + 1];
  strcpy(_stringBody, s);
  String_Num++;
  cout << "Im String constructor" << endl;
}

String::String(const String &s) : lenPlus((s.len) + 1) {
  len = strlen(s._stringBody);
  _stringBody = new char[len + 1];
  strcpy(_stringBody, s._stringBody);
  String_Num++;
  cout << "Im copy constructor" << endl;
}

String::~String() {
  delete[] _stringBody;
  cout << "Im ~String disconstructor" << endl;
  String_Num--;
}

int String::checkLen() { return len; }
int String::checkStrNum() { return String_Num; }
char *String::getString() { return _stringBody; }