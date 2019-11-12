#include <string.h>
#include <stdio.h>

int main () {
   char str[100] = "Este;eh;um;exemplo;de;split";
   const char s[2] = ";";
   char *token;
   
   /* retorna o primeiro token */
   token = strtok(str, s);
   
   /* navega nos proximos tokens */
   while( token != NULL ) {
      printf("%s\n", token );
    
      token = strtok(NULL, s);
   }
   
   return(0);
}
