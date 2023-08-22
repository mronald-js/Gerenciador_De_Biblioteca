#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMPRESTIMOS 100

// Estrutura para representar um empréstimo
typedef struct {
    char nomeAssociado[100];
    char tituloLivro[100];
} Emprestimo;

// Vetor para armazenar empréstimos
Emprestimo emprestimos[MAX_EMPRESTIMOS];
int numEmprestimos = 0;

// Função para emprestar um livro
void emprestarLivro(char nome[], char titulo[]) {
    Emprestimo novoEmprestimo;
    strcpy(novoEmprestimo.nomeAssociado, nome);
    strcpy(novoEmprestimo.tituloLivro, titulo);
    emprestimos[numEmprestimos++] = novoEmprestimo;
    printf("O Livro %s foi emprestado com sucesso para %s!\n", titulo, nome);
}

void solicitarEmprestimo(char nomeAssociado[]) {
    char tituloDesejado[tam_max];
    char tituloArquivo[tam_max];
    int id;
    char autor[tam_max];
    int livroEncontrado = 0;

    // Solicitar o título do livro ao usuário
    printf("Digite o titulo do livro que deseja pegar emprestado: ");
    scanf("%[^\n]", &tituloDesejado);
    limparbuffer();

    // Abrir o arquivo e verificar se o livro está disponível
    FILE *fp = fopen("../livros/livros.txt", "r");

    if (fp == NULL) {
        printf("Erro ao acessar a lista de livros.\n");
        return;
    }

    while (fscanf(fp, "%[^,],%d,%[^\n]\n", tituloArquivo, &id, autor) != EOF) {
        if (strcmp(tituloArquivo, tituloDesejado) == 0) {
            livroEncontrado = 1;
            break;
        }
    }
    fclose(fp);

    // Se o livro estiver disponível, realizar o empréstimo
    if (livroEncontrado)
        emprestarLivro(nomeAssociado, tituloDesejado);
    else
        printf("Desculpe, o livro '%s' nao esta disponivel no momento.\n", tituloDesejado);
}

// Função para retornar um livro
void retornarLivro(char nomeAssociado[]) {
    char tituloDesejado[tam_max];
    int found = 0;

    // Solicitar o título do livro que o associado deseja devolver
    printf("Digite o titulo do livro que deseja realizar devolucao: ");
    scanf("%[^\n]", tituloDesejado);
    limparbuffer();

    // Verificar se o livro está na lista de empréstimos
    for (int i = 0; i < numEmprestimos; i++) {
        if (strcmp(emprestimos[i].nomeAssociado, nomeAssociado) == 0 && strcmp(emprestimos[i].tituloLivro, tituloDesejado) == 0) {
            // Move os empréstimos para preencher a lacuna
            for (int j = i; j < numEmprestimos - 1; j++) {
                emprestimos[j] = emprestimos[j + 1];
            }
            numEmprestimos--;
            found = 1;
            printf("\nLivro %s retornado com sucesso por %s!\n", tituloDesejado, nomeAssociado);
            break;
        }
    }

    if (!found) {
        printf("Nao foi possível encontrar o emprestimo do livro %s para o associado %s.\n", tituloDesejado, nomeAssociado);
    }
}
