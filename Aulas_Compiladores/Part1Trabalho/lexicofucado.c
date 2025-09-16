// lexer_int_scanf_main.c - analisador léxico para inteiros e + - * / ( )
// Compilar: gcc -std=c11 -O2 lexer_int_scanf_main.c -o lexer_int
// Testar:   echo "12*(3+4) - 5/2" | ./lexer_int

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ========================= Definições ========================= */

typedef enum {
    TOKEN_INTEIRO,          // NÚMEROS INTEIROS
    TOKEN_FLOAT,            // NÚMEROS QUEBRADOS
    TOKEN_PONTOEVIRGULA,    // ;
    TOKEN_VIRGULA,          // ,
    TOKEN_DOISPONTOS,       // :
    TOKEN_IGUAL,            // =
    TOKEN_MAIS,             // +
    TOKEN_MENOS,            // -
    TOKEN_MULT,             // *
    TOKEN_DIV,              // /
    TOKEN_MAIOR,            // >
    TOKEN_MENOR,            // <
    TOKEN_ABRE_PAR,         // (
    TOKEN_FECHA_PAR,        // )
    TOKEN_PROGRAM,          // PROGRAM
    TOKEN_VARIAVEL,         // VARIAVEL
    TOKEN_BEGIN,            // BEGIN
    TOKEN_VAR,              // VAR
    TOKEN_IF,               // IF
    TOKEN_THEN,             // THEN
    TOKEN_ELSE,             // ELSE
    TOKEN_WHILE,            // WHILE
    TOKEN_DO,               // DO
    TOKEN_END,              // END 
    TOKEN_FIM,
    TOKEN_ERRO
} TipoToken;

typedef struct {
    TipoToken tipo;
    char *lexema;
    int linha;
    int coluna;
} Token;

typedef struct {
    const char *src;
    int i;
    int linha, coluna;
    char c;
} Scanner;

char* nome_token(TipoToken t){
    switch(t){
        case TOKEN_INTEIRO:   return "INTEIRO";
        case TOKEN_MAIS:      return "MAIS";
        case TOKEN_MENOS:     return "MENOS";
        case TOKEN_MULT:      return "MULT";
        case TOKEN_DIV:       return "DIV";
        case TOKEN_PONTOEVIRGULA: return "PONTO E VIRGULA";
        case TOKEN_ABRE_PAR:  return "ABRE_PAR";
        case TOKEN_FECHA_PAR: return "FECHA_PAR";
        case TOKEN_FIM:       return "FIM";
        case TOKEN_ERRO:      return "ERRO";
        case TOKEN_FLOAT:     return "RACIONAL";
        case TOKEN_VIRGULA:   return "VIRGULA";
        case TOKEN_DOISPONTOS:return "DOISPONTOS";
        case TOKEN_IGUAL:     return "IGUAL";
        case TOKEN_MAIOR:     return "MAIOR";
        case TOKEN_MENOR:     return "MENOR";
        case TOKEN_PROGRAM:   return "PROGRAM";
        case TOKEN_VARIAVEL:  return "IDENTIFICADOR";
        case TOKEN_BEGIN:     return "BEGIN";
        case TOKEN_VAR:       return "VAR";
        case TOKEN_IF:        return "IF";
        case TOKEN_THEN:      return "THEN";
        case TOKEN_ELSE:      return "ELSE";
        case TOKEN_WHILE:     return "WHILE";
        case TOKEN_DO:        return "DO";
        case TOKEN_END:       return "END";
        default:              return "?";
    }
}

char *str_ndup(const char *s, size_t n){
    char *p = (char*)malloc(n+1);
    if(!p){ fprintf(stderr,"Memória insuficiente\n"); exit(1); }
    memcpy(p, s, n); p[n]='\0'; return p;
}

void iniciar(Scanner *sc, const char *texto, int LinhaAntiga){
    sc->src = texto ? texto : "";
    sc->i = 0; 
    sc->linha = LinhaAntiga; 
    sc->coluna = 1;
    sc->c = sc->src[0];
}

void avancar(Scanner *sc){
    if(sc->c=='\0') return;
    if(sc->c=='\n'){ sc->linha++; sc->coluna=1; }
    else           { sc->coluna++; }
    sc->i++;
    sc->c = sc->src[sc->i];
}

void pular_espacos(Scanner *sc){
    while(isspace((unsigned char)sc->c)) avancar(sc);
}

Token criar_token_texto(Scanner *sc, TipoToken tipo, const char *ini, size_t n, int lin, int col){
    (void)sc;
    Token t; t.tipo=tipo;
    t.lexema=str_ndup(ini,n); 
    t.linha=lin; t.coluna=col; 
    return t;
}

