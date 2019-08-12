#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
//#include <random>
//#include <algorithm>
//#include <iterator>

#define CLEAR "CLS"


void CadastrarValores()
{

}
//template<typename RandomIt, typename Gen>
//void Desordenar(RandomIt first, RandomIt last, Gen&& g)

{
    using diff_t = typename std::iterator_traits<RandomIt>::difference_type;
    using distr_t = std::uniform_int_distribution<diff_t>;
    using param_t = typename distr_t::param_type;

    distr_t D;
    diff_t n = last - first;
    for (diff_t i = n-1; i > 0; --i)
    {
        using std::swap;
        swap(first[i], first[D(g, param_t(0, i))]);
    }
}
void Imprimir()
{
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
void ShellSort()
{
}


void imprimeMenu()
{
    printf("+---------------------------------------------------------------+\n");
    printf("|===============================================================|\n");
    printf("|       Programa para Matricula de aluno usando mutilista       |\n");
    printf("|===============================================================|\n");
    printf("| Operacoes:                                                    |\n");
    printf("| 1) Cadastrar valores                                          |\n");
    printf("| 2) Desordenar                                                 |\n");
    printf("| 3) Imprimir                                                   |\n");
    printf("| 4) InsertionSort                                              |\n");
    printf("| 5) ShellSort                                                  |\n");
    printf("| 6)                                                            |\n");
    printf("| 7)                                                            |\n");
    printf("| 8)                                                            |\n");
    printf("| 9) Sair                                                       |\n");
    printf("+---------------------------------------------------------------+\n");
    printf("  Pressione a opcao desejada ");
}



int main()
{
    caluno caba;
    caba.quant = 0;
    caba.ini = NULL;

    cdisciplina cabd;
    cabd.quant = 0;
    cabd.ini = NULL;

    int ok = 1;
    char opcao = '0';
    while(ok)
    {
        system(CLEAR);
        imprimeMenu();
        opcao = getch();
        switch(opcao)
        {
        case '1':
            cadastrarAluno(&caba);
            break;
        case '2':
            Desordenar();
            break;
        case '3':
            matricularAluno(&caba, &cabd);
            break;
        case '4':
            removerAluno(&caba);
            break;
        case '5':
            listarAlunos(&caba);
            break;
        case '6':
            listarDisciplinas(&cabd);
            break;
        case '7':
            listarDisciplinasMatriculadas(&caba);
            break;
        case '8':
            listarAlunosMatriculados(&caba, &cabd);
            break;
        case '9':
            ok = 0;
            printf("\n ¯\(°_o)/¯ \n");
            break;
        default:
            printf("\nOpcao invalida!\n");
            getch();
            break;
        }
    }
    printf("\n");
    return (EXIT_SUCCESS);
}
