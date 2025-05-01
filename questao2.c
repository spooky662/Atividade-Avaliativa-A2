#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { RED, BLACK } Color;

typedef struct Produto {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
    Color cor;
    struct Produto *esq, *dir, *pai;
} Produto;

Produto* criarProduto(int codigo, const char* nome, int quantidade, float preco) {
    Produto* novo = (Produto*)malloc(sizeof(Produto));
    novo->codigo = codigo;
    strcpy(novo->nome, nome);
    novo->quantidade = quantidade;
    novo->preco = preco;
    novo->cor = RED;
    novo->esq = novo->dir = novo->pai = NULL;
    return novo;
}

Produto* rotacaoEsquerda(Produto* raiz, Produto* x) {
    Produto* y = x->dir;
    x->dir = y->esq;
    if (y->esq != NULL) y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL)
        raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;
    y->esq = x;
    x->pai = y;
    return raiz;
}

Produto* rotacaoDireita(Produto* raiz, Produto* y) {
    Produto* x = y->esq;
    y->esq = x->dir;
    if (x->dir != NULL) x->dir->pai = y;
    x->pai = y->pai;
    if (y->pai == NULL)
        raiz = x;
    else if (y == y->pai->dir)
        y->pai->dir = x;
    else
        y->pai->esq = x;
    x->dir = y;
    y->pai = x;
    return raiz;
}

Produto* inserirBST(Produto* raiz, Produto* novo) {
    if (raiz == NULL) return novo;

    if (novo->codigo < raiz->codigo) {
        raiz->esq = inserirBST(raiz->esq, novo);
        raiz->esq->pai = raiz;
    } else if (novo->codigo > raiz->codigo) {
        raiz->dir = inserirBST(raiz->dir, novo);
        raiz->dir->pai = raiz;
    }

    return raiz;
}

Produto* corrigirInsercao(Produto* raiz, Produto* no) {
    Produto* tio;
    while (no != raiz && no->pai->cor == RED) {
        if (no->pai == no->pai->pai->esq) {
            tio = no->pai->pai->dir;
            if (tio != NULL && tio->cor == RED) {
                no->pai->cor = BLACK;
                tio->cor = BLACK;
                no->pai->pai->cor = RED;
                no = no->pai->pai;
            } else {
                if (no == no->pai->dir) {
                    no = no->pai;
                    raiz = rotacaoEsquerda(raiz, no);
                }
                no->pai->cor = BLACK;
                no->pai->pai->cor = RED;
                raiz = rotacaoDireita(raiz, no->pai->pai);
            }
        } else {
            tio = no->pai->pai->esq;
            if (tio != NULL && tio->cor == RED) {
                no->pai->cor = BLACK;
                tio->cor = BLACK;
                no->pai->pai->cor = RED;
                no = no->pai->pai;
            } else {
                if (no == no->pai->esq) {
                    no = no->pai;
                    raiz = rotacaoDireita(raiz, no);
                }
                no->pai->cor = BLACK;
                no->pai->pai->cor = RED;
                raiz = rotacaoEsquerda(raiz, no->pai->pai);
            }
        }
    }
    raiz->cor = BLACK;
    return raiz;
}

Produto* inserirProduto(Produto* raiz, int codigo, const char* nome, int quantidade, float preco) {
    Produto* novo = criarProduto(codigo, nome, quantidade, preco);
    raiz = inserirBST(raiz, novo);
    return corrigirInsercao(raiz, novo);
}

Produto* buscarProduto(Produto* raiz, int codigo) {
    if (raiz == NULL || raiz->codigo == codigo) return raiz;
    if (codigo < raiz->codigo) return buscarProduto(raiz->esq, codigo);
    else return buscarProduto(raiz->dir, codigo);
}

void listarProdutos(Produto* raiz) {
    if (raiz == NULL) return;
    listarProdutos(raiz->esq);
    printf("Código: %d | Nome: %s | Quantidade: %d | Preço: R$%.2f | Cor: %s\n",
           raiz->codigo, raiz->nome, raiz->quantidade, raiz->preco,
           raiz->cor == RED ? "Vermelho" : "Preto");
    listarProdutos(raiz->dir);
}

// Remoção e correção (versão simplificada e adaptada da original)
Produto* minimo(Produto* no) {
    while (no->esq != NULL) no = no->esq;
    return no;
}