Token token_simples(Scanner *sc, TipoToken tipo){
    int lin=sc->linha, col=sc->coluna;
    char ch=sc->c; avancar(sc);
    return criar_token_texto(sc, tipo, &ch, 1, lin, col);
}

Token token_erro_msg(Scanner *sc, const char *msg){
    return criar_token_texto(sc, TOKEN_ERRO, msg, strlen(msg), sc->linha, sc->coluna);
}

Token coletar_inteiro(Scanner *sc){
    int lin=sc->linha, col=sc->coluna;
    size_t ini = sc->i;
    if(!isdigit((unsigned char)sc->c)) return token_erro_msg(sc, "Inteiro malformado");
    while(isdigit((unsigned char)sc->c)) avancar(sc);
    return criar_token_texto(sc, TOKEN_INTEIRO, sc->src+ini, sc->i-ini, lin, col);
}
// coleta a palavara toda
Token coletar_palavra(Scanner *sc) {
    int lin = sc->linha, col = sc->coluna;
    size_t ini = sc->i;

    // Primeiro caractere deve ser letra
    if(!isalpha((unsigned char)sc->c))
        return token_erro_msg(sc, "Identificador malformado");

    // Continua enquanto for letra
    while(isalnum((unsigned char)sc->c))
        avancar(sc);

    // Pega a variavel
    Token t = criar_token_texto(sc, TOKEN_VARIAVEL, sc->src + ini, sc->i - ini, lin, col);

    // Muda para palavra reservada
    if(strcmp(t.lexema, "program") == 0) t.tipo = TOKEN_PROGRAM;
    else if(strcmp(t.lexema, "var") == 0) t.tipo = TOKEN_VAR;
    else if(strcmp(t.lexema, "begen") == 0) t.tipo = TOKEN_BEGIN;
    else if(strcmp(t.lexema, "end") == 0) t.tipo = TOKEN_END;
    else if(strcmp(t.lexema, "if") == 0) t.tipo = TOKEN_IF;
    else if(strcmp(t.lexema, "then") == 0) t.tipo = TOKEN_THEN;
    else if(strcmp(t.lexema, "else") == 0) t.tipo = TOKEN_ELSE;
    else if(strcmp(t.lexema, "while") == 0) t.tipo = TOKEN_WHILE;
    else if(strcmp(t.lexema, "do") == 0) t.tipo = TOKEN_DO;
    else if(strcmp(t.lexema, "integer") == 0) t.tipo = TOKEN_INTEIRO;
    else if(strcmp(t.lexema, "real") == 0) t.tipo = TOKEN_FLOAT;
    return t;
}



Token proximo_token(Scanner *sc){
    pular_espacos(sc);
    if(sc->c=='\0') return criar_token_texto(sc, TOKEN_FIM, "", 0, sc->linha, sc->coluna);

    if(isdigit((unsigned char)sc->c)) return coletar_inteiro(sc);

    if(isalpha((unsigned char)sc->c)) return coletar_palavra(sc); 

    switch(sc->c){
        case '+': return token_simples(sc, TOKEN_MAIS);
        case '-': return token_simples(sc, TOKEN_MENOS);
        case '*': return token_simples(sc, TOKEN_MULT);
        case '/': return token_simples(sc, TOKEN_DIV);
        case '(': return token_simples(sc, TOKEN_ABRE_PAR);
        case ')': return token_simples(sc, TOKEN_FECHA_PAR);
        case ';': return token_simples(sc, TOKEN_PONTOEVIRGULA);
        case ':': return token_simples(sc, TOKEN_DOISPONTOS);
        case '=': return token_simples(sc, TOKEN_IGUAL);
        case '>': return token_simples(sc, TOKEN_MAIOR);
        case '<': return token_simples(sc, TOKEN_MENOR);
        case ',': return token_simples(sc, TOKEN_VIRGULA);

        
        default: {
            char msg[64];
            snprintf(msg, sizeof(msg), "Caractere inválido: '%c'", sc->c);
            avancar(sc);
            return token_erro_msg(sc, msg);
        }
    }
}



/* ========================= main ========================= */

int main(void){

    FILE * fp = fopen("teste.pas", "r");
    FILE * out = fopen("teste.lex", "w");
    
    char Entrada[1024];
    int Linha = 1;

    while(fscanf(fp, "%[^\n]\n", Entrada) > 0) {
        Scanner S; 
        strcat(Entrada, "\n");
        printf("%s", Entrada);
        iniciar(&S, Entrada, Linha);

        for(;;){
            Token t = proximo_token(&S);
            fprintf(out, "{%-16s: %-9s } - \t\t linha %d, col %d\n",
                nome_token(t.tipo), t.lexema, Linha, t.coluna);
            free(t.lexema);
            if(t.tipo==TOKEN_FIM || t.tipo==TOKEN_ERRO) break;
        }
        Linha++;
    }

    return 0;
}
