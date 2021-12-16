#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int getNumeroDuGroupe(int pid){
  return getpgid(pid);
}


int main(int argc , char* argv[]){
  int nb_process;
  printf("Entrez le nombre de process que vous voulez creer : ");
  scanf("%d",&nb_process);
  printf("\nLe numero de pid est : %d\n",getpid());
  printf("Le numero du groupe est : %d\n",getNumeroDuGroupe(getpid()));
  for(int i=0;i<nb_process;i++){
    fork();
  }

  printf("Hello Guys\n");
}
