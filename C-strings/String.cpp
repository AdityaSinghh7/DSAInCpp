#include "String.h"

#include <iostream>

#include "Alloc.h"
using namespace std;

size_t String::strlen(const char *s) {
  size_t count = 0;           // counter variable
  while (s[count] != '\0') {  // while loop to check until null ptr
    count++;                  // increment
  }
  return count;  // return statement
}
char *String::strcpy(char *dest, const char *src) {
  char *p = dest;            // temp ptr p, assigned to dest value
  while ((*p++ = *src++)) {  // assignment as well as conditional statement
    ;
  }
  return dest;  // returning first char of new array with copied elements
}
char *String::strdup(const char *s) {
  size_t length = strlen(s) + 1;  // local variable assigned to length of s
  char *destination = Alloc::new_char_array(
      length);  // allocating new character array assigned to destination
  destination =
      strcpy(destination, s);  // copying s-character array to destination
  return destination;          // returning new destination character array
}
char *String::strncpy(char *dest, const char *src, int n) {
  for (int i = 0; (i < n) && (src[i] != '\0');
       i++) {  // for loop till either n or end of src
    dest[i] = src[i];
  }
  return dest;
}
char *String::strcat(char *dest, const char *src) {
  size_t destlen = strlen(dest);
  int i = 0;
  while (src[i] != '\0') {
    dest[destlen + i] = src[i];
    i++;
  }
  dest[destlen + i] = '\0';
  return dest;
}
char *String::strncat(char *dest, const char *src, int n) {
  size_t srclen = strlen(src);
  size_t destlen = strlen(dest);
  int i = 0;
  while (src[i] != '\0' || i <= n) {
    dest[destlen + i] = src[i];
    i++;
  }
  dest[destlen + srclen + 1] = '\0';
  return dest;
}
int String::strcmp(const char *left, const char *right) {
  size_t i = 0;
  while (left[i] != '\0' && right[i] != '\0') {
    if (left[i] != right[i]) {
      return static_cast<int>(left[i]) - static_cast<int>(right[i]);
    }
    i++;
  }
  return static_cast<int>(left[i]) - static_cast<int>(right[i]);
}
int String::strncmp(const char *left, const char *right, int n) {
  for (int i = 0; i < n; i++) {
    if (left[i] != right[i]) {
      if (left[i] < right[i]) {
        return -1;
      } else {
        return 1;
      }
    }
  }
  return 0;
}
void String::reverse_cpy(char *dest, const char *src) {
  size_t lenghtsrc = strlen(src);
  for (size_t i = 0; i < lenghtsrc; i++) {
    dest[i] = src[lenghtsrc - i - 1];
  }
  dest[lenghtsrc] = '\0';
}
char *String::strchr(char *str, char c) {
  while (*str) {
    if (*str == c) {
      return str;
    }
    str++;
  }
  return nullptr;
}
char *String::strstr(char *haystack, const char *needle) {
  int len_n = strlen(needle);
  for (char *p = haystack; (p = strchr(p, needle[0])); ++p) {
    if (strncmp(p, needle, len_n) == 0) {
      return p;
    }
  }
  return nullptr;
}
const char *String::strstr(const char *haystack, const char *needle) {
  return const_cast<const char *>(strstr(const_cast<char *>(haystack), needle));
}
String::String(const char *s) { buf = strdup(s); }
String::String(const String &s) { buf = strdup(s.buf); }
String::String(String &&s) {
  buf = s.buf;
  s.buf = nullptr;
}
String &String::operator=(String &&s) {
  if (this != &s) {
    Alloc::delete_char_array(buf);
    buf = s.buf;
    s.buf = nullptr;
  }
  return *this;
}
String &String::operator=(const String &s) {
  if (this != &s) {
    Alloc::delete_char_array(buf);
    buf = strdup(s.buf);
  }

  return *this;
}
char &String::operator[](int index) { return buf[index]; }
size_t String::size() {
  size_t returnval = strlen(buf);
  return returnval--;
}
String String::reverse() {
  size_t srcLength = strlen(buf);
  char *reversed = Alloc::new_char_array(srcLength + 1);
  reverse_cpy(reversed, buf);
  String reversedString(reversed);
  Alloc::delete_char_array(reversed);
  return reversedString;
}
int String::indexOf(const char c) {
  char *temp = strchr(buf, c);
  int retvalue = temp - buf;
  return retvalue;
}
int String::indexOf(const String &s) {
  char *p = strstr(buf, s.buf);
  if (p == nullptr) {
    return -1;
  } else {
    int retvalue = p - buf;
    return retvalue;
  }
}
bool String::operator==(const String &s) { return strcmp(buf, s.buf) == 0; }
bool String::operator!=(const String &s) { return (strcmp(buf, s.buf) != 0); }
bool String::operator>(const String &s) { return strcmp(buf, s.buf) > 0; }
bool String::operator<(const String &s) { return strcmp(buf, s.buf) < 0; }
bool String::operator<=(const String &s) {
  return (strcmp(buf, s.buf) == 0 || strcmp(buf, s.buf) < 0);
}
bool String::operator>=(const String &s) {
  return (strcmp(buf, s.buf) == 0 || strcmp(buf, s.buf) > 0);
}
String String::operator+(const String &s) {
  char *temp = Alloc::new_char_array(strlen(buf) + strlen(s.buf) + 1);
  strcpy(temp, buf);
  strcat(temp, s.buf);
  String strvar(temp);
  Alloc::delete_char_array(temp);
  return strvar;
}
String &String::operator+=(const String &s) {
  *this = *this + s;
  return *this;
}
void String::print(ostream &out) const { out << buf; }
void String::read(istream &in) {
  char local[1024];
  in.getline(local, 1024);
  Alloc::delete_char_array(buf);
  buf = strdup(local);
}
ostream &operator<<(ostream &out, const String &s) {
  s.print(out);
  return out;
}
istream &operator>>(istream &in, String &s) {
  s.read(in);
  return in;
}
String::~String() { Alloc::delete_char_array(buf); }