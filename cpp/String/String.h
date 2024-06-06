#ifndef String_h_
#define String_h_

class String {
private:
  static int String_Num;
  char *_stringBody;
  int len;
  const int lenPlus;

public:
  String(const char *s);
  String(const String &s);
  ~String();
  int checkLen();
  int checkStrNum();
  char *getString();
  // String &operator=(const String &thatString);
protected:
};

class newString : public String { // extend
private:
  int newStringNum;

public:
  newString(int _newStringNum, String &s);
  newString(int _newStringNum, const char *s);

protected:
};
//作者名：Gnua51
#endif