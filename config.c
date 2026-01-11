#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <config.h>

/*Configuração Padrão*/
void carregar_config_padrao(Configuracao * cfg){
    /*fisicos*/
    cfg->gravidade_base = GRAVIDADE_BASE;
    cfg->massa = MASSA_PADRAO;
    cfg->velocidade-inicial = VELOCIDADE_INICIAL;
    cfg->angulo_graus = ANGULO_LANCAMENTO;
    /*simulacao*/
    cfg->dt = DT_SIMULACAO;
    cfg->amostras_tempo = AMOSTRAS_TEMPO;
    /*render*/
    cfg->tela_largura = TELA_LARGURA;
    cfg->tela_altura = TELA_ALTURA;
    cfg->escala_metro_pixel = ESCALA_METRO_PIXEL;
    /*log*/
    cfg->log_ativo = LOG_ATIVO;
    
    /*Leitura de Configurações .TXT*/
    /*Format
        gravidade
        massa
        velocidade
        angulo
        dt
        amostras
    */
    
int carregar_config_arquivo(Configuracao *cfg, const char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(!arquivo){
        return 0;
    }
    char linha[128];
    char chave[64];
    double valor;
    
    while(fgets(linha, sizeof(linha), arquivo)){
        if(linha[0] == '#' || linha[0] == '\n'){
            continue;
        }
        if (sscanf(linha, "%63[^=]=%lf", chave, &valor) == 2) {

            if (strcmp(chave, "gravidade") == 0)
                cfg->gravidade_base = valor;

            else if (strcmp(chave, "massa") == 0)
                cfg->massa = valor;

            else if (strcmp(chave, "velocidade") == 0)
                cfg->velocidade_inicial = valor;

            else if (strcmp(chave, "angulo") == 0)
                cfg->angulo_graus = valor;

            else if (strcmp(chave, "dt") == 0)
                cfg->dt = valor;

            else if (strcmp(chave, "amostras") == 0)
                cfg->amostras_tempo = (int)valor;

        }
    }
    fclose(arquivo);
    return 1;
}
