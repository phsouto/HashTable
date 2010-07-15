#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "funcoes.h"
#include "graficos.h"

// WARNING!!!!! -3 == NULL !!!!!!!!!!!!!!!!!!!!

unsigned long hsh(int c) {
    unsigned long pos = (c % N) * sizeof (Programa);
    return (pos);
}

void arqInicializa() {
    if ((fp = fopen("Arquivo.bin", "rb+")) == NULL) {
        if ((fp = fopen("Arquivo.bin", "wb+")) == NULL) {
            perror("ERRO");
            exit(1);
        }
        int i;
        for (i = 0; i < N; i++) {
            Programa foo;
            foo.Canal = -3;
            strcpy(foo.Horario, "-3");
            strcpy(foo.Nome, "-3");
            strcpy(foo.Tipo, "-3");
            fseek(fp, i * sizeof (Programa), SEEK_SET);
            fwrite(&foo, 1, sizeof (Programa), fp);
        }
    }
}

void arqFecha() {
    fclose(fp);
}

void Inserir() {
    clrscr();
    //Moldura do titulo
    textcolor(WHITE);
    gotoxy(29, 3);
    printf("PROGRAMACAO DA TV");
    Moldura(7, 1, 70, 5, GREEN);
    //Moldura da explicacao
    Moldura(7, 21, 70, 25, GREEN);
    //Moldura da selecao
    Moldura(7, 5, 70, 21, GREEN);

    Programa foo, sao; // .......sao!
    unsigned long pos;
    foo.Canal = -3;
    while (foo.Canal != -1) {
        textcolor(YELLOW);
        gotoxy(9, 7);
        printf("Canal: ");
        gotoxy(25, 23);
        printf("Digite -1 para sair");
        gotoxy(9, 9);
        printf("Nome do programa: ");
        gotoxy(9, 11);
        printf("Tipo do programa: ");
        gotoxy(9, 13);
        printf("Horario do programa: ");
        gotoxy(16, 7);
        fflush(stdin);
        scanf("%d", &foo.Canal);
        textcolor(BLACK);
        gotoxy(25, 23);
        printf("XXXXXXXXXXXXXXXXXXXXX");
        textcolor(YELLOW);
        if (foo.Canal == -1) break;
        gotoxy(27, 9);
        fflush(stdin);
        scanf("%80[^\n]", foo.Nome);
        gotoxy(27, 11);
        fflush(stdin);
        scanf("%40[^\n]", foo.Tipo);
        fflush(stdin);
        gotoxy(25, 23);
        printf("Horario dado em hh:mm");
        gotoxy(30, 13);
        scanf("%6[^\n]", foo.Horario);
        textcolor(BLACK);
        gotoxy(25, 23);
        printf("XXXXXXXXXXXXXXXXXXXXX");
        textcolor(YELLOW);
        pos = hsh(foo.Canal);
        fseek(fp, pos, SEEK_SET);
        fread(&sao, sizeof (Programa), 1, fp);

        /* Verifica se a posicao esta ocupada */
        while (sao.Canal != -3) {
            pos += sizeof (Programa);
            fseek(fp, pos, SEEK_SET);
            fread(&sao, sizeof (Programa), 1, fp);
        }
        if (sao.Canal == -3) {
            fseek(fp, pos, SEEK_SET);
            fwrite(&foo, sizeof (Programa), 1, fp);
        }
        gotoxy(16, 7);
        textcolor(BLACK);
        printf("XXXXXXXXXXXXXXXXXXXXX");
        gotoxy(27, 9);
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
        gotoxy(27, 11);
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
        gotoxy(30, 13);
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    }
}

