//programa de gerenciamento de bibliotecas

//bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//bibliotecas locais
#include "libs/admins.h"
#include "libs/auxiliarfunctions.h"

int main(){

    carregarDados();
    libManager();
    bemVindo();

    int opcao, counter = 0, logado = 0, adminJaExistente = 1, naoAutenticado = 1;
    char nome[100], senha[20], entrada[10];

    while(1){

        exibirMenu();

        do{

            if(counter>0) printf("Opcao invalida!\nTente novamente!\n");

            fgets(entrada, sizeof(entrada), stdin); // Ler a entrada como string
            substitui(entrada);

            char *endptr;
            long tempOpcao = strtol(entrada, &endptr, 10);
            if (*endptr == '\0' && tempOpcao >= 0 && tempOpcao <= 2) opcao = (int)tempOpcao;
            else opcao = -1; // Marcar como opção inválida
            counter++;

        } while (opcao != 0 && opcao != 1 && opcao != 2);

        counter = 0;
        if (opcao == 0) return 0;


        if(opcao == 1){
            do{
                do{
                    if(counter == 0) {
                        printf("Digite o nome do Admin a ser cadastrado: ");
                        fgets(nome, 100, stdin);
                        substitui(nome);
                        printf("\nDigite a senha desejada\n(Observacoes: A Senha deve ter pelo menos 6 caracteres\nTente combinar letras, simbolos e numeros para uma senha mais segura!)\n");
                    }
                    else if(counter>0) printf("Senha invalida!\nDigite novamente!\n");
                    fgets(senha, 20, stdin);
                    substitui(senha);
                    counter++;
                }while(strlen(senha) < 6 || strlen(senha) > 20);
                counter = 0;
                if(autenticarAdmin(nome, senha, logado)){
                    printf("\nADMIN JA CADASTRADO!\nCADASTRE-SE COM UM NOME DE ADMIN DIFERENTE\n\n");
                    break;
                }else adminJaExistente = 0;
        }while(adminJaExistente);

            if(adminJaExistente == 0){
                addAdmin(nome, senha);
                salvarDados();
                    printf("\nAdmin registrado com sucesso!\n");
                opcao = 2, naoAutenticado = 0;
            }else break;
        }

        else if(opcao == 2){

            logado = 1;

            while(naoAutenticado){

                printf("\nAdmin: ");

                fgets(nome, 100, stdin);
                substitui(nome);

                if(buscarAdmin(nome) == NULL) {
                    printf("\nADMIN INEXISTENTE!!\n");
                    break;
                }

                do{
                    if(counter>=1) printf("SENHA INVALIDA\nPOR FAVOR DIGITE NOVAMENTE!!\n");
                    printf("\nDigite sua senha: ");
                    fgets(senha, 20, stdin);
                    substitui(senha);
                    counter++;
                }while(strlen(senha) < 6 || strlen(senha) > 20);

                counter = 0;
                if(carregarAdmin(nome, senha) == 1){
                    naoAutenticado = 0;
                    limparTela();
                }else printf("\nSENHA INCORRETA!!\nDIGITE NOVAMENTE\n\n");
            }

            if(naoAutenticado == 0){
                
                //busca na struct Associado
                struct ADMIN *admin = buscarAdmin(nome);
                printf("\nAtualmente logado como \033[1;32m%s\033[0m | \033[31mA\033[32ms\033[33ms\033[34mo\033[35mc\033[36mi\033[37ma\033[31md\033[32mo\033[0m\n\n", nome);

                printf("\nQuando desejar sair digite 0\n");

                while(logado){
                    //variavel tarefa sendo definida como uma opcao a ser definida
                    //dependendo do que for uma acao será executada
                    int tarefa;
                    //esse printf e ilustrativo, daqui pra baixo será onde entrará o menu com as ações requeridas
                    printf("Opcoes (1) Adicionar Livres (2) Conferir Atrasos de Devoluções...(3) Limpar terminal\n");
                        do{
                            scanf("%d", &tarefa);
                        } while (tarefa != 0 && tarefa != 1 && tarefa != 2 && tarefa != 3 );
                        if (tarefa == 0){
                            logado = 0;
                        } else{
                        if(tarefa == 3) {
                            limparTela();
                            printf("\nQuando desejar sair digite 0\n");
                            printf("\nAtualmente logado como \033[1;32m%s\033[0m | \033[31mA\033[32ms\033[33ms\033[34mo\033[35mc\033[36mi\033[37ma\033[31md\033[32mo\033[0m\n\n", nome);
                        }
                    }
                }
            }
        }
            break;
    }

    return 0;

}
