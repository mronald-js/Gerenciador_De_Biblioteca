#ifndef ASSOCIADO_H
#define ASSOCIADO_H

#include <string.h>
#include <stdlib.h>

#define MAX_ASSOCIADOS 100

//struct que guarda os associados
struct Associado {
    char nome[100];
    char senha[20];
    char plano;
};

struct Associado associados[MAX_ASSOCIADOS];
int numAssociados = 0;

//função que adiciona os associados
struct Associado addAssociado(char nome[], char senha[], char plano){

    struct Associado novoAssociado;

    strcpy(novoAssociado.nome, nome);
    strcpy(novoAssociado.senha, senha);
    novoAssociado.plano = plano;

    //Armaneza o novo associado na lista de associados
    associados[numAssociados++] = novoAssociado;

    return novoAssociado;
    
}

//função para saber se o nome do associado digitado já nao existe
struct Associado *buscarAssociado(char nome[]) {
    FILE *fp = fopen("users/dados.txt", "r");
    if (fp == NULL) {
        //caso o arquivo não exista
        return NULL;
    }

    struct Associado *associadoEncontrado = malloc(sizeof(struct Associado));
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
    return NULL; //caso o usuario não tenha sido encontrado
}


int carregarAssociado(const char *nomeProcurado, const char *senhaProcurada) {
    FILE *fp;
    fp = fopen("users/dados.txt", "r");
    if (fp == NULL) {
        return 0; // Retorna 0 para indicar que o arquivo não foi encontrado
    }
    char nome[100];
    char senha[100];
    char plano;
    while (fscanf(fp, "%[^,],%[^,],%c\n", nome, senha, &plano) != EOF) {
        if (strcmp(nome, nomeProcurado) == 0 && strcmp(senha, senhaProcurada) == 0) {
            fclose(fp);
            return 1; // Retorna 1 para indicar sucesso (associado autenticado)
        }
    }
    fclose(fp);
    return -1; // Retorna -1 para indicar que o associado não foi encontrado
}



int autenticarAssociado(char nome[], char senha[], int logado){

    struct Associado *associado = buscarAssociado(nome);

    //caso o status de logado seja 0 significa que o usuario ainda está cadastrado
    if(logado == 0){
        if (associado != NULL) { // Verifica se o associado foi encontrado
            if ((strcmp(associado->senha, senha) == 0) && strcmp(associado->nome, nome) == 0) {
                printf("Autenticação bem-sucedida para o Usuario: %s\n", nome);
                return 1; // registro bem-sucedido
            } else
                return -1; // registro falhou

    } else if(logado == 1){//caso seja 1 segnifica que ele já tem cadastro e esta tentado realizar login
        if(carregarAssociado(nome, senha) == -1) {
            printf("Usuario %s não cadastrado\n", nome);
            return -1;
        }
        else if(strcmp(associado->senha, senha) != 0) {
            printf("Senha Incorreta\nDigite novamente!\n");
            return -1;
        }
        else return 1;
        }
    }
}

#endif // ASSOCIADO_H