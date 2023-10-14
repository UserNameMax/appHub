#include "../include/MyLib.h"
#include <iostream>
int main() {
  MyLib myLib = MyLib("../deps/omp");
  char *file = "../deps/text.txt";
  myLib.regist("nano", "/bin/nano", ".txt");
  myLib.open(".txt", file);
  return 0;
}