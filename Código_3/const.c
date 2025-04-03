#include <stdio.h>
#include "const.h"

const char *tipos_consulta[] = {
    "🩺  Consulta Geral",
    "❤️  Cardiologia",
    "🌟  Dermatologia",
    "👩  Ginecologia",
    "🧠  Neurologia",
    "🦴  Ortopedia",
    "👶  Pediatria",
    "💬  Psiquiatria",
    "🚻  Urologia"
};

const char *medicos[9][2] = {
    {"Dr. Carlos", "Dra. Daniela"},
    {"Dr. Eric", "Dra. Bruna"},
    {"Dr. Gabriel", "Dra. Helena"},
    {"Dra. Isabela", "Dr. João"},
    {"Dra. Vitoria", "Dr. Leonardo"},
    {"Dra. Mariana", "Dr. Nicolas"},
    {"Dra. Olivia", "Dr. Paulo"},
    {"Dr. Gustavo", "Dra. Roberta"},
    {"Dra. Sofia", "Dr. Tiago"}
};

const int num_tipos_consulta = sizeof(tipos_consulta) / sizeof(tipos_consulta[0]);

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

//Função para selecionar o médico
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
}