#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){
  pid_t pid1, pid2;
  int status;
  pid1 = fork();
  if(pid1<0){
    perror("Fork failed");
    return 1;
  } 
  else if(pid1==0){
  printf("Child1 (PID%d):exiting normally with code 10\n", getpid());
  exit(10);
  }
  wait(&status);
      if(WIFEXITED(status)){
        printf("Parents:Child1 exited wiht code %d \n", WEXITSTATUS(status));
        
      }
      pid2 = fork();
      if (pid2<0){
       perror("Fork failed");
       return 1;
      }
      else if(pid2 == 0){
       printf("Child2 (PID%d):aborting....\n",getpid());
       abort();
      }
      wait(&status);
      if(WIFSIGNALED(status)){
       printf("Parent: Child2 terminated by signal %d\n", WTERMSIG(status));
      }
      printf("Parent:Done.\n");
      return 0;
     } 
