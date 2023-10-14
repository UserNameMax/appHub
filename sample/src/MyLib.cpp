#include "../include/MyLib.h"
#include <cerrno>
#include <cstddef>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
MyLib::MyLib(char *path) : _pathToLib(path) {}
void MyLib::regist(char *name, char *path, char *type) {
  pid_t chield;
  if ((chield = fork()) == 0) {
    char *argVec[] = {_pathToLib, "-r", name, path, type, NULL};
    execve(_pathToLib, argVec, NULL);
    std::cout << "chield: " << errno << "\n";
  } else {
    sleep(3);
    wait(&chield);
  }
}
void MyLib::open(char *type, char *file) {
  pid_t chield;
  if ((chield = fork()) == 0) {
    char *argVec[] = {_pathToLib, "-e", type, file, type, NULL};
    execve(_pathToLib, argVec, NULL);
    std::cout << "chield: " << errno << "\n";
  } else {
    sleep(3);
    wait(&chield);
  }
}