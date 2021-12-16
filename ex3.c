#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
  int i, n = 5;
  pid_t  childpid;

  for(i = 1;i<n;i++){
    childpid = fork();
    if(childpid < 0) break;
    printf("processus %d avec pere %d , i =%d\n",getpid(),getppid(),i);
  }

  return 0;
}
