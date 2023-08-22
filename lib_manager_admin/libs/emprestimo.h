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
    printf("Livro %s emprestado com sucesso para %s!\n", titulo, nome);
}

// Função para verificar livros emprestados por um usuário
void verificarLivrosEmprestados(char nome[]) {
    printf("Livros emprestados por %s:\n", nome);
    for (int i = 0; i < numEmprestimos; i++) {
        if (strcmp(emprestimos[i].nomeAssociado, nome) == 0) {
            printf("- %s\n", emprestimos[i].tituloLivro);
        }
    }
}

// Função para retornar um livro
void retornarLivro(char nome[], char titulo[]) {
    int found = 0;
    for (int i = 0; i < numEmprestimos; i++) {
        if (strcmp(emprestimos[i].nomeAssociado, nome) == 0 && strcmp(emprestimos[i].tituloLivro, titulo) == 0) {
            // Move os empréstimos para preencher a lacuna
            for (int j = i; j < numEmprestimos - 1; j++) {
                emprestimos[j] = emprestimos[j + 1];
            }
            numEmprestimos--;
            found = 1;
            printf("Livro %s retornado com sucesso por %s!\n", titulo, nome);
            break;
        }
    }
    if (!found) printf("Não foi possível encontrar o empréstimo do livro %s por %s.\n", titulo, nome);
}