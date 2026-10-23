#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100

const char* classificarConsumo(double consumo, double limite) {
    if (consumo <= limite) {
        return "Dentro do limite";
    } else if (consumo <= limite * 1.20) {
        return "Atencao";
    } else {
        return "Critico";
    }
}

int processarEGerarRelatorio() {
    FILE *f_entrada = fopen("consumo_campus.txt", "r");
    if (f_entrada == NULL) {
        printf("\n[Erro] Nao foi possivel abrir 'consumo_campus.txt'. Crie o arquivo primeiro.\n");
        return 1;
    }

    char nome[MAX_NOME];
    double consumo = 0.0, limite = 0.0;

    int qtd_locais = 0;
    double consumo_total = 0.0;
    
    double maior_consumo = 0.0;
    char local_maior[MAX_NOME] = "";

    double menor_consumo = 0.0;
    char local_menor[MAX_NOME] = "";

    int qtd_alertas = 0;

    while (fscanf(f_entrada, "%s %lf %lf", nome, &consumo, &limite) == 3) {
        qtd_locais++;
        consumo_total += consumo;

        if (qtd_locais == 1 || consumo > maior_consumo) {
            maior_consumo = consumo;
            strcpy(local_maior, nome);
        }

        if (qtd_locais == 1 || consumo < menor_consumo) {
            menor_consumo = consumo;
            strcpy(local_menor, nome);
        }

        if (consumo > limite) {
            qtd_alertas++;
        }
    }
    fclose(f_entrada);

    if (qtd_locais == 0) {
        printf("\n[Aviso] O arquivo de entrada esta vazio.\n");
        return 0;
    }

    double consumo_medio = consumo_total / qtd_locais;

    printf("\n=========================================================================\n");
    printf("                       RELATORIO GERAL ECOCAMPUS                         \n");
    printf("=========================================================================\n");
    printf("Locais analisados: %d\n", qtd_locais);
    printf("Consumo total:     %.2f litros\n", consumo_total);
    printf("Consumo medio:     %.2f litros\n", consumo_medio);
    printf("Maior consumo:     %s (%.2f litros)\n", local_maior, maior_consumo);
    printf("Menor consumo:     %s (%.2f litros)\n", local_menor, menor_consumo);
    printf("Locais em alerta:  %d\n", qtd_alertas);
    printf("-------------------------------------------------------------------------\n");
    printf("%-20s | %-10s | %-10s | %-10s | %-15s\n", "LOCAL", "CONSUMO", "LIMITE", "EXCESSO", "CLASSIFICACAO");
    printf("-------------------------------------------------------------------------\n");

    f_entrada = fopen("consumo_campus.txt", "r");
    FILE *f_saida = fopen("relatorio_consumo.txt", "w");

    if (f_saida != NULL) {
        fprintf(f_saida, "ECOCAMPUS\n");
        fprintf(f_saida, "Locais analisados: %d\n", qtd_locais);
        fprintf(f_saida, "Consumo total: %.2f litros\n", consumo_total);
        fprintf(f_saida, "Consumo medio: %.2f litros\n", consumo_medio);
        fprintf(f_saida, "Maior consumo %s\n%.2f litros\n", local_maior, maior_consumo);
        fprintf(f_saida, "Menor consumo: %s (%.2f litros)\n", local_menor, menor_consumo);
        fprintf(f_saida, "Locais em alerta: %d\n\n", qtd_alertas);
        fprintf(f_saida, "DETALHAMENTO POR LOCAL:\n");
    }

    while (fscanf(f_entrada, "%s %lf %lf", nome, &consumo, &limite) == 3) {
        const char* classe = classificarConsumo(consumo, limite);
        double pct_excesso = 0.0;

        if (consumo > limite) {
            pct_excesso = ((consumo - limite) / limite) * 100.0;
            printf("%-20s | %8.2fL | %8.2fL | +%6.2f%%   | %-15s\n", nome, consumo, limite, pct_excesso, classe);
        } else {
            printf("%-20s | %8.2fL | %8.2fL |    0.00%%   | %-15s\n", nome, consumo, limite, classe);
        }

        if (f_saida != NULL) {
            if (consumo > limite) {
                fprintf(f_saida, "%s | Consumo: %.2fL | Limite: %.2fL | Excesso: +%.2f%% | Status: %s\n",
                        nome, consumo, limite, pct_excesso, classe);
            } else {
                fprintf(f_saida, "%s | Consumo: %.2fL | Limite: %.2fL | Status: %s\n",
                        nome, consumo, limite, classe);
            }
        }
    }

    fclose(f_entrada);
    if (f_saida != NULL) {
        fclose(f_saida);
        printf("-------------------------------------------------------------------------\n");
        printf("[Sucesso] Relatorio gravado em 'relatorio_consumo.txt'.\n");
    }

    return 0;
}

