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
#include "../lib_manager_user/libs/associados.h"

int main(){

    carregarDados();
    libManager();
    bemVindo();

    int opcao, logado = 0;
    char nome[100], senha[20];

    while(1){
    
        menuPrincipal();
        opcao = getOpcao();

        if(opcao == 0) return 0;
        if(opcao == 1){
            registrarAdm(opcao);
            continue;
        }

        if (opcao == 2) {
        int logado = 1;

        printf("Adm: ");
        fgets(nome, 100, stdin);
        substitui(nome);

        char senhaInserida[20];
        printf("Digite sua senha: ");
        fgets(senhaInserida, 20, stdin);
        substitui(senhaInserida);

        // Uso da função autenticarAdmin para autenticação
        if (autenticarAdmin(nome, senhaInserida, logado) == -1)  {
            continue;
        } else {
            while (logado) {
                menuLogado(nome);  // nome do administrador logado

                int tarefa = getTarefa();

                if (tarefa == 0) logado = 0;

                if (tarefa == 1) {
                    cadlivro();
                    continue;
                }

                if (tarefa == 2) {
                    carregarLivros();
                    listar(qntd_livros);
                    continue;
                }
                if (tarefa == 3) {
                    char nome[100];
                    listarAssociados();
                    printf("Checar emprestimos de: ");
                    scanf("%[^\n]", nome);
                    limparbuffer();
                    verificarLivrosEmprestados(nome);
                    continue;
                }

                if (tarefa == 4) limparTela();
            }
        }
    }
    }
    return 0;
}
