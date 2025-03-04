#include <iostream>
#include <cstring>

using namespace std;

class btn {
 public:
  char* value;
  btn* left;
  btn* right;

  btn();
};
