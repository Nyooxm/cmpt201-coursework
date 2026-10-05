#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 5

char *input_history[MAX_LEN];
int count = 0;
void add_history(char *input);
void remove_old(void);
void print_history();
char *get_input();

char *get_input() {
  char *buffer = NULL;
  size_t buffsize = 0;
  printf("Enter input: ");
  ssize_t len = getline(&buffer, &buffsize, stdin);
  if (len == -1) {
    free(buffer);
    return NULL;
  }
  buffer[len - 1] = '\0';
  return buffer;
}

void add_history(char *input) {
  if (count >= MAX_LEN) {
    remove_old();
  }
  input_history[count] = input;
  count++;
}

void remove_old(void) {
  if (count > 0) {
    free(input_history[0]);
    for (int i = 1; i < count; i++) {
      input_history[i - 1] = input_history[i];
    }
    count--;
  }
}

void print_history(void) {
  for (int i = 0; i < count; i++) {
    printf("%s\n", input_history[i]);
  }
}

int main() {
  char *input;
  while ((input = get_input()) != NULL) {
    add_history(input);
    if (strcmp(input, "print") == 0) {
      print_history();
    }
  }
}
