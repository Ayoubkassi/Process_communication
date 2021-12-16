#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(){

  int fd[2];
  if(pipe(fd) == -1){
    return 1;
  }

  int pid = fork();
  if(pid == -1){
    return 2;
  }

  if( pid == 0){
    //process child
    close(fd[0]);
    char str[200];
    printf("Entrez un string : ");
    fgets(str,200,stdin);
    str[strlen(str)-1] = '\0';
    int n = strlen(str) + 1;
    if(write(fd[1],&n,sizeof(int)) < 0){
      return 3;
    }
    if(write(fd[1],str,sizeof(char) * n) < 0){
      //error case
      return 4;
    }
    close(fd[1]);

  }else{
    //process parent
    close(fd[1]);
    char str[200];
    int n;


    if(read(fd[0],&n,sizeof(int)) < 0){
      return 5;
    }
    if(read(fd[0],str,sizeof(char)*n) < 0){
      return 6;
    }

    printf("la valeur Reçoit au Niveau du parent est  : %s\n",str);

    close(fd[0]);
    wait(NULL); //attendre la fin du process child

  }


  printf("\n");

  return 0;
}
