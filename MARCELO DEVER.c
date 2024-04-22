#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define numero_alunos 100
#define numero_nomes 100
#define numero_notas 100

typedef struct {
    char nome[numero_nomes];
    char telefone[20];
    char curso[numero_nomes];
    float notas[numero_notas];
    int num_notas;
} Aluno;

float calcularMedia(float notas[], int num_notas) {
    float soma = 0;
    for (int i = 0; i < num_notas; i++) {
        soma += notas[i];
    }
    return soma / num_notas;
}

char* determinarSituacao(float media) {
    return media >= 7.0 ? "APROVADO" : "REPROVADO"; //O "?" É ULTILIZADO PRA DIZER "condição ? valor_se_verdadeiro : valor_se_falso"
}

int main() {
    FILE *entrada = fopen("DadosEntrada.csv", "r");
    FILE *saida = fopen("SituacaoFinal.csv", "w");


    Aluno alunos[numero_alunos];
    int num_alunos = 0;

    char linha[500]; 


    // LEITURA DAS LINHAS DO ARQUIVO
    while(fgets(linha, sizeof(linha), entrada) != NULL) {
        sscanf(linha, "%[^,],%[^,],%[^,],%f,%f", alunos[num_alunos].nome, alunos[num_alunos].telefone, alunos[num_alunos].curso, &alunos[num_alunos].notas[0], &alunos[num_alunos].notas[1]);

        alunos[num_alunos].num_notas = 2; // Sempre teremos duas notas para cada aluno
        num_alunos++ ;
    }

    for (int i = 0; i < num_alunos; i++) {
        //CALCULO DA MEDIA DOS ALUNOS
        float media = calcularMedia(alunos[i].notas, alunos[i].num_notas);

        if (alunos[i].num_notas == 0) {
        media = 0;
        }
        //SITUAÇÃO DO ALUNO
        char *situacao = determinarSituacao(media);
        //ESCREVER DADOS DOS ALUNOS
        fprintf(saida, "%s,%.2f,%s\n", alunos[i].nome, media, situacao);
    }

    fclose(entrada);
    fclose(saida);
    
    return 0;
}