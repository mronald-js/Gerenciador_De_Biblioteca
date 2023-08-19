#ifndef ASSOCIADO_H
#define ASSOCIADO_H

#include <string.h>
#include <stdlib.h>

#define MAX_ASSOCIADOS 100

// Estrutura para representar um associado
typedef struct {
    char nome[100];
    char senha[20];
    char plano;
} Associado;

//definindo um vetor para armazenar o numero de associados
Associado associados[MAX_ASSOCIADOS];
int numAssociados = 0;

// Adiciona um novo associado à lista de associados
Associado addAssociado(char nome[], char senha[], char plano) {
    Associado novoAssociado;

    strcpy(novoAssociado.nome, nome);
    strcpy(novoAssociado.senha, senha);
    novoAssociado.plano = plano;

    associados[numAssociados++] = novoAssociado;

    return novoAssociado;
}

// Busca um associado pelo nome no arquivo de dados
Associado* buscarAssociadoPorNome(char nome[]) {
    FILE *fp = fopen("users/dados.txt", "r");
    if (!fp) {
        return NULL; // Arquivo não encontrado
    }

    Associado* associadoEncontrado = (Associado*) malloc(sizeof(Associado));
    char nomeArquivo[100];
    char senha[100];
    char plano;

    while (fscanf(fp, "%[^,],%[^,],%c\n", nomeArquivo, senha, &plano) != EOF) {

        if (strcmp(nomeArquivo, nome) == 0) {

            strcpy(associadoEncontrado->nome, nomeArquivo);
            strcpy(associadoEncontrado->senha, senha);
            associadoEncontrado->plano = plano;

            fclose(fp);
            return associadoEncontrado;

        }

    }

    fclose(fp);
    free(associadoEncontrado);
    return NULL; // Associado não encontrado

}

// Autentica um associado com base no nome e senha fornecidos
int autenticarAssociado(char nome[], char senha[], int logado) {
    
    Associado* associado = buscarAssociadoPorNome(nome);

    // Se o usuário estiver tentando se registrar
    if (logado == 0) {
        if (associado) {
            printf("O nome de usuario %s já está em uso. Por favor, escolha outro nome.\n", nome);
            free(associado);
            return -1;  // Nome de usuário já em uso
        }
        return 1;  // Registro bem-sucedido
    } 
    // Se o usuário estiver tentando fazer login
    else if (logado == 1) {
        if (!associado) {
            printf("Usuario %s não cadastrado\n", nome);
            return -1;
        } else if (strcmp(associado->senha, senha) != 0) {
            printf("Senha Incorreta\nDigite novamente!\n");
            free(associado);
            return -1;
        } else {
            free(associado);
            return 1;  // Autenticação bem-sucedida
        }
    }
    return -1;  // Para quaisquer outros casos imprevistos
}

#endif  // ASSOCIADO_H