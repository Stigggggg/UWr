#include "csapp.h"
#include "signal.h"

static void signal_handler(int signum, siginfo_t *info, void *data)
{
	if (signum == SIGINT)
	{
		safe_printf("(%d) Screw you guys... I'm going home!\n", getpid());
		_exit(0);
	}
}

static void play(pid_t next, const sigset_t *set)
{
	for (;;)
	{
		printf("(%d) Waiting for a ball!\n", getpid());
		Sigsuspend(set); //musi czekać na sygnał SIGUSR1 (piłkę)
		usleep((300 + random() % 400) * 1000);
		Kill(next, SIGUSR1); //po dostaniu sygnału zagrywa do następnego
		printf("(%d) Passing ball to (%d)!\n", getpid(), next);
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		app_error("Usage: %s [CHILDREN]", argv[0]);

	int children = atoi(argv[1]);

	if (children < 4 || children > 20)
		app_error("Give number of children in range from 4 to 20!");

	struct sigaction action = {.sa_sigaction = signal_handler};
	Sigaction(SIGINT, &action, NULL);
	Sigaction(SIGUSR1, &action, NULL);
     
	sigemptyset(&action.sa_mask); //czyscimy maske ojca
  sigaddset(&action.sa_mask, SIGUSR1); 
  Sigprocmask(SIG_BLOCK, &action.sa_mask, &action.sa_mask);

  pid_t next_pid = getpid(); //pid ojca
  for (int i = 0; i < children; i++)
  {
      pid_t pid = Fork(); //tworzyny dziecko
      if (pid == 0)
        play(next_pid, &action.sa_mask); //dziecko wie, że będzie grać do jakiegoś następnego
      else
        next_pid = pid; //ojciec szuka najmłodszego
  }
  Kill(next_pid, SIGUSR1); //wprowadzenie ojca do gry
  play(next_pid, &action.sa_mask);

	return EXIT_SUCCESS;
}