void Alterar() {
    clrscr();
    //Moldura do titulo
    textcolor(WHITE);
    gotoxy(29, 3);
    printf("PROGRAMACAO DA TV");
    Moldura(7, 1, 70, 5, GREEN);
    //Moldura da explicacao
    Moldura(7, 21, 70, 25, GREEN);
    //Moldura da selecao
    Moldura(7, 5, 70, 21, GREEN);
    Programa foo, sao; // .......sao!
    int Canal, opt;
    gotoxy(9, 7);
    textcolor(YELLOW);
    printf("Canal a ser alterado: ");
    gotoxy(25, 23);
    printf("Digite -1 para sair");
    gotoxy(31, 7);
    scanf("%d", &Canal);
    if (Canal == -1)return;
    unsigned long pos = hsh(Canal);
    fseek(fp, pos, SEEK_SET);
    fread(&foo, sizeof (Programa), 1, fp);
    while (!feof(fp)) {
        if (foo.Canal != Canal) {
            pos += sizeof (Programa);
            fseek(fp, pos, SEEK_SET);
            fread(&foo, sizeof (Programa), 1, fp);
        }
        if (foo.Canal == Canal) {
            gotoxy(25, 23);
            textcolor(BLACK);
            printf("XXXXXXXXXXXXXXXXXXXXX");
            textcolor(YELLOW);
            gotoxy(9, 7);
            printf("Dados do Canal Selecionado");
            gotoxy(9, 9);
            printf("1: Canal: %d", foo.Canal);
            gotoxy(9, 10);
            printf("2: Nome do Programa: %s", foo.Nome);
            gotoxy(9, 11);
            printf("3: Horario: %s", foo.Horario);
            gotoxy(9, 12);
            printf("4: Tipo: %s", foo.Tipo);
            gotoxy(9, 13);
            printf("Opcao: ");
            fflush(stdin);
            scanf("%d", &opt);

            if (opt == 1) {
                /* Apagando posicao antiga */
                sao.Canal = -3;
                strcpy(sao.Horario, "-3");
                strcpy(sao.Nome, "-3");
                strcpy(sao.Tipo, "-3");
                fseek(fp, pos, SEEK_SET);
                fwrite(&sao, sizeof (Programa), 1, fp);
                gotoxy(9, 15);
                printf("Novo Canal: ");
                gotoxy(21, 15);
                fflush(stdin);
                scanf("%d", &Canal);
                pos = hsh(Canal);
                fseek(fp, pos, SEEK_SET);
                fread(&sao, sizeof (Programa), 1, fp);
                /* Verifica se a posicao esta ocupada */
                while (!feof(fp)) {
                    if (sao.Canal != -3) {
                        pos += sizeof (Programa);
                        fseek(fp, pos, SEEK_SET);
                        fread(&sao, sizeof (Programa), 1, fp);
                    }
                    if (sao.Canal == -3) {
                        foo.Canal = Canal;
                        fseek(fp, pos, SEEK_SET);
                        fwrite(&foo, sizeof (Programa), 1, fp);
                        textcolor(YELLOW);
                        gotoxy(25, 23);
                        printf("Canal Alterado com sucesso!");
                        system("PAUSE>Null");
                        return;
                    }
                }
            }
            if (opt == 2 || opt == 3 || opt == 4) {
                if (opt == 2) {
                    gotoxy(9, 15);
                    printf("Novo Nome: ");
                    gotoxy(20, 15);
                    fflush(stdin);
                    scanf("%80[^\n]", foo.Nome);
                }
                if (opt == 3) {
                    gotoxy(9, 15);
                    printf("Novo Horario: ");
                    gotoxy(23, 15);
                    fflush(stdin);
                    scanf("%6[^\n]", foo.Horario);
                }
                if (opt == 4) {
                    gotoxy(9, 15);
                    printf("Novo Tipo: ");
                    gotoxy(21, 15);
                    fflush(stdin);
                    scanf("%40[^\n]", foo.Tipo);
                }
                fseek(fp, pos, SEEK_SET);
                fwrite(&foo, sizeof (Programa), 1, fp);
                textcolor(YELLOW);
                gotoxy(25, 23);
                printf("Canal Alterado com sucesso!");
                system("PAUSE>Null");
                return;
            }
            if (opt != 1 && opt != 2 && opt != 3 && opt != 4) {
                gotoxy(25, 23);
                printf("Opcao Invalida!");
                system("PAUSE>Null");
                return;
            }
        }
    }
    if (foo.Canal != Canal) {
        gotoxy(25, 23);
        textcolor(BLACK);
        printf("XXXXXXXXXXXXXXXXXXXXX");
        textcolor(YELLOW);
        gotoxy(25, 23);
        printf("Canal Inexistente!");
    }
    system("PAUSE>Null");
    return;
}

void Imprimir() {
    unsigned long pos = 0;
    Programa foo;
    int i, opt;
    opt = 0;
    i = 0;
    while (i <= N) {
        i++;
        fseek(fp, pos, SEEK_SET);
        fread(&foo, sizeof (Programa), 1, fp);
        if (foo.Canal != -3) {
            clrscr();
            //Moldura do titulo
            textcolor(WHITE);
            gotoxy(29, 3);
            printf("PROGRAMACAO DA TV");
            Moldura(7, 1, 70, 5, GREEN);
            //Moldura da explicacao
            Moldura(7, 21, 70, 25, GREEN);
            //Moldura da selecao
            Moldura(7, 5, 70, 21, GREEN);
            textcolor(YELLOW);
            gotoxy(9, 7);
            printf("Dados do Canal");
            gotoxy(9, 10);
            printf("1: Canal: %d", foo.Canal);
            gotoxy(9, 11);
            printf("2: Nome do Programa: %s", foo.Nome);
            gotoxy(9, 12);
            printf("3: Horario: %s", foo.Horario);
            gotoxy(9, 13);
            printf("4: Tipo: %s", foo.Tipo);
            gotoxy(25, 23);
            printf("Canais Encontrado");
            system("Pause > null");
            opt = 1;
        }
        pos += sizeof (Programa);
    }
    if (opt != 1) {
        clrscr();
        //Moldura do titulo
        textcolor(WHITE);
        gotoxy(29, 3);
        printf("PROGRAMACAO DA TV");
        Moldura(7, 1, 70, 5, GREEN);
        //Moldura da explicacao
        Moldura(7, 21, 70, 25, GREEN);
        //Moldura da selecao
        Moldura(7, 5, 70, 21, GREEN);
        gotoxy(25, 23);
        textcolor(YELLOW);
        printf("Nenhum canal registrado!");
        system("Pause > null");
        return;
    }
    return;
}

