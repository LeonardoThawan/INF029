#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

typedef struct vetorPrincipal {
    int *aux;
    int tamanho;
    int cont;
} vetorPrincipal;

vetorPrincipal vp[TAM];

void imprimir_est(int posicao) {
    int i;
    for (i = 0; i < vp[posicao].cont; i++) {
        printf("%dº Valor: %d\n", i + 1, vp[posicao].aux[i]);
    }
}

int validarPosicao(int posicao) {
    if (posicao < 0 || posicao >= TAM) {
        return POSICAO_INVALIDA;
    }
    return SUCESSO;
}

int verificarEstrutura(int posicao) {
    if (vp[posicao].aux == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    return SUCESSO;
}

int criarEstruturaAuxiliar(int posicao, int tamanho) {
    int retorno = 0;
    posicao--;

    retorno = validarPosicao(posicao);
    if (retorno != SUCESSO) return retorno;

    if (vp[posicao].aux != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }
    if (tamanho < 1) {
        return TAMANHO_INVALIDO;
    }

    vp[posicao].aux = malloc(tamanho * sizeof(int));
    if (!vp[posicao].aux) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    vp[posicao].tamanho = tamanho;
    vp[posicao].cont = 0;
    return SUCESSO;
}

int inserirNumeroEmEstrutura(int posicao, int valor) {
    int retorno = 0;
    posicao--;

    retorno = validarPosicao(posicao);
    if (retorno != SUCESSO) return retorno;

    retorno = verificarEstrutura(posicao);
    if (retorno != SUCESSO) return retorno;

    if (vp[posicao].cont < vp[posicao].tamanho) {
        vp[posicao].aux[vp[posicao].cont++] = valor;
        return SUCESSO;
    }
    return SEM_ESPACO;
}

int excluirNumeroDoFinaldaEstrutura(int posicao) {
    int retorno = 0;
    posicao--;

    retorno = validarPosicao(posicao);
    if (retorno != SUCESSO) return retorno;

    retorno = verificarEstrutura(posicao);
    if (retorno != SUCESSO) return retorno;

    if (vp[posicao].cont > 0) {
        vp[posicao].cont--;
        return SUCESSO;
    }
    return ESTRUTURA_AUXILIAR_VAZIA;
}

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    int i;
    int retorno = 0;
    posicao--;

    retorno = validarPosicao(posicao);
    if (retorno != SUCESSO) return retorno;

    retorno = verificarEstrutura(posicao);
    if (retorno != SUCESSO) return retorno;

    if (vp[posicao].cont == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    for (i = 0; i < vp[posicao].cont; i++) {
        if (vp[posicao].aux[i] == valor) {
            for (int j = i; j < vp[posicao].cont - 1; j++) {
                vp[posicao].aux[j] = vp[posicao].aux[j + 1];
            }
            vp[posicao].cont--;
            return SUCESSO;
        }
    }

    return NUMERO_INEXISTENTE;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    int retorno = 0;
    posicao--;

    retorno = validarPosicao(posicao);
    if (retorno != SUCESSO) return retorno;

    retorno = verificarEstrutura(posicao);
    if (retorno != SUCESSO) return retorno;

    for (int i = 0; i < vp[posicao].cont; i++) {
        vetorAux[i] = vp[posicao].aux[i];
    }
    return SUCESSO;
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    int retorno = 0;
    posicao--;

    retorno = validarPosicao(posicao);
    if (retorno != SUCESSO) return retorno;

    retorno = verificarEstrutura(posicao);
    if (retorno != SUCESSO) return retorno;

    for (int i = 0; i < vp[posicao].cont; i++) {
        vetorAux[i] = vp[posicao].aux[i];
    }

    // Ordenação
    for (int i = 0; i < vp[posicao].cont - 1; i++) {
        for (int j = i + 1; j < vp[posicao].cont; j++) {
            if (vetorAux[i] > vetorAux[j]) {
                int temp = vetorAux[i];
                vetorAux[i] = vetorAux[j];
                vetorAux[j] = temp;
            }
        }
    }

    return SUCESSO;
}

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int T = 0;
    int retorno = 0;
    for (int i = 0; i < TAM; i++) {
        if (vp[i].cont > 0) {
            for (int j = 0; j < vp[i].cont; j++, T++) {
                vetorAux[T] = vp[i].aux[j];
            }
        }
    }
    return (T > 0) ? SUCESSO : TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
}

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int retorno = 0;
    int T = 0;
    for (int i = 0; i < TAM; i++) {
        if (vp[i].cont > 0) {
            for (int j = 0; j < vp[i].cont; j++, T++) {
                vetorAux[T] = vp[i].aux[j];
            }
        }
    }

    // Ordenação
    for (int i = 0; i < T - 1; i++) {
        for (int j = i + 1; j < T; j++) {
            if (vetorAux[i] > vetorAux[j]) {
                int temp = vetorAux[i];
                vetorAux[i] = vetorAux[j];
                vetorAux[j] = temp;
            }
        }
    }

    return (T > 0) ? SUCESSO : TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
}

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    int retorno = 0;
    posicao--;

    retorno = validarPosicao(posicao);
    if (retorno != SUCESSO) return retorno;

    retorno = verificarEstrutura(posicao);
    if (retorno != SUCESSO) return retorno;

    if (novoTamanho <= 0) {
        return NOVO_TAMANHO_INVALIDO;
    }

    int *novo_pont = realloc(vp[posicao].aux, (vp[posicao].tamanho + novoTamanho) * sizeof(int));
    if (!novo_pont) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    vp[posicao].aux = novo_pont;
    vp[posicao].tamanho += novoTamanho;

    if (vp[posicao].cont > vp[posicao].tamanho) {
        vp[posicao].cont = vp[posicao].tamanho;
    }

    return SUCESSO;
}

int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    int retorno = 0;
    posicao--;

    retorno = validarPosicao(posicao);
    if (retorno != SUCESSO) return retorno;

    retorno = verificarEstrutura(posicao);
    if (retorno != SUCESSO) return retorno;

    return (vp[posicao].cont > 0) ? vp[posicao].cont : ESTRUTURA_AUXILIAR_VAZIA;
}

No *create_node(int key) {
    No *node = malloc(sizeof(No));
    node->conteudo = key;
    node->prox = NULL;
    return node;
}

No *montarListaEncadeadaComCabecote() {
    No *head = NULL, *prev = NULL;
    for (int i = 0; i < TAM; i++) {
        if (vp[i].cont > 0) {
            for (int j = 0; j < vp[i].cont; j++) {
                No *node = create_node(vp[i].aux[j]);
                if (head == NULL) {
                    head = node;
                } else {
                    prev->prox = node;
                }
                prev = node;
            }
        }
    }
    return head;
}

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    int j = 0;
    for (No *i = inicio; i != NULL; i = i->prox) {
        vetorAux[j++] = i->conteudo;
    }
}

void destruirListaEncadeadaComCabecote(No **inicio) {
    No *j = *inicio;
    *inicio = NULL;
    while (j != NULL) {
        No *aux = j;
        j = j->prox;
        free(aux);
    }
}

void inicializar() {
    for (int i = 0; i < TAM; i++) {
        vp[i].aux = NULL;
        vp[i].cont = 0;
        vp[i].tamanho = 0;
    }
}

void finalizar() {
    for (int i = 0; i < TAM; i++) {
        if (vp[i].aux != NULL) {
            free(vp[i].aux);
            vp[i].aux = NULL;
            vp[i].cont = 0;
            vp[i].tamanho = 0;
        }
    }
}
