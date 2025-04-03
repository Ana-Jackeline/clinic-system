#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consulta.h"
#include "usuario.h"

int main() {
    NoConsulta *lista_consultas = NULL;
    Usuario *lista_usuarios = NULL;

    carregar_consultas(&lista_consultas);
    carregar_usuarios(&lista_usuarios);

    int opcao;
    char nome[50], senha[20];

    printf("- - - - - - - - - - - - - \n");
    printf("-\033[1;34m Olá, Bem-vindo ao CMA \033[0m-\n");
    printf("-                       -\n");
    printf("-\033[1;36m Centro Médico Avançado\033[0m-\n");
    printf("- - - - - - - - - - - - - \n");

    do {
        printf("\n-----------------------\n");
        printf("|1| Cadastrar-se      |\n");
        printf("|2| Login             |\n");
        printf("|3| Sair              |\n");
        printf("-----------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_usuario(&lista_usuarios);
                break;
            case 2:
                printf("Nome de usuário: ");
                scanf(" %s", nome);
                printf("Senha: ");
                scanf(" %s", senha);

                if (realizar_login(lista_usuarios, nome, senha)) {
                    printf("\nLogin realizado com sucesso!\n");

                    int opcao_interna;
                    do {
                        printf("\n------------------ Menu -----------------\n");
                        printf("|1| Cadastrar consulta                    |\n");
                        printf("|2| Listar consultas                      |\n");
                        printf("|3| Editar consulta                       |\n");
                        printf("|4| Excluir consulta                      |\n");
                        printf("|5| Salvar consultas                      |\n");
                        printf("|6| Filtrar consultas por tipo            |\n");
                        printf("|7| Filtrar consultas por data            |\n");
                        printf("|8| Buscar ficha do paciente              |\n");
                        printf("|0| Sair                                  |\n");
                        printf("-------------------------------------------\n");
                        printf("Digite a opção desejada: ");
                        scanf("%d", &opcao_interna);

                        switch (opcao_interna) {
                            case 1:
                                cadastrar_consulta(&lista_consultas);
                                break;
                            case 2:
                                listar_consultas(lista_consultas);
                                break;
                            case 3: {
                                char nome_paciente[50];
                                printf("Nome do paciente para editar: ");
                                scanf(" %s", nome_paciente);
                                editar_consulta(lista_consultas, nome_paciente);
                                break;
                            }
                            case 4: {
                                char nome_paciente[50];
                                printf("Nome do paciente para excluir: ");
                                scanf(" %s", nome_paciente);
                                excluir_consulta(&lista_consultas, nome_paciente);
                                break;
                            }
                            case 5:
                                salvar_consulta(lista_consultas);
                                break;
                            case 6:
                                filtrar_consultas_por_tipo(lista_consultas);
                                break;
                            case 7: {
                                char data[9];
                                printf("Digite a data (DDMMYYYY): ");
                                scanf(" %s", data);
                                filtrar_consultas_por_dia(lista_consultas, data);
                                break;
                            }
                            case 8: {
                                char nome_paciente[50];
                                printf("Digite o nome do paciente: ");
                                scanf(" %s", nome_paciente);
                                buscar_ficha_paciente(&lista_consultas, nome_paciente);
                                break;
                            }
                            case 0:
                                printf("\nSaindo do menu de consultas.\n");
                                break;
                            default:
                                printf("\nOpção inválida!\n");
                        }
                    } while (opcao_interna != 0);
                } else {
                    printf("\n❌ Login falhou! Nome de usuário ou senha incorretos.\n");
                }
                break;
            case 3:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (opcao != 3);

    salvar_consulta(lista_consultas);
    salvar_usuario(lista_usuarios);
    liberar_memoria_consultas(lista_consultas);
    liberar_memoria_usuario(lista_usuarios);

    return 0;
}
