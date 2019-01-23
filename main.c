/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Vitor
 *
 * Created on 8 de Janeiro de 2019, 16:24
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct no_ {
    char nome[30];
    int prioridade;
} no;

typedef struct fila_ {
    int qtd;
    no elementos[MAX];
} fila;

/**
 * 
 * @return 0 caso tenha inserido, -1 caso contrÃ¡rio.
 */
int insereFila(fila * fp, int prio, char nome[30]) {
    if (fp->qtd == MAX)
        return -1;
    int atual, pai;
    no aux;
    //insere o elemento no final
    atual = fp->qtd;
    fp->elementos[atual].prioridade = prio;
    strncpy(fp->elementos[atual].nome, nome, 30);
    pai = (atual - 1) / 2; //calcula a posiÃ§Ã£o do pai do elemento
    while (fp->elementos[atual].prioridade > fp->elementos[pai].prioridade) {
        //copia valores do pai para aux
        strncpy(aux.nome, fp->elementos[pai].nome, 30);
        aux.prioridade = fp->elementos[pai].prioridade;

        //copia valores do atual para o pais
        strncpy(fp->elementos[pai].nome, fp->elementos[atual].nome, 30);
        fp->elementos[pai].prioridade = fp->elementos[atual].prioridade;

        //copia valores do aux para o atual
        strncpy(fp->elementos[atual].nome, aux.nome, 30);
        fp->elementos[atual].prioridade = aux.prioridade;

        atual = pai;
        pai = (atual - 1) / 2;
    }
    fp->qtd++;
    return 0;
}

/**
 * 
 * @param fp ponteiro para a fila de prioridades
 * @return NULL caso esteja vazia, ou o elemento desejadp, caso exista.
 */
no * removeFila(fila * fp) {
    if (fp->qtd == 0)
        return NULL;
    no * temp = malloc(sizeof(no));
    int atual = 0, esq, dir;
    temp->prioridade = fp->elementos[0].prioridade;
    strncpy(temp->nome, fp->elementos[0].nome, 30);
    //copiando valores do ultimo elemento para primeiro
    fp->elementos[0].prioridade = fp->elementos[fp->qtd - 1].prioridade;
    strncpy(fp->elementos[0].nome, fp->elementos[fp->qtd - 1].nome, 30);
    esq = atual * 2 + 1;
    if(esq >= fp->qtd)
        esq = fp->qtd - 1;
    dir = atual * 2 + 2;
    if(dir >= fp->qtd)
        dir = fp->qtd - 1;
    while ((fp->elementos[atual].prioridade < fp->elementos[esq].prioridade)
            || (fp->elementos[atual].prioridade < fp->elementos[dir].prioridade)) {
        if (fp->elementos[esq].prioridade > fp->elementos[dir].prioridade) {
            no aux;
            //copiando valores de atual para aux
            strncpy(aux.nome, fp->elementos[atual].nome, 30);
            aux.prioridade = fp->elementos[atual].prioridade;

            //copiando valores de esq para atual
            strncpy(fp->elementos[atual].nome, fp->elementos[esq].nome, 30);
            fp->elementos[atual].prioridade = fp->elementos[esq].prioridade;

            //copiando valores de aux para esq
            strncpy(fp->elementos[esq].nome, aux.nome, 30);
            fp->elementos[esq].prioridade = aux.prioridade;

            atual = esq;

        } else {
            no aux;
            //copiando valores de atual para aux
            strncpy(aux.nome, fp->elementos[atual].nome, 30);
            aux.prioridade = fp->elementos[atual].prioridade;

            //copiando valores de dir para atual
            strncpy(fp->elementos[atual].nome, fp->elementos[dir].nome, 30);
            fp->elementos[atual].prioridade = fp->elementos[dir].prioridade;

            //copiando valores de aux para dir
            strncpy(fp->elementos[dir].nome, aux.nome, 30);
            fp->elementos[dir].prioridade = aux.prioridade;

            atual = dir;
        }
        esq = atual * 2 + 1;
        if(esq >= fp->qtd)
            break;
        dir = atual * 2 + 2;
        if(dir >= fp->qtd)
            dir = esq;
    }
    fp->qtd--;
    return temp;
}

/**
 * 
 * @param fp ponteiro para a fila de prioridades
 */
void escreve(fila fp) {
    int i;
    for (i = 0; i < fp.qtd; i++)
        printf("Nome: %s\tPrioridade: %d\n", fp.elementos[i].nome, fp.elementos[i].prioridade);
}

/*
 * 
 */
int main() {
    fila fp;
    int prioridade, opcao, flag;
    char nome[30];
    fp.qtd = 0;

    do {
        printf("---------------\n");
        printf("| [1] Inserir |\n");
        printf("| [2] Remover |\n");
        printf("| [3] Exibir  |\n");
        printf("| [4] Sair    |\n");
        printf("---------------\n");
        scanf(" %d", &opcao);
        switch (opcao) {
                no * n;
            case 1:
                printf("Digite o nome:\n");
                scanf(" %s", nome);
                printf("Digite a prioridade:\n");
                scanf(" %d", &prioridade);
                flag = insereFila(&fp, prioridade, nome);
                if (flag == 0)
                    printf("Valor inserido com sucesso\n");
                else
                    printf("Valor nÃ£o foi inserido, fila cheia\n");
                break;
            case 2:
                n = removeFila(&fp);
                if (!n)
                    printf("Nao tem nada\n");
                else
                    printf("%s %d\n", n->nome, n->prioridade);
                free(n);
                break;
            case 3:
                escreve(fp);
                break;
            case 4:printf("Saindo...");
                break;
            default: break;
        }
    } while (opcao != 4);

    return (EXIT_SUCCESS);
}
