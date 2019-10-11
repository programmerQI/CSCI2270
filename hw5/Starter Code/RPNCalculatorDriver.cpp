/****************************************************************/
/*                  RPN Calculator Driver File                  */
/****************************************************************/
/*      TODO: Implement driver as described in the writeup      */
/****************************************************************/

#include "RPNCalculator.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

bool isOperand(std::string s){
    if(s == "+" || s == "*"){
      return true;
    }
    return false;
}

RPNCalculator :: RPNCalculator()
{
    stackHead = NULL;
}

RPNCalculator :: ~RPNCalculator()
{
    while(stackHead != NULL){
      pop();
    }
}

bool RPNCalculator :: isEmpty()
{
    if(stackHead == NULL){
      return true;
    }
    return false;
}

void RPNCalculator :: push(float num)
{
    stackHead = new Operand();
    stackHead -> number = num;
    stackHead -> next = NULL;
}

void RPNCalculator :: pop()
{
    if(stackHead == NULL){
      std::cout << "Stack empty, cannot pop an item." << std::endl;
      return;
    }
    if(stackHead -> next == NULL){
      delete stackHead;
      stackHead = NULL;
      return;
    }
    Operand *node = stackHead;
    while(node -> next -> next != NULL){
      node = node -> next;
    }
    delete node -> next;
    node -> next = NULL;
}

Operand* RPNCalculator :: peek()
{
    if(stackHead == NULL){
      std::cout << "Stack empty, cannot peek." << std::endl;
      return NULL;
    }
    Operand *node = stackHead;
    while(node -> next != NULL){
      node = node -> next;
    }
    return node;
}

bool RPNCalculator :: compute(std::string symbol)
{
    Operand *o1 = peek();
    if(o1 == NULL) {
      return false;
    }
    Operand *o2 = peek();
    if(o2 == NULL) {
      return false;
    }
    int num1 = o1 -> number;
    int num2 = o2 -> number;
    int ans;
    if(symbol == "+"){
      ans = num1 + num2;
      push(ans);
      return true;
    } else if (symbol == "*"){
      ans = num1 * num2;
      push(ans);
      return true;
    }
    std::cout << "err: invalid operation" << std::endl;
    return false;
}

int main()
{
  // TODO - Declare a stack to hold the operands
  RPNCalculator ca;

  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;

  while(true)
  {
    cout << "#> ";
    /* TODO
       1. Read input (operators and operands) until you encounter a "="
       2. Use the isNumber function to check if the input is an operand
       3. push all operands to the stack
       4. If input is not an operand, call the compute function to evaluate
          the partial expression
    */
    std::string str;
    std::cin >> str;
    if(isNumber(str)) {
      ca.push(std::stod(str));
    } else if (isOperand(str)) {
      ca.compute(str);
    } else if (str == "="){
      break;
    } else {
      std::cout << "err: invalid operation" << std::endl;
    }
  }

  /* TODO - If the stack is empty then print "No operands: Nothing to evaluate" */
  if(ca -> isEmpty()){
    std::cout << "No operands: Nothing to evaluate" << std::endl;
  }
  /* TODO - Validate the expression
      1. If valid then print the result
      2. Else, print "Invalid expression"*/

  return 0;
}
