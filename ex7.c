#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


int main(){
  //create file discrepter
  int fd[2];
  if(pipe(fd) < 0){
    //error occured
    return 1;
  }

  int pid1 = fork();
  if(pid1 < 0){
    return 2;
  }

  if( pid1 == 0){
    //first child
    int n1,n2;
    close(fd[0]);
    printf("Entrez 2 nombre entier : ");
    scanf("%d%d",&n1,&n2);

    if(write(fd[1],&n1,sizeof(int)) < 0){
      return 3;
    }

    if(write(fd[1],&n2,sizeof(int)) < 0){
      return 4;
    }

    close(fd[1]);

  }

  int pid2 = fork();

  if(pid2 < 0){
    return 5;
  }

  if( pid2 == 0){
    //second child process
    int n1,n2;
    close(fd[1]);
    if(read(fd[0],&n1,sizeof(int)) < 0){
      return 6;
    }

    if(read(fd[0],&n2,sizeof(int)) < 0){
      return 7;
    }

    printf("La somme de ces 2 nombres est : %d\n",n1+n2);

    close(fd[0]);

  }

  
  waitpid(pid1,NULL,0);
  waitpid(pid2,NULL,0);


  printf("\n");
  return 0;
}
