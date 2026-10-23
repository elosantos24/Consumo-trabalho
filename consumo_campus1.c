#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100

int main(void) {

    char nome[MAX_NOME];
    double consumo = 0.0;
    double limite = 0.0;

    int qtd_locais = 0;
    double consumo_total = 0.0;
    double consumo_medio = 0.0;
    
    double maior_consumo = 0.0;
    char local_maior_consumo[MAX_NOME] = "";
    
    int qtd_alertas = 0;

    FILE *f_entrada = fopen("consumo_campus.txt", "r");
    
    if (f_entrada == NULL) {
        printf("Erro: Nao foi possivel abrir o ficheiro 'consumo_campus.txt'.\n");
        printf("Certifique-se de que o ficheiro se encontra na mesma pasta do programa.\n");
        return 1;
    }


    while (fscanf(f_entrada, "%s %lf %lf", nome, &consumo, &limite) == 3) {
        qtd_locais++;
        consumo_total += consumo;

        if (qtd_locais == 1 || consumo > maior_consumo) {
            maior_consumo = consumo;
            strcpy(local_maior_consumo, nome);
        }

        if (consumo > limite) {
            qtd_alertas++;
        }
    }

    fclose(f_entrada);

    if (qtd_locais > 0) {
        consumo_medio = consumo_total / qtd_locais;
    }

    printf("ECOCAMPUS\n");
    printf("Locais analisados: %d\n", qtd_locais);
    printf("Consumo total: %.2f litros\n", consumo_total);
    printf("Consumo medio: %.2f litros\n", consumo_medio);
    if (qtd_locais > 0) {
        printf("Maior consumo %s\n%.2f litros\n", local_maior_consumo, maior_consumo);
    } else {
        printf("Maior consumo: N/A\n");
    }
    printf("Locais em alerta: %d\n", qtd_alertas);

    FILE *f_saida = fopen("relatorio_consumo.txt", "w");
    if (f_saida == NULL) {
        printf("\nErro: Nao foi possivel criar o ficheiro 'relatorio_consumo.txt'.\n");
        return 1;
    }

    fprintf(f_saida, "ECOCAMPUS\n");
    fprintf(f_saida, "Locais analisados: %d\n", qtd_locais);
    fprintf(f_saida, "Consumo total: %.2f litros\n", consumo_total);
    fprintf(f_saida, "Consumo medio: %.2f litros\n", consumo_medio);
    if (qtd_locais > 0) {
        fprintf(f_saida, "Maior consumo %s\n%.2f litros\n", local_maior_consumo, maior_consumo);
    } else {
        fprintf(f_saida, "Maior consumo: N/A\n");
    }
    fprintf(f_saida, "Locais em alerta: %d\n", qtd_alertas);

    fclose(f_saida);

    printf("\n[Sucesso] Relatorio gravado em 'relatorio_consumo.txt'.\n");

    return 0;
}