void transplantar(Produto** raiz, Produto* u, Produto* v) {
    if (u->pai == NULL)
        *raiz = v;
    else if (u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;
    if (v != NULL)
        v->pai = u->pai;
}

Produto* corrigirRemocao(Produto* raiz, Produto* x) {
    while (x != raiz && (x == NULL || x->cor == BLACK)) {
        Produto* w;
        if (x == x->pai->esq) {
            w = x->pai->dir;
            if (w->cor == RED) {
                w->cor = BLACK;
                x->pai->cor = RED;
                raiz = rotacaoEsquerda(raiz, x->pai);
                w = x->pai->dir;
            }
            if ((w->esq == NULL || w->esq->cor == BLACK) &&
                (w->dir == NULL || w->dir->cor == BLACK)) {
                w->cor = RED;
                x = x->pai;
            } else {
                if (w->dir == NULL || w->dir->cor == BLACK) {
                    if (w->esq != NULL) w->esq->cor = BLACK;
                    w->cor = RED;
                    raiz = rotacaoDireita(raiz, w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                if (w->dir != NULL) w->dir->cor = BLACK;
                raiz = rotacaoEsquerda(raiz, x->pai);
                x = raiz;
            }
        } else {
            w = x->pai->esq;
            if (w->cor == RED) {
                w->cor = BLACK;
                x->pai->cor = RED;
                raiz = rotacaoDireita(raiz, x->pai);
                w = x->pai->esq;
            }
            if ((w->dir == NULL || w->dir->cor == BLACK) &&
                (w->esq == NULL || w->esq->cor == BLACK)) {
                w->cor = RED;
                x = x->pai;
            } else {
                if (w->esq == NULL || w->esq->cor == BLACK) {
                    if (w->dir != NULL) w->dir->cor = BLACK;
                    w->cor = RED;
                    raiz = rotacaoEsquerda(raiz, w);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                if (w->esq != NULL) w->esq->cor = BLACK;
                raiz = rotacaoDireita(raiz, x->pai);
                x = raiz;
            }
        }
    }
    if (x != NULL)
        x->cor = BLACK;
    return raiz;
}

Produto* removerProduto(Produto* raiz, int codigo) {
    Produto* z = buscarProduto(raiz, codigo);
    if (z == NULL) return raiz;

    Produto *y = z, *x;
    Color cor_original = y->cor;

    if (z->esq == NULL) {
        x = z->dir;
        transplantar(&raiz, z, z->dir);
    } else if (z->dir == NULL) {
        x = z->esq;
        transplantar(&raiz, z, z->esq);
    } else {
        y = minimo(z->dir);
        cor_original = y->cor;
        x = y->dir;
        if (y->pai == z) {
            if (x != NULL) x->pai = y;
        } else {
            transplantar(&raiz, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplantar(&raiz, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }

    free(z);
    if (cor_original == BLACK)
        raiz = corrigirRemocao(raiz, x);
    return raiz;
}

void menu() {
    printf("\n===== SISTEMA DE INVENTÁRIO =====\n");
    printf("1. Cadastrar produto\n");
    printf("2. Remover produto\n");
    printf("3. Buscar produto\n");
    printf("4. Listar produtos (em ordem)\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    Produto* raiz = NULL;
    int opcao;

    raiz = inserirProduto(raiz, 101, "Teclado", 50, 120.00);
    raiz = inserirProduto(raiz, 105, "Mouse", 30, 65.00);
    raiz = inserirProduto(raiz, 102, "Monitor", 20, 900.00);
    raiz = inserirProduto(raiz, 110, "Webcam", 15, 300.00);

    do {
        menu();
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        if (opcao == 1) {
            int codigo, quantidade;
            float preco;
            char nome[50];

            printf("Código do produto: ");
            scanf("%d", &codigo);
            getchar();

            printf("Nome do produto: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0'; // remover \n

            printf("Quantidade: ");
            scanf("%d", &quantidade);

            printf("Preço: ");
            scanf("%f", &preco);

            raiz = inserirProduto(raiz, codigo, nome, quantidade, preco);
            printf("Produto cadastrado com sucesso!\n");

        } else if (opcao == 2) {
            int codigo;
            printf("Código do produto a remover: ");
            scanf("%d", &codigo);
            Produto* buscado = buscarProduto(raiz, codigo);
            if (buscado) {
                raiz = removerProduto(raiz, codigo);
                printf("Produto removido com sucesso.\n");
            } else {
                printf("Produto não encontrado.\n");
            }

        } else if (opcao == 3) {
            int codigo;
            printf("Código do produto a buscar: ");
            scanf("%d", &codigo);
            Produto* p = buscarProduto(raiz, codigo);
            if (p != NULL)
                printf("Encontrado: %s | Qtd: %d | Preço: %.2f\n", p->nome, p->quantidade, p->preco);
            else
                printf("Produto não encontrado.\n");

        } else if (opcao == 4) {
            if (raiz == NULL)
                printf("Nenhum produto cadastrado.\n");
            else {
                printf("\n--- Produtos cadastrados ---\n");
                listarProdutos(raiz);
            }

        } else if (opcao == 0) {
            printf("Encerrando o sistema.\n");
        } else {
            printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}

