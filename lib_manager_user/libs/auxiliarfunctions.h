//Esse arquivo supõe-se ser para as funções auxiliares

#include <stdio.h>
#include <stdlib.h>

//troca o último \n por um caracter nulo, dessa forma evitando que o \n fique no buffer
void substitui(char *vetor){
    vetor[strcspn(vetor, "\n")] = '\0'; 
}

//função que lê e retorna a opcao da tarefa desejada
int getTarefa() {
    int tarefa;
    do {
        scanf("%d", &tarefa);
        limparbuffer();
    } while (tarefa < 0 || tarefa > 4);
    return tarefa;
}

void menuPrincipal() {
    printf("\nMenu Principal:\n");
    printf("1 - Registrar (Plano A - ASSOCIADO)\n");
    printf("2 - Registrar (Plano B - MEMBRO BASICO)\n");
    printf("3 - Login\n");
    printf("0 - Sair\n");
}

void menuLogado(char *nome, char plano) {
    printf("\nAtualmente logado como \033[32m%s\033[0m | PLANO \033[31m%c\033[0m\n", nome, plano);
    printf("\nOpcoes:\n");
    printf("1 - Exibir Livros\n");
    printf("2 - Solicitar Emprestimo\n");
    printf("3 - Realizar Devolucao\n");
    printf("4 - Limpar terminal\n");
    printf("0 - Logout\n");
}

//função que salva os dados dos usuarios num arquivo users/dados.txt
//ele salva, o nome, a senha e o plano dos associados
void salvarDados() {
    FILE *fp;
    fp = fopen("users/dados.txt", "w");
    for(int i = 0; i < numAssociados; i++) {
        fprintf(fp, "%s,%s,%c\n", associados[i].nome, associados[i].senha, associados[i].plano);
    }
    fclose(fp);
}
//funcao que le uma opcao especifica escolhida pelo usuario de acordo com os menu
int getOpcao() {
    int opcao;
    do {
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparbuffer();
    } while (opcao < 0 || opcao > 3);
    return opcao;
}

//funcao que registra o usuario
void registrarUsuario(int opcao) {

    char nome[100], senha[20];
    int counter = 0;
    
    do {

        printf("Digite seu nome de usuario: ");
        scanf("%[^\n]", nome);
        limparbuffer();

        do {
            if(counter > 0) printf("Senha invalida!\nDigite novamente!\n");
            else printf("Digite sua senha (6-20 caracteres): ");
            scanf("%[^\n]", senha);
            limparbuffer();
            counter++;
        } while(strlen(senha) < 6 || strlen(senha) > 20);

        counter = 0;

    } while(autenticarAssociado(nome, senha, 0) != 1);

    char plano = opcao == 1 ? 'A' : 'B';
    addAssociado(nome, senha, plano);
    salvarDados();
    printf("\nUsuario \033[032m%s\033[0m registrado com sucesso!\n", nome);
}

void carregarDados() {
    FILE *fp;
    fp = fopen("users/dados.txt", "r");
    if (fp == NULL) {
        return;
    }
    while(!feof(fp)) {
        Associado novoAssociado;
        fscanf(fp, "%[^,],%[^,],%c\n", novoAssociado.nome, novoAssociado.senha, &novoAssociado.plano);
        associados[numAssociados++] = novoAssociado;
    }
    fclose(fp);
}

//mensagem de boas vindas

void bemVindo(){
    printf("\n\nSeja Bem Vindo a [NOME DA BIBLIOTECA]!\n\n");
}

// Interface de usuário
void exibirMenu() {
    printf("Por Gentileza Cadastra-se No Sistema\n");
    printf("(Cadastrar como associado - assinatura mensal) Digite 1\n(Cadastrar conta basica - gratuito) Digite 2   \n");
    printf("\nDigite 3 se ja tiver cadastro; Digite 0 para sair\n");
}

