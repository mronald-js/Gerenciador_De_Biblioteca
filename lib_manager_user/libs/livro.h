#include <stdio.h>
#include <string.h>

#define max_livros 100
#define tam_max 100

typedef struct {
    char titulo[tam_max];
    int id;
    char autor[tam_max];
}LIVRO;

void limparbuffer(){
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

LIVRO livros[max_livros];
int qntd_livros = 0;

void carregarLivros(){
    FILE *fp;
    fp = fopen("../livros/livros.txt", "r");
    if (fp == NULL) {
        return;
    }
    while(!feof(fp)) {
        LIVRO novoLIVRO;
        fscanf(fp, "%[^,],%d,%[^\n]\n", novoLIVRO.titulo, &novoLIVRO.id, novoLIVRO.autor);
        livros[qntd_livros++] = novoLIVRO;
    }
    fclose(fp);
}


void listar(int qtd) {

    int i;
    if(qtd == 0){
        printf("Nenhum livro disponivel\n");
    } else {
        printf("\nLivros cadastrados:\n");
        for (i = 0; i < qtd; i++) {
            printf("--------------------------------------\n");
            printf("Livro %d:\n", i + 1);
            printf("Nome: %s\n", livros[i].titulo);
            printf("ID: %d\n", livros[i].id);
            printf("Autor: %s\n", livros[i].autor);
            printf("--------------------------------------\n");
        }
    }
}