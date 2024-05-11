#include "is_balanced.h"

#include <iostream>
#include <stack>
#include <string>
using namespace std;
bool is_balanced(string s) {
  stack<char> stack_balance;

  for (char c : s) {
    switch (c) {
      case '{':
      case '[':
      case '(':
      case '<':
        stack_balance.push(c);
        break;
      case '}':
        if (stack_balance.empty() || stack_balance.top() != '{') return false;
        stack_balance.pop();
        break;
      case ']':
        if (stack_balance.empty() || stack_balance.top() != '[') return false;
        stack_balance.pop();
        break;
      case ')':
        if (stack_balance.empty() || stack_balance.top() != '(') return false;
        stack_balance.pop();
        break;
      case '>':
        if (stack_balance.empty() || stack_balance.top() != '<') return false;
        stack_balance.pop();
        break;
      default:
        return false;
    }
  }

  return stack_balance.empty();
}

void error(string msg, char c) {
  cout << "Error: " << msg << ": " << c << endl;
}

void test_is_balanced() {
  string test1_true = "({(())})((([({})])))(((((<>([{()}])(<>))))))()";
  string test2_false = "({(<>)})((([({})])))(((((()([{()}])(())))))";
  string test3_false = "({(<>)})((([({})])))((((([]([{<>}])(()))))))()])";

  cout << boolalpha << "Test 1 (expected true): " << is_balanced(test1_true)
       << endl;
  cout << boolalpha << "Test 2 (expected false): " << is_balanced(test2_false)
       << endl;
  cout << boolalpha << "Test 3 (expected false): " << is_balanced(test3_false)
       << endl;
}