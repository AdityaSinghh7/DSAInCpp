
#include <iostream>

#include "String.h"

using namespace std;

int main() {
  // Test constructors
  String s1("Hello, World!");
  String s2(s1);
  String s3 = s1;
  String s4(move(s1));

  // Test operator<<
  cout << "s2: " << s2 << endl;
  cout << "s3: " << s3 << endl;
  cout << "s4: " << s4 << endl;

  // Test operator[]
  cout << "s2[7]: " << s2[7] << endl;

  // Test size()
  cout << "s2 size: " << s2.size() << endl;

  // Test reverse()
  s2.reverse();
  cout << "s2 reverse: " << s2 << endl;

  // Test indexOf()
  cout << "Index of 'o' in s2: " << s2.indexOf('o') << endl;
  cout << "Index of 'World' in s2: " << s2.indexOf(String("World")) << endl;

  // Test relational operators
  String str1("apple");
  String str2("banana");

  cout << boolalpha;
  cout << "str1 == str2: " << (str1 == str2) << endl;
  cout << "str1 != str2: " << (str1 != str2) << endl;
  cout << "str1 > str2: " << (str1 > str2) << endl;
  cout << "str1 < str2: " << (str1 < str2) << endl;
  cout << "str1 <= str2: " << (str1 <= str2) << endl;
  cout << "str1 >= str2: " << (str1 >= str2) << endl;

  // Test concatenation
  String cat1 = str1 + str2;
  cout << "str1 + str2: " << cat1 << endl;

  // Test operator+=
  str1 += str2;
  cout << "str1 += str2: " << str1 << endl;

  // Test operator>>
  String inputStr;
  cout << "Enter a string: ";
  cin >> inputStr;
  cout << "You entered: " << inputStr << endl;

  return 0;
}