#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ANSI_COLOR_VERDE   "\033[1;32m"
typedef struct btnode bintree;
struct btnode
{
    int dado;
    bintree *esquerdo;
    bintree *direito;
};
bintree *criarno(int valor)
{
  bintree *novo = (bintree *)malloc(sizeof(bintree));
  novo->dado = valor;
  novo->esquerdo = NULL;
  novo->direito = NULL;
  return novo;
}
void em_ordem(bintree *raiz)
{
    if (raiz != NULL)
    {
        em_ordem(raiz->esquerdo);
        printf("%d\n",raiz->dado);
        em_ordem(raiz->direito);
    }
}
void pos_ordem(bintree *raiz)
{
    if (raiz != NULL)
    {
        pos_ordem(raiz->esquerdo);
        pos_ordem(raiz->direito);
        printf("%d\n",raiz->dado);
    }
}
void pre_ordem(bintree *raiz)
{
    if (raiz != NULL)
    {
        printf("%d\n",raiz->dado);
        pre_ordem(raiz->esquerdo);
        pre_ordem(raiz->direito);
    }
}

bintree *busca_binaria(bintree *raiz, int valor)
{
    while (raiz != NULL)
    {
        if (valor < raiz->dado)
            raiz = raiz->esquerdo;
        else if (valor > raiz->dado)
            raiz = raiz->direito;
        else
            return(raiz);
    }
    return(NULL);
}

bintree *insere_binaria(bintree **raiz, int valor)
{
    bintree *novo,*y = NULL, *aux=*raiz;
    novo = (bintree *) malloc(sizeof(bintree));
    novo->esquerdo = novo->direito = NULL;
    novo->dado = valor;
    if (*raiz == NULL)
        *raiz = novo;
    else
    {
        while(aux != NULL)
        {
            y = aux;
            if (valor < aux->dado)
                aux = aux->esquerdo;
            else
                aux = aux->direito;
        }
        if ((y != NULL) && (valor < y->dado))
            y->esquerdo = novo;
        else
            y->direito = novo;
    }
    return(novo);
}

void remover_binaria(bintree **raiz, int valor)
{
    bintree *aux = *raiz;
    bintree *pai = busca_binaria(aux, valor);
    if(pai != NULL)
    {
        if(pai->esquerdo != NULL && pai->esquerdo->dado == valor)
        {
            aux = pai->esquerdo;
            //Caso 1
            if(aux->direito == NULL && aux->esquerdo == NULL)
            {
                pai->esquerdo =NULL;
                free(aux);
            }
            else if (aux->esquerdo !=NULL && aux->direito == NULL)
            {
                pai->esquerdo = aux->esquerdo;
                free(aux);
            }
            else if(aux->esquerdo == NULL && aux->direito !=NULL)
            {
                pai->esquerdo=aux->direito;
                free(aux);
            }
            //Caso 2
            else if(aux->esquerdo !=NULL && aux->direito!=NULL)
            {
                bintree *aux2 = aux->esquerdo;
                while(aux2->direito!=NULL)
                {
                    aux2 = aux2->direito;
                }
                int valorremover = aux2->dado;
                remover_binaria(raiz,valorremover);
                bintree *no = criarno(valorremover);
                pai->esquerdo= no;
                no->esquerdo = aux->esquerdo;
                no->direito = aux->direito;
                free(aux);
            }
        }
        else if(pai->direito !=NULL && pai->dado==valor)
        {
            aux=pai->direito;
            if(aux->direito==NULL && aux == NULL)
            {
                pai->direito=NULL;
                free(aux);
            }
            else if(aux->esquerdo == NULL && aux->direito!=NULL)
            {
                pai->direito = aux->direito;
                free(aux);
            }
            else if(aux->esquerdo != NULL && aux->direito ==NULL)
            {
                pai->esquerdo = aux->esquerdo;
                free(aux);
            }
            else if(aux->esquerdo !=NULL && aux->direito !=NULL)
            {
                bintree *aux2 = aux->esquerdo;
                while(aux2->direito!=NULL)
                {
                    aux2 = aux2->direito;
                }
                int valorremover = aux2->dado;
                remover_binaria(raiz,valorremover);
                bintree *no = criarno(valorremover);
                pai->direito= no;
                no->esquerdo = aux->esquerdo;
                no->direito = aux->direito;
                free(aux);
            }
        }
        else
        {
            if(aux->direito == NULL && aux->esquerdo ==NULL)
            {
                *raiz=NULL;
                free(aux);
            }
            else if(aux->esquerdo!=NULL && aux->direito ==NULL)
            {
                *raiz = aux->esquerdo;
                free(aux);
            }
            else if(aux->esquerdo ==NULL && aux->direito !=NULL)
            {
                *raiz = aux->direito;
                free(aux);
            }
            else if(aux->esquerdo != NULL && aux->direito !=NULL)
            {
                bintree *aux2 = aux->esquerdo;
                while(aux2->direito!=NULL)
                {
                    aux2 = aux2->direito;
                }
                int valorremover = aux2->dado;
                remover_binaria(raiz,valorremover);
                bintree *no = criarno(valorremover);
                *raiz= no;
                no->esquerdo = aux->esquerdo;
                no->direito = aux->direito;
                free(aux);
            }
        }
    }
    else
    {
        printf("Valor não encontrado !!! \n");
    }
}



