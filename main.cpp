#include <iostream>
#include <cstring>
// GOT THE PUSH POP WORKING YAY
// cleaned up the code as well
// next class figure out how to implement the peek in the algorithm. maybe replace the opStack[opStackIndex-1] or something. im going to sleep now

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
      if (opStackIndex == 0 || opStack[opStackIndex-1] == '+' || opStack[opStackIndex-1] == '-') { // previous is smaller or end of stack
        opStack[opStackIndex] = input[i];
        char* pushed = &(input[i]);
        push(stackHead, pushed);
        opStackIndex++;
      } else { // previous is greator or same
        while (opStackIndex > 0 && opStack[opStackIndex-1] != '(' && opStack[opStackIndex-1] != '+' && opStack[opStackIndex-1] != '-') { // create a barrier at ( and also continue with the the + and -
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
        while (opStackIndex > 0 && opStack[opStackIndex-1] != '(') { // create a barrier at (
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
      while (opStackIndex > 0 && opStack[opStackIndex-1] != '(') { // stops at (
        output[outputIndex] = opStack[opStackIndex-1];
        char* popped = pop(stackHead); // pop
        enqueue(queueHead, popped); // enqueue
        outputIndex++;
        opStackIndex--;
      }
      if (opStackIndex > 0 && opStack[opStackIndex-1] == '(') { // removes it after the stop
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
