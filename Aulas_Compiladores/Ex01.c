#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum{Q0, Q1, Q2, Q3, ERRO} Estados;

Estados Transicao(Estados s, char x){

    switch(s){
        case Q0:
            if(x == 'a') return Q1;
            if(x == 'b') return Q0;
            break;
        
        case Q1:
            if(x == 'b') return Q1;
            if(x == 'a') return Q2;
            break;

        case Q2:
            if(x == 'b') return Q2;
            if(x == 'a') return Q1;
            break;

        default:
            break;
    }
    return ERRO;
}

int main(){
    char buffer[1024];
    
    printf("Digita a senha: ");

    while(fgets(buffer, sizeof(buffer), stdin)){
        
        Estados s = Q0;
        int flag = 1;

        for(int i = 0; buffer[i] != '\0'; i++){
            char ch = buffer[i];
            if(ch == '\n' || ch == '\r' || isspace(ch)) continue;
            if(ch != 'a' && ch != 'b'){flag = 0; break;}
            s = Transicao(s, ch);
            if(s == ERRO){flag = 0; break;}
        }

        if(flag == 1 && s == Q0 || s == Q2) puts("ACEITA");
        else puts("REJEITA");
    }
}