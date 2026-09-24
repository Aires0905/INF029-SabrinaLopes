#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CAD_SUCESSO -1
#define MATRICULA_INVALIDA -2
#define ATUALIZACAO_SUCESSO 3
#define MATRICULA_INEXISTENTE -5
#define EXCLUSAO_SUCESSO 6
#define ERRO -7
#define ERRO_SEXO -8
#define DATA_INVALIDA -9
#define CPF_INVALIDO -10
#define DISCIPLINA_CHEIA -11

typedef struct dma {
    int dia;
    int mes;
    int ano; 
} Data;

typedef struct aluno {
    int matricula;
    char nome[50];
    char sexo;
    Data data_nascimento;
    char CPF[15];
    struct aluno *proximo;
} Aluno;

typedef struct professor {
    int matricula;
    char nome[50];
    char sexo;
    Data data_nascimento;
    char CPF[15];
    struct professor *proximo;
} Professor;

typedef struct elementoAluno {
    Aluno *aluno;
    struct elementoAluno *proximo;
} ElementoAluno;

typedef struct disciplina {
    int codigo;
    char nome[50];
    int semestre;
    Professor D;
    ElementoAluno M;
    int qtdAlunos;
    struct disciplina *proximo;
} Disciplina;

int menuGeral();
int menuCRUD(const char *modulo);
int menuDisciplina();
int menuRelatorios();

void limparBuffer();
void removerQuebraLinha(char *str);
int validarData(Data d);
int validarCPF(const char *cpf);

int cadastrarAluno(Aluno **inicio, int *proxMatricula);
void listarAlunos(Aluno *inicio);
int atualizarAluno(Aluno *inicio);
int excluirAluno(Aluno **inicio);
Aluno* buscarAlunoPorMatricula(Aluno *inicio, int mat);

int cadastrarProfessor(Professor **inicio, int *proxMatricula);
void listarProfessores(Professor *inicio);
int atualizarProfessor(Professor *inicio);
int excluirProfessor(Professor **inicio);
Professor* buscarProfePorMat(Professor *inicio, int mat);

int cadastrarDisciplina(Disciplina **inicio, Professor *listaProf, int *proxCodigo);
void listarDisciplinas(Disciplina *inicio);
int atualizarDisciplina(Disciplina *inicio, Professor *listaProf);
int excluirDisciplina(Disciplina **inicio);
int inserirAlunoDisciplina(Disciplina *listaDisci, Aluno *listaAluno);
int excluirAlunoDisciplina(Disciplina *listaDisci);
void listarUmaDisciplina(Disciplina *listaDisci);


void relatorioAlunosPorSexo(Aluno *inicio);
void relatorioProfessoresPorSexo(Professor *inicio);
void relatorioAniversariantes(Aluno *inicioAluno, Professor *inicioProf);
void relatorioBuscaString(Aluno *inicioAluno, Professor *inicioProf);
void relatorioAlunosMenos3Disciplinas(Aluno *inicioAluno, Disciplina *inicioDisc);
void relatorioDisciplinasMais40(Disciplina *inicioDisc);

