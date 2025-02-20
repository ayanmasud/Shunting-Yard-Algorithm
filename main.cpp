#include <iostream>
#include <cstring>

using namespace std;

struct Node {
  char value;
  struct Node* next;

  Node() {
    next = NULL;
  }
};

int main() {
  char input[20];
  cin.getline(input, 20);
  int inputLen = strlen(input);
  
  //char operators[5] = {'+', '-', 'x', '/'};
  char opStack[20];
  int opStackIndex = 0;

  char output[20];
  int outputIndex = 0;
  
  // attempt to do shunting yard algorithm
  for (int i = 0; i < inputLen; i++) {
    if (input[i] == '^') { // ^ operator
      if (opStack[opStackIndex-1] == '^') { // same precedence
	for (int j = 0; j < strlen(opStack); j++) {
          output[outputIndex] = opStack[opStackIndex-1];
          outputIndex++;
          opStackIndex--;
        }
        opStack[opStackIndex] = input[i];
        opStackIndex++;
      }
      else { // since the rest are smaller, just add it to the next
	opStack[opStackIndex] = '^';
	opStackIndex++;
      }
    }
    else if (input[i] == 'x' || input[i] == '/') { // x or / operators
      if (opStack[opStackIndex-1] == '-' || opStack[opStackIndex-1] == '+') { // previous is smaller
	opStack[opStackIndex] = input[i];
        opStackIndex++;
      }
      else { // previous is greater or same
	for (int j = 0; j < strlen(opStack); j++) {
	  if (opStack[j] == '+' || opStack[j] == '-') {
	    break;
	  }
          output[outputIndex] = opStack[opStackIndex-1];
          outputIndex++;
          opStackIndex--;
        }
        opStack[opStackIndex] = input[i];
        opStackIndex++;
      }
    }
    else if (input[i] == '+' || input[i] == '-') { // + or - operators
      if (opStackIndex == 0) { // if its the first in the stack.
	opStack[opStackIndex] = input[i];
	opStackIndex++;
      }
      else { // if not, its garunteed to be the same or of lower precedence
	for (int j = 0; j < strlen(opStack); j++) {
	  output[outputIndex] = opStack[opStackIndex-1];
	  outputIndex++;
	  opStackIndex--;
	}
	opStack[opStackIndex] = input[i];
	opStackIndex++;
      }
    }
    else if (input[i] == '(') { // inside a parenthesis!

    }
    else {
      output[outputIndex] = input[i];
      outputIndex++;
    }
  }

  for (int j = 0; j < strlen(opStack); j++) {
    output[outputIndex] = opStack[opStackIndex-1];
    outputIndex++;
    opStackIndex--;
  }
  
  cout << output;

  return 0;
}
