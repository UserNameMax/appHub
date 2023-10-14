#include "../include/FileReader.h"
#include "../include/FileWriter.h"
#include <cerrno>
#include <cstddef>
#include <dirent.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <string>
#include <sys/stat.h>
#include <utility>

void prepair(std::string dirName) {
  auto pDir = opendir(dirName.c_str());
  if (pDir == NULL && errno == 2) {
    mkdir(dirName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  } else {
    closedir(pDir);
  }
}
void regist(std::string name, std::string path, std::string type) {
  FileReader *reader = new FileReader("resources/types");
  auto typesMap = reader->readMultiMap();
  delete reader;
  reader = new FileReader("resources/progs");
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
  FileWriter *writer = new FileWriter("resources/types");
  writer->writeMultiMap(typesMap);
  delete writer;
  writer = new FileWriter("resources/progs");
  writer->writeSimpleMap(programs);
  delete writer;
}
void execute(std::string type) {}

int main(int argc, char *argv[]) {
  if (argc < 2)
    return 0;
  prepair("./resources");
  if (std::string(argv[1]) == "-r") {
    if (argc < 5)
      return 0;
    regist(argv[2], argv[3], argv[4]);
    return 0;
  }
  if (std::string(argv[1]) == "-e") {
    if (argc < 3)
      return 0;
    execute(argv[2]);
    return 0;
  }
  return 0;
}