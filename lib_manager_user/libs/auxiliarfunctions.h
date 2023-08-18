#ifndef AUXILIAR_FUNC_H
#define AUXILIAR_FUNC_H

#include <stdio.h>
#include <stdlib.h>

void substitui(char *vetor){
    vetor[strcspn(vetor, "\n")] = '\0'; //troca o último \n por um caracter nulo, dessa forma evitando que o \n fique no buffer
}

void salvarDados() {
    FILE *fp;
    fp = fopen("users/dados.txt", "w");
    for(int i = 0; i < numAssociados; i++) {
        fprintf(fp, "%s,%s,%c\n", associados[i].nome, associados[i].senha, associados[i].plano);
    }
    fclose(fp);
}

void carregarDados() {
    FILE *fp;
    fp = fopen("users/dados.txt", "r");
    if (fp == NULL) {
        return;
    }
    while(!feof(fp)) {
        struct Associado novoAssociado;
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
        printf("Por Gentileza Cadastra-se No Sistema\n\n");
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
#endif // ASSOCIADO_H