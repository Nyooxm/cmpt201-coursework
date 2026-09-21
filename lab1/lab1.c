#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *lineptr = NULL;
  size_t length = 0;

  while (1) {
    printf("Please enter some text: ");

    ssize_t num = getline(&lineptr, &length, stdin);
    if (num == -1) {
      perror("getline failed.");
      exit(EXIT_FAILURE);
    }
    printf("Tokens:\n");
    char *saveptr;
    char *token = strtok_r(lineptr, " ", &saveptr);
    while (token != NULL) {
      printf(" %s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }
  }
  free(lineptr);
  return 0;
}
