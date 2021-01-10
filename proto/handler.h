struct command {
  int action;
  int data_type;
  char* key;
  void *data;
};

struct command *handle(char* data);

