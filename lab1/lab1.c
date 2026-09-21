#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *lineptr = NULL;
  size_t length = 0;

  while (1) {
    printf("Please enter some text: ");
    if (getline(&lineptr, &length, stdin) == -1) {
      break;
    }
    printf("Tokens:\n");
    char *saveptr;
    char *token = strtok_r(lineptr, &saveptr);
    while (token != NULL) {
      printf(" %s\n, token);
      token = strtok_r(NULL, &saveptr);
    }
  }
  free(lineptr);
  return 0;
}
