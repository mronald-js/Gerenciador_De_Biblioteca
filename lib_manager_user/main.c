//programa de gerenciamento de bibliotecas
//Líder de projeto: Marcello Ronald
//Co-participantes: Claudio Cristiano, Davi Neco, Matheus Vieira;

//bibliotecas globais
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//bibliotecas locais que foram criadas com a finalidade de cadastrar clientes da biblioteca
#include "libs/associados.h"
#include "libs/auxiliarfunctions.h"

int main(){

    //chama a função de carregar os dados salvo em um arquivo
    carregarDados();
    
    //Funções que fornecem uma mensagem de boas vindas
    libManager();
    bemVindo();

    int opcao, counter = 0, logado = 0;
    int usuarioJaExistente = 1, naoAutenticado = 1;
    char nome[100], senha[20], entrada[10];

    //programa vai rodar em loop infinito, a ideia de fazer isso é para que rode até que o usuario decida sair
    while(1){

        exibirMenu();
        
        //O código a seguir lê qual a opção escolhida do Menu e caso a opção não esteja entre as listadas ele retorna opção inválida
        do{

            if(counter>0) printf("Opcao invalida!\nTente novamente!\n");

            fgets(entrada, sizeof(entrada), stdin); // Ler a entrada como string
            substitui(entrada);

            // O bloco de código abaixo faz uma validação que checa se a opção informada pelo usuário é válida
            //caso não seja opcao recebe -1 e o loop é reniciado
            char *endptr;
            long tempOpcao = strtol(entrada, &endptr, 10);
            if (*endptr == '\0' && tempOpcao >= 0 && tempOpcao <= 3) opcao = (int)tempOpcao;
            else opcao = -1; // Marcar como opção inválida
            counter++;

        } while (opcao != 0 && opcao != 1 && opcao != 2 && opcao != 3);

        counter = 0;

        if(opcao == 0) return 0;

        //Caso a opção escolhida tenha sido como associado
        if (opcao == 1){
            /*
                O bloco a seguir pode parecer confuso
                Mas basicamente é um do-while aninhado, o do-while de dentro lê uma senha até que a mesma seja válida
                e o do-while de fora lê até que o usuario seja diferente de algum usuário já registrado;
            */
            do{
                do{
                    if(counter == 0) {
                        printf("Digite seu nome de usuario: ");
                        fgets(nome, 100, stdin);
                        substitui(nome);
                        printf("\nDigite sua senha\n(Observacoes: A Senha deve ter pelo menos 6 caracteres\nTente combinar letras, simbolos e numeros para uma senha mais segura!)\n");
                    }else if(counter>0) printf("Senha invalida!\nDigite novamente!\n");
                    fgets(senha, 20, stdin);
                    substitui(senha);
                    counter++;
                }while(strlen(senha) < 6 || strlen(senha) > 20);

                counter = 0;
                if(autenticarAssociado(nome, senha, logado)){
                    //Caso o cliente já exista na base de dados o programa informa que o usuario já existe;
                    printf("\nUSUARIO JA CADASTRADO!\nCADASTRE-SE COM UM NOME DE USUARIO DIFERENTE\n\n");
                    break;
                }else usuarioJaExistente = 0;
            }while(usuarioJaExistente);

            //Registra o usuário como associado (plano A);
            if(usuarioJaExistente == 0){
                addAssociado(nome, senha, 'A');
                salvarDados();
                printf("\nRegistrado Com Sucesso!\n");
                opcao = 3, naoAutenticado = 0;
            }
            else break;
        }

        //Caso a opção escolhida tenha sido como membro básico
        else if(opcao == 2){

            do{
                do{
                    if(counter == 0) {
                        printf("Digite seu nome de usuario: ");
                        fgets(nome, 100, stdin);
                        substitui(nome);
                        printf("\nDigite sua senha\n(Observacoes: A Senha deve ter pelo menos 6 caracteres\nTente combinar letras, simbolos e numeros para uma senha mais segura!)\n");
                    }else if(counter>0) printf("Senha invalida!\nDigite novamente!\n");
                    fgets(senha, 20, stdin);
                    substitui(senha);
                    counter++;
                }while(strlen(senha) < 6 || strlen(senha) > 20);

                counter = 0;
                if(autenticarAssociado(nome, senha, logado)){
                    printf("\nUSUARIO JA CADASTRADO!\nCADASTRE UM NOME DE USUARIO DIFERENTE\n\n");
                    break;
                }else usuarioJaExistente = 0;
            }while(usuarioJaExistente);
            
            if(usuarioJaExistente == 0){
                addAssociado(nome, senha, 'B');
                salvarDados();
                printf("\nRegistrado Com Sucesso!\n");
                opcao = 3, naoAutenticado = 0;
            } else break;

        }

        if(opcao == 3){
            
            //agora o usuario está logado!...
            logado = 1;

            //No caso do usuário já ter cadastro no sistema vai executar a função abaixo;
            while(naoAutenticado){

                printf("\nDigite seu nome de usuario: ");

                fgets(nome, 100, stdin);
                substitui(nome);

                if(buscarAssociado(nome) == NULL) {
                    printf("\nUSUARIO INEXISTENTE!!\n");
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

                if(carregarAssociado(nome, senha) == 1){
                    naoAutenticado = 0;
                    limparTela();
                }else printf("\nSENHA INCORRETA PARA O USUARIO %s!!\nDIGITE NOVAMENTE\n\n", buscarAssociado(nome)->nome);

            }

            if(naoAutenticado == 0){
                
                //Estabelece um ponteiro associado na Estrutura Associado que chama a função "buscarAssociado"
                struct Associado *associado = buscarAssociado(nome);

                //Os nomes estão estranhos porque isso dá cor ao texto, e quis destacar as palavras associado e o nome do usuário.
                if(associado->plano == 'A')
                    printf("\nAtualmente logado como \033[1;32m%s\033[0m | \033[31mA\033[32ms\033[33ms\033[34mo\033[35mc\033[36mi\033[37ma\033[31md\033[32mo\033[0m\n\n", nome);
                else if(associado->plano == 'B')
                    printf("\nAtualmente logado como \033[1;32m%s\033[0m | Plano Basico\n", nome);
                else {
                    printf("\n\nUSUARIO NAO CADASTRADO NO SISTEMA!\n\n");
                    break;
                }
                printf("\nQuando desejar sair digite 0\n");

                while(logado){

                    //variavel tarefa sendo definida como uma opcao a ser definida
                    //dependendo do que for uma acao será executada
                    int tarefa;
                    //esse printf e ilustrativo, daqui pra baixo será onde entrará o menu com as ações requeridas
                    printf("Opcoes (1) buscar livro (2) Solicitar Emprestimo...(3) Limpar terminal\n");
                        do
                        {
                            scanf("%d", &tarefa);
                        } while (tarefa != 0 && tarefa != 1 && tarefa != 2 && tarefa != 3 );
                        if (tarefa == 0){
                            printf("\nSESSAO DE %s ENCERRADA!\nATE A PROXIMA!!\n", nome);
                            return 0;
                        } else{
                        if(tarefa == 3) {
                            limparTela();
                            printf("\nQuando desejar sair digite 0\n");
                            if(associado->plano == 'A')
                                printf("\nAtualmente logado como \033[1;32m%s\033[0m | \033[31mA\033[32ms\033[33ms\033[34mo\033[35mc\033[36mi\033[37ma\033[31md\033[32mo\033[0m\n\n", nome);
                            else if(associado->plano == 'B')
                                printf("\nAtualmente logado como \033[1;32m%s\033[0m | Plano Basico\n", nome);
                        }
                    }
                    
                }
            }
        }
        break;
    }
    return 0;
}
