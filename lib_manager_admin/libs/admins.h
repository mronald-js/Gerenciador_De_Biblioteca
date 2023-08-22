#include <string.h>
#include <stdlib.h>

#define MAX_ADMINS 10

typedef struct {
    char nome[100];
    char senha[20];
} Administrador;

Administrador admins[MAX_ADMINS];
int numAdmins = 0;

Administrador addAdm(char nome[], char senha[]) {
    Administrador novoAdm;
    strcpy(novoAdm.nome, nome);
    strcpy(novoAdm.senha, senha);
    admins[numAdmins++] = novoAdm;
    return novoAdm;
}

Administrador* buscaAdmPorNome(char *nome) {
    FILE *fp = fopen("admins/dados.txt", "r");
    if(!fp) {
        return NULL;
    }

    Administrador* admEncontrado = (Administrador*) malloc(sizeof(Administrador));
    char nomeArquivo[100];
    char senha[100];

    while(fscanf(fp, "%[^,],%[^\n]", nomeArquivo, senha) != EOF) {
        if (strcmp(nomeArquivo, nome) == 0) {
            strcpy(admEncontrado->nome, nomeArquivo);
            strcpy(admEncontrado->senha, senha);
            fclose(fp);
            return admEncontrado;
        }
    }

    fclose(fp);
    free(admEncontrado);
    return NULL;
}

int autenticarAdmin(char nome[], char senha[], int logado) {
    
    Administrador* adm = buscaAdmPorNome(nome);

    if (logado == 0) {
        if (adm) {
            printf("O nome de administrador %s ja este em uso. Por favor, escolha outro nome.\n", nome);
            free(adm);
            return -1;
        }
        return 1;  // Registro bem-sucedido
    } 
    else if (logado == 1) {
        if (!adm) {
            printf("Adm %s não cadastrado\n", nome);
            return -1;
        } else if (strcmp(adm->senha, senha) != 0) {
            printf("Senha Incorreta\nDigite novamente!\n");
            free(adm);
            return -1;
        } else {
            free(adm);
            return 1;  // Autenticação bem-sucedida
        }
    }
    free(adm);
    return -1;  // Para quaisquer outros casos imprevistos
}