class MyLib {
private:
  char *_pathToLib;

public:
  MyLib(char *path);
  void regist(char *name, char *path, char *type);
  void open(char *type, char *file);
};