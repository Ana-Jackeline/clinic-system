#ifndef CONST_H
#define CONST_H

extern const char *tipos_consulta[];
extern const char *medicos[9][2];
extern const int num_tipos_consulta;

void selecionar_tipo_consulta(char *consulta, int *tipo);
int selecionar_medico(char *medico, int tipo);

#endif