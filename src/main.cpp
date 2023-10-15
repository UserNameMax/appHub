#include "../include/FileReader.h"
#include "../include/FileWriter.h"
#include <cerrno>
#include <cstddef>
#include <dirent.h>
#include <iostream>
#include <map>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <utility>

std::string resPath;

void prepair(std::string dirName) {
  auto pDir = opendir(dirName.c_str());
  if (pDir == NULL && errno == 2) {
    mkdir(dirName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  } else {
    closedir(pDir);
  }
}
void regist(std::string name, std::string path, std::string type) {
  FileReader *reader = new FileReader(resPath + "/types");
  auto typesMap = reader->readMultiMap();
  delete reader;
  reader = new FileReader(resPath + "/progs");
  auto programs = reader->readSimpleMap();
  delete reader;
  if (typesMap.count(type)) {
    if (typesMap[type].count(name) == 0) {
      typesMap[type].insert(name);
    }
  } else {
    typesMap.insert(std::pair(type, std::set{name}));
  }
  programs[name] = path;
  FileWriter *writer = new FileWriter(resPath + "/types");
  writer->writeMultiMap(typesMap);
  delete writer;
  writer = new FileWriter(resPath + "/progs");
  writer->writeSimpleMap(programs);
  delete writer;
}
void execute(std::string type, char *file) {
  FileReader *reader = new FileReader(resPath + "/types");
  auto typesMap = reader->readMultiMap();
  delete reader;
  reader = new FileReader(resPath + "/progs");
  auto programs = reader->readSimpleMap();
  delete reader;
  if (typesMap.count(type)) {
    auto progs = typesMap[type];
    auto name = *(progs.begin());
    if (progs.size() > 1) {
      for (auto selectProg = progs.cbegin(); selectProg != progs.cend();
           ++selectProg) {
        char answer;
        std::cout << "open with " << *selectProg << " (y/n): ";
        std::cin >> answer;
        if (answer == 'y') {
          name = *selectProg;
          break;
        }
      }
    }
    auto path = programs[name];
    char *pPath = new char[path.length() + 1];
    strcpy(pPath, path.c_str());
    char *argVec[3] = {pPath, file, NULL};
    execve(argVec[0], argVec, NULL);
    std::cout << errno;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2)
    return 0;
  auto path = std::string(argv[0]);
  path.erase(path.begin() + path.find_last_of("/"), path.end());
  resPath = path + "/resources";
  prepair(resPath);
  if (std::string(argv[1]) == "-r") {
    if (argc < 5)
      return 0;
    regist(argv[2], argv[3], argv[4]);
    return 0;
  }
  if (std::string(argv[1]) == "-e") {
    if (argc < 4)
      return 0;
    execute(argv[2], argv[3]);
    return 0;
  }
  return 0;
}