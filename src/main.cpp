#include "../include/FileWriter.h"
#include <iostream>
#include <map>
#include <string>

int main() {
  FileWriter writer = FileWriter("text.txt");
  std::map<std::string, std::set<std::string>> map;
  map.insert(
      std::pair("key1", std::set<std::string>{"value0", "value1", "value2"}));
  map.insert(
      std::pair("key2", std::set<std::string>{"value0", "value1", "value2"}));
  map.insert(
      std::pair("key3", std::set<std::string>{"value0", "value1", "value2"}));
  writer.writeMultiMap(map);
  std::cout << "hello world\n";
  return 0;
}