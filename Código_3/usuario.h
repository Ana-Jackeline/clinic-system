#ifndef USUARIO_H
#define USUARIO_H

typedef struct Usuario {
    char nome[50];
    char email[80];
    char senha[20];
    struct Usuario *proximo; 
} Usuario;

Usuario* criar_usuario(char *nome, char *email, char *senha);
void salvar_usuario(Usuario *usuario);
void carregar_usuarios(Usuario **usuarios);
void cadastrar_usuario(Usuario **usuarios);
int realizar_login(Usuario *usuarios, char *nome, char *senha);
void liberar_memoria_usuario(Usuario *usuarios);

#endif