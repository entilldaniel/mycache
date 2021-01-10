#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "protocol.h"
#include "handler.h"

void *extract_data(int data_type, char *data);
char *extract_key(char *data);

struct command *handle(char *data) {
  char *token = strtok(data, "::");

  struct command *c = malloc(sizeof(struct command));
  int pass = 0;
  while (token != NULL) {
	switch (pass) {
	case 0:
	  printf("1:: %s\n", token);
	  c->action = atoi(token);
	  break;
	case 1:
	  printf("2:: %s\n", token);
	  c->data_type = atoi(token);
	  break;
	case 2:
	  printf("3\n");
	  c->data = extract_key(token);
	  break;	  
	case 3:
	  printf("4\n");
	  c->data = extract_data(c->data_type, token);
	  break;
	default:
	  perror("invalid input.\n");
	}
	token = strtok(NULL, "::");
	++pass;
  }
  
  return c;
}

char *extract_key(char *data) {
  int len = strlen(data);
  char *key = malloc(sizeof(char) * (len+1));
  strcpy(key, data);
  return key;
}

void *extract_data(int data_type, char *data) {
  printf("data type: %d\n", data_type);
  if (data_type == DATA_NUM) {
	int *result = malloc(sizeof(int));
	*result = atoi(data);
	return result;
  } else if (data_type == DATA_STR) {
	int len = strlen(data);
	printf("data: %s\n", data);
	char *result = malloc(sizeof(char) * (len + 1));
	strcpy(result, data);
	return result;
  } else {
	perror("Could not extract data type.");
	int *result = malloc(sizeof(int));
	*result = -1;
	return result;
  }
}