//Apenas uma arte para exibir o nome do programa (pode ignorar essa função);
void libManager() {
    printf("\033[31m*\033[0m    ,--, \n");
    printf("\033[32m*\033[0m ,---.'|\033[33m                                   ____ \033[0m\n");
    printf("\033[34m*\033[0m |   | :\033[35m                                 ,'  , `. \033[0m\n");
    printf("\033[36m*\033[0m :   : |\033[37m      ,--,\033[31m      ,---,\033[32m         ,-+-,.' _ | \033[0m\n");
    printf("\033[33m*\033[0m |   ' :\033[34m    ,--.'|\033[35m    ,---.'|\033[36m      ,-+-. ;   , ||\033[0m\033[37m                     ,---,\033[31m                                         __  ,-. \033[0m\n");
    printf("\033[32m*\033[0m ;   ; '\033[33m    |  |,\033[34m     |   | :\033[35m     ,--.'|'   |  ;|\033[0m\033[36m                 ,-+-. /  |\033[37m                 ,----._,\033[31m.\033[32m            ,' ,'/ /|\033[0m\n");
    printf("\033[33m*\033[0m '   | |\033[31m__\033[32m  `--'_\033[0m\033[33m     :   : :\033[34m    |   |  ,', |  ':\033[35m    ,--.--.\033[0m\033[36m     ,--.'|'   |\033[37m    ,--.--.\033[31m     /   /  ' /\033[32m    ,---.\033[33m   '  | |' |\033[0m\n");
    printf("\033[34m*\033[0m |   | :\033[31m.'|\033[32m ,' ,'|\033[0m\033[33m    :     |,-. |   | /  | |  ||\033[34m   /       \\   \033[0m\033[35m  |   |  ,\"' |\033[36m   /       \\   \033[37m  |   :\033[31m     |\033[32m   /     \\\033[33m  |  |   \033[0m\n");
    printf("\033[35m*\033[0m '   :\033[31m    ;\033[32m '  | |\033[0m\033[33m    |   : '  |\033[34m '   | :  | :  |,\033[35m  .--.  .-. |\033[0m\033[36m  |   | /  | |\033[37m  .--.  .-. |\033[31m  |   | .\\  .\033[32m  /    /  |\033[33m '  :  /\033[0m \n");
    printf("\033[36m*\033[0m |   |\033[31m  ./\033[32m  |  | :\033[0m\033[33m    |   |  / : |   : |  ; |--'\033[34m    \\__\\/:\033[0m\033[35m . .\033[0m\033[36m  |   | |  | |\033[37m   \\__\\/:\033[31m . .\033[32m  .   ; ';  |\033[33m .    ' / |\033[0m\033[34m |  | \033[0m\n");
    printf("\033[37m*\033[0m ;   :\033[31m ;\033[32m    '  : |\033[33m__\033[34m  '   : |: | ;   . |  ; |--'\033[35m       ,\" .--.; |\033[0m\033[36m  |   | |  |/    ,\" .--.; |\033[37m  '   .\033[31m   . |\033[32m '   ;   /|\033[33m ;  : \033[0m\n");
    printf("\033[31m*\033[0m |   ,/\033[32m     |  | '.'| |   | '/ : |   : '  |/\033[33m       /  /  ,.  |\033[0m\033[34m  |   | |--'    /  /  ,.  |\033[35m   `---`-'|\033[0m\033[36m | '   |  / |\033[37m |  , ;\033[0m\n");
    printf("\033[32m*\033[0m '---'\033[33m      ;  :    ; |   :    |\033[34m ;   | |`-'       ;  :   .'   \\|   |/       ;  :   .'   \\\033[35m  .'__/\\_: |\033[36m |   :    |\033[0m\033[37m  ---'\033[0m\n");
    printf("\033[34m*\033[0m            |  ,   /  /\033[35m    \\  /\033[35m  |   ;/           |  ,     .-./ '---'        |  ,     .-./  |\033[0m   :    :  \\   \\  /\n");
    printf("\033[32m*\033[0m             ---`-'\033[32m   `-'----'   '---'\033[0m             `--`---'                   `--`---'       \\   \\  /    `----'\n");
    printf("_._._._._._._._._._._._._._._._._._._._._._._._._.._._._._._._._._._._._._._._._._._._._._._._._._._._._.._._._._._._._._.\n");
}

// limpa terminal
void limparTela() {
    system("cls"); // para Windows
    system("clear"); // para Linux ou macOS
    libManager();
}