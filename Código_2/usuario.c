#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função para validar email
int validar_email(char *email, Usuario **usuarios, int qtd_usuarios) {
  if (strlen(email) >= 80) return 0;
  if (strchr(email, '@') == NULL) return 0;

  // Verificação de duplicidade
  for (int i = 0; i < qtd_usuarios; i++) {
      if (strcmp(usuarios[i]->email, email) == 0) {
          return 0; 
      }
  }
  return 1;
}

//Função para salvar usuário
void salvar_usuario(Usuario *usuario) {
  FILE *arquivo = fopen("usuarios.txt", "a");
  if (!arquivo) {
      printf("Erro ao abrir o arquivo de usuários.\n");
      return;
  }
  fprintf(arquivo, "%s %s %s\n", usuario->nome, usuario->email, usuario->senha);
  fclose(arquivo);
}

//Função para carregar usuário
void carregar_usuarios(Usuario ***usuarios, int *qtd_usuarios) {
  FILE *arquivo = fopen("usuarios.txt", "r");
  if (!arquivo) return;

  Usuario *usuario;
  while (!feof(arquivo)) {
      usuario = malloc(sizeof(Usuario));
      if (fscanf(arquivo, "%s %s %s", usuario->nome, usuario->email, usuario->senha) == 3) {
          *usuarios = realloc(*usuarios, (*qtd_usuarios + 1) * sizeof(Usuario*));
          (*usuarios)[*qtd_usuarios] = usuario;
          (*qtd_usuarios)++;
      } else {
          free(usuario);
      }
  }
  fclose(arquivo);
}

//Função para cadastrar usuário
void cadastrar_usuario(Usuario ***usuarios, int *qtd_usuarios) {
  Usuario *novo_usuario = malloc(sizeof(Usuario));
  printf("Digite o nome do usuário: ");
  scanf(" %s", novo_usuario->nome);
  printf("Digite o e-mail do usuário: ");
  scanf(" %s", novo_usuario->email);
  if (!validar_email(novo_usuario->email, *usuarios, *qtd_usuarios)) {
      printf("E-mail inválido!\n");
      free(novo_usuario);
      return;
  }
  printf("Digite a senha do usuário: ");
  scanf(" %s", novo_usuario->senha);

  *usuarios = realloc(*usuarios, (*qtd_usuarios + 1) * sizeof(Usuario*));
  (*usuarios)[*qtd_usuarios] = novo_usuario;
  (*qtd_usuarios)++;

  salvar_usuario(novo_usuario);
}

//Função para realizar login
int realizar_login(Usuario **usuarios, int qtd_usuarios, char *nome, char *senha) {
  for (int i = 0; i < qtd_usuarios; i++) {
      if (strcmp(usuarios[i]->nome, nome) == 0 && strcmp(usuarios[i]->senha, senha) == 0) {
          return 1;
      }
  }
  return 0;
}

//Função para liberar memória do usuario
void liberar_memoria(Usuario **usuarios, int qtd_usuarios) {
    for (int i = 0; i < qtd_usuarios; i++) {
        free(usuarios[i]);
    }
    free(usuarios);
}