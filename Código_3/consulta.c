
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consulta.h"
#include "const.h"

// Função para adicionar uma consulta à lista
void cadastrar_consulta(NoConsulta **lista) {
    Consulta nova_consulta;
    int tipo_consulta;

    printf("Cadastro de nova consulta:\n");
    selecionar_tipo_consulta(nova_consulta.consulta, &tipo_consulta);

    if (tipo_consulta == -1) {
        return; 
    }

    if (selecionar_medico(nova_consulta.medico, tipo_consulta) == -1) {
        return;
    }

    printf("Nome do paciente: ");
    scanf(" %s", nova_consulta.nome);
    printf("CPF do paciente: ");
    scanf(" %s", nova_consulta.cpf);
    printf("Data da consulta (dd/mm/aaaa): ");
    scanf(" %s", nova_consulta.data);
    printf("Horário da consulta (hh:mm): ");
    scanf(" %s", nova_consulta.horario);

    // Adiciona a nova consulta à lista
    NoConsulta *novo_no = (NoConsulta *)malloc(sizeof(NoConsulta));
    novo_no->consulta = nova_consulta;
    novo_no->prox = *lista;
    *lista = novo_no;

    printf("Consulta cadastrada com sucesso!\n");
}

// Função para listar todas as consultas
void listar_consultas(NoConsulta *lista) {
    NoConsulta *temp = lista;
    int index = 1;
    while (temp != NULL) {
        printf("Consulta %d:\n", index++);
        printf("CPF: %s\n", temp->consulta.cpf);
        printf("Nome: %s\n", temp->consulta.nome);
        printf("Consulta: %s\n", temp->consulta.consulta);
        printf("Médico: %s\n", temp->consulta.medico);
        printf("Data: %s\n", temp->consulta.data);
        printf("Horário: %s\n\n", temp->consulta.horario);
        temp = temp->prox;
    }
}


// Função para editar uma consulta
void editar_consulta(NoConsulta *lista, char *nome_paciente) {
    NoConsulta *atual = lista;

    while (atual != NULL) {
        if (strcmp(atual->consulta.nome, nome_paciente) == 0) {
            printf("Edição de consulta para %s:\n", nome_paciente);
            int tipo_consulta;
            selecionar_tipo_consulta(atual->consulta.consulta, &tipo_consulta);

            if (tipo_consulta == -1) {
                return; 
            }

            if (selecionar_medico(atual->consulta.medico, tipo_consulta) == -1) {
                return; 
            }

            printf("Data da consulta (dd/mm/aaaa): ");
            scanf(" %s", atual->consulta.data);
            printf("Horário da consulta (hh:mm): ");
            scanf(" %s", atual->consulta.horario);
            printf("Consulta editada com sucesso!\n");
            return;
        }
        atual = atual->prox;
    }
    printf("Paciente não encontrado!\n");
}

// Função para excluir uma consulta
void excluir_consulta(NoConsulta **lista, char *nome_paciente) {
    NoConsulta *temp = *lista;
    NoConsulta *anterior = NULL;

    while (temp != NULL && strcmp(temp->consulta.nome, nome_paciente) != 0) {
        anterior = temp;
        temp = temp->prox;
    }

    if (temp == NULL) {
        printf("Consulta não encontrada!\n");
        return;
    }

    if (anterior == NULL) {
        *lista = temp->prox;
    } else {
        anterior->prox = temp->prox;
    }
    free(temp);
    printf("Consulta excluída com sucesso!\n");
}

