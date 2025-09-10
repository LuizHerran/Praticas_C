#include "Manipulacao_De_Dados.h"

int main(){
    quantidadeDeMarcas = lerMarcas(varredura);  
    do{
    printf("\n//=============== Menu ===============\\\\");
    printf("\n||\n");
    printf("||\t1 - Ver marcas e cores do estoque\n");
    printf("||\t2 - Adicionar Marca ou cor\n");
    printf("||\t3 - Remover Marca ou cor\n");
    printf("||\n");
    printf("||\t4 - Sair!\n");
    printf("||\n");
    printf("\\\\==================================//");
    scanf("%d", &menu);
    while ((c = getchar()) != '\n' && c != EOF);
    }while(menu < 1 || menu > 4);

    switch(menu){

        case 1:
            verDados();
        break;
    }

    

    //valor celecionado

    
    
}