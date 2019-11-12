#include <string.h>
#include <stdio.h>

int main () {
   char str[100] = "gremio;inter;santos;saopaulo";
   const char s[2] = ";";
   char *token;
   char times[4][20] = {"","","",""};
	
   /* retorna o primeiro token */
   token = strtok(str, s);
   
   int i=0;

   /* navega nos proximos tokens */
   while( token != NULL ) {
      strcpy(times[i],token);
      i++;
      //printf("%s\n", token );
    
      token = strtok(NULL, s);
   }

   printf("%s\n",times[0]);
   printf("%s\n",times[1]);
   printf("%s\n",times[2]);
   printf("%s\n",times[3]);
   
   return(0);
}
