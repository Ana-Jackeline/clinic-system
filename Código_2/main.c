#include "usuario.h"
#include "consulta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


const char *tipos_consulta[] = {
    "🩺  Consulta Geral",
    "❤️  Cardiologia",
    "🌟  Dermatologia",
    "👩  Ginecologia",
    "🧠  Neurologia",
    "🦴  Ortopedia",
    "👶  Pediatria",
    "💬  Psiquiatria",
    "🚻  Urologia"
};

const char *medicos[9][2] = {
    {"Dr. Carlos", "Dra. Daniela"},
    {"Dr. Eric", "Dra. Bruna"},
    {"Dr. Gabriel", "Dra. Helena"},
    {"Dra. Isabela", "Dr. João"},
    {"Dra. Vitoria", "Dr. Leonardo"},
    {"Dra. Mariana", "Dr. Nicolas"},
    {"Dra. Olivia", "Dr. Paulo"},
    {"Dr. Gustavo", "Dra. Roberta"},
    {"Dra. Sofia", "Dr. Tiago"}
};

const int num_tipos_consulta = sizeof(tipos_consulta) / sizeof(tipos_consulta[0]);


int main() {
    setlocale(LC_ALL, "Portuguese");

    // Inicializa listas de usuários e consultas
    Usuario **usuarios = NULL;
    int qtd_usuarios = 0;
    carregar_usuarios(&usuarios, &qtd_usuarios);

    Consulta **consultas = NULL;
    int qtd_consultas = 0;
    carregar_consultas(&consultas, &qtd_consultas);

    int opcao;
    char nome[50], senha[20];

    printf("- - - - - - - - - - - - - \n");
    printf("-\033[1;34m Olá, Bem-vindo ao CMA \033[0m-\n");
    printf("-                       -\n");
    printf("-\033[1;36m Centro Médico Avançado\033[0m-\n");
    printf("- - - - - - - - - - - - - \n");
    
    while (1) {
        printf("-----------------------\n");
        printf("|1| Cadastrar-se      |\n");
        printf("|2| Login             |\n");
        printf("|3| Sair              |\n");
        printf("-----------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_usuario(&usuarios, &qtd_usuarios);
                break;
            case 2:
                printf("Digite o nome do usuário: ");
                scanf(" %s", nome);
                printf("Digite a senha: ");
                scanf(" %s", senha);
                if (realizar_login(usuarios, qtd_usuarios, nome, senha)) {
                    printf("\nLogin realizado com sucesso!\n");
                    int opcao_interna;
                    do {
                      printf("\n-------------------- Menu -----------------\n");
                      printf("|1| Cadastrar consulta                    |\n");
                      printf("|2| Listar consultas                      |\n");
                      printf("|3| Editar consulta                       |\n");
                      printf("|4| Excluir consulta                      |\n");
                      printf("|5| Quantitativo de consultas cadastradas |\n");
                      printf("|6| Filtrar consultas por tipo            |\n");
                      printf("|7| Filtar consultas por data             |\n");
                      printf("|8| Buscar ficha do paciente              |\n");
                      printf("|0| Sair                                  |\n");
                      printf("-------------------------------------------\n");
                      printf("Digite a opção desejada: ");
                        scanf("%d", &opcao_interna);
                        switch (opcao_interna) {
                            case 1:
                                cadastrar_consulta(&consultas, &qtd_consultas);
                                break;
                            case 2:
                                listar_consultas(consultas, qtd_consultas);
                                break;
                            case 3: {
                                listar_consultas(consultas, qtd_consultas);
                                int indice;
                                printf("Digite o índice da consulta a ser editada: ");
                                scanf("%d", &indice);
                                editar_consulta(consultas, qtd_consultas, indice - 1);
                                break;
                            }
                          case 4:
                            listar_consultas(consultas, qtd_consultas);
                            int indice; 
                            printf("\nDigite o índice da consulta que deseja excluir: ");
                            scanf("%d", &indice);
                            getchar(); 
                            excluir_consulta(consultas, &qtd_consultas, indice - 1);
                              printf("\nConsulta excluida com sucesso!\n");
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
                              buscar_ficha_paciente(consultas, qtd_consultas);
                              break;
                            case 0:
                            break;
                        default:
                            printf("❌ Opção inválida!\n");
                    }
                } while (opcao_interna != 0);
                break; 
            case 3:
                printf("\nSaindo do sistema...\n");
                liberar_memoria(usuarios, qtd_usuarios);
                liberar_memoria_consultas(consultas, qtd_consultas);
                return 0;
            default:
                printf("❌ Opção inválida!\n");
        }
         else{
            printf("\nLogin falhou!\n");
        }
    }
}
}
