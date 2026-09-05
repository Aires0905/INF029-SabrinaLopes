#include <stdio.h>
#define TAM_ALUNO 3


#define CAD_ALUNO_SUCESSO -1
#define MATRICULA_INVALIDA -2
#define LISTA_CHEIA -3
#define ATUALIZACAO_ALUNO_SUCESSO -4
#define MATRICULA_INEXISTENTE -5
#define EXCLUSAO_ALUNO_SUCESSO -6

typedef struct {
	int matricula;
	char sexo;
	int ativo;
} Aluno;

int menuGeral();
int menuAluno();
int cadastrarAluno(Aluno listaAluno[], int qtdAluno);
void listarAluno(Aluno listaAluno[], int qtdAluno);
int atualizarAluno(Aluno listaAluno[], int qtdAluno);
int excluirAluno(Aluno listaAluno[], int qtdAluno);

int main(void) {

	Aluno listaAluno[TAM_ALUNO];
	int opcao;
	int qtdAluno = 0;  //contador
	int sair = 0;

	while (!sair) {

		opcao = menuGeral();

		switch (opcao) {
		case 0: {
			sair = 1;
			break;
		}
		case 1: {
			printf("Modulo Aluno\n");
			int sairAluno = 0;
			int opcaoAluno;
			while(!sair) {
				opcaoAluno = menuAluno();
				switch (opcaoAluno) {
				case 0: {
					sairAluno = 1;
					break;
				}
				case 1: {

					int retorno = cadastrarAluno(listaAluno, qtdAluno);
					if (retorno == LISTA_CHEIA)
						printf("Lista de Alunos Cheia\n");
					else if (retorno == MATRICULA_INVALIDA)
						printf("Matricula Invalida\n");
					else {
						printf("Cadastrado com sucesso\n");
						qtdAluno++;
					}
					break;
				}
				case 2: {

					listarAluno(listaAluno, qtdAluno);
					break;
				}
				case 3: {
					int retorno = atualizarAluno(listaAluno, qtdAluno);
					switch (retorno) {
					case MATRICULA_INVALIDA:{
						printf("Matricula invalida\n");
						break;
					}
					case MATRICULA_INEXISTENTE:{
							printf("Matricula inexistente\n");
							break;
					}
					case ATUALIZACAO_ALUNO_SUCESSO:{
						printf("Aluno atualizado com sucesso\n");
						break;
					}
			    	}

					break;
				}
				case 4: {
					    
				    int retorno = excluirAluno(listaAluno, qtdAluno);
				    switch (retorno) {
				        case MATRICULA_INVALIDA: {
						     printf("Matricula invalida\n");
						     break;
					    }
					    case MATRICULA_INEXISTENTE: {
							printf("Matricula inexistente\n");
							break;
						}
					    case EXCLUSAO_ALUNO_SUCESSO: {
							printf("Aluno excluido com sucesso\n");
							qtdAluno--;
							break;
						}
					}
					break;
				}
				default: {
					printf("Opção Invalida\n");
					break;
				}

				}

			}
     		break;
		}
		case 2: {
			printf("Modulo Professor\n");
			break;
		}
		case 3: {
			printf("Modulo Disciplina\n");
			break;
		}
		default: {
			printf("Opção Invalida\n");
			break;
		}

	}


}



	return 0;
}
// funcoes

int menuGeral() {
	int opcao;
	printf("Projeto Escola\n");
	printf("0 - Sair\n");
	printf("1 - Aluno\n");
	printf("2 - Professor\n");
	printf("3 - Disciplina\n");

	scanf("%d", &opcao);

	return opcao;
}

int menuAluno() {
	int opcao;
	printf("0 - Voltar\n");
	printf("1 - Cadastrar Aluno\n");
	printf("2 - listar Aluno\n");
	printf("3 - Atualizar Aluno\n");
	printf("4 - Excluir Aluno\n");

	scanf("%d", &opcao);

	return opcao;
}

int cadastrarAluno(Aluno listaAluno[], int qtdAluno) {
	printf("Cadastrar Aluno\n");
	if (qtdAluno == TAM_ALUNO)
		return LISTA_CHEIA;
	else {
		printf("Digite a matricula do Aluno\n");
		int matricula;
		scanf("%d", &matricula);
		if (matricula < 0)
			return MATRICULA_INVALIDA;
		listaAluno[qtdAluno].matricula = matricula;
		listaAluno[qtdAluno].ativo = 1;
		return CAD_ALUNO_SUCESSO;
	}
}

void listarAluno(Aluno listaAluno[], int qtdAluno) {
	printf("Listar Aluno\n");
	if(qtdAluno == 0)
		printf("Lista de Aluno Vazia \n");
	else {
		for(int iCont = 0; iCont < qtdAluno; iCont++) {
			if (listaAluno[iCont].ativo == 1);
			printf("Matricula: %d\n", listaAluno[iCont].matricula);
		}
	}
}

int atualizarAluno(Aluno listaAluno[], int qtdAluno) {
	printf("Atualizar Aluno\n");
	printf("Digite a matricula do Aluno\n");
	int matricula;
	scanf("%d", &matricula);
	int achou = 0;
	if (matricula < 0)
		return MATRICULA_INVALIDA;
	else {
		for(int iCont = 0; iCont < qtdAluno; iCont++) {
			if(matricula == listaAluno[iCont].matricula && listaAluno[iCont].ativo) {
				printf("Digite a nova matricula do Aluno\n");
				int novaMatricula;
				scanf("%d", &novaMatricula);
				if(matricula < 0) {
					return MATRICULA_INVALIDA;
				}
				listaAluno[iCont].matricula = novaMatricula;
				achou = 1;
				break;
			}	
		}
		if (achou)
		    return ATUALIZACAO_ALUNO_SUCESSO;
		else
		    return MATRICULA_INEXISTENTE;
	}	
}

int excluirAluno(Aluno listaAluno[], int qtdAluno) {
	printf("Excluir Aluno\n");
	printf("Digite a matricula do Aluno\n");
	int matricula;
	scanf("%d", &matricula);
	int achou = 0;
	if (matricula < 0)
		return MATRICULA_INVALIDA;
	else {
		for(int iCont = 0; iCont < TAM_ALUNO; iCont++) {
			if(matricula == listaAluno[iCont].matricula) {
				listaAluno[iCont].ativo = -1;

				for(int jCont = iCont; jCont < qtdAluno - 1; jCont++) {
					listaAluno[jCont].matricula = listaAluno[jCont+iCont].matricula;
					listaAluno[jCont].sexo = listaAluno[jCont+iCont].sexo;
					listaAluno[jCont].ativo = listaAluno[jCont+iCont].ativo;
				}

				achou = 1;
				break;
			}
	    }
	    if (achou)
			return EXCLUSAO_ALUNO_SUCESSO;
		else
			return MATRICULA_INEXISTENTE;
	}
}