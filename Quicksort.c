#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//Contadores de trocar+chamadas de cada tipo
int TrocasChamadasLomutoPadrao = 0, TrocasChamadasLomutoAleatorio = 0, TrocasChamadasLomutoMediana = 0;
int TrocasChamadasHoarePadrao = 0, TrocasChamadasHoareAleatorio = 0, TrocasChamadasHoareMediana = 0;

//Struct pra gravar a contagem com o seu determinado tipo de ordenação
typedef struct
{
    int numeroChamadasTrocas;
    char tipo[3];
} Ordenacoes;

//Função de troca entre dois valores com um contador que incrementa sempre que houver uma troca
void trocar(int *a, int *b, int *contadorTrocasChamadas)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    (*contadorTrocasChamadas)++;
}

//Função mergesort para impressão do tipo de ordenção com menor número de chamadas + trocas para o maior número
void merge(Ordenacoes *vetor, int inicio, int meio, int fim)
{
    Ordenacoes *aux = (Ordenacoes *)malloc((fim - inicio + 1) * sizeof(Ordenacoes));
    if (aux == NULL)
    {
        fprintf(stderr, "Falha ao alocar memória para merge.\n");
        exit(EXIT_FAILURE);
    }

    int primeiroInicio = inicio, segundoInicio = meio + 1, posicaoAux = 0;
    while (primeiroInicio <= meio && segundoInicio <= fim)
    {
        if (vetor[primeiroInicio].numeroChamadasTrocas <= vetor[segundoInicio].numeroChamadasTrocas)
        {
            aux[posicaoAux++] = vetor[primeiroInicio++];
        }
        else
        {
            aux[posicaoAux++] = vetor[segundoInicio++];
        }
    }
    while (primeiroInicio <= meio)
    {
        aux[posicaoAux++] = vetor[primeiroInicio++];
    }
    while (segundoInicio <= fim)
    {
        aux[posicaoAux++] = vetor[segundoInicio++];
    }
    for (primeiroInicio = inicio, posicaoAux = 0; primeiroInicio <= fim; primeiroInicio++, posicaoAux++)
    {
        vetor[primeiroInicio] = aux[posicaoAux];
    }
    free(aux);
}

