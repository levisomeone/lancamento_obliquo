#ifndef FISICA_H
#define FISICA_H

#include <tipos.h>
#include <config.h>

/*Estrutura Física*/
typedef struct{
    real t;
    real x;
    real y;
    real vx;
    real vy;
} EstadoFisico;

/*Dados Globais*/
typedef struct{
    real tempo_total;
    real distancia_total;
    real distancia_horizontal;
    real altura_maxima;
} ResultadoSimulacao;

/*Funções Físicas*/
void fisica_inicializar(EstadoFisico *estado, const Configuracao *cfg);

real gravidade(real y, real t, const Configuracao *cfg);

void fisica_passo(Estadofisico *estado, const Configuracao *cfg, real *distancia_acumulada, real *altura_maxima);

int fisica_atingiu_solo(const EstudoFisica *estado);

/*Simulação Completa*/
ResultadoSimulacao fisica_simular(const Configuracao *cfg);

#endif
