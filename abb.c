#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int i;
typedef struct _no no;
no *buscar(no *raiz, int valor);
struct _no
{
  int valor;
  no *esq;
  no *dir;
};

int _print_t(no *tree, int is_left, int offset, int depth, char s[20][255])
{
  char b[20];
  int width = 5;

  if (!tree)
    return 0;

  sprintf(b, "(%03d)", tree->valor);

  int left = _print_t(tree->esq, 1, offset, depth + 1, s);
  int right = _print_t(tree->dir, 0, offset + left + width, depth + 1, s);

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

void print_t(no *tree)
{
  system("clear");
  char s[20][255];
  for (int i = 0; i < 20; i++)
    sprintf(s[i], "%80s", " ");

  _print_t(tree, 0, 0, 0, s);

  for (int i = 0; i < 20; i++)
    printf("%s\n", s[i]);
}

no *criarno(int valor)
{
  no *novo = (no *)malloc(sizeof(no));
  novo->valor = valor;
  novo->esq = NULL;
  novo->dir = NULL;
  return novo;
}

void inserir(no **raiz, int valor)
{
  no *aux = *raiz;
  if (buscar(aux, valor) == NULL)
  {
    no *y;
    no *novo = criarno(valor);
    if (*raiz == NULL)
      *raiz = novo;
    else
    {
      while (aux != NULL)
      {
        y = aux;
        if (valor < aux->valor)
          aux = aux->esq;
        else
          aux = aux->dir;
      }
      if ((y != NULL) && (valor < y->valor))
        y->esq = novo;
      else
        y->dir = novo;
    }
  }
  else
  {
    printf("Elemento ja existe!\n");
  }
}

void remover(no **raiz, int valor)
{
  no *aux = *raiz;
  no *pai = buscar(aux, valor);
  if (pai != NULL)
  {
    if (pai->esq != NULL && pai->esq->valor == valor)
    {
      aux = pai->esq;
      if (aux->dir == NULL && aux->esq == NULL)
      {
        pai->esq = NULL;
        free(aux);
      }
      else if (aux->esq != NULL && aux->dir == NULL)
      {
        pai->esq = aux->esq;
        free(aux);
      }
      else if (aux->esq == NULL && aux->dir != NULL)
      {
        pai->esq = aux->dir;
        free(aux);
      }
      else if (aux->esq != NULL && aux->dir != NULL)
      {
        no *auxb = aux->esq;
        while (auxb->dir != NULL)
        {
          auxb = auxb->dir;
        }
        int _v = auxb->valor;
        remover(raiz, _v);
        no *_novo = criarno(_v);
        pai->esq = _novo;
        _novo->dir = aux->dir;
        _novo->esq = aux->esq;
        free(aux);
      }
    }
    else if (pai->dir != NULL && pai->dir->valor == valor)
    {
      aux = pai->dir;
      if (aux->dir == NULL && aux->esq == NULL)
      {
        pai->dir = NULL;
        free(aux);
      }
      else if (aux->esq != NULL && aux->dir == NULL)
      {
        pai->dir = aux->esq;
        free(aux);
      }
      else if (aux->esq == NULL && aux->dir != NULL)
      {
        pai->dir = aux->dir;
        free(aux);
      }
      else if (aux->esq != NULL && aux->dir != NULL)
      {
        no *auxb = aux->esq;
        while (auxb->dir != NULL)
        {
          auxb = auxb->dir;
        }
        int _v = auxb->valor;
        remover(raiz, _v);
        no *_novo = criarno(_v);
        pai->dir = _novo;
        _novo->dir = aux->dir;
        _novo->esq = aux->esq;
        free(aux);
      }
    }
    else
    {
      if (aux->dir == NULL && aux->esq == NULL)
      {
        *raiz = NULL;
        free(aux);
      }
      else if (aux->esq != NULL && aux->dir == NULL)
      {
        *raiz = aux->esq;
        free(aux);
      }
      else if (aux->esq == NULL && aux->dir != NULL)
      {
        *raiz = aux->dir;
        free(aux);
      }
      else if (aux->esq != NULL && aux->dir != NULL)
      {
        no *auxb = aux->esq;
        while (auxb->dir != NULL)
        {
          auxb = auxb->dir;
        }
        int _v = auxb->valor;
        remover(raiz, _v);
        no *_novo = criarno(_v);
        *raiz = _novo;
        _novo->dir = aux->dir;
        _novo->esq = aux->esq;
        free(aux);
      }
    }
  }
  else
  {
    printf("Valor Nao Encontrado!\n");
  }
}

void em_ordem(no *raiz)
{
  if (raiz != NULL)
  {
    em_ordem(raiz->esq);
    printf("%d\t", raiz->valor);
    em_ordem(raiz->dir);
  }
}

void pos_ordem(no *raiz)
{
  if (raiz != NULL)
  {
    pos_ordem(raiz->esq);
    pos_ordem(raiz->dir);
    printf("%d\t", raiz->valor);
  }
}

void pre_ordem(no *raiz)
{
  if (raiz != NULL)
  {
    printf("%d\t", raiz->valor);
    pre_ordem(raiz->esq);
    pre_ordem(raiz->dir);
  }
}

no *buscar(no *raiz, int valor)
{
  no *y = raiz;
  while (raiz != NULL)
  {
    if (valor < raiz->valor)
    {
      y = raiz;
      raiz = raiz->esq;
    }
    else if (valor > raiz->valor)
    {
      y = raiz;
      raiz = raiz->dir;
    }
    else
      return y;
  }
  return NULL;
}

void imprimeMenu()
{
  printf("================================================================\n");
  printf("|     Tempo de execução de diferentes métodos de ordenação     |\n");
  printf("================================================================\n");
  printf("| Operacoes:                                                   |\n");
  printf("| 1) Inserir Valor                                             |\n");
  printf("| 2) Remover No                                                |\n");
  printf("| 3) Buscar No                                                 |\n");
  printf("| 4) Em Ordem                                                  |\n");
  printf("| 5) Pre Ordem                                                 |\n");
  printf("| 6) Pos Ordem                                                 |\n");
  printf("| 7) Representacao arvore                                      |\n");
  printf("| 9) Sair                                                      |\n");
  printf("+--------------------------------------------------------------+\n");
  printf("  Pressione a opcao desejada ");
}
int main()
{
  system("CLS");
  no *raiz = NULL;

  while (1)
  {
    imprimeMenu();
    char _opcao[10];
    gets(_opcao);
    int o = atoi(_opcao);
    system("CLS");
    if (o == 1)
    {
      printf("Insira o valor: ");
      char _valor[10];
      gets(_valor);
      int valor = atoi(_valor);
      inserir(&raiz, valor);
    }
    else if (o == 2)
    {
      printf("Insira o valor: ");
      char _valor[10];
      gets(_valor);
      int valor = atoi(_valor);
      remover(&raiz, valor);
    }
    else if (o == 3)
    {
      printf("Insira o valor: ");
      char _valor[10];
      gets(_valor);
      int valor = atoi(_valor);
      if (buscar(raiz, valor) != NULL)
      {
        printf("Elemento Encontrado!\n");
      }
      else
      {
        printf("Elemento Nao Encontrado!\n");
      }
    }
    else if (o == 4)
    {
      em_ordem(raiz);
      printf("\n");
    }
    else if (o == 5)
    {
      pre_ordem(raiz);
      printf("\n");
    }
    else if (o == 6)
    {
      pos_ordem(raiz);
      printf("\n");
    }
    else if (o == 7)
    {
      print_t(raiz);
    }
    else if (o == 9)
    {
      return 0;
    }
  }

  return 0;
}