//Recursividade do mergeSort
void mergeSort(Ordenacoes *vetor, int inicio, int fim)
{
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

int32_t lomutoPadrao(int32_t *V, int32_t i, int32_t j, int *contadorTrocasChamadas)
{
    // Declaração do pivô e índices
    int32_t P = V[j], x = i - 1, y = i;
    // Particionando o vetor pelo pivô
    for (y = i; y < j; y++)
        if (V[y] <= P)
        {
            trocar(&V[++x], &V[y], contadorTrocasChamadas);
        }
    // Posicionando o pivô no vetor
    trocar(&V[++x], &V[j], contadorTrocasChamadas);
    // Retornando índice do pivô
    return x;
}

void quicksortLomutoPadrao(int32_t *V, int32_t i, int32_t j, int *contadorTrocasChamadas)
{
    (*contadorTrocasChamadas)++;
    // Caso base
    if (i < j)
    {
        // Particionamento do vetor
        int32_t p = lomutoPadrao(V, i, j, contadorTrocasChamadas);
        // Divisão em subvetores
        quicksortLomutoPadrao(V, i, p - 1, contadorTrocasChamadas);
        quicksortLomutoPadrao(V, p + 1, j, contadorTrocasChamadas);
    }
}

int32_t lomutoMediana(int32_t *V, int32_t i, int32_t j, int *contadorTrocasChamadas)
{
    int32_t n = j - i + 1;          // Tamanho do subvetor
    int32_t pos1 = i + n / 4;       // Posição n/4
    int32_t pos2 = i + n / 2;       // Posição n/2
    int32_t pos3 = i + (3 * n) / 4; // Posição 3n/4
    if (pos1 > j)
        pos1 = j;
    if (pos2 > j)
        pos2 = j;
    if (pos3 > j)
        pos3 = j;
    int32_t a = V[pos1], b = V[pos2], c = V[pos3];
    int32_t mediana;

    // Escolher a mediana
    if ((a <= b && b <= c) || (c <= b && b <= a))
    {
        mediana = pos2;
    }
    else if ((b <= a && a <= c) || (c <= a && a <= b))
    {
        mediana = pos1;
    }
    else
    {
        mediana = pos3;
    }

    // Trocar o pivô para a posição 'i'

    trocar(&V[mediana], &V[j], contadorTrocasChamadas);

    return lomutoPadrao(V, i, j, contadorTrocasChamadas);
}

void quicksortLomutoMediana(int32_t *V, int32_t i, int32_t j, int *contadorTrocasChamadas)
{
    (*contadorTrocasChamadas)++;
    // Caso base
    if (i < j)
    {
        // Particionamento do vetor
        int32_t p = lomutoMediana(V, i, j, contadorTrocasChamadas);
        // Divisão em subvetores
        quicksortLomutoMediana(V, i, p - 1, contadorTrocasChamadas);
        quicksortLomutoMediana(V, p + 1, j, contadorTrocasChamadas);
    }
}

int32_t lomutoAleatorio(int32_t *V, int32_t i, int32_t j, int *contadorTrocasChamadas)
{
    int32_t n = j - i + 1; // Tamanho do subvetor
    if (n <= 0)
        return i; // Evita divisão por zero ou índices inválidos

    // Calcula o índice aleatório usando a fórmula ini + |V[ini]| % n
    int32_t indiceAleatorio = i + (abs(V[i]) % n);

    // Garante que o índice esteja dentro dos limites
    if (indiceAleatorio < i || indiceAleatorio > j)
    {
        indiceAleatorio = i;
    }

    // Troca o elemento aleatório com o primeiro elemento (pivô)
    trocar(&V[indiceAleatorio], &V[j], contadorTrocasChamadas);

    // Chama o particionamento padrão de Lomuto
    return lomutoPadrao(V, i, j, contadorTrocasChamadas);
}

void quicksortLomutoAleatorio(int32_t *V, int32_t i, int32_t j, int *contadorTrocasChamadas)
{
    (*contadorTrocasChamadas)++;
    // Caso base
    if (i < j)
    {
        // Particionamento do vetor
        int32_t p = lomutoAleatorio(V, i, j, contadorTrocasChamadas);
        // Divisão em subvetores
        quicksortLomutoAleatorio(V, i, p - 1, contadorTrocasChamadas);
        quicksortLomutoAleatorio(V, p + 1, j, contadorTrocasChamadas);
    }
}

int32_t hoarePadrao(int32_t *V, int32_t i, int32_t j, int *contadorTrocasChamadas)
{
    // Declaração do pivô e índices
    int32_t P = V[i], x = i - 1, y = j + 1;
    // Particionando o vetor pelo pivô
    while (1)
    {
        while (V[--y] > P)
            ;
        while (V[++x] < P)
            ;
        if (x < y)
        {
            trocar(&V[x], &V[y], contadorTrocasChamadas);
        }
        else
            return y;
    }
}

void quicksortHoarePadrao(int32_t *V, int32_t i, int32_t j, int *contadorTrocasChamadas)
{
    (*contadorTrocasChamadas)++;
    // Caso base
    if (i < j)
    {

        // Particionamento do vetor
        int32_t p = hoarePadrao(V, i, j, contadorTrocasChamadas);
        // Divisão em subvetores
        quicksortHoarePadrao(V, i, p, contadorTrocasChamadas);
        quicksortHoarePadrao(V, p + 1, j, contadorTrocasChamadas);
    }
}

int32_t hoareMediana(int32_t *V, int32_t i, int32_t j, int *contadorTrocasChamadas)
{
    int32_t n = j - i + 1;          // Tamanho do subvetor
    int32_t pos1 = i + n / 4;       // Posição n/4
    int32_t pos2 = i + n / 2;       // Posição n/2
    int32_t pos3 = i + (3 * n) / 4; // Posição 3n/4
    if (pos1 > j)
        pos1 = j;
    if (pos2 > j)
        pos2 = j;
    if (pos3 > j)
        pos3 = j;
    
    int32_t a = V[pos1], b = V[pos2], c = V[pos3];
    int32_t mediana;

    // Escolher a mediana
    if ((a <= b && b <= c) || (c <= b && b <= a))
    {
        mediana = pos2;
    }
    else if ((b <= a && a <= c) || (c <= a && a <= b))
    {
        mediana = pos1;
    }
    else
    {
        mediana = pos3;
    }

    // Trocar o pivô para a posição 'i'
    trocar(&V[mediana], &V[i], contadorTrocasChamadas);
    return hoarePadrao(V, i, j, contadorTrocasChamadas);
}

void quicksortHoareMediana(int32_t *V, int32_t i, int32_t j, int *contadorTrocasChamadas)
{
    (*contadorTrocasChamadas)++;
    // Caso base
    if (i < j)
    {

        // Particionamento do vetor
        int32_t p = hoareMediana(V, i, j, contadorTrocasChamadas);
        // Divisão em subvetores
        quicksortHoareMediana(V, i, p, contadorTrocasChamadas);
        quicksortHoareMediana(V, p + 1, j, contadorTrocasChamadas);
    }
}

int32_t hoareAleatorio(int32_t *V, int32_t i, int32_t j, int *contadorTrocasChamadas)
{
    int32_t n = j - i + 1; // Tamanho do subvetor
    if (n <= 0)
        return i; // Evita divisão por zero ou índices inválidos

    // Calcula o índice aleatório usando a fórmula ini + |V[ini]| % n
    int32_t indiceAleatorio = i + (abs(V[i]) % n);

    // Garante que o índice esteja dentro dos limites
    if (indiceAleatorio < i || indiceAleatorio > j)
    {
        indiceAleatorio = i;
    }

    // Troca o elemento aleatório com o primeiro elemento (pivô)
    trocar(&V[i], &V[indiceAleatorio], contadorTrocasChamadas);

    // Chama o particionamento padrão de Hoare
    return hoarePadrao(V, i, j, contadorTrocasChamadas);
}

void quicksortHoareAleatorio(int32_t *V, int32_t i, int32_t j, int *contadorTrocasChamadas)
{
    (*contadorTrocasChamadas)++;
    // Caso base
    if (i < j)
    {
        // Particionamento do vetor
        int32_t p = hoareAleatorio(V, i, j, contadorTrocasChamadas);
        // Divisão em subvetores
        quicksortHoareAleatorio(V, i, p, contadorTrocasChamadas);
        quicksortHoareAleatorio(V, p + 1, j, contadorTrocasChamadas);
    }
}

int main(int argc, char* argv[])
{
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    //Verifica se o arquivo foi aberto corretamente
    if (input == NULL || output == NULL)
    {
        fprintf(output, "Falha ao abrir o arquivo!");
        system("pause");
        return 0;
    }

    
    int totalDeVetores, qtdDeElementosVetor;

    //Leitura dos dados nos arquivos
    fscanf(input, "%d", &totalDeVetores);
    for (int i = 0; i < totalDeVetores; i++)
    {
        //Vetor de structs para a impressão
        Ordenacoes *vetorOrdenacoes = (Ordenacoes *)malloc(7 * sizeof(Ordenacoes));
        fscanf(input, "%d", &qtdDeElementosVetor);

        //Declaração de vetores
        int *vetorDeNumerosLomutoPadrao = (int *)malloc(qtdDeElementosVetor * sizeof(int));
        int *vetorDeNumerosLomutoAleatorio = (int *)malloc(qtdDeElementosVetor * sizeof(int));
        int *vetorDeNumerosLomutoMediana = (int *)malloc(qtdDeElementosVetor * sizeof(int));
        int *vetorDeNumerosHoarePadrao = (int *)malloc(qtdDeElementosVetor * sizeof(int));
        int *vetorDeNumerosHoareAleatorio = (int *)malloc(qtdDeElementosVetor * sizeof(int));
        int *vetorDeNumerosHoareMediana = (int *)malloc(qtdDeElementosVetor * sizeof(int));

        //Reset no contador para usar em um novo vetor
        TrocasChamadasLomutoPadrao = 0, TrocasChamadasLomutoAleatorio = 0, TrocasChamadasLomutoMediana = 0;
        TrocasChamadasHoarePadrao = 0, TrocasChamadasHoareAleatorio = 0, TrocasChamadasHoareMediana = 0;
        for (int i = 0; i < qtdDeElementosVetor; i++)
        {
            int valor;
            fscanf(input, "%d", &valor);
            vetorDeNumerosLomutoPadrao[i] = valor;
            vetorDeNumerosLomutoAleatorio[i] = valor;
            vetorDeNumerosLomutoMediana[i] = valor;
            vetorDeNumerosHoarePadrao[i] = valor;
            vetorDeNumerosHoareAleatorio[i] = valor;
            vetorDeNumerosHoareMediana[i] = valor;
        }

        //Ordenações e suas respectivas siglas
        quicksortLomutoPadrao(vetorDeNumerosLomutoPadrao, 0, qtdDeElementosVetor - 1, &TrocasChamadasLomutoPadrao);
        vetorOrdenacoes[0].numeroChamadasTrocas = TrocasChamadasLomutoPadrao;
        strcpy(vetorOrdenacoes[0].tipo, "LP");
        quicksortLomutoMediana(vetorDeNumerosLomutoMediana, 0, qtdDeElementosVetor - 1, &TrocasChamadasLomutoMediana);
        vetorOrdenacoes[1].numeroChamadasTrocas = TrocasChamadasLomutoMediana;
        strcpy(vetorOrdenacoes[1].tipo, "LM");
        quicksortLomutoAleatorio(vetorDeNumerosLomutoAleatorio, 0, qtdDeElementosVetor - 1, &TrocasChamadasLomutoAleatorio);
        vetorOrdenacoes[2].numeroChamadasTrocas = TrocasChamadasLomutoAleatorio;
        strcpy(vetorOrdenacoes[2].tipo, "LA");
        quicksortHoarePadrao(vetorDeNumerosHoarePadrao, 0, qtdDeElementosVetor - 1, &TrocasChamadasHoarePadrao);
        vetorOrdenacoes[3].numeroChamadasTrocas = TrocasChamadasHoarePadrao;
        strcpy(vetorOrdenacoes[3].tipo, "HP");
        quicksortHoareMediana(vetorDeNumerosHoareMediana, 0, qtdDeElementosVetor - 1, &TrocasChamadasHoareMediana);
        vetorOrdenacoes[4].numeroChamadasTrocas = TrocasChamadasHoareMediana;
        strcpy(vetorOrdenacoes[4].tipo, "HM");
        quicksortHoareAleatorio(vetorDeNumerosHoareAleatorio, 0, qtdDeElementosVetor - 1, &TrocasChamadasHoareAleatorio);
        vetorOrdenacoes[5].numeroChamadasTrocas = TrocasChamadasHoareAleatorio;
        strcpy(vetorOrdenacoes[5].tipo, "HA");

        //Ordenação por meio do número de chamadas+trocas para a impressão
        mergeSort(vetorOrdenacoes, 0, 5);

        //Impressão
        fprintf(output, "%d:N(%d),%s(%d),%s(%d),%s(%d),%s(%d),%s(%d),%s(%d)\n", i, qtdDeElementosVetor, vetorOrdenacoes[0].tipo, vetorOrdenacoes[0].numeroChamadasTrocas, vetorOrdenacoes[1].tipo, vetorOrdenacoes[1].numeroChamadasTrocas, vetorOrdenacoes[2].tipo, vetorOrdenacoes[2].numeroChamadasTrocas, vetorOrdenacoes[3].tipo, vetorOrdenacoes[3].numeroChamadasTrocas, vetorOrdenacoes[4].tipo, vetorOrdenacoes[4].numeroChamadasTrocas, vetorOrdenacoes[5].tipo, vetorOrdenacoes[5].numeroChamadasTrocas);

        //Liberação de memória
        free(vetorDeNumerosLomutoPadrao);
        free(vetorDeNumerosLomutoAleatorio);
        free(vetorDeNumerosLomutoMediana);
        free(vetorDeNumerosHoarePadrao);
        free(vetorDeNumerosHoareAleatorio);
        free(vetorDeNumerosHoareMediana);
        free(vetorOrdenacoes);
    }
    fclose(input);
    fclose(output);
    return 0;
}
