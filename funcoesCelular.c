#include <stdio.h>
#define TAM_CELULARES 3
#define CADASTRO_SUCESSO -1
#define CADASTRO_ERRO -2
#define CELULAR_NAO_ENCONTRADO -3
#define CELULAR_ATUALIZADO -4
#define LISTA_VAZIA -5
#define CELULAR_DELETADO -6

typedef struct{
    int id;
    int ano;
    float preco;
}Celular;

int menu_com_retorno_e_paramentros(int tipo);
int menu_com_retorno();
void menu_vendas();
void menu_cadastros();
int cadastrarCelular(Celular listaCelulares[], int idAtual, int qtdCelulares);
void listaCelulares(Celular listaCelulares[], int qtdCelulares);

int main(){
    Celular listaCelulares[TAM_CELULARES];

    int sair = 0;
    int idAtual = 1;
    int qtdCelulares = 0;
    while(!sair){ //sair == 0
        int opcao;
        opcao = menu_com_retorno_e_paramentros(1);

        switch (opcao){
            case 0: {
                sair = 1;
                break;
            }
            case 1: {
                int resultado = cadastrarCelular(listaCelulares, qtdCelulares);
                if (resultado == CADASTRO_SUCESSO){
                    qtdCelulares++;
                    idAtual++;
                    printf("Cadastro realizado com sucesso\n");
                }

                break;
              
            }
            case 2: {
                listaCelulares(listaCelulares, qtdCelulares);
                break;
            }
            case 3: {
                
                break;
            }
            case 4: {
                printf("Deletar");
                qtdCelulares--;
                break;
            }
            default: printf("Opção Inválida");
        }

    }

}


void menu_cadastros(){
    printf("Digite a opção: \n");
    printf("0 - Sair \n");
    printf("1 - Inserir \n");
    printf("2 - Listar \n");
    printf("3 - Atualizar \n");
    printf("4 - Deletar \n");

}

void menu_vendas(){
    printf("Digite a opção: \n");
    printf("0 - Sair \n");
    printf("1 - Comprar \n");
    printf("2 - Ver preços \n");
    printf("3 - Pagar \n");
    printf("4 - Financiar \n");

}

int menu_com_retorno(){
    menu_cadastros();

    int op;

    scanf("%d", &op);

    return op;
}

int menu_com_retorno_e_paramentros(int tipo){

    if (tipo == 1)
        menu_cadastros();
    else if (tipo == 2)
        menu_vendas();

    int op;

    scanf("%d", &op);

    return op;
}

int cadastrarCelular(Celular listaCelulares[], int idAtual, int qtdCelulares){
    printf("Digite o ano: ");
    scanf("%d", &listaCelulares[qtdCelulares].ano);
    printf("Digite o Preço: ");
    scanf("%f", &listaCelulares[qtdCelulares].preco);
    listaCelulares[qtdCelulares].id = idAtual;
    
    return CADASTRO_SUCESSO;
    
    
}
void listarCelulares(Celular listaCelulares[], int qtdCelulares){
     printf("Lista Celulares\n");
     for (int i = 0; i < qtdCelulares; i++)
          printf("%d - %d - %f\n", listaCelulares[i].id, listaCelulares[i].ano, listaCelulares[i].preco);     

}
int atualizarCelulares(Celular listaCelulares[], int idAtual, int qtdCelulares){
     printf("Atualizar");
     listarCelulares(listaCelulares, qtdCelulares);
     printf("Digite o id do celular: \n");
     int id;
     scanf("%d", &id);
     int achou = 0;
     for (int i = 0; i < qtdCelulares; i++){
         if (id == listaCelulares[i].id){
             printf("Digite o ano: ");
             scanf("%d", &listaCelulares[i].ano);
             printf("Digite o Preço: ");
             scanf("%f", &listaCelulares[i].preco);
             achou = 1;
             break;
         }
     }
     if (!achou) CELULAR_NAO_ENCONTRADO;
     else CELULAR_ATUALIZADO;
}

  
