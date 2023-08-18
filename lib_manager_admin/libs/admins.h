#ifndef ADMIN_H
#define ADMIN_H

#include <string.h>
#include <stdlib.h>

#define MAX_ADMINS 10

//struct que guarda os admins
struct ADMIN {
    char nome[100];
    char senha[20];
};

struct ADMIN admins[MAX_ADMINS];
int numAdmins = 0;

//função que adiciona os admins
struct ADMIN addAdmin(char nome[], char senha[]){

    struct ADMIN novoAdmin;

    strcpy(novoAdmin.nome, nome);
    strcpy(novoAdmin.senha, senha);

    //Armaneza o novo admin na lista de admins
    admins[numAdmins++] = novoAdmin;

    return novoAdmin;
    
}

//função para saber se o nome do admin digitado já nao existe
struct ADMIN *buscarAdmin(char nome[]) {
    FILE *fp = fopen("admins/dados.txt", "r");
    if (fp == NULL) {
        //caso o arquivo não exista
        return NULL;
    }

    struct ADMIN *adminEncontrado = malloc(sizeof(struct ADMIN));
    char nomeArquivo[100];
    char senha[100];

    while (fscanf(fp, "%[^,],%[^\n]\n", nomeArquivo, senha) != EOF) {
        if (strcmp(nomeArquivo, nome) == 0) {
            strcpy(adminEncontrado->nome, nomeArquivo);
            strcpy(adminEncontrado->senha, senha);
            fclose(fp);
            return adminEncontrado;
        }
    }

    fclose(fp);
    free(adminEncontrado);
    return NULL; //caso o usuario não tenha sido encontrado
}


int carregarAdmin(const char *nomeProcurado, const char *senhaProcurada) {
    FILE *fp;
    fp = fopen("admins/dados.txt", "r");
    if (fp == NULL) {
        return 0; // Retorna 0 para indicar que o arquivo não foi encontrado
    }
    char nome[100];
    char senha[100];
    while (fscanf(fp, "%[^,],%[^\n]\n", nome, senha) != EOF) {
        if (strcmp(nome, nomeProcurado) == 0 && strcmp(senha, senhaProcurada) == 0) {
            fclose(fp);
            return 1; // Retorna 1 para indicar sucesso (associado autenticado)
        }
    }
    fclose(fp);
    return -1; // Retorna -1 para indicar que o admin não foi encontrado
}



int autenticarAdmin(char nome[], char senha[], int logado){

    struct ADMIN *admin = buscarAdmin(nome);

    //caso o status de logado seja 0 significa que o usuario ainda está cadastrado
    if(logado == 0){
        if (admin != NULL) { // Verifica se o admin foi encontrado
            if ((strcmp(admin->senha, senha) == 0) && strcmp(admin->nome, nome) == 0) {
                printf("Autenticação bem-sucedida para o Usuario: %s\n", nome);
                return 1; // registro bem-sucedido
            } else
                return -1; // registro falhou

    } else if(logado == 1){//caso seja 1 segnifica que ele já tem cadastro e esta tentado realizar login
        if(carregarAdmin(nome, senha) == -1) {
            printf("Usuario %s não cadastrado\n", nome);
            return -1;
        }
        else if(strcmp(admin->senha, senha) != 0) {
            printf("Senha Incorreta\nDigite novamente!\n");
            return -1;
        }
        else return 1;
        }
    }
}

#endif