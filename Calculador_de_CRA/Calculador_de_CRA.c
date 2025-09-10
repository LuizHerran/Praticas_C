#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NumeroDeMaterias 10

char linhas[250];
int i = 0;

typedef struct {
    char nomeMateria[40];
    int peso;
    float nota;
}materias;
materias dd[NumeroDeMaterias];

void puxarDados(materias dados[]){

    i = 0;
    FILE * arc = fopen("Materias_e_notas.csv", "r");
    if(arc == NULL){
        printf("\n//=========================================\\\\\n");
        printf("||\n");
        perror("|| Erro ao abrir o arquivo de dados: ");
        printf("||\n");
        printf("\\\\=========================================//\n");
        return 1;
    }

    //Pula cabeçalho
    fgets(linhas, sizeof(linhas), arc);
    
    //Lê os dados:
    while(fgets(linhas, sizeof(linhas), arc) != NULL){

        char * tk;
        //Nome da Materia
        linhas[strcspn(linhas, "\n")] = 0;
        tk = strtok(linhas, ";");
        if (tk == NULL) continue;
        if(strlen(tk) >= sizeof(dados[i].nomeMateria)){
            printf("\n//=========================================\\\\\n");
            printf("||\n");
            printf("|| Estouro de memoria em NOME DA MATERIA!\n");
            printf("||\n");
            printf("\\\\=========================================//\n");
        }
        strcpy(dados[i].nomeMateria, tk);

        //Nota
        tk = strtok(NULL, ";");
        if (tk == NULL) continue;
        dados[i].nota = atof(tk);

        //Peso
        tk = strtok(NULL, ";");
        if (tk == NULL) continue;
        dados[i].peso = atoi(tk);
        
        i++;
    }

    fclose(arc);
}

void adicionar(){

    char materiaNova[40];
    float novaNota;
    int novoPeso;
    int c, dig;

    FILE * narc = fopen("Materias_e_notas.csv", "a");
    if(narc == NULL){
        perror("Erro ao adicionar dados: ");
    }

        printf("\n//=== Cuidado novas informacoes nao podem ser apagadas ===\\\\\n");
        printf("||\n");
        printf("|| Qual nome da materia: ");
        fgets(materiaNova, sizeof(materiaNova), stdin);
        materiaNova[strcspn(materiaNova, "\n")] = '\0';

        printf("|| Qual a nota: ");
        scanf("%f", &novaNota);
        while ((c = getchar()) != '\n' && c != EOF);

        printf("|| Qual o peso: ");
        scanf("%d", &novoPeso);
        while ((c = getchar()) != '\n' && c != EOF);
        printf("||\n|| Nome da Materia: %s\n|| Nota: %.2f\n|| Peso:%d", materiaNova, novaNota, novoPeso);
        printf("\n||\n|| Os dados estao corretos? ");
        printf("\n|| 1 - sim / 2 - nao ");
        scanf("%d", &dig);
        if(dig == 2){
            return 0;
        }else printf("||\n|| Nova materia adicionada!\n");
        printf("||\n");
        printf("\\\\=========================================//\n");

        fprintf(narc, "\n%s;%.2f;%d", materiaNova, novaNota, novoPeso);
        fclose(narc);
}

float soma(materias dados[]){

    float notasXpeso = 0, pesoTotal = 0, total;

    for(int p = 0; p < i; p++){
        notasXpeso += dados[p].nota * dados[p].peso;
        pesoTotal += dados[p].peso;
    }

    total = notasXpeso/pesoTotal;
    return total;
}

int main(){
    puxarDados(dd);

    int opc, menu = 0;

    printf("\nSistema iniciando..\n");

    do{
    printf("\n//=========================================\\\\\n");
    printf("||\n");
    printf("||\t1 - Exibir dados.\n");
    printf("||\t2 - Adicionar mateira/nota/peso\n");
    printf("||\t3 - Somar CRA!\n");
    printf("||\n");
    printf("||\t(4) - para sair!\n");
    printf("\\\\=========================================//\n");
    scanf("%d", &opc);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    switch(opc){
        //Exibir dados:
        case 1:
        printf("\n//============================================================\\\\\n");
        printf("|| Nome da Materia                      | Nota  | Peso/Credito\n");
        printf("||------------------------------------------------------------\n");
        for(int j = 0; j < i; j++){
            printf("|| %-36s | %-5.2f | %-5d\n", dd[j].nomeMateria, dd[j].nota, dd[j].peso);
        }
        printf("||\n");
        printf("||\t(%d)\n", i);
        printf("\\\\===================================================//\n\n");

        break;

        //Adicionar:
        case 2:
        
        adicionar();
        puxarDados(dd);

        break;

        //somar:
        case 3:

        printf("\n//===================================================\\\\\n");
        printf("||\n");
        printf("||\tSeu CRA e: %.2f", soma(dd));
        printf("\n||\n");
        printf("\\\\=========================================//");

        break;

        //sair:
        case 4:
        printf("\n//=========================================\\\\\n");
        printf("||\n");
        printf("||\tObrigado por usar nossos servicos!");
        printf("\n||\n");
        printf("\\\\=========================================//\n");
        system("pause");
        return 1;
    }
    }while(menu != 1);
    
}