void Excluir() {
    clrscr();
    //Moldura do titulo
    textcolor(WHITE);
    gotoxy(29, 3);
    printf("PROGRAMACAO DA TV");
    Moldura(7, 1, 70, 5, GREEN);
    //Moldura da explicacao
    Moldura(7, 21, 70, 25, GREEN);
    //Moldura da selecao
    Moldura(7, 5, 70, 21, GREEN);
    Programa foo;
    int bar;
    gotoxy(9, 7);
    textcolor(YELLOW);
    printf("Canal a ser excluido: ");
    gotoxy(25, 23);
    printf("CUIDADO!!");
    gotoxy(35, 23);
    printf("Digite -1 para sair");
    gotoxy(31, 7);
    fflush(stdin);
    scanf("%d", &bar);

    if (bar == -1) return;

    unsigned long pos = hsh(bar);
    fseek(fp, pos, SEEK_SET);
    fread(&foo, sizeof (Programa), 1, fp);

    while (!feof(fp)) {
        if (foo.Canal != bar) {
            pos += sizeof (Programa);
            fseek(fp, pos, SEEK_SET);
            fread(&foo, sizeof (Programa), 1, fp);
        }
        if (foo.Canal == bar) {
            foo.Canal = -3;
            strcpy(foo.Horario, "-3");
            strcpy(foo.Nome, "-3");
            strcpy(foo.Tipo, "-3");
            fseek(fp, pos, SEEK_SET);
            fwrite(&foo, sizeof (Programa), 1, fp);
            gotoxy(25, 23);
            textcolor(BLACK);
            printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
            textcolor(YELLOW);
            gotoxy(25, 23);
            printf("Canal Excluido com sucesso!");
            system("Pause > null");
            return;
        }
    }
    if (foo.Canal != bar) {
        gotoxy(25, 23);
        textcolor(BLACK);
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
        textcolor(YELLOW);
        gotoxy(25, 23);
        printf("Canal Inexistente!");
    }
    system("PAUSE>Null");
    return;
}

void Buscar() {
    clrscr();
    //Moldura do titulo
    textcolor(WHITE);
    gotoxy(29, 3);
    printf("PROGRAMACAO DA TV");
    Moldura(7, 1, 70, 5, GREEN);
    //Moldura da explicacao
    Moldura(7, 21, 70, 25, GREEN);
    //Moldura da selecao
    Moldura(7, 5, 70, 21, GREEN);
    Programa foo;
    int bar;
    gotoxy(9, 7);
    textcolor(YELLOW);
    printf("Canal a ser pesquisado: ");
    gotoxy(25, 23);
    printf("Digite -1 para sair");
    gotoxy(33, 7);
    fflush(stdin);
    scanf("%d", &bar);
    if (bar == -1) return;
    unsigned long pos = hsh(bar);
    fseek(fp, pos, SEEK_SET);
    fread(&foo, sizeof (Programa), 1, fp);
    while (!feof(fp)) {
        if (foo.Canal != bar) {
            pos += sizeof (Programa);
            fseek(fp, pos, SEEK_SET);
            fread(&foo, sizeof (Programa), 1, fp);
        }
        if (foo.Canal == bar) {
            gotoxy(25, 23);
            textcolor(BLACK);
            printf("XXXXXXXXXXXXXXXXXXXXX");
            gotoxy(33, 7);
            printf("XXXXXXXXX");
            textcolor(YELLOW);
            gotoxy(9, 7);
            printf("Dados do Canal Pesquisado");
            gotoxy(9, 9);
            printf("1: Canal: %d", foo.Canal);
            gotoxy(9, 10);
            printf("2: Nome do Programa: %s", foo.Nome);
            gotoxy(9, 11);
            printf("3: Horario: %s", foo.Horario);
            gotoxy(9, 12);
            printf("4: Tipo: %s", foo.Tipo);
            gotoxy(25, 23);
            printf("Canal Encontrado!");
            system("Pause > null");
            return;
        }
    }
    if (foo.Canal != bar) {
        gotoxy(25, 23);
        textcolor(BLACK);
        printf("XXXXXXXXXXXXXXXXXXXXX");
        textcolor(YELLOW);
        gotoxy(25, 23);
        printf("Canal Inexistente!");
    }
    system("PAUSE>Null");
    return;
}

void Sobre() {
    clrscr();
    Moldura(20, 3, 55, 18, 3);
    gotoxy(25, 7);
    textcolor(LIGHTGRAY);
    printf("Este Projeto foi feito por:");
    gotoxy(28, 10);
    textcolor(GREEN);
    printf("George Rocha Teofilo");
    gotoxy(25, 12);
    textcolor(YELLOW);
    printf("Daniel Felipe P. D. Menezes");
    gotoxy(26, 14);
    textcolor(RED);
    printf("Pedro Henrique G. Souto");
    system("Pause > null");
}