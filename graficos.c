#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include "graficos.h"
#include "funcoes.h"

void Moldura(int a, int b, int c, int d, int color) {
    int x;
    textcolor(color);
    gotoxy(a, b);
    printf("%c", 218);
    gotoxy(c, d);
    printf("%c", 217);
    gotoxy(c, b);
    printf("%c", 191);
    gotoxy(a, d);
    printf("%c", 192);
    for (x = b + 1; x < d; x++) {
        gotoxy(a, x);
        printf("%c", 179);
        gotoxy(c, x);
        printf("%c", 179);
    }
    for (x = a + 1; x < c; x++) {
        gotoxy(x, b);
        printf("%c", 196);
        gotoxy(x, d);
        printf("%c", 196);
    }
}

void Menu() {
    int i;
    int opcao = 0;
    char ch;
    int colunas[7] = {8, 18, 28, 40, 50, 58, 66};
    char nomes[7][20];
    char mensagens[7][60];

    arqInicializa();

    strcpy(mensagens[0], "Inserir um novo programa de TV");
    strcpy(mensagens[1], "Alterar um programa de TV");
    strcpy(mensagens[2], "Pesquisar um programa de TV");
    strcpy(mensagens[3], "Excluir um programa de TV");
    strcpy(mensagens[4], "Listar os Programas de TV");
    strcpy(mensagens[5], "Sobre o programa");
    strcpy(mensagens[6], "Fechar o programa ");
    strcpy(nomes[0], "INSERIR");
    strcpy(nomes[1], "ALTERAR");
    strcpy(nomes[2], "PESQUISAR");
    strcpy(nomes[3], "EXCLUIR");
    strcpy(nomes[4], "LISTA");
    strcpy(nomes[5], "SOBRE");
    strcpy(nomes[6], "SAIR");

    textbackground(BLACK);
    clrscr();
    if (opcao == 0) {
        textcolor(WHITE);
        gotoxy(23, 23);
        printf("%s", mensagens[opcao]);
    }

    while (1) {
        //Moldura do titulo
        textcolor(WHITE);
        gotoxy(29, 3);
        printf("PROGRAMACAO DA TV");
        Moldura(7, 1, 70, 5, GREEN);
        //Moldura da explicacao
        Moldura(7, 21, 70, 25, GREEN);
        //Moldura da selecao
        Moldura(7, 5, 70, 21, GREEN);
        Moldura(7, 5, 70, 7, GREEN);
        gotoxy(53, 9);
        textcolor(YELLOW);
        printf("      .___.");
        gotoxy(53, 10);
        printf("     /     \\");
        gotoxy(53, 11);
        printf("    | O _ O |");
        gotoxy(53, 12);
        printf("    /  \\_/  \\ ");
        gotoxy(53, 13);
        printf("  .' /     \\ `.");
        gotoxy(53, 14);
        printf(" / _|       |_ \\");
        gotoxy(53, 15);
        printf("(_/ |       | \\_)");
        gotoxy(53, 16);
        printf("    \\       /");
        gotoxy(53, 17);
        printf("   __\\_>-<_/__");
        gotoxy(53, 18);
        printf("   ~;/     \\;~");
        gotoxy(8, 11);
        printf(" _____     _            _                       ");
        gotoxy(8, 12);
        printf("/__   \\___| | _____   _(_)___  __ _  ___       ");
        gotoxy(8, 13);
        printf("  / /\\/ _ \\ |/ _ \\ \\ / / / __|/ _` |/ _ \\  ");
        gotoxy(8, 14);
        printf(" / / |  __/ |  __/\\ V /| \\__ \\ (_| | (_) |   ");
        gotoxy(8, 15);
        printf(" \\/   \\___|_|\\___| \\_/ |_|___/\\__,_|\\___/ ");
        for (i = 0; i < 7; i++) {
            textcolor(WHITE);
            textbackground(BLACK);
            gotoxy(colunas[i], 6);
            printf("%s", nomes[i]);
        }

        textcolor(YELLOW);
        textbackground(BLACK);
        gotoxy(colunas[opcao], 6);
        printf("%s", nomes[opcao]);
        ch = getch();
        textcolor(WHITE);
        textbackground(BLACK);
        gotoxy(colunas[opcao], 6);
        printf("%s", nomes[opcao]);

        if (ch == 77) opcao++;
        if (ch == 75) opcao--;
        if (opcao > 6) opcao = 0;
        if (opcao < 0) opcao = 6;

        if (opcao == 0) {
            textcolor(WHITE);
            gotoxy(23, 23);
            printf("%s", mensagens[opcao]);
        }
        if (opcao == 1) {
            textcolor(BLACK);
            gotoxy(23, 23);
            printf("%s", mensagens[0]);
            textcolor(WHITE);
            gotoxy(23, 23);
            printf("%s", mensagens[opcao]);
        }
        if (opcao == 2) {
            textcolor(BLACK);
            gotoxy(23, 23);
            printf("%s", mensagens[0]);
            textcolor(WHITE);
            gotoxy(23, 23);
            printf("%s", mensagens[opcao]);
        }
        if (opcao == 3) {
            textcolor(BLACK);
            gotoxy(23, 23);
            printf("%s", mensagens[0]);
            textcolor(WHITE);
            gotoxy(23, 23);
            printf("%s", mensagens[opcao]);

        }
        if (opcao == 4) {
            textcolor(BLACK);
            gotoxy(23, 23);
            printf("%s", mensagens[0]);
            textcolor(WHITE);
            gotoxy(23, 23);
            printf("%s", mensagens[opcao]);
        }
        if (opcao == 5) {
            textcolor(BLACK);
            gotoxy(23, 23);
            printf("%s", mensagens[0]);
            textcolor(WHITE);
            gotoxy(23, 23);
            printf("%s", mensagens[opcao]);
        }
        if (opcao == 6) {
            textcolor(BLACK);
            gotoxy(23, 23);
            printf("%s", mensagens[0]);
            textcolor(WHITE);
            gotoxy(23, 23);
            printf("%s", mensagens[opcao]);
        }

        if (ch == 13) {
            // INSERIR
            if (opcao == 0) {
                Inserir();
                clrscr();
            }
            // ALTERAR
            if (opcao == 1){
                Alterar();
                clrscr();
            }
            // PESQUISAR
            if (opcao == 2){
                Buscar();
                clrscr();
            }
            // EXCLUIR
            if (opcao == 3){
                Excluir();
                clrscr();
            }
            // LISTAR
            if (opcao == 4){
                Imprimir();
                system("Pause > null");
                clrscr();
            }
            // SOBRE
            if (opcao == 5) {
                Sobre();
                clrscr();
            }
            // SAIR
            if (opcao == 6) {
                arqFecha();
                break;
            }
        }
    }
    clrscr();
}