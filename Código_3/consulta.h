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

typedef struct NoConsulta {
    Consulta consulta;
    struct NoConsulta *prox;
} NoConsulta;

void salvar_consulta(NoConsulta *lista);
void carregar_consultas(NoConsulta **lista);
void cadastrar_consulta(NoConsulta **lista);
void listar_consultas(NoConsulta *lista);
void editar_consulta(NoConsulta *lista, char *nome_paciente);
void excluir_consulta(NoConsulta **lista, char *nome_paciente);
void filtrar_consultas_por_tipo(NoConsulta *lista);
void filtrar_consultas_por_dia(NoConsulta *lista, const char *data);
void buscar_ficha_paciente(NoConsulta **lista, const char *nome_paciente);
void liberar_memoria_consultas(NoConsulta *lista);

#endif