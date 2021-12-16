#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

  pid_t id = fork();
  if (pid == -1)
    perror("Erreur pour demarrer fork !!");
  //process pere
  else if(id != 0)
    printf("Identificateur du process pere : %d\n",getpid());
  //process fils
  else
    printf("Identificateur du process fils : %d\n",getpid());

  return 0;
}
