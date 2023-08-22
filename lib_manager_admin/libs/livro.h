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

LIVRO addLivro(char titulo[], int id, char autor[]) {

    LIVRO novoLivro;

    strcpy(novoLivro.titulo, titulo);
    novoLivro.id = id;
    strcpy(novoLivro.autor, autor);

    livros[qntd_livros++] = novoLivro;

    return novoLivro;
}

void salvarLivros() {
    FILE *fp;
    fp = fopen("../livros/livros.txt", "w");
    for(int i = 0; i < qntd_livros; i++) {
        fprintf(fp, "%s,%d,%s\n", livros[i].titulo, livros[i].id, livros[i].autor);
    }
    fclose(fp);
}

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


void cadlivro() {

    int qtd, i;

    do
    {
        printf("Quantos livros deseja cadastrar? (max %d): ", max_livros);
        scanf("%d", &qtd);
        limparbuffer();
    } while (qtd > max_livros);

    for(i = 0; i<qtd; i++){
        char titulo[100], autor[20];
        int id;

        printf("Digite o nome do livro: ");
        scanf("%[^\n]", titulo);
        limparbuffer();

        printf("Digite o ID do livro: ");
        scanf("%d", &id);
        limparbuffer();
        

        printf("Digite o autor do livro: ");
        scanf("%[^\n]", autor);
        limparbuffer();


        printf("Livro %s Adicionado a biblioteca!\n", titulo);
        addLivro(titulo, id, autor);
    }

    salvarLivros();

}

void listar(int qtd) {



    int i;
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