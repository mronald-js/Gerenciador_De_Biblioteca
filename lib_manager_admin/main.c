//lib_manager_admin-version

//bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//bibliotecas locais
#include "libs/admins.h"
#include "libs/livro.h"
#include "libs/auxiliarfunctions.h"
#include "libs/emprestimo.h"

int main(){

    carregarDados();
    libManager();
    bemVindo();

    int opcao;
    char nome[100], senha[20];

    while(1){
    
        menuPrincipal();
        opcao = getOpcao();

        if(opcao == 0) return 0;
        if(opcao == 1){
            registrarAdm(opcao);
            continue;
        }

        if (opcao == 2){

            printf("\nAdm: ");

            fgets(nome, 100, stdin);
            substitui(nome);

            Administrador *adm = buscaAdmPorNome(nome);

            if(adm == NULL) {
                printf("ADMNISTRADOR INEXISTENTE!!\n\n");
                continue;
            }

            char senhaInserida[20];
            
            printf("Digite sua senha: ");
            fgets(senhaInserida, 20, stdin);
            substitui(senhaInserida);

            if(strcmp(senhaInserida, adm->senha) != 0){
                printf("\nSenha incorreta! Tente novamente.\n");
                continue;
            }

            int logado = 1;

            while (logado) {
                
                menuLogado(adm->nome);

                int tarefa = getTarefa();

                if (tarefa == 0) logado = 0;

                if(tarefa == 1) {
                    cadlivro();
                    continue;
                }

                if(tarefa == 2) {
                    carregarLivros();
                    listar(qntd_livros);
                    continue;
                }

                if (tarefa == 3) limparTela();

            }

        }
    }
    return 0;
}
