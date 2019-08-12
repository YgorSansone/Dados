#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ANSI_COLOR_VERDE   "\033[1;32m"
void embaralhar(int *vet, int vetSize)
{
    for (int i = 0; i < vetSize; i++)
    {
        int r = rand() % vetSize;
        int temp = vet[i];
        vet[i] = vet[r];
        vet[r] = temp;
    }
}
void printar(int *vet, int vetSize)
{
    int cont = 0;
    char w[vetSize];
    for(int i = 0; i<vetSize; i++)
    {
        cont++;
        printf("\t%d", vet[i]);
        if(cont == 10)
        {
            printf("\n");
            cont = 0;
        }
    }
}
int *cad( int vetSize)
{
    int *arr = malloc(sizeof(int)*vetSize);

    for(int i = 0; i<vetSize; i++)
    {
        //int aux = (rand() % max)+min;
        arr[i] = i+1;
    }
    return arr;
}
void merge(int *x, int *temp, int esq, int meio, int dir)
{
    int i, esq_fim, tam, tmp_pos;
    esq_fim = meio - 1;
    tmp_pos = esq;
    tam = dir - esq + 1;
    while ((esq <= esq_fim) && (meio <= dir))   //Junção ordenada em temp
    {
        if (x[esq] <= x[meio])                  //Se elemento da esquerda menor
        {
            temp[tmp_pos] = x[esq];
            tmp_pos++;
            esq++;
        }
        else
        {
            temp[tmp_pos] = x[meio];            //Se elemento da direita menor
            tmp_pos++;
            meio++;
        }
    }
    if (esq <= esq_fim)                         //Sobraram elementos na esquerda
    {
        memcpy(&temp[tmp_pos], &x[esq], (esq_fim - esq + 1)*sizeof(int));
    }
    if (meio <= dir)                            //Sobraram elementos na direita
    {
        memcpy(&temp[tmp_pos], &x[meio], (dir - meio + 1)*sizeof(int));
    }
    //Copiar elementos de temp para x
    memcpy(&x[dir - tam + 1], &temp[dir - tam + 1], tam*sizeof(int));
}

void mergesort(int *x, int *temp, int esq, int dir)
{
    int meio;
    if (dir > esq)
    {
        meio = (dir + esq) / 2;
        mergesort(x, temp, esq, meio);
        mergesort(x, temp, meio+1, dir);
        merge(x, temp, esq, meio+1, dir);
    }
}
void insertionSort(int x[], int n)
{
    int i, k, aux;
    for (k = 1; k < n; k++)
    {
        aux = x[k];
        for (i = k - 1; i >= 0 && aux < x[i]; i--)
        {
            x[i + 1] = x[i];
        }
        x[i + 1] = aux;
    }
}
void shellsort(int x[], int n)
{
    int gap, j, k, aux;
    for(gap = n / 2; gap >= 1; gap = gap / 2)
    {
        for(j = gap; j < n; j++)
        {
            aux = x[j];
            for(k = j - gap; k >= 0 && aux < x[k]; k-=gap)
            {
                x[k + gap] = x[k];
            }
            x[k + gap] = aux;
        }
    }
}
void bubblesort(int v[], int n)
{
    int i, j, aux;
    for(j = n - 1; j > 0; j--)
    {
        for(i = 0; i < j; i++)
        {
            if(v[i] > v[i + 1])
            {
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
            }
        }
    }
}
void quicksort(int x[], int p, int u)
{
    int i, j, pivo, aux;
    i = p;
    j = u;
    pivo = x[(i + j)/2];
    do
    {
        while(x[i] < pivo && i < u)
            i++;
        while(x[j] > pivo && j > p)
            j--;
        if(i <= j)
        {
            aux = x[i];
            x[i] = x[j];
            x[j] = aux;
            i++;
            j--;
        }
    }
    while(i <= j);
    if(p < j)
        quicksort(x, p, j);
    if(i < u)
        quicksort(x, i, u);
}

void imprimeMenu()
{
    printf(ANSI_COLOR_VERDE"+--------------------------------------------------------------+\n");
    printf("|==============================================================|\n");
    printf("| Programa para opera%c%co de lista simplesmente encadeada       |\n",135,198);
    printf("|==============================================================|\n");
    printf("| Opera%c%ces:                                                   |\n",135,198);
    printf("| 1) Cadastrar                                                 |\n");
    printf("| 2) Desordenar                                                |\n");
    printf("| 3) Printar                                                   |\n");
    printf("| 4) Merge                                                     |\n");
    printf("| 5) Bubblesort                                                |\n");
    printf("| 6) Quicksort                                                 |\n");
    printf("| 7) Shellsort                                                 |\n");
    printf("| 8) InsertionSort                                             |\n");
    printf("| 9) Sair                                                      |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("  Entre a op%c%co desejada ",135,198);
}
int main(int argc, char** argv)
{
    unsigned int tamanho;
    int cadastrarmenu = 0;
    int *v;
    int *temp;
    unsigned int opcao = 0;
    while(opcao != 9)
    {
        system("CLS");
        imprimeMenu();
        time_t inicial, final1;
        scanf("%d",&opcao);
        switch(opcao)
        {
        case 1:
            if(cadastrarmenu == 0)
            {
                printf("Entre com o tamanho: ");
                scanf("%d",&tamanho);
                v = cad(tamanho);
                cadastrarmenu = 1;
            }
            else
            {
                printf("\nOp%c%co invalida!\n",135,198);

            }

            break;
        case 2:
            if (cadastrarmenu == 1)
            {
                inicial = time(NULL);
                embaralhar(v,tamanho);
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
                printar(v,tamanho);
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
                temp = malloc(tamanho*sizeof(int));
                mergesort(v,temp,0, tamanho-1);
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
                bubblesort(v,tamanho);
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
                quicksort(v,0, tamanho-1);
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
                inicial = time(NULL);
                shellsort(v,tamanho);
                final1 = time(NULL);
                printf("Segundos : %ld\n",final1-inicial);
            }
            else
            {
                printf("\nOp%c%co invalida!\n",135,198);
            }

            break;
        case 8:
            if (cadastrarmenu == 1)
            {
                inicial = time(NULL);
                insertionSort(v,tamanho);
                final1 = time(NULL);
                printf("Segundos : %ld\n",final1-inicial);
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
