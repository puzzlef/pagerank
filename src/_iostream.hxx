#pragma once
#include <string>
#include <fstream>

using std::ios;
using std::string;
using std::ifstream;




// READ-FILE
// ---------

string readFile(const char *pth) {
  string a; ifstream f(pth);
  f.seekg(0, ios::end);
  a.resize(f.tellg());
  f.seekg(0);
  f.read(a.data(), a.size());
  return a;
}
