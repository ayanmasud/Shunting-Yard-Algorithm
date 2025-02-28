#include <iostream>
#include <cstring>
//#include <bits/stdc++.h>

using namespace std;

struct Node {
  char* value;
  struct Node* next;

  Node() {
    next = NULL;
    value = nullptr;
  }
};
void enqueue(Node* &head, char* &data);
void dequeue(Node* head);

void enqueue(Node* &head, char* &data) {
  Node* newNode = new Node();
  newNode->value = data;
  newNode->next = NULL;
  
  if (head == NULL) {
    head = newNode;
  } else {
    Node* temp = head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

Node* push(Node* &head, char* &data) {
  Node* newNode = new Node();
  newNode->value = data;
  newNode->next = head;
  return newNode;
}

char* pop(Node* &head) { // CREATE A DESTRUCToR
  char* data = head->value;
  Node* temp = head->next;
  //delete head;
  head = temp;
  return data;
}
Node* push(Node* &head, char* &data);
char* pop(Node* &head);

int main() {
  /*Stack* stackHead = NULL; // head of stack 
  Stack* na = new Stack();
  char aa = 'a';
  na.value = 'a';
  Node nb = new Node();
  char bb = 'b';
  nb.value = 'b';
  st.push(na);
  st.push(nb);

  
  while () {
    cout << ' ' << st.top();
    st.pop();
    }*/

  Node* queueHead = NULL; // head of queue
  Node* stackHead = NULL; // head of stack

  
  
  
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
      opStack[opStackIndex] = '^'; // push
      opStackIndex++;
	//}
    }
    else if (input[i] == '*' || input[i] == '/') { // * or / operators
      if (opStack[opStackIndex-1] == '-' || opStack[opStackIndex-1] == '+') { // previous is smaller
	opStack[opStackIndex] = input[i]; // push
	char* pushed = &(input[i]);
        stackHead = push(stackHead, pushed);
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
	  char* popped = pop(stackHead); // pop
	  enqueue(queueHead, popped); // enqueue
	  outputIndex++;
	  opStack[opStackIndex-1] = '\0';
          opStackIndex--;
        }
        opStack[opStackIndex] = input[i]; // push
	char* pushed = &(input[i]);
	stackHead = push(stackHead, pushed);
        opStackIndex++;
      }
    }
    else if (input[i] == '+' || input[i] == '-') { // + or - operators
      if (opStackIndex == 0) { // if its the first in the stack.
	opStack[opStackIndex] = input[i]; // push
	char* pushed = &(input[i]);
        stackHead = push(stackHead, pushed);
	opStackIndex++;
      }
      else { // if not, its guaranteed to be the same or of lower precedence
	int len = strlen(opStack);
	for (int j = 0; j < len; j++) {
	  if (opStack[opStackIndex-1] == '(') { // create barrier at (
	    break;
	  }
	  output[outputIndex] = opStack[opStackIndex-1];
	  char* popped = pop(stackHead); // pop
          enqueue(queueHead, popped); // enqueue
	  outputIndex++;
	  opStack[opStackIndex-1] = '\0';
	  opStackIndex--;
	}
	opStack[opStackIndex] = input[i]; // push
	char* pushed = &(input[i]);
        stackHead = push(stackHead, pushed);
	opStackIndex++;
      }
    }
    else if (input[i] == '(') { // inside a parenthesis!
      opStack[opStackIndex] = input[i]; // push
      char* pushed = &(input[i]);
      stackHead = push(stackHead, pushed);
      opStackIndex++;
    }
    else if (input[i] == ')') { // parenthesis ended
      //cout << "len" << strlen(opStack) << endl;
      int len = strlen(opStack);
      for (int j = 0; j < len; j++) {
	if (opStack[opStackIndex-1] == '(') { // stop at (
	  opStack[opStackIndex-1] = '\0';
	  char* popped = pop(stackHead); // pop
	  opStackIndex--;
	  break;
	}
	output[outputIndex] = opStack[opStackIndex-1];
	char* popped = pop(stackHead); // pop
	enqueue(queueHead, popped); // enqueue
	outputIndex++;
	opStack[opStackIndex-1] = '\0';
	opStackIndex--;
      }
    }
    else { // not an operator
      output[outputIndex] = input[i];
      char* cp = &(output[outputIndex]); // enqueue
      enqueue(queueHead, cp);
      outputIndex++;
    }
  }

  //cout << strlen(opStack) << endl;
  //cout << output << endl;
  int len = strlen(opStack);
  for (int j = 0; j < len; j++) {
    output[outputIndex] = opStack[opStackIndex-1];
    char* popped = pop(stackHead); // pop
    enqueue(queueHead, popped); // enqueue
    outputIndex++;
    opStack[opStackIndex-1] = '\0';
    opStackIndex--;
  }

  cout << output << endl;

  // display the queue:
  if (queueHead != NULL) {
    Node* temp = queueHead;
    while (temp != NULL) {
      cout << *temp->value << " ";  // Dereference value to print the character
      temp = temp->next;
    }
    cout << endl;
  }

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

/*void enqueue(Node* &head, char* &data) {
  // Add the element to the rear
  if (head == NULL){
    Node* newHead = new Node();
    newHead->value = data;
    head = newHead;
  }
  else if (head->next == NULL) {
    Node* newNode = new Node();
    newNode->value = data;
    head->next = newNode;
  }
  else {
    enqueue(head->next, data); // recurse until the end of the queue
  }
  }*/

void dequeue(Node* head) {
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
