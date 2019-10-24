#include <stdio.h>
#include <unistd.h>

int main () {
   char buf[BUFSIZ];

   setbuf(stdout, buf);
   puts("This is tutorialspoint");
   sleep(1);
   fflush(stdout);
   sleep(2);
   return(0);
}