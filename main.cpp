#include <iostream>
#include <cstring>
// good progress today maybe. took forever but got the postfix and infix to finally work and after cleaning up some code and adding comments, it stopped working bruh. im gonna figure this out tomorrow

using namespace std;

struct Node { // used for making the linked list for the stacks and queues in the shunting yard algorithm
  char* value;
  struct Node* next;

  Node() {
    next = NULL;
    value = nullptr;
  }
};

// moved the btn file here because this is what i wanted to do initially and i dont have to swap tabs so much.
class btn { // binary tree node class
public:
  char* value;
  btn* left;
  btn* right;

  // constructor requires setting its value
  btn(char* val) {
    value = val;
    left = nullptr;
    right = nullptr;
  }

  // destructor
  ~btn() {
    delete[] value;
  }

  // set left child
  void setLeft(btn* node) {
    left = node;
  }

  // set right child
  void setRight(btn* node) {
    right = node;
  }

  // get left
  btn* getLeft() {
    return left;
  }

  // get the right child
  btn* getRight() {
    return right;
  }

  // get the char value
  char* getValue() {
    return value;
  }
};

// stack for storing the btns. this is a linked list
struct btnStack {
  btn* value;
  btnStack* next;

  // constructor sets the value which is a btn when called
  btnStack(btn* node) {
    next = nullptr;
    value = node;
  }
};

// prototypes
void enqueue(Node* &head, char* &data);
char* dequeue(Node* &head);
void push(Node* &head, char* &data);
char* pop(Node* &head);
char* peek(Node* &head);
void pushTree(btnStack*& head, btn* node);
btn* popTree(btnStack*& head);
void printPostfix(btn* node);
void printInfix(btn* node);
void printPrefix(btn* node);

// enqueue to the queue
void enqueue(Node* &head, char* &data) {
  Node* newNode = new Node(); // makes a new node to modify and add
  newNode->value = data;
  newNode->next = NULL;
  
  if (head == NULL) { // this becomes the head if the queue is empty
    head = newNode;
  } else { // add the node to the end of the queue linked list (last in)
    Node* temp = head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

// dequeue from the queue
char* dequeue(Node* &head) {
  if (head == NULL) { // empty
    return nullptr;
  }

  // take the heads value and remove it (first out)
  Node* temp = head;
  char* data = temp->value;
  head = head->next;
  delete temp;
  return data;
}

// push pop peek functions for stacks
void push(Node* &head, char* &data) { // first in
  Node* newNode = new Node();
  newNode->value = data;
  newNode->next = head;
  head = newNode;
}

char* pop(Node* &head) { // first out
  if (head == NULL) {
    return nullptr;
  }
  Node* temp = head;
  char* data = temp->value;
  head = head->next;
  delete temp;
  return data;
}

char* peek(Node* &head) { // peek at the first
  if (head == NULL) {
    return nullptr;
  }
  return head->value;
}

// push and pops, similar to the stack earlier
void pushTree(btnStack*& head, btn* node) { // first in
  btnStack* newNode = new btnStack(node); // make a new one to make first
  newNode->next = head;
  head = newNode;
}

btn* popTree(btnStack*& head) { // first out
  if (!head) { 
    return nullptr;
  }
  btnStack* temp = head;
  btn* node = temp->value;
  head = head->next;
  delete temp;
  return node;
}

// functions for printing the postfix, infix, and prefix from the trees head
void printPostfix(btn* node) {
  if (node == nullptr) { // stop
    return;
  }

  printPostfix(node->getLeft()); // go through the left half of the tree
  printPostfix(node->getRight()); // also go through the right half
  cout << *node->getValue(); // print the value of the node
}

void printInfix(btn* node) {
  if (node == nullptr) { // stop
    return;
  }

  // put starting parenthesis if its a left or right child
  if (node->getLeft() != nullptr || node->getRight() != nullptr) {
      cout << "(";
  }

  printInfix(node->getLeft()); // go through the left half of the tree
  cout << *node->getValue(); // print that value, typically an operator
  printInfix(node->getRight()); // go through the right

  // put ending parenthesis for the same reason after it printed
  if (node->getLeft() != nullptr || node->getRight() != nullptr) {
      cout << ")";
  }
}

void printPrefix(btn* node) {
  if (node == nullptr) { // stop
    return;
  }

  cout << *node->getValue(); // print the character
  printPrefix(node->getLeft()); // go through the left of the tree
  printPrefix(node->getRight()); // then go through the right
}

int main() {
  Node* queueHead = NULL; // head of queue
  Node* stackHead = NULL; // head of stack
  
  cout << "Type an expression in infix notation: ";

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
      char* pushed = new char(input[i]);
      push(stackHead, pushed); // push
      opStackIndex++;
    }
    else if (input[i] == '*' || input[i] == '/') { // * or / operators
      if (opStackIndex == 0 || *(peek(stackHead)) == '+' || *(peek(stackHead)) == '-') { // previous is smaller or end of stack
	      opStack[opStackIndex] = input[i];
        char* pushed = new char(input[i]);
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
        char* pushed = new char(input[i]);
        push(stackHead, pushed); // push
        opStackIndex++;
      }
    }
    else if (input[i] == '+' || input[i] == '-') { // + or - operators
      if (opStackIndex == 0) { // if its the first in the stack.
        opStack[opStackIndex] = input[i];
        char* pushed = new char(input[i]);
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
        char* pushed = new char(input[i]);
        push(stackHead, pushed); // push
        opStackIndex++;
      }
    }
    else if (input[i] == '(') { // inside a parenthesis!
      opStack[opStackIndex] = input[i];
      char* pushed = new char(input[i]);
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

  // add the rest of the stack to the queue cause its now done with the other chars
  /*while (opStackIndex > 0) {
    output[outputIndex] = opStack[opStackIndex-1];
    char* popped = pop(stackHead);
    enqueue(queueHead, popped);
    outputIndex++;
    opStackIndex--;
  }*/

  /*// display the queue:
  if (queueHead != NULL) {
    Node* temp = queueHead;
    while (temp != NULL) {
      cout << *temp->value << " ";
      temp = temp->next;
    }
    cout << endl;
  }*/

  // creating the tree
  btnStack* treeStack = nullptr; // binary tree stack head
  while (queueHead != nullptr) {
      char* val = dequeue(queueHead); // char value from the dequeue
      btn* newNode = new btn(val); // new parent

      if (*val == '+' || *val == '-' || *val == '*' || *val == '/' || *val == '^') { // we need to make the last two in the stack combine under a tree
          if (treeStack != nullptr) {
              newNode->setRight(popTree(treeStack)); // set the right child
          }
          if (treeStack != nullptr) {
              newNode->setLeft(popTree(treeStack)); // set the left child
          }
      }

      // otherise, push it into the stack
      pushTree(treeStack, newNode);
  }

  // now we should only have one thing left in the stack. we'll just put that node into it's own thing
  btn* treeFinish = popTree(treeStack);

  // print the infix postfix and previx
  cout << endl << "Infix: ";
  printInfix(treeFinish);
  cout << endl;

  cout << endl << "Postfix: ";
  printPostfix(treeFinish);
  cout << endl;

  cout << endl << "Prefix: ";
  printPrefix(treeFinish);
  cout << endl;
  
  return 0;
}
