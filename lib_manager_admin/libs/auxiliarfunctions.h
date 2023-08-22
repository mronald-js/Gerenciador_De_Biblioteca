#include <stdio.h>
#include <stdlib.h>

void substitui(char *vetor){
    vetor[strcspn(vetor, "\n")] = '\0'; //troca o último \n por um caracter nulo, dessa forma evitando que o \n fique no buffer
}

int getTarefa() {
    int tarefa;
    do {
        scanf("%d", &tarefa);
        limparbuffer();
    } while (tarefa < 0 || tarefa > 4);
    return tarefa;
}

void menuPrincipal() {
    printf("Menu Principal:\n");
    printf("1 - Registrar\n");
    printf("2 - Login\n");
    printf("0 - Sair\n");
}


void menuLogado(char *nome) {
    printf("\nAtualmente logado como \033[32m%s\033[0m\n", nome);
    printf("\nOpcoes:\n");
    printf("1 - Cadastrar Livros\n");
    printf("2 - Verificar Livros Cadastrados\n");
    printf("3 - Checar Emprestimos\n");
    printf("4 - Limpar terminal\n");
    printf("0 - Logout\n");
}

void salvarDados() {
    FILE *fp;
    fp = fopen("admins/dados.txt", "w");
    for(int i = 0; i < numAdmins; i++) {
        fprintf(fp, "%s,%s\n", admins[i].nome, admins[i].senha);
    }
    fclose(fp);
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

int adminExistente(char *nome) {
    Administrador* adm = buscaAdmPorNome(nome);
    if (adm != NULL) {
        free(adm);
        return 1; // Admin exists
    }
    return 0; // Admin does not exist
}

void registrarAdm(int opcao) {

    char nome[100], senha[50];
    int counter = 0;
    
    do {

        printf("ADM: ");
        scanf("%[^\n]", nome);
        limparbuffer();

        do {
            if(counter > 0) printf("Senha invalida!\nDigite novamente!\n");
            else printf("Digite sua senha (6-20 caracteres): ");
            scanf("%[^\n]", senha);
            limparbuffer();
            counter++;
        } while(strlen(senha) < 6 || strlen(senha) > 50);

        counter = 0;

    } while(autenticarAdmin(nome, senha, 0) != 1);

    addAdm(nome, senha);
    salvarDados();
    printf("\nAdm %s registrado com sucesso!\n\n", nome);
}


void carregarDados() {
    FILE *fp;
    fp = fopen("admins/dados.txt", "r");
    if (fp == NULL) {
        return;
    }
    while(!feof(fp)) {
        Administrador novoADM;
        fscanf(fp, "%[^,],%[^\n]", novoADM.nome, novoADM.senha);
        admins[numAdmins++] = novoADM;
    }
    fclose(fp);
}

//mensagem de boas vindas

void bemVindo(){
    printf("\n\nSeja Bem Vindo a [NOME DA BIBLIOTECA]!\n\n");
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