// Função para salvar as consultas em arquivo
void salvar_consulta(NoConsulta *lista) {
    FILE *arquivo = fopen("consultas.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    NoConsulta *temp = lista;
    while (temp != NULL) {
        fprintf(arquivo, "%s %s %s %s %s %s\n", temp->consulta.cpf, temp->consulta.nome, temp->consulta.consulta, temp->consulta.medico, temp->consulta.data, temp->consulta.horario);
        temp = temp->prox;
    }
    fclose(arquivo);
    printf("Consultas salvas com sucesso!\n");
}

// Função para carregar consultas do arquivo
void carregar_consultas(NoConsulta **lista) {
    FILE *arquivo = fopen("consultas.txt", "r");
    if (!arquivo) {
        return;
    Consulta consulta;
    while (fscanf(arquivo, "%s %s %s %s %s %s", consulta.cpf, consulta.nome, consulta.consulta, consulta.medico, consulta.data, consulta.horario) != EOF) {
        NoConsulta *novo_no = (NoConsulta *)malloc(sizeof(NoConsulta));
        novo_no->consulta = consulta;
        novo_no->prox = NULL;

        if (*lista == NULL) {
            *lista = novo_no;
        } else {
            NoConsulta *temp = *lista;
            while (temp->prox != NULL) {
                temp = temp->prox;
            }
            temp->prox = novo_no;
        }
    }
    }

    fclose(arquivo);
}

// Função para filtrar consultas por tipo de consulta
void filtrar_consultas_por_tipo(NoConsulta *lista) {
    if (lista == NULL) {
        printf("Não há consultas cadastradas.\n");
        return;
    }
    printf("Selecione o tipo de consulta:\n");
    for (int i = 0; i < num_tipos_consulta; i++) {
        printf("|%d| %s\n", i + 1, tipos_consulta[i]);
    }
    int tipo;
    printf("Digite o número correspondente ao tipo de consulta: ");
    scanf("%d", &tipo);
    if (tipo < 1 || tipo > num_tipos_consulta) {
        printf("Opção inválida!\n");
        return;
    }
    const char *tipo_selecionado = tipos_consulta[tipo - 1];
    int encontrou = 0;

    printf("\nConsultas do tipo %s:\n", tipo_selecionado);
    while (lista != NULL) {
        if (strcmp(lista->consulta.consulta, tipo_selecionado) == 0) {
            printf("Paciente: %s\n", lista->consulta.nome);
            printf("Médico: %s\n", lista->consulta.medico);
            printf("Data: %s\n", lista->consulta.data);
            printf("Horário: %s\n", lista->consulta.horario);
            printf("------------------------\n");
            encontrou = 1;
        }
        lista = lista->prox;
    }
    if (!encontrou) {
        printf("Nenhuma consulta do tipo %s foi encontrada.\n", tipo_selecionado);
    }
}

// Função para filtrar consultas por uma data específica
void filtrar_consultas_por_dia(NoConsulta *lista, const char *data) {
    NoConsulta *temp = lista;
    printf("Consultas no dia %s:\n", data);
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->consulta.data, data) == 0) {
            printf("Paciente: %s\n", temp->consulta.nome);
            printf("Tipo de Consulta: %s\n", temp->consulta.consulta);
            printf("Médico: %s\n", temp->consulta.medico);
            printf("Horário: %s\n\n", temp->consulta.horario);
            found = 1;
        }
        temp = temp->prox;
    }
    if (!found) {
        printf("Nenhuma consulta encontrada para a data %s.\n", data);
    }
}

// Função para ordenar consultas pelo nome do paciente (QuickSort)
NoConsulta* quicksort_list(NoConsulta* lista) {
    if (lista == NULL || lista->prox == NULL) return lista;

    NoConsulta *pivo = lista;
    NoConsulta *menor = NULL, *maior = NULL;
    NoConsulta *temp = lista->prox;

    while (temp != NULL) {
        NoConsulta *prox = temp->prox;
        if (strcmp(temp->consulta.nome, pivo->consulta.nome) < 0) {
            temp->prox = menor;
            menor = temp;
        } else {
            temp->prox = maior;
            maior = temp;
        }
        temp = prox;
    }

    menor = quicksort_list(menor);
    maior = quicksort_list(maior);

    NoConsulta *ordenada = menor;
    if (menor != NULL) {
        temp = menor;
        while (temp->prox != NULL) temp = temp->prox;
        temp->prox = pivo;
    } else {
        ordenada = pivo;
    }
    pivo->prox = maior;
    return ordenada;
}

// Função para realizar busca binária pelo nome do paciente
NoConsulta* busca_binaria_nome(NoConsulta *lista, const char *nome_paciente) {
    NoConsulta *inicio = lista, *fim = NULL;

    while (inicio != fim) {
        NoConsulta *meio = inicio, *avancado = inicio;
        int count = 0;

        while (avancado != fim && count < 2) {
            avancado = avancado->prox;
            if (avancado != fim) {
                avancado = avancado->prox;
                meio = meio->prox;
            }
            count++;
        }
        int cmp = strcmp(meio->consulta.nome, nome_paciente);
        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            inicio = meio->prox;
        } else {
            fim = meio;
        }
    }
    return NULL;
}

// Função para buscar a ficha do paciente usando busca binária
void buscar_ficha_paciente(NoConsulta **lista, const char *nome_paciente) {
    *lista = quicksort_list(*lista); // Ordenar a lista antes da busca
    NoConsulta *resultado = busca_binaria_nome(*lista, nome_paciente);

    if (resultado != NULL) {
        printf("Consulta encontrada:\n");
        printf("CPF: %s\n", resultado->consulta.cpf);
        printf("Nome: %s\n", resultado->consulta.nome);
        printf("Consulta: %s\n", resultado->consulta.consulta);
        printf("Médico: %s\n", resultado->consulta.medico);
        printf("Data: %s\n", resultado->consulta.data);
        printf("Horário: %s\n\n", resultado->consulta.horario);
    } else {
        printf("Nenhuma consulta encontrada para o paciente '%s'.\n", nome_paciente);
    }
}


// Função para liberar a memória da lista
void liberar_memoria_consultas(NoConsulta *lista) {
    NoConsulta *temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->prox;
        free(temp);
    }
}