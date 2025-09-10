#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char varredura[100][20];
char linha[100];
int i;
int menu, Marca, Cor, Quantidade, c;
int quantidadeDeMarcas;

char cor[100][100];
float valor;


int lerMarcas(char varredura[][20]){
    //Ler todos arquivos
    FILE * varreduraDeMarcas = fopen("Marcas.csv", "r");
    if(varreduraDeMarcas == NULL){
        perror("Erro ao fazer a varredura das marcas: ");
        exit(1);
    }

    int v = 0;
    while (fgets(linha, 100, varreduraDeMarcas) != NULL) {
    linha[strcspn(linha, "\n")] = '\0';

    strcpy(varredura[v], linha);
    v++;
    }
    fclose(varreduraDeMarcas);
    return v;
}


int abrirMarca(int marca){

    //Adicionar .csv e abre o arquivo
    strcat(varredura[marca], ".csv");
    FILE * marcaEscolhida = fopen(varredura[marca], "r");
    if(marcaEscolhida == NULL){
        perror("Erro ao abrir os dados da Marca: ");
        exit(1);
    }

    int vc = 0;
    char *tk;
    while(fgets(linha, 100, marcaEscolhida) != NULL){
        linha[strcspn(linha, "\n")] = '\0';

        tk = strtok(linha, ",");
        strcpy(cor[vc], tk);

        tk = strtok(NULL, ",");
        valor = atof(tk);
        vc++;
    }
    fclose(marcaEscolhida);
    return vc;
}

float valorDeEsmaltePorCliente(float valor, int quantidade){
    valor /= 8;
    valor *=quantidade;
    return valor;
}

void verDados(){
    printf("\n//=============== Menu de Marcas ===============\\\\");
    printf("\n||\n");
    printf("||\tEscolha a marca do esmalte:\n||\n");
    for(i = 1; i <= quantidadeDeMarcas; i++){
        printf("||\t%d - %s\n", i, varredura[i-1]);
    }
    printf("||\n");
    printf("\\\\===============================//");
    scanf("%d", &Marca);
    while ((c = getchar()) != '\n' && c != EOF);
    Marca -=1;
    int quantidadeDeCores = abrirMarca(Marca);

    printf("\n//=============== Menu de Cor ===============\\\\");
    printf("\n||");
    printf("\n||\tEscolha a cor do esmalte:\n");
    for(int c = 1; c <= quantidadeDeCores; c++){
        printf("||\t%d - %s\n", c, cor[c-1]);
    }
    printf("||\n");
    printf("\\\\===============================//");
    scanf("%d", &Cor);
    while ((c = getchar()) != '\n' && c != EOF);
    Cor -=1;

    printf("\n//=============== Quantidade estimada ===============\\\\");
    printf("\n||");
    printf("\n||\tQuantidade para quantas esmaltacoes? ");
    scanf("%d", &Quantidade);
    while ((c = getchar()) != '\n' && c != EOF);
    printf("||\n");
    printf("\\\\===============================//\n");

    printf("\n//=============== Valores ===============\\\\");
    printf("\n||\n");
    printf("||\tMarca: %s\n", varredura[Marca]);
    printf("||\tCor: %s\n", cor[Cor]);
    printf("||\tQuantidade estimada: %s\n", Quantidade == 1 ? "Quantidade comum para as maos" : "Mais que o normal!");
    printf("||\tValor do esmalte: %.2f", valor);
    printf("\n||\tValor de custo por cliente: %.2f\n", valorDeEsmaltePorCliente(valor, Quantidade));
    printf("||\n");
    printf("\\\\===============================//");
}

