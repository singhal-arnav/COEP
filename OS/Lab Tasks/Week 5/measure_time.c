#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int run_and_measure(char *cmd)
{
  int start = uptime();

  int pid = fork();
  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }

  if(pid == 0){
    char *argv[] = { cmd, 0 };
    exec(cmd, argv);
    printf(1, "exec %s failed\n", cmd);
    exit();
  } else {
    wait();
    int end = uptime();
    return end - start;
  }
}

int
main(int argc, char *argv[])
{
  int fd = open("time.txt", O_CREATE | O_WRONLY);
  if(fd < 0){
    printf(1, "failed to open time.txt\n");
    exit();
  }

  int t1 = run_and_measure("usertests");
  int t2 = run_and_measure("stressfs");

  printf(fd, "usertests: %d ticks (~%d.%d seconds)\nstressfs: %d ticks (~%d.%d seconds)\n", t1, t1/100, (t1%100)*10, t2, t2/100, (t2%100)*10);
  
  close(fd);

  exit();
}

