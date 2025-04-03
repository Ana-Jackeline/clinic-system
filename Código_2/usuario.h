#ifndef USUARIO_H
#define USUARIO_H

typedef struct {    
    char nome[50];
    char email[80];
    char senha[20];
} Usuario;

int validar_email(char *email, Usuario **usuarios, int qtd_usuarios);
void salvar_usuario(Usuario *usuario);
void carregar_usuarios(Usuario ***usuarios, int *qtd_usuarios);
void cadastrar_usuario(Usuario ***usuarios, int *qtd_usuarios);
int realizar_login(Usuario **usuarios, int qtd_usuarios, char *nome, char *senha);
void liberar_memoria(Usuario **usuarios, int qtd_usuarios);

#endif