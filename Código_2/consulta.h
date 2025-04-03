#ifndef CONSULTA_H
#define CONSULTA_H

typedef struct {
    char cpf[12];
    char nome[50];
    char consulta[50];
    char medico[50];
    char data[9];
    char horario[6];
} Consulta;

void salvar_consulta(Consulta *consulta);
void carregar_consultas(Consulta ***consultas, int *qtd_consultas);
void cadastrar_consulta(Consulta ***consultas, int *qtd_consultas);
void listar_consultas(Consulta **consultas, int qtd_consultas);
void editar_consulta(Consulta **consultas, int qtd_consultas, int indice);
void excluir_consulta(Consulta **consultas, int *qtd_consultas, int indice);
void filtrar_consultas_por_tipo(Consulta **consultas, int qtd_consultas);
void filtrar_consultas_por_dia(Consulta **consultas, int qtd_consultas);
void buscar_ficha_paciente(Consulta **consultas, int qtd_consultas);
void liberar_memoria_consultas(Consulta **consultas, int qtd_consultas);

#endif