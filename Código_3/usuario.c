#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para criar um novo usuário
Usuario* criar_usuario(char *nome, char *email, char *senha) {
    Usuario *novo_usuario = (Usuario *)malloc(sizeof(Usuario));
    if (novo_usuario != NULL) {
        strcpy(novo_usuario->nome, nome);
        strcpy(novo_usuario->email, email);
        strcpy(novo_usuario->senha, senha);
        novo_usuario->proximo = NULL;
    }
    return novo_usuario;
}

// Função para salvar usuário
void salvar_usuario(Usuario *usuario) {
    FILE *arquivo = fopen("usuarios.txt", "a");
    if (!arquivo) {
        printf("❌ Erro ao abrir o arquivo de usuários.\n");
        return;
    }
    fprintf(arquivo, "%s %s %s\n", usuario->nome, usuario->email, usuario->senha);
    fclose(arquivo);
}

// Função para carregar usuários
void carregar_usuarios(Usuario **usuarios) {
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (!arquivo) return;

    char nome[50], email[80], senha[20];
    while (fscanf(arquivo, "%s %s %s", nome, email, senha) == 3) {
        Usuario *novo_usuario = criar_usuario(nome, email, senha);
        if (novo_usuario) {
            novo_usuario->proximo = *usuarios; // Adiciona no início da lista
            *usuarios = novo_usuario;
        }
    }
    fclose(arquivo);
}

// Função para cadastrar usuário
void cadastrar_usuario(Usuario **usuarios) {
    char nome[50], email[80], senha[20];

    printf("\nDigite seu nome: ");
    scanf(" %[^\n]", nome);

    int email_valido = 0;
    do {
        printf("Digite seu email: ");
        scanf(" %[^\n]", email);

        // Verificar se o email contém '@'
        if (strchr(email, '@') == NULL) {
            printf("❌ Email inválido! Tente novamente.\n");
        } else {
            email_valido = 1;
            // Verificar se o email já está cadastrado
            for (Usuario *u = *usuarios; u != NULL; u = u->proximo) {
                if (strcmp(u->email, email) == 0) {
                    printf("❌ Email já cadastrado! Digite um novo email.\n");
                    email_valido = 0;
                    break;
                }
            }
        }
    } while (!email_valido);
    
    printf("Digite sua senha: ");
    scanf(" %[^\n]", senha);

    Usuario *novo_usuario = criar_usuario(nome, email, senha);
    if (novo_usuario) {
        novo_usuario->proximo = *usuarios; 
        *usuarios = novo_usuario;
        salvar_usuario(novo_usuario);
        printf("Usuário cadastrado com sucesso!\n");
    }
}

// Função para realizar login
int realizar_login(Usuario *usuarios, char *nome, char *senha) {
    for (Usuario *u = usuarios; u != NULL; u = u->proximo) {
        if (strcmp(u->nome, nome) == 0 && strcmp(u->senha, senha) == 0) {
            return 1; 
        }
    }
    return 0; 
}

// Função para liberar memória
void liberar_memoria_usuario(Usuario *usuarios) {
    Usuario *atual = usuarios;
    while (atual != NULL) {
        Usuario *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}
