#include "../include/FileReader.h"
#include "../include/FileWriter.h"
#include <iostream>
#include <map>
#include <string>
#include <utility>

int main() {
  FileWriter *writer = new FileWriter("text.txt");
  writer->writeSimpleMap(
      std::map{std::pair<std::string, std::string>{"key", "value"},
               std::pair<std::string, std::string>{"key2", "value"}});
  delete writer;
  FileReader reader = FileReader("text.txt");
  auto map = reader.readSimpleMap();
  for (auto i : map) {
    std::cout << i.first << ": " << i.second << "\n";
  }
  std::cout << "hello world\n";
  return 0;
}