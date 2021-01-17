#include "handler.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char data[2048] = "2::2::foo::bajs";
  struct command *result = handle(data);
  printf("result: %s\n", (char*)result->data);
  free(result);

  char data2[2048] = "2::1::bar::123";
  result = handle(data2);
  int *d = (int*)result->data;
  printf("result: %d\n", *d);
  free(result);
  
  return 0;
}