int main(void) {
    Aluno *listaAlunos = NULL;
    Professor *listaProfessores = NULL;
    Disciplina *listaDisciiplinas = NULL;

    int proxMatriculaAluno = 1000;
    int proxMatriculaProf = 2000;
    int proxCodigoDisc = 1;

    int opcaoGeral, opcaoModulo, retorno;
    int sair = 0;

    while (!sair) {
        opcaoGeral = menuGeral();

        switch (opcaoGeral) {
            case 0:
                sair = 1;
                printf("Saindo do sistema...\n");
                break;

            case 1: {
                int sairModulo = 0;
                while (!sairModulo) {
                    opcaoModulo = menuCRUD("Aluno");
                    switch (opcaoModulo) {
                        case 0:
                            sairModulo = 1;
                            break;
                        case 1:
                            retorno = cadastrarAluno(&listaAlunos, &proxMatriculaAluno);
                            if (retorno == CAD_SUCESSO) printf("Aluno cadastrado com sucesso!\n");
                            else if (retorno == ERRO_SEXO) printf("Erro: Sexo invalido (M/F).\n");
                            else if (retorno == DATA_INVALIDA) printf("Erro: Data de nascimento invalida.\n");
                            else if (retorno == CPF_INVALIDO) printf("Erro: CPF invalido.\n");
                            else printf("Erro ao cadastrar aluno.\n");
                            break;
                        case 2:
                            listarAlunos(listaAlunos);
                            break;
                        case 3:
                            retorno = atualizarAluno(listaAlunos);
                            if (retorno == ATUALIZACAO_SUCESSO) printf("Aluno atualizado com sucesso!\n");
                            else printf("Matricula invalida ou nao encontrada.\n");
                            break;
                        case 4:
                            retorno = excluirAluno(&listaAlunos);
                            if (retorno == EXCLUSAO_SUCESSO) printf("Aluno excluido com sucesso!\n");
                            else printf("Matricula invalida ou nao encontrada.\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                }
                break;
            }

            case 2: { 
                int sairModulo = 0;
                while (!sairModulo) {
                    opcaoModulo = menuCRUD("Professor");
                    switch (opcaoModulo) {
                        case 0:
                            sairModulo = 1;
                            break;
                        case 1:
                            retorno = cadastrarProfessor(&listaProfessores, &proxMatriculaProf);
                            if (retorno == CAD_SUCESSO) printf("Professor cadastrado com sucesso!\n");
                            else if (retorno == ERRO_SEXO) printf("Erro: Sexo invalido (M/F).\n");
                            else if (retorno == DATA_INVALIDA) printf("Erro: Data de nascimento invalida.\n");
                            else if (retorno == CPF_INVALIDO) printf("Erro: CPF invalido.\n");
                            else printf("Erro ao cadastrar professor.\n");
                            break;
                        case 2:
                            listarProfessores(listaProfessores);
                            break;
                        case 3:
                            retorno = atualizarProfessor(listaProfessores);
                            if (retorno == ATUALIZACAO_SUCESSO) printf("Professor atualizado com sucesso!\n");
                            else printf("Matricula invalida ou nao encontrada.\n");
                            break;
                        case 4:
                            retorno = excluirProfessor(&listaProfessores);
                            if (retorno == EXCLUSAO_SUCESSO) printf("Professor excluido com sucesso!\n");
                            else printf("Matricula invalida ou nao encontrada.\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                }
                break;
            }

            case 3: {
                int sairModulo = 0;
				int retorno;
				int opcaoModulo;
                while (!sairModulo) {
                    opcaoModulo = menuDisciplina();

                    switch (opcaoModulo) {
                        case 0:
                            sairModulo = 1;
                            break;
                        case 1:
                            retorno = cadastrarDisciplina(&listaDisciiplinas, listaProfessores, &proxCodigoDisc);
                            if (retorno == CAD_SUCESSO) printf("Disciplina cadastrada com sucesso!\n");
                            else printf("Erro ao cadastrar disciplina.\n");
                            break;
                        case 2:
                            listarDisciplinas(listaDisciiplinas);
                            break;
                        case 3:
                            retorno = atualizarDisciplina(listaDisciiplinas, listaProfessores);
                            if (retorno == ATUALIZACAO_SUCESSO) printf("Disciplina atualizada com sucesso!\n");
                            else printf("Codigo invalido ou nao encontrado.\n");
                            break;
                        case 4:
                            retorno = excluirDisciplina(&listaDisciiplinas);
                            if (retorno == EXCLUSAO_SUCESSO) printf("Disciplina excluida com sucesso!\n");
                            else printf("Codigo invalido ou nao encontrado.\n");
                            break;
                        case 5:
                            retorno = inserirAlunoDisciplina(listaDisciiplinas, listaAlunos);
                            if (retorno == CAD_SUCESSO) printf("Aluno inserido na disciplina com sucesso!\n");
                            else if (retorno == DISCIPLINA_CHEIA) printf("Erro: Disciplina atingiu o limite de vagas!\n");
                            else printf("Erro na operacao. Verifique codigos/matriculas.\n");
                            break;
                        case 6:
                            retorno = excluirAlunoDisciplina(listaDisciiplinas);
                            if (retorno == EXCLUSAO_SUCESSO) printf("Aluno removido da disciplina com sucesso!\n");
                            else printf("Erro na operacao. Verifique codigos/matriculas.\n");
                            break;
                        case 7:
                            listarUmaDisciplina(listaDisciiplinas);
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                }
                break;
            }

            case 4: { // Módulo Relatórios
                int sairModulo = 0;
                while (!sairModulo) {
                    opcaoModulo = menuRelatorios();
                    switch (opcaoModulo) {
                        case 0:
                            sairModulo = 1;
                            break;
                        case 1:
                            listarAlunos(listaAlunos);
                            break;
                        case 2:
                            listarProfessores(listaProfessores);
                            break;
                        case 3:
                            relatorioAlunosPorSexo(listaAlunos);
                            break;
                        case 4:
                            relatorioProfessoresPorSexo(listaProfessores);
                            break;
                        case 5:
                            relatorioAniversariantes(listaAlunos, listaProfessores);
                            break;
                        case 6:
                            relatorioBuscaString(listaAlunos, listaProfessores);
                            break;
                        case 7:
                            relatorioAlunosMenos3Disciplinas(listaAlunos, listaDisciiplinas);
                            break;
                        case 8:
                            relatorioDisciplinasMais40(listaDisciiplinas);
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                }
                break;
            }

            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removerQuebraLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int validarData(Data d) {
    if (d.ano < 1900 || d.ano > 2100) return 0;
    if (d.mes < 1 || d.mes > 12) return 0;
    
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((d.ano % 4 == 0 && d.ano % 100 != 0) || (d.ano % 400 == 0)) {
        diasPorMes[2] = 29;
    }
    
    if (d.dia < 1 || d.dia > diasPorMes[d.mes]) return 0;
    
    return 1;
}

int validarCPF(const char *cpf) {
    if (strlen(cpf) < 11) return 0;
    return 1; 
}


int menuGeral() {
    int opcao;
    printf("\n=================================\n");
    printf("     PROJETO ESCOLA - IFBA       \n");
    printf("=================================\n");
    printf("0 - Sair\n");
    printf("1 - Aluno\n");
    printf("2 - Professor\n");
    printf("3 - Disciplina\n");
    printf("4 - Relatorios\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    limparBuffer();
    return opcao;
}

int menuCRUD(const char *modulo) {
    int opcao;
    printf("\n--- Modulo %s ---\n", modulo);
    printf("0 - Voltar\n");
    printf("1 - Cadastrar\n");
    printf("2 - Listar\n");
    printf("3 - Atualizar\n");
    printf("4 - Excluir\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    limparBuffer();
    return opcao;
}

int menuDisciplina() {
	int opcao;
	printf("\n--- Modulo Disciplina ---\n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar Disciplina\n");
    printf("2 - Listar Disciplinas (Resumido)\n");
    printf("3 - Atualizar Disciplina\n");
    printf("4 - Excluir Disciplina\n");
    printf("5 - Inserir Aluno na Disciplina\n");
    printf("6 - Excluir Aluno da Disciplina\n");
    printf("7 - Detalhar Disciplina (com Alunos)\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    limparBuffer();
	return opcao;
}

int menuRelatorios() {
    int opcao;
    printf("\n--- Modulo Relatorios ---\n");
    printf("0 - Voltar\n");
    printf("1 - Listar Alunos\n");
    printf("2 - Listar Professores\n");
    printf("3 - Listar Alunos por Sexo\n");
    printf("4 - Listar Professores por Sexo\n");
    printf("5 - Aniversariantes do Mes\n");
    printf("6 - Buscar Pessoa por String\n");
    printf("7 - Alunos matriculados em menos de 3 disciplinas\n");
    printf("8 - Disciplinas com mais de 40 alunos\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    limparBuffer();
    return opcao;
}


int cadastrarAluno(Aluno **inicio, int *proxMatricula) {
    Aluno *novo = (Aluno *)malloc(sizeof(Aluno));
    if (novo == NULL) return ERRO;

    novo->matricula = *proxMatricula;

    printf("Digite o nome: ");
    fgets(novo->nome, 50, stdin);
    removerQuebraLinha(novo->nome);

    printf("Digite o sexo (M/F): ");
    scanf(" %c", &novo->sexo);
    novo->sexo = toupper(novo->sexo);
    limparBuffer();

    if (novo->sexo != 'M' && novo->sexo != 'F') {
        free(novo);
        return ERRO_SEXO;
    }

    printf("Digite a data de nascimento (DD MM AAAA): ");
    scanf("%d %d %d", &novo->data_nascimento.dia, &novo->data_nascimento.mes, &novo->data_nascimento.ano);
    limparBuffer();

    if (!validarData(novo->data_nascimento)) {
        free(novo);
        return DATA_INVALIDA;
    }

    printf("Digite o CPF: ");
    fgets(novo->CPF, 15, stdin);
    removerQuebraLinha(novo->CPF);

    if (!validarCPF(novo->CPF)) {
        free(novo);
        return CPF_INVALIDO;
    }

    novo->proximo = NULL;

    if (*inicio == NULL) {
        *inicio = novo;
    } else {
        Aluno *atual = *inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    (*proxMatricula)++;
    return CAD_SUCESSO;
}

void listarAlunos(Aluno *inicio) {
    printf("\n--- Lista de Alunos ---\n");
    if (inicio == NULL) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    Aluno *atual = inicio;
    while (atual != NULL) {
        printf("Matricula: %d | Nome: %s | Sexo: %c | Data Nasc: %02d/%02d/%04d | CPF: %s\n",
               atual->matricula, atual->nome, atual->sexo,
               atual->data_nascimento.dia, atual->data_nascimento.mes, atual->data_nascimento.ano,
               atual->CPF);
        atual = atual->proximo;
    }
}

int atualizarAluno(Aluno *inicio) {
    int mat;
    printf("Digite a matricula do aluno a ser atualizado: ");
    scanf("%d", &mat);
    limparBuffer();

    Aluno *aluno = buscarAlunoPorMatricula(inicio, mat);
    if (aluno == NULL) return MATRICULA_INEXISTENTE;

    printf("Digite o novo nome: ");
    fgets(aluno->nome, 50, stdin);
    removerQuebraLinha(aluno->nome);

    printf("Digite o novo sexo (M/F): ");
    scanf(" %c", &aluno->sexo);
    aluno->sexo = toupper(aluno->sexo);
    limparBuffer();

    printf("Digite a nova data de nascimento (DD MM AAAA): ");
    scanf("%d %d %d", &aluno->data_nascimento.dia, &aluno->data_nascimento.mes, &aluno->data_nascimento.ano);
    limparBuffer();

    printf("Digite o novo CPF: ");
    fgets(aluno->CPF, 15, stdin);
    removerQuebraLinha(aluno->CPF);

    return ATUALIZACAO_SUCESSO;
}

int excluirAluno(Aluno **inicio) {
    int mat;
    printf("Digite a matricula do aluno a ser excluido: ");
    scanf("%d", &mat);
    limparBuffer();

    if (*inicio == NULL) return MATRICULA_INEXISTENTE;

    Aluno *atual = *inicio;
    Aluno *anterior = NULL;

    while (atual != NULL && atual->matricula != mat) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return MATRICULA_INEXISTENTE;

    if (anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    return EXCLUSAO_SUCESSO;
}

Aluno* buscarAlunoPorMatricula(Aluno *inicio, int mat) {
    Aluno *atual = inicio;
    while (atual != NULL) {
        if (atual->matricula == mat) return atual;
        atual = atual->proximo;
    }
    return NULL;
}


int cadastrarProfessor(Professor **inicio, int *proxMatricula) {
    Professor *novo = (Professor *)malloc(sizeof(Professor));
    if (novo == NULL) return ERRO;

    novo->matricula = *proxMatricula;

    printf("Digite o nome: ");
    fgets(novo->nome, 50, stdin);
    removerQuebraLinha(novo->nome);

    printf("Digite o sexo (M/F): ");
    scanf(" %c", &novo->sexo);
    novo->sexo = toupper(novo->sexo);
    limparBuffer();

    if (novo->sexo != 'M' && novo->sexo != 'F') {
        free(novo);
        return ERRO_SEXO;
    }

    printf("Digite a data de nascimento (DD MM AAAA): ");
    scanf("%d %d %d", &novo->data_nascimento.dia, &novo->data_nascimento.mes, &novo->data_nascimento.ano);
    limparBuffer();

    if (!validarData(novo->data_nascimento)) {
        free(novo);
        return DATA_INVALIDA;
    }

    printf("Digite o CPF: ");
    fgets(novo->CPF, 15, stdin);
    removerQuebraLinha(novo->CPF);

    if (!validarCPF(novo->CPF)) {
        free(novo);
        return CPF_INVALIDO;
    }

    novo->proximo = NULL;

    if (*inicio == NULL) {
        *inicio = novo;
    } else {
        Professor *atual = *inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    (*proxMatricula)++;
    return CAD_SUCESSO;
}

void listarProfessores(Professor *inicio) {
    printf("\n--- Lista de Professores ---\n");
    if (inicio == NULL) {
        printf("Nenhum professor cadastrado.\n");
        return;
    }

    Professor *atual = inicio;
    while (atual != NULL) {
        printf("Matricula: %d | Nome: %s | Sexo: %c | Data Nasc: %02d/%02d/%04d | CPF: %s\n",
        atual->matricula, atual->nome, atual->sexo,
        atual->data_nascimento.dia, atual->data_nascimento.mes, atual->data_nascimento.ano,
        atual->CPF);
        atual = atual->proximo;
    }
}

int atualizarProfessor(Professor *inicio) {
    int mat;
    printf("Digite a matricula do professor a ser atualizado: ");
    scanf("%d", &mat);
    limparBuffer();

    Professor *prof = buscarProfePorMat(inicio, mat);
    if (prof == NULL) return MATRICULA_INEXISTENTE;

    printf("Digite o novo nome: ");
    fgets(prof->nome, 50, stdin);
    removerQuebraLinha(prof->nome);

    printf("Digite o novo sexo (M/F): ");
    scanf(" %c", &prof->sexo);
    prof->sexo = toupper(prof->sexo);
    limparBuffer();

    printf("Digite a nova data de nascimento (DD MM AAAA): ");
    scanf("%d %d %d", &prof->data_nascimento.dia, &prof->data_nascimento.mes, &prof->data_nascimento.ano);
    limparBuffer();

    printf("Digite o novo CPF: ");
    fgets(prof->CPF, 15, stdin);
    removerQuebraLinha(prof->CPF);

    return ATUALIZACAO_SUCESSO;
}

int excluirProfessor(Professor **inicio) {
    int mat;
    printf("Digite a matricula do professor a ser excluido: ");
    scanf("%d", &mat);
    limparBuffer();

    if (*inicio == NULL) return MATRICULA_INEXISTENTE;

    Professor *atual = *inicio;
    Professor *anterior = NULL;

    while (atual != NULL && atual->matricula != mat) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return MATRICULA_INEXISTENTE;

    if (anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    return EXCLUSAO_SUCESSO;
}

Professor* buscarProfePorMat(Professor *inicio, int mat) {
    Professor *atual = inicio;
    while (atual != NULL) {
        if (atual->matricula == mat) return atual;
        atual = atual->proximo;
    }
    return NULL;
}


int cadastrarDisciplina(Disciplina **inicio, Professor *listaProf, int *proxCodigo) {
    Disciplina *nova = (Disciplina *)malloc(sizeof(Disciplina));
    if (nova == NULL) return ERRO;

    nova->codigo = *proxCodigo;

    printf("Digite o nome da disciplina: ");
    fgets(nova->nome, 50, stdin);
    removerQuebraLinha(nova->nome);

    printf("Digite o semestre: ");
    scanf("%d", &nova->semestre);
    limparBuffer();

    int matProf;
    printf("Digite a matricula do Professor responsavel: ");
    scanf("%d", &matProf);
    limparBuffer();

    Professor *prof = buscarProfePorMat(listaProf, matProf);
    if (prof == NULL) {
        printf("Professor nao encontrado! Cadastre o professor primeiro.\n");
        free(nova);
        return ERRO;
    }

    nova->D = *prof;
    nova->M.aluno = NULL;
    nova->qtdAlunos = 0;
    nova->M.proximo = NULL;

    if (*inicio == NULL) {
        *inicio = nova;
    } else {
        Disciplina *atual = *inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = nova;
    }

    (*proxCodigo)++;
    return CAD_SUCESSO;
}

void listarDisciplinas(Disciplina *inicio) {
    printf("\n--- Lista de Disciplinas (Resumo) ---\n");
    if (inicio == NULL) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }

    Disciplina *atual = inicio;
    while (atual != NULL) {
        printf("Codigo: %d | Nome: %s | Semestre: %d | Professor: %s | Alunos: %d\n",
        atual->codigo, atual->nome, atual->semestre,
        atual->D.nome,
        atual->qtdAlunos);
        atual = atual->proximo;
    }
}

int atualizarDisciplina(Disciplina *inicio, Professor *listaProf) {
    int cod;
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &cod);
    limparBuffer();

    Disciplina *atual = inicio;
    while (atual != NULL && atual->codigo != cod) {
        atual = atual->proximo;
    }

    if (atual == NULL) return MATRICULA_INEXISTENTE;

    printf("Digite o novo nome: ");
    fgets(atual->nome, 50, stdin);
    removerQuebraLinha(atual->nome);

    printf("Digite o novo semestre: ");
    scanf("%d", &atual->semestre);
    limparBuffer();

    int matProf;
    printf("Digite a matricula do novo Professor: ");
    scanf("%d", &matProf);
    limparBuffer();

    Professor *prof = buscarProfePorMat(listaProf, matProf);
    if (prof != NULL) {
        atual->D = *prof;
    } else {
        printf("Professor nao encontrado. Mantido o anterior.\n");
    }

    return ATUALIZACAO_SUCESSO;
}

int excluirDisciplina(Disciplina **inicio) {
    int cod;
    printf("Digite o codigo da disciplina a ser excluida: ");
    scanf("%d", &cod);
    limparBuffer();

    if (*inicio == NULL) return MATRICULA_INEXISTENTE;

    Disciplina *atual = *inicio;
    Disciplina *anterior = NULL;

    while (atual != NULL && atual->codigo != cod) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return MATRICULA_INEXISTENTE;

    if (anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    ElementoAluno *elem = atual->M.proximo;
    while (elem != NULL) {
        ElementoAluno *temp = elem;
        elem = elem->proximo;
        free(temp);
    }

    free(atual);
    return EXCLUSAO_SUCESSO;
}

int inserirAlunoDisciplina(Disciplina *listaDisci, Aluno *listaAluno) {
    int codDisci, matAluno;
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &codDisci);
    printf("Digite a matricula do aluno: ");
    scanf("%d", &matAluno);
    limparBuffer();

    Disciplina *disci = listaDisci;
    while (disci != NULL && disci->codigo != codDisci) {
        disci = disci->proximo;
    }

    if (disci == NULL) return ERRO;

    Aluno *aluno = buscarAlunoPorMatricula(listaAluno, matAluno);
    if (aluno == NULL) return ERRO;

    ElementoAluno *novoElem = (ElementoAluno *)malloc(sizeof(ElementoAluno));
    novoElem->aluno = aluno;
    novoElem->proximo = disci->M.proximo;
    disci->M.proximo = novoElem;
    disci->qtdAlunos++;

    return CAD_SUCESSO;
}

int excluirAlunoDisciplina(Disciplina *listaDisci) {
    int codDisci, matAluno;
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &codDisci);
    printf("Digite a matricula do aluno a remover: ");
    scanf("%d", &matAluno);
    limparBuffer();

    Disciplina *disci = listaDisci;
    while (disci != NULL && disci->codigo != codDisci) {
        disci = disci->proximo;
    }

    if (disci == NULL) return ERRO;

    ElementoAluno *atual = disci->M.proximo;
    ElementoAluno *anterior = NULL;

    while (atual != NULL && atual->aluno->matricula != matAluno) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return ERRO;

    if (anterior == NULL) {
        disci->M.proximo = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    disci->qtdAlunos--;
    return EXCLUSAO_SUCESSO;
}

void listarUmaDisciplina(Disciplina *listaDisci) {
    int codDisci;
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &codDisci);
    limparBuffer();

    Disciplina *disci = listaDisci;
    while (disci != NULL && disci->codigo != codDisci) {
        disci = disci->proximo;
    }

    if (disci == NULL) {
        printf("Disciplina nao encontrada.\n");
        return;
    }

    printf("\n--- Detalhes da Disciplina ---\n");
    printf("Codigo: %d | Nome: %s | Semestre: %d\n", disci->codigo, disci->nome, disci->semestre);
    printf("Professor Responsavel: %s\n", disci->D.nome);
    printf("Alunos Matriculados (%d):\n", disci->qtdAlunos);

    ElementoAluno *elem = disc->M.proximo;
    while (elem != NULL) {
        printf("  - Mat: %d | Nome: %s\n", elem->aluno->matricula, elem->aluno->nome);
        elem = elem->proximo;
    }
}


void relatorioAlunosPorSexo(Aluno *inicio) {
    char sexo;
    printf("Informe o sexo para listagem (M/F): ");
    scanf(" %c", &sexo);
    sexo = toupper(sexo);
    limparBuffer();

    printf("\n--- Alunos do Sexo %c ---\n", sexo);
    Aluno *atual = inicio;
    while (atual != NULL) {
        if (atual->sexo == sexo) {
            printf("Matricula: %d | Nome: %s\n", atual->matricula, atual->nome);
        }
        atual = atual->proximo;
    }
}

void relatorioProfessoresPorSexo(Professor *inicio) {
    char sexo;
    printf("Informe o sexo para listagem (M/F): ");
    scanf(" %c", &sexo);
    sexo = toupper(sexo);
    limparBuffer();

    printf("\n--- Professores do Sexo %c ---\n", sexo);
    Professor *atual = inicio;
    while (atual != NULL) {
        if (atual->sexo == sexo) {
            printf("Matricula: %d | Nome: %s\n", atual->matricula, atual->nome);
        }
        atual = atual->proximo;
    }
}

void relatorioAniversariantes(Aluno *inicioAluno, Professor *inicioProf) {
    int mes;
    printf("Informe o mes desejado (1-12): ");
    scanf("%d", &mes);
    limparBuffer();

    printf("\n--- Aniversariantes do Mes %d ---\n", mes);
    
    printf("Alunos:\n");
    Aluno *alu = inicioAluno;
    while (alu != NULL) {
        if (alu->data_nascimento.mes == mes) {
            printf("  - %s (Dia %d)\n", alu->nome, alu->data_nascimento.dia);
        }
        alu = alu->proximo;
    }

    printf("Professores:\n");
    Professor *prof = inicioProf;
    while (prof != NULL) {
        if (prof->data_nascimento.mes == mes) {
            printf("  - %s (Dia %d)\n", prof->nome, prof->data_nascimento.dia);
        }
        prof = prof->proximo;
    }
}

void relatorioBuscaString(Aluno *inicioAluno, Professor *inicioProf) {
    char busca[50];
    printf("Digite no minimo 3 letras para busca: ");
    fgets(busca, 50, stdin);
    removerQuebraLinha(busca);

    if (strlen(busca) < 3) {
        printf("Busca deve conter ao menos 3 caracteres.\n");
        return;
    }

    printf("\n--- Resultados da Busca por '%s' ---\n", busca);
    
    printf("Alunos encontrados:\n");
    Aluno *alu = inicioAluno;
    while (alu != NULL) {
        if (strstr(alu->nome, busca) != NULL) {
            printf("  - %s (Matricula: %d)\n", alu->nome, alu->matricula);
        }
        alu = alu->proximo;
    }

    printf("Professores encontrados:\n");
    Professor *prof = inicioProf;
    while (prof != NULL) {
        if (strstr(prof->nome, busca) != NULL) {
            printf("  - %s (Matricula: %d)\n", prof->nome, prof->matricula);
        }
        prof = prof->proximo;
    }
}

void relatorioAlunosMenos3Disciplinas(Aluno *inicioAluno, Disciplina *inicioDisc) {
    printf("\n--- Alunos Matriculados em menos de 3 Disciplinas ---\n");
    Aluno *alu = inicioAluno;

    while (alu != NULL) {
        int iCont = 0;
        Disciplina *disci = inicioDisc;

        while (disci != NULL) {
            ElementoAluno *elem = disci->M.proximo;
            while (elem != NULL) {
                if (elem->aluno != NULL && elem->aluno->matricula == alu->matricula) {
                    iCont++;
                    break;
                }
                elem = elem->proximo;
            }
            disci = disci->proximo;
        }

        if (iCont < 3) {
            printf("Matricula: %d | Nome: %s | Qtd Disciplinas: %d\n", alu->matricula, alu->nome, iCont);
        }
        alu = alu->proximo;
    }
}

void relatorioDisciplinasMais40(Disciplina *inicioDisc) {
    printf("\n--- Disciplinas que extrapolam 40 vagas ---\n");
    Disciplina *disci = inicioDisc;

    while (disci != NULL) {
        if (disci->qtdAlunos > 40) {
            printf("Codigo: %d | Nome: %s | Professor: %s | Qtd Alunos: %d\n",
                   disci->codigo, disci->nome,
                   disci->D.nome,
                   disci->qtdAlunos);
        }
        disci = disci->proximo;
    }
}