int _print_t(bintree *tree, int is_left, int offset, int depth, char s[20][255])
{
  char b[20];
  int width = 5;

  if (!tree)
    return 0;

  sprintf(b, "(%03d)", tree->dado);

  int left = _print_t(tree->esquerdo, 1, offset, depth + 1, s);
  int right = _print_t(tree->direito, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
  for (int i = 0; i < width; i++)
    s[depth][offset + left + i] = b[i];

  if (depth && is_left)
  {

    for (int i = 0; i < width + right; i++)
      s[depth - 1][offset + left + width / 2 + i] = '-';

    s[depth - 1][offset + left + width / 2] = '.';
  }
  else if (depth && !is_left)
  {

    for (int i = 0; i < left + width; i++)
      s[depth - 1][offset - width / 2 + i] = '-';

    s[depth - 1][offset + left + width / 2] = '.';
  }
#else
  for (int i = 0; i < width; i++)
    s[2 * depth][offset + left + i] = b[i];

  if (depth && is_left)
  {

    for (int i = 0; i < width + right; i++)
      s[2 * depth - 1][offset + left + width / 2 + i] = '-';

    s[2 * depth - 1][offset + left + width / 2] = '+';
    s[2 * depth - 1][offset + left + width + right + width / 2] = '+';
  }
  else if (depth && !is_left)
  {

    for (int i = 0; i < left + width; i++)
      s[2 * depth - 1][offset - width / 2 + i] = '-';

    s[2 * depth - 1][offset + left + width / 2] = '+';
    s[2 * depth - 1][offset - width / 2 - 1] = '+';
  }
#endif

  return left + width + right;
}

void print_t(bintree *tree)
{
  //system("CLS");
  char s[20][255];
  for (int i = 0; i < 20; i++)
    sprintf(s[i], "%80s", " ");

  _print_t(tree, 0, 0, 0, s);

  for (int i = 0; i < 5; i++)
    printf("%s\n", s[i]);
}


void imprimeMenu()
{
    printf(ANSI_COLOR_VERDE"+--------------------------------------------------------------+\n");
    printf("|==============================================================|\n");
    printf("| Programa para opera%c%co de lista simplesmente encadeada       |\n",135,198);
    printf("|==============================================================|\n");
    printf("| Opera%c%ces:                                                   |\n",135,198);
    printf("| 1) Cadastrar                                                 |\n");
    printf("| Listar em:                                                   |\n");
    printf("|   2) Ordem                                                   |\n");
    printf("|   3) Pré-ordem                                               |\n");
    printf("|   4) Pós-ordem                                               |\n");
    printf("| 5) buscar                                                    |\n");
    printf("| 6) remover                                                   |\n");
    printf("| 7) Sair                                                      |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("  Entre a op%c%co desejada ",135,198);
}
int main(int argc, char** argv)
{
    unsigned int valorc, valorb, valorr;
    int cadastrarmenu = 0;
    bintree *raiz = NULL;

    unsigned int opcao = 0;
    while(opcao != 8)
    {
        system("CLS");
        imprimeMenu();
        time_t inicial, final1;
        scanf("%d",&opcao);
        //system("CLS");
        switch(opcao)
        {
        case 1:

            printf("Entre com o tamanho: ");
            scanf("%d",&valorc);
            insere_binaria(&raiz,valorc);
            cadastrarmenu= 1;
            break;
        case 2:
            if (cadastrarmenu == 1)
            {
                inicial = time(NULL);
                em_ordem(raiz);
                final1 = time(NULL);
                printf("Segundos : %ld\n",final1-inicial);
            }
            else
            {
                printf("\nOp%c%co invalida!\n",135,198);

            }
            break;
        case 3:
            if (cadastrarmenu == 1)
            {
                pre_ordem(raiz);
                printf("\n");
            }
            else
            {
                printf("\nOp%c%co invalida!\n",135,198);

            }
            break;
        case 4:
            if (cadastrarmenu == 1)
            {
                inicial = time(NULL);
                pos_ordem(raiz);
                final1 = time(NULL);
                printf("Segundos : %ld\n",final1-inicial);
            }
            else
            {
                printf("\nOp%c%co invalida!\n",135,198);

            }
            break;
        case 5:
            if (cadastrarmenu == 1)
            {
                inicial = time(NULL);
                printf("Insira o valor: ");
                scanf("%d",&valorb);
                if (busca_binaria(raiz, valorb) != NULL)
                {
                    printf("Elemento Encontrado!\n");
                }
                else
                {
                    printf("Elemento Nao Encontrado!\n");
                }

                final1 = time(NULL);
                printf("Segundos : %ld\n",final1-inicial);
            }
            else
            {
                printf("\nOp%c%co invalida!\n",135,198);

            }
            break;
        case 6:
            if (cadastrarmenu == 1)
            {
                inicial = time(NULL);
                printf("Insira o valor a ser removido: ");
                scanf("%d",&valorr);
                remover_binaria(&raiz, valorr);
                final1 = time(NULL);
                printf("Segundos : %ld\n",final1-inicial);
            }
            else
            {
                printf("\nOp%c%co invalida!\n",135,198);

            }
            break;
                    case 7:
            if (cadastrarmenu == 1)
            {
    print_t(raiz);
            }
            else
            {
                printf("\nOp%c%co invalida!\n",135,198);

            }
            break;
        default:
            printf("\n\t\t\t\tTchau!\n");
            break;
        }
        getchar();
        getchar();
    }
    return (EXIT_SUCCESS);
}
