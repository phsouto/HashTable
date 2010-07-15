/* 
 * File:   funcoes.h
 * Author: Pedro
 *
 * Created on 29 de Junho de 2010, 15:27
 */

#ifndef _FUNCOES_H
#define	_FUNCOES_H

#ifdef	__cplusplus
extern "C" {
#endif

#define N 127

    typedef struct {
        int Canal;
        char Nome[81];
        char Tipo[41];
        char Horario[6];
    } Programa;

    /* Variaveis Globais */
    unsigned long Hash[N];
    FILE *fp;

    unsigned long hsh(int c);
    void arqInicializa();
    void Inserir();
    void Alterar();
    void Imprimir();
    void Excluir();
    void Buscar();
    void Sobre();
    void arqFecha();


#ifdef	__cplusplus
}
#endif

#endif	/* _FUNCOES_H */

