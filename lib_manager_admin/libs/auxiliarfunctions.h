#ifndef AUXILIAR_FUNC_H
#define AUXILIAR_FUNC_H

#include <stdio.h>
#include <stdlib.h>

void substitui(char *vetor) {
    vetor[strcspn(vetor, "\n")] = '\0';
}

void salvarDados() {
    FILE *fp;
    fp = fopen("admins/dados.txt", "w");
    for(int i = 0; i < numAdmins; i++) {
        fprintf(fp, "%s,%s\n", admins[i].nome, admins[i].senha);
    }
    fclose(fp);
}

void carregarDados() {
    FILE *fp;
    fp = fopen("admins/dados.txt", "r");
    if (fp == NULL) {
        return;
    }
    while(!feof(fp)) {
        struct ADMIN novoAdmin;
        fscanf(fp, "%[^,],%[^\n]\n", novoAdmin.nome, novoAdmin.senha);
        admins[numAdmins++] = novoAdmin;
    }
    fclose(fp);
}

//mensagem de boas vindas

void bemVindo(){
    printf("\n\nSeja Bem Vindo a [NOME DA BIBLIOTECA]!\n\n");
}


// Interface de usuário
void exibirMenu() {
        printf("(Para Cadastrar Admin) Digite 1\n(Para Logar como admin) Digite 2\n");
        printf("Digite 0 para sair\n");
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
#endif