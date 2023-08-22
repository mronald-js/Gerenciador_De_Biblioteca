//lib_manager_user version
//lider de equipe: Marcello Ronald
//Co-participantes: Claudio Cristiano, Matheus Vieira Pacheco, Davi Neco

//bibliotecas globais
#include <stdio.h>
#include <string.h>
//bibliotecas locais
#include "libs/associados.h"
#include "libs/livro.h"
#include "libs/auxiliarfunctions.h"
#include "libs/emprestimo.h"

int main() {
    //funcao que carrega os dados do 'banco de dados'
    carregarDados();
    //funcao que exibe a arte do nome do programa
    libManager();
    //funcao que exibe uma mensagem de boas-vindas na primeira execucao do programa
    bemVindo();

    int opcao;
    char nome[100], senha[20];

    //programa roda em loop ate que o usuario decida sair
    while (1) {
        
        //funcao que chama o menu
        menuPrincipal();
        //armazena o resultado da funcao getOpcao numa variavel chamada opcao
        opcao = getOpcao();
        if (opcao == 0) return 0;
        if (opcao == 1 || opcao == 2) {
            registrarUsuario(opcao);
            continue;
        }

        //a opcao 3 indica que o usuario esta tentando se conectar a sua conta
        if (opcao == 3) {

            printf("\nDigite seu nome de usuario: ");
            scanf("%[^\n]", &nome);
            limparbuffer();

            Associado *associado = buscarAssociadoPorNome(nome);

            if (associado == NULL) {
                printf("\nUSUARIO INEXISTENTE!!\n");
                continue;
            }

            char senhaInserida[20];
            printf("Digite sua senha: ");
            scanf("%[^\n]", &senhaInserida);
            limparbuffer();
            
            if (strcmp(senhaInserida, associado->senha) != 0) {
                printf("\nSenha incorreta! Tente novamente.\n");
                continue;
            }

            int logado = 1;
        
            while (logado) {

                menuLogado(associado->nome, associado->plano);

                int tarefa = getTarefa();

                if (tarefa == 0) logado = 0;
                if (tarefa == 1) {
                    carregarLivros();
                    listar(qntd_livros);
                }
                if (tarefa == 2) {
                    carregarLivros();
                    solicitarEmprestimo(associado->nome);
                }
                if (tarefa == 3) {
                    carregarLivros();
                    retornarLivro(associado->nome);
                }
                if (tarefa == 4) limparTela();
            }
        }
    }
    return 0;
}