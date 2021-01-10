#include "handler.h"
#include <string.h>
#include <stdio.h>

int main(void) {
  char data[2048] = "2::2::foo::bajs";
  struct command *result = handle(data);
  printf("result: %s\n", (char*)result->data);

  return 0;
}



