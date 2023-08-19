//lib_manager_user version

#include <stdio.h>
#include <string.h>

#include "libs/associados.h"
#include "libs/auxiliarfunctions.h"

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

                menuLogado(associado->nome, associado->plano);

                int tarefa = getTarefa();

                if (tarefa == 0) logado = 0;
                if (tarefa == 3) limparTela();
            }
        }
    }
    return 0;
}