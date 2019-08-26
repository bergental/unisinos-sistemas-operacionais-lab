#include <stdio.h>

int main(){
    char string[] = "Teste";
    for(int i = 0; i < sizeof(string); i++)
        if(string[i] != '\0')
            printf("%c\n", string[i]);
}