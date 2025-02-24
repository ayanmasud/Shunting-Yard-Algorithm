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
	int len = strlen(opStack);
	for (int j = 0; j < len; j++) {
	  if (opStack[opStackIndex-1] == '(') { // create barrier at (
	    break;
          }
	  output[outputIndex] = opStack[opStackIndex-1];
          outputIndex++;
	  opStack[opStackIndex-1] = '\0';
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
    else if (input[i] == '*' || input[i] == '/') { // * or / operators
      if (opStack[opStackIndex-1] == '-' || opStack[opStackIndex-1] == '+') { // previous is smaller
	opStack[opStackIndex] = input[i];
        opStackIndex++;
	
      }
      else { // previous is greater or same
	int len = strlen(opStack);
	for (int j = 0; j < len; j++) {
	  if (opStack[opStackIndex-1] == '(') { // create a barrier at (
            break;
          }
	  if (opStack[opStackIndex-1] == '+' || opStack[opStackIndex-1] == '-') {
	    break;
	  }
          output[outputIndex] = opStack[opStackIndex-1];
          outputIndex++;
	  opStack[opStackIndex-1] = '\0';
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
      else { // if not, its guaranteed to be the same or of lower precedence
	int len = strlen(opStack);
	for (int j = 0; j < len; j++) {
	  if (opStack[opStackIndex-1] == '(') { // create barrier at (
	    break;
	  }
	  output[outputIndex] = opStack[opStackIndex-1];
	  outputIndex++;
	  opStack[opStackIndex-1] = '\0';
	  opStackIndex--;
	}
	opStack[opStackIndex] = input[i];
	opStackIndex++;
      }
    }
    else if (input[i] == '(') { // inside a parenthesis!
      opStack[opStackIndex] = input[i];
      opStackIndex++;
    }
    else if (input[i] == ')') { // parenthesis ended
      cout << "len" << strlen(opStack) << endl;
      int len = strlen(opStack);
      for (int j = 0; j < len; j++) {
	cout << output << endl;
	cout << "fwhs" << endl;
	cout << opStack << endl;
	cout << opStackIndex << endl;
	if (opStack[opStackIndex-1] == '(') { // stop at (
	  opStack[opStackIndex-1] = '\0';
	  opStackIndex--;
	  cout << "happened" << endl;
	  break;
	}
	output[outputIndex] = opStack[opStackIndex-1];
	outputIndex++;
	opStack[opStackIndex-1] = '\0';
	opStackIndex--;
      }
    }
    else { // not an operator
      output[outputIndex] = input[i];
      outputIndex++;
    }
  }

  cout << strlen(opStack) << endl;
  cout << output << endl;
  int len = strlen(opStack);
  for (int j = 0; j < len; j++) {
    output[outputIndex] = opStack[opStackIndex-1];
    outputIndex++;
    opStack[opStackIndex-1] = '\0';
    opStackIndex--;
  }

  cout << output;

  return 0;
}
