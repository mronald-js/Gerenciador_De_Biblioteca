#include <stdio.h>
#include <stdlib.h>

void substitui(char *vetor){
    vetor[strcspn(vetor, "\n")] = '\0'; //troca o último \n por um caracter nulo, dessa forma evitando que o \n fique no buffer
}

int getTarefa() {
    int tarefa;
    do {
        scanf("%d", &tarefa);
    } while (tarefa < 0 || tarefa > 3);
    return tarefa;
}

void menuPrincipal() {
    printf("Menu Principal:\n");
    printf("1 - Registrar\n");
    printf("2 - Login\n");
    printf("0 - Sair\n");
}


void menuLogado(char *nome) {
    printf("\nAtualmente logado como \033[32m%s\033[0m", nome);
    printf("\nOpcoes:\n");
    printf("1 - Cadastrar livro\n");
    printf("2 - Verificar Estoque\n");
    printf("3 - Limpar terminal\n");
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

void limparbuffer(){
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
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

void registrarAdm(int opcao) {

    char nome[100], senha[20];
    int usuarioJaExistente, counter = 0;
    
    do {
        usuarioJaExistente = 0;
        printf("ADM: ");
        fgets(nome, 100, stdin);
        substitui(nome);
        
        do {
            if(counter > 0)
                printf("Senha invalida!\nDigite novamente!\n");
            else
                printf("Digite sua senha (6-20 caracteres): ");
            fgets(senha, 20, stdin);
            substitui(senha);
            counter++;
        } while(strlen(senha) < 6 || strlen(senha) > 20);
        counter = 0;

    } while(autenticarAdmin(nome, senha, 0) != 1);

    addAdm(nome, senha);
    salvarDados();
    printf("\nADMIN \033[032m%s\033[0m registrado com sucesso!\n", nome);
}

void carregarDados() {
    FILE *fp;
    fp = fopen("admins/dados.txt", "r");
    if (fp == NULL) {
        return;
    }
    while(!feof(fp)) {
        Administrador novoADM;
        fscanf(fp, "%[^,],%^[\n]", novoADM.nome, novoADM.senha);
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