int adicionarRegistro() {
    FILE *f = fopen("consumo_campus.txt", "a");
    if (f == NULL) {
        printf("\n[Erro] Nao foi possivel abrir o arquivo para edicao.\n");
        return 1;
    }

    char nome[MAX_NOME];
    double consumo = 0.0, limite = 0.0;

    printf("\n--- ADICIONAR NOVO LOCAL ---\n");
    printf("Nome do local (sem espacos): ");
    scanf("%99s", nome);
    printf("Consumo em litros: ");
    scanf("%lf", &consumo);
    printf("Limite recomendado em litros: ");
    scanf("%lf", &limite);

    fprintf(f, "%s %.2f %.2f\n", nome, consumo, limite);
    fclose(f);

    printf("\n[Sucesso] Registro '%s' adicionado ao arquivo 'consumo_campus.txt'.\n", nome);
    return 0;
}

int consultarLocal() {
    char busca[MAX_NOME];
    printf("\nDigite o nome do local para consultar: ");
    scanf("%99s", busca);

    FILE *f = fopen("consumo_campus.txt", "r");
    if (f == NULL) {
        printf("\n[Erro] Nao foi possivel abrir 'consumo_campus.txt'.\n");
        return 1;
    }

    char nome[MAX_NOME];
    double consumo = 0.0, limite = 0.0;
    int encontrado = 0;

    while (fscanf(f, "%s %lf %lf", nome, &consumo, &limite) == 3) {
        if (strcmp(nome, busca) == 0) {
            encontrado = 1;
            const char* classe = classificarConsumo(consumo, limite);
            
            printf("\n-----------------------------------------\n");
            printf("RESULTADO DA CONSULTA: %s\n", nome);
            printf("-----------------------------------------\n");
            printf("Consumo medido:     %.2f litros\n", consumo);
            printf("Limite recomendado: %.2f litros\n", limite);
            printf("Classificacao:      %s\n", classe);

            if (consumo > limite) {
                double pct_excesso = ((consumo - limite) / limite) * 100.0;
                printf("Excesso registrado: +%.2f%%\n", pct_excesso);
            } else {
                printf("Situacao:           Dentro do limite permitido.\n");
            }
            printf("-----------------------------------------\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\n[Aviso] O local '%s' nao foi encontrado no arquivo.\n", busca);
    }

    fclose(f);
    return 0;
}

int main() {
    int opcao = 0;

    do {
        printf("\n=========================================\n");
        printf("       SISTEMA MONITOR ECOCAMPUS         \n");
        printf("=========================================\n");
        printf("1. Analisar Consumo e Gerar Relatorio\n");
        printf("2. Consultar Local por Nome\n");
        printf("3. Acrescentar Novo Registro ao Arquivo\n");
        printf("4. Sair\n");
        printf("Opcao desejada: ");
        
        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n');
            opcao = 0;
            continue;
        }

        switch (opcao) {
            case 1:
                processarEGerarRelatorio();
                break;
            case 2:
                consultarLocal();
                break;
            case 3:
                adicionarRegistro();
                break;
            case 4:
                printf("\nEncerrando o sistema. Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}