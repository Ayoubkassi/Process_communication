#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>



int main(){

  //initialize our file descipter
  int fd[2][2];

  for(int i=0;i<2;i++){
    if(pipe(fd[i]) < 0){
      return 1;
    }
  }

  int pid1 = fork();
  if(pid1 < 0){
    return 2;
  }

  if(pid1 == 0){
    //process child 1
    close(fd[0][1]);
    close(fd[1][0]);


    char str[200];
    printf("Enter un mot : ");
    fgets(str,200,stdin);
    str[strlen(str)-1] = '\0';
    int n = strlen(str) + 1;



    if(write(fd[1][1],&n,sizeof(int)) < 0){
      return 3;
    }

    //transformation du string

    for (int i = 0; str[i]!='\0'; i++) {
      if(str[i] >= 'a' && str[i] <= 'z') {
         str[i] = str[i] -32;
      }
   }

    if(write(fd[1][1],str,sizeof(char) * n) < 0){
      //error case
      return 4;
    }

    close(fd[0][0]);
    close(fd[1][1]);
    return 0;


  }

  int pid2 = fork();

  if(pid2 < 0){
    return 5;
  }

  if(pid2 == 0){
    //child process 2

    close(fd[1][1]);
    close(fd[0][0]);

    char str[200];
    int n;

    // if(write(fd[0][1],&x,sizeof(int)) < 0){
    //   return 7;
    // }

    if(read(fd[1][0],&n,sizeof(int)) < 0){
      return 6;
    }
    if(read(fd[1][0],str,sizeof(char)*n) < 0){
      return 7;
    }

    printf("le string transforme au niveau de process 3 est : %s\n",str);


    close(fd[1][0]);
    close(fd[0][1]);

  }

  waitpid(pid1,NULL,0);
  waitpid(pid2,NULL,0);


  printf("\n");
  return 0;
}
