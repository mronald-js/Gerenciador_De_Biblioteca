#include <stdio.h>
#include <string.h>

#include "libs/associados.h"
#include "libs/auxiliarfunctions.h"

void menuPrincipal() {
    printf("\nMenu Principal:\n");
    printf("1 - Registrar (Plano A - ASSOCIADO)\n");
    printf("2 - Registrar (Plano B - MEMBRO BASICO)\n");
    printf("3 - Login\n");
    printf("0 - Sair\n");
}

int getOpcao() {
    int opcao;
    do {
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparbuffer();
    } while (opcao < 0 || opcao > 3);
    return opcao;
}

void menuLogado() {
    printf("\nOpcoes:\n");
    printf("1 - Buscar livro\n");
    printf("2 - Solicitar Emprestimo\n");
    printf("3 - Limpar terminal\n");
    printf("0 - Logout\n");
}

int getTarefa() {
    int tarefa;
    do {
        scanf("%d", &tarefa);
    } while (tarefa < 0 || tarefa > 3);
    return tarefa;
}

int main() {
    carregarDados();
    libManager();
    bemVindo();

    int opcao;
    char nome[100], senha[20];

    while (1) {
        
        menuPrincipal();
        opcao = getOpcao();

        if (opcao == 0) return 0;

        if (opcao == 1 || opcao == 2) {
            registrarUsuario(opcao);
            continue;
        }

        if (opcao == 3) {

            printf("\nDigite seu nome de usuario: ");
            fgets(nome, 100, stdin);
            substitui(nome);
            Associado *associado = buscarAssociadoPorNome(nome);

            if (associado == NULL) {
                printf("\nUSUARIO INEXISTENTE!!\n");
                continue;
            }

            char senhaInserida[20];
            printf("\nDigite sua senha: ");
            fgets(senhaInserida, 20, stdin);
            substitui(senhaInserida);
            
            if (strcmp(senhaInserida, associado->senha) != 0) {
                printf("\nSenha incorreta! Tente novamente.\n");
                continue;
            }

            int logado = 1;

            while (logado) {
                menuLogado();
                int tarefa = getTarefa();

                if (tarefa == 0) logado = 0;
                if (tarefa == 3) limparTela();
            }
        }
    }
    return 0;
}