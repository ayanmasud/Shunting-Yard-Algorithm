#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

struct Node {
  char value;
  //struct Node next;

  Node() {
    next = NULL;
  }
};

struct Queue {
  char* value;
  struct Queue* next;

  Queue() {
    next = NULL;
  }
};
void enqueue(Queue* &head, char* &data);
void dequeue(Queue* head);

int main() {
  //Stack* stackHead = NULL; // head of stack // I DONT THINK I CAN DO STACKS LIKE THIS. THIS IS NOT A LINKED LIST
  stack<Node> st;
  Node na = new Node();
  char aa = 'a';
  na.value = 'a';
  Node nb = new Node();
  char bb = 'b';
  nb.value = 'b';
  st.push(na);
  st.push(nb);

  while (!st.empty()) {
    cout << ' ' << st.top();
    st.pop();
  }

  Queue* queueHead = NULL; // head of queue

  char a = 'a';
  char* ap = &a;
  char b = 'b';
  char* bp = &b;
  char c = '+';
  char* cp = &c;
  enqueue(queueHead, ap);
  enqueue(queueHead, bp);
  enqueue(queueHead, cp);

  // PRINTING INDIV NOT WORKING FOR SOME GOOFY REASON
  if (queueHead->next != NULL) {//->value;
    cout << queueHead->next->value;
  }

  
  
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
      /*if (opStack[opStackIndex-1] == '^') { // same precedence
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
	}*/
      //else {
      // since the rest are smaller or same, just add it to the next
      opStack[opStackIndex] = '^';
      opStackIndex++;
	//}
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
      //cout << "len" << strlen(opStack) << endl;
      int len = strlen(opStack);
      for (int j = 0; j < len; j++) {
	//cout << output << endl;
	//cout << "fwhs" << endl;
	//cout << opStack << endl;
	//cout << opStackIndex << endl;
	if (opStack[opStackIndex-1] == '(') { // stop at (
	  opStack[opStackIndex-1] = '\0';
	  opStackIndex--;
	  //cout << "happened" << endl;
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

  //cout << strlen(opStack) << endl;
  //cout << output << endl;
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






/*class Queue {
private:
  char* value;
  Queue* next;
public:
  // Constructor to initialize the queue
  Queue() {    
    next = NULL;
  }
  
  // Destructor to free the allocated memory
  ~Queue() {
    delete value;
    next = NULL;
  }
  };*/

void enqueue(Queue* &head, char* &data) {
  // Add the element to the rear
  if (head == NULL){
    Queue* newHead = new Queue();
    newHead->value = data;
    head = newHead;
  }
  else if (head->next == NULL) {
    Queue* newNode = new Queue();
    newNode->value = data;
    head->next = newNode;
  }
  else {
    enqueue(head->next, data); // recurse until the end of the queue
  }
}

void dequeue(Queue* head) {
  /*if (size == 0) {
    cout << "Queue is empty" << endl;
    return;
  }
  
  // Shift all elements to the left by one position
  for (int i = 1; i < size; i++) {
    queue[i - 1] = queue[i];
  }
  size--;*/
}
