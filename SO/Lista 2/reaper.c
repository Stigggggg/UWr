#include "csapp.h"

static pid_t spawn(void (*fn)(void)) {
  pid_t pid = Fork();
  if (pid == 0) {
    fn();
    printf("(%d) I'm done!\n", getpid());
    exit(EXIT_SUCCESS);
  }
  return pid;
}

static void grandchild(void) {
  printf("(%d) Waiting for signal!\n", getpid());
  pause();
  printf("(%d) Got the signal!\n", getpid());
}

static void child(void) {
  pid_t pid;
  pid = spawn(grandchild);
  setpgid(pid, getpgrp());
  printf("(%d) Grandchild (%d) spawned!\n", getpid(), pid);
}

static void ps(void) {
  pid_t pid = Fork();
  if (pid == 0){
    char *argv[] = {"/bin/ps", "-o", "pid,ppid,pgrp,stat,cmd", NULL};
    execve("/bin/ps", argv, environ);
    exit(EXIT_SUCCESS);
  }
  waitpid(pid, NULL, 0);
}

int main(void) {
  /* TODO: Make yourself a reaper. */
#ifdef LINUX
  Prctl(PR_SET_CHILD_SUBREAPER, 1);
#endif
  printf("(%d) I'm a reaper now!\n", getpid());

  pid_t pid;
  int status;
  pid = spawn(child);
  setpgid(pid, 0);
  waitpid(pid, &status, 0);
  ps();
  kill(-pid, SIGINT);
  waitpid(-pid, &status, 0);

  return EXIT_SUCCESS;
}
