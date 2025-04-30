#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do no (usuario)
typedef struct NO {
    char nome[100];  // chave
    int id;
    char email[100];
    int altura;
    struct NO* esq;
    struct NO* dir;
} NO;

typedef NO* AVLTree;

// Funcao para obter altura
int altura_NO(NO* no) {
    return (no == NULL) ? -1 : no->altura;
}

// Maior entre dois numeros
int maior(int a, int b) {
    return (a > b) ? a : b;
}

// Fator de balanceamento
int fatorBalanceamento_NO(NO* no) {
    return abs(altura_NO(no->esq) - altura_NO(no->dir));
}

// Rotacoes
void RotacaoLL(AVLTree* raiz) {
    NO* no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = *raiz;
    (*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
    no->altura = maior(altura_NO(no->esq), (*raiz)->altura) + 1;
    *raiz = no;
}

void RotacaoRR(AVLTree* raiz) {
    NO* no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = *raiz;
    (*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
    no->altura = maior(altura_NO(no->dir), (*raiz)->altura) + 1;
    *raiz = no;
}

void RotacaoLR(AVLTree* raiz) {
    RotacaoRR(&(*raiz)->esq);
    RotacaoLL(raiz);
}

void RotacaoRL(AVLTree* raiz) {
    RotacaoLL(&(*raiz)->dir);
    RotacaoRR(raiz);
}

// Inserir usuario
int cadastrarUsuario(AVLTree* raiz, char* nome, int id, char* email) {
    if (*raiz == NULL) {
        NO* novo = (NO*)malloc(sizeof(NO));
        if (novo == NULL) return 0;
        strcpy(novo->nome, nome);
        novo->id = id;
        strcpy(novo->email, email);
        novo->altura = 0;
        novo->esq = novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    NO* atual = *raiz;
    int res;
    if (strcmp(nome, atual->nome) < 0) {
        res = cadastrarUsuario(&atual->esq, nome, id, email);
        if (fatorBalanceamento_NO(atual) >= 2) {
            if (strcmp(nome, atual->esq->nome) < 0)
                RotacaoLL(raiz);
            else
                RotacaoLR(raiz);
        }
    } else if (strcmp(nome, atual->nome) > 0) {
        res = cadastrarUsuario(&atual->dir, nome, id, email);
        if (fatorBalanceamento_NO(atual) >= 2) {
            if (strcmp(nome, atual->dir->nome) > 0)
                RotacaoRR(raiz);
            else
                RotacaoRL(raiz);
        }
    } else {
        printf("Usuário já cadastrado!\n");
        return 0;
    }

    atual->altura = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;
    return res;
}

// Buscar usuario
NO* buscarUsuario(AVLTree raiz, char* nome) {
    if (raiz == NULL) return NULL;
    int cmp = strcmp(nome, raiz->nome);
    if (cmp < 0)
        return buscarUsuario(raiz->esq, nome);
    else if (cmp > 0)
        return buscarUsuario(raiz->dir, nome);
    else
        return raiz;
}

// Função auxiliar para procurar menor
NO* procuraMenor(NO* atual) {
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

// Remover usuario
int removerUsuario(AVLTree* raiz, char* nome) {
    if (*raiz == NULL) return 0;

    int res;
    if (strcmp(nome, (*raiz)->nome) < 0) {
        res = removerUsuario(&(*raiz)->esq, nome);
        if (fatorBalanceamento_NO(*raiz) >= 2) {
            if (altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                RotacaoRR(raiz);
            else
                RotacaoRL(raiz);
        }
    } else if (strcmp(nome, (*raiz)->nome) > 0) {
        res = removerUsuario(&(*raiz)->dir, nome);
        if (fatorBalanceamento_NO(*raiz) >= 2) {
            if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
                RotacaoLL(raiz);
            else
                RotacaoLR(raiz);
        }
    } else {
        NO* temp = *raiz;
        if ((*raiz)->esq == NULL)
            *raiz = (*raiz)->dir;
        else if ((*raiz)->dir == NULL)
            *raiz = (*raiz)->esq;
        else {
            NO* menor = procuraMenor((*raiz)->dir);
            strcpy((*raiz)->nome, menor->nome);
            (*raiz)->id = menor->id;
            strcpy((*raiz)->email, menor->email);
            removerUsuario(&(*raiz)->dir, menor->nome);
            if (fatorBalanceamento_NO(*raiz) >= 2) {
                if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
        free(temp);
        return 1;
    }

    if (*raiz != NULL)
        (*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
    return res;
}

// Listar usuarios em ordem alfabetica
void listarUsuarios(AVLTree raiz) {
    if (raiz != NULL) {
        listarUsuarios(raiz->esq);
        printf("Nome: %s, ID: %d, Email: %s\n", raiz->nome, raiz->id, raiz->email);
        listarUsuarios(raiz->dir);
    }
}

void menu() {
    AVLTree usuarios = NULL;
    int opcao, id;
    char nome[100], email[100];
    NO* encontrado;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Cadastrar Usuario\n");
        printf("2. Remover Usuario\n");
        printf("3. Buscar Usuario\n");
        printf("4. Listar Usuarios\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                printf("\n--- Cadastrar Usuario ---\n");
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remove o \n
                printf("ID: ");
                scanf("%d", &id);
                getchar(); // limpa \n
                printf("Email: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0';
                if (cadastrarUsuario(&usuarios, nome, id, email))
                    printf("Usuario cadastrado com sucesso!\n");
                break;

            case 2:
                printf("\n--- Remover Usuario ---\n");
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                if (removerUsuario(&usuarios, nome))
                    printf("Usuario removido.\n");
                else
                    printf("Usuario não encontrado.\n");
                break;

            case 3:
                printf("\n--- Buscar Usuario ---\n");
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                encontrado = buscarUsuario(usuarios, nome);
                if (encontrado)
                    printf("Encontrado: %s, ID: %d, Email: %s\n", encontrado->nome, encontrado->id, encontrado->email);
                else
                    printf("Usuario nao encontrado.\n");
                break;

            case 4:
                printf("\n--- Lista de Usuarios (Ordem Alfabetica) ---\n");
                listarUsuarios(usuarios);
                break;

            case 0:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main() {
    AVLTree usuarios = NULL;

    // Possivelmente nao vai funcionar, mas e um modelo para criar os novos usuarios que pode ser usado ao inicializar o algoritmo
    cadastrarUsuario(&usuarios, "Carlos", 101, "carlos@email.com");
    cadastrarUsuario(&usuarios, "Ana", 102, "ana@email.com");
    cadastrarUsuario(&usuarios, "Joao", 103, "joao@email.com");
    cadastrarUsuario(&usuarios, "Beatriz", 104, "bia@email.com");

    menu();
    return 0;
}
