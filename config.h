#ifndef CONFIG_H
#define CONFIG_H

#include <tipos.h>

/*Configurações de simulação */
#define DT_SIMULACAO 0.001 // seg(VAR_base)
#define AMOSTRAS_TEMPO 10  // (VAR_divisao_(3s./10isnt))

/*Parâmetros físicos Iniciais*/
#define GRAVIDADE_BASE 9.8 // m/s2(VAR_base(m/s'2))

#define MASSA_PADRAO 1.0  // kg(VAR_base(kg))

#define VELOCIDADE_INICIAL 25.0 // m/s(VAR_base(m/s))

#define ANGULO_LANCAMENTO 45.0 
// (VAR_base(g(n-const))__VAR_INFO(V(ox)=Vo*cos(0teta)))
// (VAR_base(g(n-const))__VAR_INFO(V(oy)=Vo*sin(0teta)))
// (VAR_base(0g - 90g /]S))

/*Configurações de Renderização*/
#define TELA_LARGURA 1000 // VAR_INFO(!const)
#define TELA_ALTURA 700 // VAR_INFO(!const)

#define ESCALA_METRO_PIXEL 40 // VAR_INFO(VAR_base(graphic_scale_40px))

/*Controle de Log*/
#define LOG_ATIVO 1

/*Estrutura Global de Configuração*/

typedef struct{
    /*fisico*/
    real gravidade_base;
    real massa;
    real velocidade_inicial;
    real angulo_graus;
    
    /*simulação*/
    real dt;
    int amostras_tempo;
    
    /*render*/
    int tela_largura;
    int tela_altura;
    int escala_metro_pixel;
    
    /*log*/
    int log_ativo;
} Configuracao;

/*Funções*/
void carregra_config_padrao(Configuracao *cfg);
void carregarcarregar_config_arquivo(Configuracao *cfg, const char *nome_arquivo);

#endif
