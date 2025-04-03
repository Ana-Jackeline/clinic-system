#include <stdio.h>

struct Aluno {
  int mat;
  char nome[10];
  float media;
};


void atualizar(struct Aluno *v, int qtd) {
  int i;
  int mat;
  printf("Digite a matricula do aluno: ");
  scanf("%d", &mat);
  int atualizou = 0;
  for (i = 0; i < qtd; i++) {
    if (v[i].mat == mat) {
      printf("Informe a nova media: ");
      scanf("%f", &v[i].media);
      atualizou = 1;
    }
  }
  if (atualizou == 0) {
    printf("Aluno nao encontrado!\n");
  }
}

void excluir(struct Aluno *v, int *qtd) {
  int i;
  printf("Informe a matricula do aluno: \n");
  int mat;
  scanf("%d", &mat);
  struct Aluno temp[*qtd];
  int j = 0;
  for (i = 0; i < *qtd; i++) {
    if (v[i].mat != mat) {
      temp[j] = v[i];
      j++;
    }
  }
  for (i = 0; i < j; i++) {
    v[i] = temp[i];
  }
  if (j == *qtd) {
    printf("Aluno nao encontrado!\n");
  }
  else {
    *qtd = *qtd - 1;
  }
}

void cadastrar(struct Aluno* v, int* qtd) {
    printf("Informe os dados do aluno:\n");
    scanf("%d %s %f", &v[*qtd].mat, v[*qtd].nome, &v[*qtd].media);
    *qtd = *qtd + 1;
}

void listar(struct Aluno* v, int qtd) {
    int i;
    for (i = 0; i < qtd; i++) {
        printf("Aluno: %d %s %f\n", v[i].mat, v[i].nome, v[i].media);
    }
}

void menu() {
    printf("=== escolha uma opcao ===\n");
    printf("1 - cadastrar\n");
    printf("2 - listar\n");
    printf("3 - atualizar\n");
    printf("4 - excluir\n");
    printf("0 - sair\n");
    printf("==========================\n");
}

int main() {
    //!showMemory(start=65520)
    struct Aluno v[20];
    int qtd = 0;
    menu();
    int op;
    scanf("%d", &op);
    while (op != 0) {
        if (op == 1) {
            cadastrar(v, &qtd);
        }
        else if (op == 2) {
            listar(v, qtd);
        } 
        else if (op == 3) {
            atualizar(v, qtd);
        }
        else if(op == 4) {
            excluir(v, &qtd);
        }
        menu();
        scanf("%d", &op);
    }
    return 0;
}