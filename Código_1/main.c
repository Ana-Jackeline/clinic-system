/*Programa de um sistema básico de gestão de consultas médicas.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura para armazenar informações do usuário
typedef struct {    
    char nome[50];
    char email[80];
    char senha[20];
} Usuario;

// Estrutura para armazenar informações da consulta
typedef struct {
    char cpf[12];
    char nome[50];
    char consulta[50];
    char medico[50];
    char data[9];
    char horario[6];
} Consulta;

const char *tipos_consulta[] = {
    "🩺  Consulta Geral",
    "❤️  Cardiologia ",
    "🌟  Dermatologia",
    "👩  Ginecologia",
    "🧠  Neurologia",
    "🦴  Ortopedia",
    "👶  Pediatria",
    "💬  Psiquiatria",
    "🚻  Urologia"
};

const char *medicos[9][2] = {
    {"Carlos", "Daniela"},
    {"Eric", "Bruna"},
    {"Gabriel", "Helena"},
    {"Isabela", "João"},
    {"Vitoria", "Leonardo"},
    {"Mariana", "Nicolas"},
    {"Olivia", "Paulo"},
    {"Gustavo", "Roberta"},
    {"Sofia", "Tiago"}
};

const int num_tipos_consulta = sizeof(tipos_consulta) / sizeof(tipos_consulta[0]);

// Função para verificar se o e-mail é válido
int validar_email(char *email) {
    if (strlen(email) >= 80) return 0;
    if (strchr(email, '@') == NULL) return 0;
    return 1;
}

// Função para cadastrar um usuário
void cadastrar_usuario(Usuario ***usuarios, int *qtd_usuarios) {
    Usuario *novo_usuario = malloc(sizeof(Usuario));
    printf("Digite o nome do usuário: ");
    scanf(" %s", novo_usuario->nome);
    printf("Digite o e-mail do usuário: ");
    scanf(" %s", novo_usuario->email);
    if (!validar_email(novo_usuario->email)) {
        printf("E-mail inválido!\n");
        free(novo_usuario);
        return;
    }
    printf("Digite a senha do usuário: ");
    scanf(" %s", novo_usuario->senha);

    *usuarios = realloc(*usuarios, (*qtd_usuarios + 1) * sizeof(Usuario*));
    (*usuarios)[*qtd_usuarios] = novo_usuario;
    (*qtd_usuarios)++;
}

// Função para realizar login
int realizar_login(Usuario **usuarios, int qtd_usuarios, char *nome, char *senha) {
    for (int i = 0; i < qtd_usuarios; i++) {
        if (strcmp(usuarios[i]->nome, nome) == 0 && strcmp(usuarios[i]->senha, senha) == 0) {
            return 1;
        }
    }
    return 0;
}

// Função para exibir e selecionar tipos de consulta
void selecionar_tipo_consulta(char *consulta, int *tipo) {
    while (1) {
        printf("Selecione o tipo de consulta:\n");
        for (int i = 0; i < num_tipos_consulta; i++) {
            printf("|%d| %s\n", i + 1, tipos_consulta[i]);
        }
        int opcao;
        printf("Digite o número da consulta desejada: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao >= 1 && opcao <= num_tipos_consulta) {
            strcpy(consulta, tipos_consulta[opcao - 1]);
            *tipo = opcao - 1;
            break;
        } else {
            printf("\nOpção inválida!\nTente novamente.\n\n");
        }
    }
}

// Função para exibir e selecionar o médico
int selecionar_medico(char *medico, int tipo) {
    int opcao;
    do {
        printf("Selecione o médico:\n");
        for (int i = 0; i < 2; i++) {
            printf("|%d| %s\n", i + 1, medicos[tipo][i]);
        }
        printf("Digite o número do médico: ");
        scanf("%d", &opcao);
        getchar();
        if (opcao < 1 || opcao > 2) {
            printf("\nOpção inválida!\nTente novamente.\n\n");
        } else {
            strcpy(medico, medicos[tipo][opcao - 1]);
            return 1;
        }
    } while (1);

    return 0; 
}

// Função para cadastrar uma consulta
void cadastrar_consulta(Consulta ***consultas, int *qtd_consultas) {
    Consulta *nova_consulta = malloc(sizeof(Consulta));
    int tipo;
    printf("\nDigite o CPF do paciente (11 dígitos): ");
    scanf(" %s", nova_consulta->cpf);

    printf("Digite o nome do paciente: ");
    scanf(" %s", nova_consulta->nome);
    selecionar_tipo_consulta(nova_consulta->consulta, &tipo);
    selecionar_medico(nova_consulta->medico, tipo);

    printf("Digite a data (dd/mm/aaaa): ");
    scanf("%s", nova_consulta->data);

    printf("Digite o horário (hh:mm): ");
    scanf("%s", nova_consulta->horario);

    *consultas = realloc(*consultas, (*qtd_consultas + 1) * sizeof(Consulta*));
    (*consultas)[*qtd_consultas] = nova_consulta;
    (*qtd_consultas)++;
}

// Função para listar consultas
void listar_consultas(Consulta **consultas, int qtd_consultas) {
    for (int i = 0; i < qtd_consultas; i++) {
        printf("Consulta %d:\n", i + 1);
        printf("CPF: %s\n", consultas[i]->cpf);
        printf("Paciente: %s\n", consultas[i]->nome);
        printf("Consulta: %s\n", consultas[i]->consulta);
        printf("Médico: %s\n", consultas[i]->medico);
        printf("Data: %s\n", consultas[i]->data);
        printf("Horário: %s\n\n", consultas[i]->horario);
    }
}

// Função para editar uma consulta
void editar_consulta(Consulta **consultas, int qtd_consultas, int indice) {
    if (indice < 0 || indice >= qtd_consultas) {
        printf("\nÍndice inválido!\n");
        return;
    }
    Consulta *consulta = consultas[indice];
    int tipo;
    printf("Digite o novo CPF do paciente: ");
    scanf(" %s", consulta->cpf);
    printf("Digite o novo nome do paciente: ");
    scanf(" %s", consulta->nome);
    selecionar_tipo_consulta(consulta->consulta, &tipo);
    selecionar_medico(consulta->medico, tipo);
    printf("Digite a nova data da consulta (dd/mm/aaaa): ");
    scanf("%s", consulta->data);
    printf("Digite o novo horário (hh:mm): ");
    scanf("%s", consulta->horario);
}

// Função para excluir uma consulta
void excluir_consulta(Consulta **consultas, int *qtd_consultas, int indice) {
    if (indice < 0 || indice >= *qtd_consultas) {
        printf("\nÍndice inválido!\n");
        return;
    }
    free(consultas[indice]);
    for (int i = indice; i < *qtd_consultas - 1; i++) {
        consultas[i] = consultas[i + 1];
    }
    (*qtd_consultas)--;
    *consultas = realloc(*consultas, (*qtd_consultas) * sizeof(Consulta*));
}

// Função para filtrar consultas por tipo de consulta
void filtrar_consultas_por_tipo(Consulta **consultas, int qtd_consultas) {
    int tipo;
    char consulta[50];
    selecionar_tipo_consulta(consulta, &tipo);
    printf("\nConsultas do tipo '%s':\n", consulta);
    for (int i = 0; i < qtd_consultas; i++) {
        if (strcmp(consultas[i]->consulta, consulta) == 0) {
            printf("Paciente: %s\n", consultas[i]->nome);
            printf("Médico: %s\n", consultas[i]->medico);
            printf("Data: %s\n", consultas[i]->data);
            printf("Horário: %s\n\n", consultas[i]->horario);
        }
    }
}

// Função para filtrar consultas por uma data específica
void filtrar_consultas_por_dia(Consulta **consultas, int qtd_consultas) {
    char data[11];
    printf("\nDigite a data desejada (dd/mm/aaaa): ");
    scanf("%s", data);
    printf("Consultas no dia %s:\n", data);
    for (int i = 0; i < qtd_consultas; i++) {
        if (strcmp(consultas[i]->data, data) == 0) {
            printf("Paciente: %s\n", consultas[i]->nome);
            printf("Tipo de Consulta: %s\n", consultas[i]->consulta);
            printf("Médico: %s\n", consultas[i]->medico);
            printf("Horário: %s\n\n", consultas[i]->horario);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    Usuario **usuarios = NULL;
    int qtd_usuarios = 0;
    Consulta **consultas = NULL;
    int qtd_consultas = 0;

    int opcao;
    char nome[50];
    char senha[20];

    printf("- - - - - - - - - - - - - - -\n");
    printf("-\033[1;34m   Olá, Bem-vindo ao CMA   \033[0m-\n");
    printf("-                           -\n");
    printf("-\033[1;36m   Centro Médico Avançado  \033[0m-\n");
    printf("- - - - - - - - - - - - - - -\n");

    while (1) {
        printf("\n-------------------------\n");
        printf("|1| Cadastrar-se        |\n");
        printf("|2| Realizar login      |\n");
        printf("|3| Sair                |\n");
        printf("-------------------------\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_usuario(&usuarios, &qtd_usuarios);
                break;
            case 2:
                printf("Digite o nome do usuário: ");
                scanf(" %s", nome);
                printf("Digite a senha do usuário: ");
                scanf(" %s", senha);
                if (realizar_login(usuarios, qtd_usuarios, nome, senha)) {
                    printf("Login realizado com sucesso!\n");

                    while (1) {
                        printf("\n-------------------- Menu -----------------\n");
                        printf("|1| Cadastrar consulta                    |\n");
                        printf("|2| Listar consultas                      |\n");
                        printf("|3| Editar consulta                       |\n");
                        printf("|4| Excluir consulta                      |\n");
                        printf("|5| Quantitativo de consultas cadastradas |\n");
                        printf("|6| Filtrar consultas por tipo            |\n");
                        printf("|7| Filtar consultas por data             |\n");
                        printf("|8| Busca ficha do paciente               |\n");
                        printf("|0| Sair                                  |\n");
                        printf("-------------------------------------------\n");
                        printf("Digite a opção desejada: ");
                        scanf("%d", &opcao);
                        getchar();

                        switch (opcao) {
                            case 1:
                                cadastrar_consulta(&consultas, &qtd_consultas);
                                break;
                            case 2:
                                listar_consultas(consultas, qtd_consultas);
                                break;
                            case 3:
                                listar_consultas(consultas, qtd_consultas);
                                printf("\nDigite o índice da consulta que deseja editar: ");
                                int indice;
                                scanf("%d", &indice);
                                getchar();
                                editar_consulta(consultas, qtd_consultas, indice - 1);
                                break;
                            case 4:
                                listar_consultas(consultas, qtd_consultas);
                                printf("\nDigite o índice da consulta que deseja excluir: ");
                                scanf("%d", &indice);
                                getchar();
                                excluir_consulta(consultas, &qtd_consultas, indice - 1);
                                break;
                            case 5:
                                printf("Total de consultas cadastradas: %d\n", qtd_consultas);
                                break;
                            case 6:
                                filtrar_consultas_por_tipo(consultas, qtd_consultas);
                                break;
                            case 7:
                                filtrar_consultas_por_dia(consultas, qtd_consultas);
                                break;
                            case 8:
                            printf("Digite o nome do paciente: ");
                                char termo_busca[50];
                                fgets(termo_busca, 50, stdin);
                                termo_busca[strcspn(termo_busca, "\n")] = 0; 

                                int encontrou = 0;
                                for (int i = 0; i < qtd_consultas; i++) {
                                    if (strstr(consultas[i]->nome, termo_busca) != NULL) {
                                        printf("Consulta encontrada:\n");
                                        printf("CPF: %s\n", consultas[i]->cpf);
                                        printf("Nome: %s\n", consultas[i]->nome);
                                        printf("Consulta: %s\n", consultas[i]->consulta);
                                        printf("Médico: %s\n", consultas[i]->medico);
                                        printf("Data: %s\n", consultas[i]->data);
                                        printf("Horário: %s\n\n", consultas[i]->horario);
                                        encontrou = 1;
                                    }
                                }
                                if (!encontrou) {
                                    printf("\nNenhuma consulta encontrada com o termo '%s'.\n", termo_busca);
                                }
                                break;
                            case 0:
                                printf("\nSaindo do sistema...\n");
                                for (int i = 0; i < qtd_usuarios; i++) {
                                    free(usuarios[i]);
                                }
                                free(usuarios);

                                for (int i = 0; i < qtd_consultas; i++) {
                                    free(consultas[i]);
                                }
                                free(consultas);
                                return 0;
                            default:
                                printf("\nOpção inválida!\n");
                        }
                    }
                } else {
                    printf("Login inválido!\n");
                }
                break;
            case 3:
                printf("\nSaindo do sistema...\n");
                for (int i = 0; i < qtd_usuarios; i++) {
                    free(usuarios[i]);
                }
                free(usuarios);

                for (int i = 0; i < qtd_consultas; i++) {
                    free(consultas[i]);
                }
                free(consultas);
                return 0;
            default:
                printf("\nOpção inválida!\n");
        }
    }

    return 0;
}
