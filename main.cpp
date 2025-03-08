#include <iostream>
#include <cstring>
#include "btn.h"
// got the peek working. that was actually really easy. now time to figure out the binary tree

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
char* dequeue(Node* &head);
void push(Node* &head, char* &data);
char* pop(Node* &head);
char* peek(Node* &head);
void pushTree(btnStack*& head, btn* node);
btn* popTree(btnStack*& head);

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

char* dequeue(Node* &head) {
  if (head == NULL) {
    return nullptr;
  }
  Node* temp = head;
  char* data = temp->value;
  head = head->next;
  delete temp;
  return data;
}

void push(Node* &head, char* &data) {
  Node* newNode = new Node();
  newNode->value = data;
  newNode->next = head;
  head = newNode;
}

char* pop(Node* &head) {
  if (head == NULL) {
    return nullptr;
  }
  Node* temp = head;
  char* data = temp->value;
  head = head->next;
  delete temp;
  return data;
}

char* peek(Node* &head) {
  if (head == NULL) {
    return nullptr;
  }
  return head->value;
}

struct btnStack {
  btn* value;
  btnStack* next;

  btnStack(btn* node) {
    next = NULL;
    value = node;
  }
};

// push and pops, similar to the stack earlier
void pushTree(btnStack*& head, btn* node) {
    btnStack* newNode = new btnStack(node);
    newNode->next = head;
    head = newNode;
}

btn* popTree(btnStack*& head) {
    if (!head) return nullptr;
    btnStack* temp = head;
    btn* node = temp->value;
    head = head->next;
    delete temp;
    return node;
}

void printTree(btn* root, int depth = 0) {
    if (!root) return;
    printTree(root->right, depth + 1);
    for (int i = 0; i < depth; i++) cout << "  ";
    cout << *root->value << endl;
    printTree(root->left, depth + 1);
}

int main() {
  Node* queueHead = NULL; // head of queue
  Node* stackHead = NULL; // head of stack
  
  char input[20];
  cin.getline(input, 20);
  int inputLen = strlen(input);
  
  char opStack[20];
  int opStackIndex = 0;

  char output[20];
  int outputIndex = 0;
  
  // shunting yard algorithm
  for (int i = 0; i < inputLen; i++) {
    if (input[i] == '^') { // ^ operator
      opStack[opStackIndex] = '^';
      char* pushed = &(input[i]);
      push(stackHead, pushed);
      opStackIndex++;
    }
    else if (input[i] == '*' || input[i] == '/') { // * or / operators
      if (opStackIndex == 0 || *(peek(stackHead)) == '+' || *(peek(stackHead)) == '-') {//opStack[opStackIndex-1] == '+' || opStack[opStackIndex-1] == '-') { // previous is smaller or end of stack
	//char test = opStack[opStackIndex-1];
	//char* ptest = *test;
	//char* test = peek(stackHead);
	//cout << "test" << *test << endl;
	opStack[opStackIndex] = input[i];
        char* pushed = &(input[i]);
        push(stackHead, pushed);
        opStackIndex++;
      } else { // previous is greator or same
        while (opStackIndex > 0 && *(peek(stackHead)) != '(' && *(peek(stackHead)) != '+' && *(peek(stackHead)) != '-') { // create a barrier at ( and also continue with the the + and -
          output[outputIndex] = opStack[opStackIndex-1];
          char* popped = pop(stackHead); // pop
          enqueue(queueHead, popped); // enqueue
          outputIndex++;
          opStackIndex--;
        }
        opStack[opStackIndex] = input[i];
        char* pushed = &(input[i]);
        push(stackHead, pushed); // push
        opStackIndex++;
      }
    }
    else if (input[i] == '+' || input[i] == '-') { // + or - operators
      if (opStackIndex == 0) { // if its the first in the stack.
        opStack[opStackIndex] = input[i];
        char* pushed = &(input[i]);
        push(stackHead, pushed);
        opStackIndex++;
      } else { // if not, its gauranteed to be the same or of lower precedence
        while (opStackIndex > 0 && *(peek(stackHead)) != '(') { // create a barrier at (
          output[outputIndex] = opStack[opStackIndex-1];
          char* popped = pop(stackHead); // pop
          enqueue(queueHead, popped); // enqueue
          outputIndex++;
          opStackIndex--;
        }
        opStack[opStackIndex] = input[i];
        char* pushed = &(input[i]);
        push(stackHead, pushed); // push
        opStackIndex++;
      }
    }
    else if (input[i] == '(') { // inside a parenthesis!
      opStack[opStackIndex] = input[i];
      char* pushed = &(input[i]);
      push(stackHead, pushed); // push
      opStackIndex++;
    }
    else if (input[i] == ')') { // parenthesis ended
      while (opStackIndex > 0 && *(peek(stackHead)) != '(') { // stops at (
        output[outputIndex] = opStack[opStackIndex-1];
        char* popped = pop(stackHead); // pop
        enqueue(queueHead, popped); // enqueue
        outputIndex++;
        opStackIndex--;
      }
      if (opStackIndex > 0 && *(peek(stackHead)) == '(') { // removes it after the stop
        char* popped = pop(stackHead); // pop
        opStackIndex--;
      }
    }
    else { // not an operator
      output[outputIndex] = input[i];
      char* cp = &(output[outputIndex]);
      enqueue(queueHead, cp); // enqueue
      outputIndex++;
    }
  }

  // print the string version (delete this when done. just use this for comparison)
  while (opStackIndex > 0) {
    output[outputIndex] = opStack[opStackIndex-1];
    char* popped = pop(stackHead);
    enqueue(queueHead, popped);
    outputIndex++;
    opStackIndex--;
  }

  cout << output << endl;

  // display the queue:
  if (queueHead != NULL) {
    Node* temp = queueHead;
    while (temp != NULL) {
      cout << *temp->value << " ";
      temp = temp->next;
    }
    cout << endl;
  }

  // creating the tree
  btnStack* treeStack = nullptr; // binary tree stack head
  btn* test = NULL;
  while (queueHead != NULL) {
    // create and prepare the node
    char* val = dequeue(queueHead);
    btn* newNode = new btn();
    newNode->value = val;
    
    if (*val == '+' || *val == '-' || *val == '*' || *val == '/' || *val == '^') { // we need to make the last two in the stack combine under a tree
      newNode->right = pop(treeStack);
      newNode->left = pop(treeStack);
    }

    // otherise, push it into the stack
    push(treeStack, newNode);
  }
  
  cout << endl;

  // now we should only have one thing left in the stack. we'll just put that node into it's own thing
  btn* treeFinish = pop(treeStack);
  
  
  return 0;
}
