// Receives user input from the keybrd
// full path of the program
// No need for commandline arg handling
// execs command user typed
// repeats the above two steps forever, use fork, exec & waitpid
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *path = NULL;
  size_t len = 0;
  ssize_t inputpath;

  while (1) {
    printf("Enter programs to run.\n");
    printf(">");
    inputpath = getline(&path, &len, stdin);
    if (inputpath == -1) {
      break;
    }
    path[inputpath - 1] = '\0';
    pid_t pid = fork();
    if (pid == 0) {
      execlp(path, path, NULL);
      printf("execlp failed!\n");
      return 1;
    } else {
      waitpid(pid, NULL, 0);
    }
  }
}
