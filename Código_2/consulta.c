#include "consulta.h"
#include "const.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função para salvar consulta
void salvar_consulta(Consulta *consulta) {
  FILE *arquivo = fopen("consultas.txt", "a");
  if (!arquivo) {
      printf("❌ Erro ao abrir o arquivo de consultas.\n");
      return;
  }
  fprintf(arquivo, "%s %s %s %s %s %s\n", consulta->cpf, consulta->nome, consulta->consulta, consulta->medico, consulta->data, consulta->horario);
  fclose(arquivo);
}

//Função para carregar consultas
void carregar_consultas(Consulta ***consultas, int *qtd_consultas) {
  FILE *arquivo = fopen("consultas.txt", "r");
  if (!arquivo) return;

  Consulta *consulta;
  while (!feof(arquivo)) {
      consulta = malloc(sizeof(Consulta));
      if (fscanf(arquivo, "%s %s %s %s %s %s", consulta->cpf, consulta->nome, consulta->consulta, consulta->medico, consulta->data, consulta->horario) == 6) {
          *consultas = realloc(*consultas, (*qtd_consultas + 1) * sizeof(Consulta*));
          (*consultas)[*qtd_consultas] = consulta;
          (*qtd_consultas)++;
      } else {
          free(consulta);
      }
  }
  fclose(arquivo);
}

//Função para selecionar tipo de consulta
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
          printf("\n❌ Opção inválida!\nTente novamente.\n\n");
      }
  }
}

//Função para selecionar médico
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
          printf("\n❌ Opção inválida!\nTente novamente.\n\n");
      } else {
          strcpy(medico, medicos[tipo][opcao - 1]);
          return 1;
      }
  } while (1);

  return 0; 
}

//Função para cadastrar consulta
void cadastrar_consulta(Consulta ***consultas, int *qtd_consultas) {
  Consulta *nova_consulta = malloc(sizeof(Consulta));
  int tipo;
  printf("\nDigite o CPF do paciente: ");
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

  salvar_consulta(nova_consulta);
}

//Função para listar consultas
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

//Função para editar consulta
void editar_consulta(Consulta **consultas, int qtd_consultas, int indice) {
  if (indice < 0 || indice >= qtd_consultas) {
      printf("\n❌ Índice inválido!\n");
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
  printf("Digite a nova data (dd/mm/aaaa): ");
  scanf("%s", consulta->data);
  printf("Digite o novo horário (hh:mm): ");
  scanf("%s", consulta->horario);

  FILE *arquivo = fopen("consultas.txt", "w");
  for (int i = 0; i < qtd_consultas; i++) {
      salvar_consulta(consultas[i]);
  }
  fclose(arquivo);
}

// Função para excluir uma consulta
void excluir_consulta(Consulta **consultas, int *qtd_consultas, int indice) {
  if (indice < 0 || indice >= *qtd_consultas) {
      printf("\n❌ Índice inválido!\n");
      return;
  }
  free(consultas[indice]);
  for (int i = indice; i < *qtd_consultas - 1; i++) {
      consultas[i] = consultas[i + 1];
  }
  (*qtd_consultas)--;
  *consultas = realloc(*consultas, (*qtd_consultas) * sizeof(Consulta*));
  FILE *arquivo = fopen("consultas.txt", "w");
  if (!arquivo) {
      printf("❌ Erro ao abrir o arquivo de consultas para salvar as alterações.\n");
      return;
  }
  for (int i = 0; i < *qtd_consultas; i++) {
      fprintf(arquivo, "%s %s %s %s %s %s\n", consultas[i]->cpf, consultas[i]->nome, consultas[i]->consulta, consultas[i]->medico, consultas[i]->data, consultas[i]->horario);
  }
  fclose(arquivo);
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

// Função de Quicksort para ordenar as consultas pelo nome do paciente
void quicksort(Consulta **consultas, int inicio, int fim) {
  if (inicio < fim) {
      int pivo = particao(consultas, inicio, fim);
      quicksort(consultas, inicio, pivo - 1);
      quicksort(consultas, pivo + 1, fim);
  }
}

int particao(Consulta **consultas, int inicio, int fim) {
  char *pivo = consultas[fim]->nome;
  int i = inicio - 1;
  for (int j = inicio; j < fim; j++) {
      if (strcmp(consultas[j]->nome, pivo) < 0) {
          i++;
          Consulta *temp = consultas[i];
          consultas[i] = consultas[j];
          consultas[j] = temp;
      }
  }
  Consulta *temp = consultas[i + 1];
  consultas[i + 1] = consultas[fim];
  consultas[fim] = temp;
  return i + 1;
}

// Função de Busca Binária para procurar a ficha do paciente pelo nome
int busca_binaria(Consulta **consultas, int qtd_consultas, char *nome_paciente) {
  int esquerda = 0;
  int direita = qtd_consultas - 1;

  while (esquerda <= direita) {
      int meio = (esquerda + direita) / 2;
      int cmp = strcmp(consultas[meio]->nome, nome_paciente);

      if (cmp == 0) {
          return meio; 
      } else if (cmp < 0) {
          esquerda = meio + 1;
      } else {
          direita = meio - 1;
      }
  }
  return -1; 
}

// Função para buscar a ficha do paciente
void buscar_ficha_paciente(Consulta **consultas, int qtd_consultas) {
  char nome_paciente[50];
  printf("Digite o nome do paciente: ");
  scanf(" %[^\n]", nome_paciente);

  quicksort(consultas, 0, qtd_consultas - 1);

  int indice = busca_binaria(consultas, qtd_consultas, nome_paciente);

  if (indice != -1) {
      printf("Consulta encontrada:\n");
      printf("CPF: %s\n", consultas[indice]->cpf);
      printf("Nome: %s\n", consultas[indice]->nome);
      printf("Consulta: %s\n", consultas[indice]->consulta);
      printf("Médico: %s\n", consultas[indice]->medico);
      printf("Data: %s\n", consultas[indice]->data);
      printf("Horário: %s\n\n", consultas[indice]->horario);
  } else {
      printf("❌ Nenhuma consulta encontrada para o paciente '%s'.\n", nome_paciente);
  }
}

//Função para liberae memória da consulta
void liberar_memoria_consultas(Consulta **consultas, int qtd_consultas) {
    for (int i = 0; i < qtd_consultas; i++) {
        free(consultas[i]);
    }
    free(consultas);
}