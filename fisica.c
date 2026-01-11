#include "fisica.h"
#include <math.h>
/*Funções Auxiliares*/

static real graus_para_radianos(real graus) {
    return graus * (real)M_PI / (real)180.0;
}


/*Inicialização*/

void fisica_inicializar(EstadoFisico *estado, const Configuracao *cfg) {
    real angulo_rad = graus_para_radianos(cfg->angulo_graus);

    estado->t = 0.0;

    estado->x = 0.0;
    estado->y = 0.0;

    estado->vx = cfg->velocidade_inicial * cos(angulo_rad);
    estado->vy = cfg->velocidade_inicial * sin(angulo_rad);
}


/*Gravidade*/
real gravidade(real y, real t, const Configuracao *cfg) {
    // Exemplo de modelo simples:
    // gravidade diminui levemente com a altura
    real fator_altura = 1.0 - 0.0001 * y;

    if (fator_altura < 0.5)
        fator_altura = 0.5;

    return cfg->gravidade_base * fator_altura;
}


/*Passo da Simulação*/

void fisica_passo(EstadoFisico *estado,
                  const Configuracao *cfg,
                  real *distancia_acumulada,
                  real *altura_maxima) {

    real g = gravidade(estado->y, estado->t, cfg);

    /* aceleração */
    real ax = 0.0;
    real ay = -g;

    /* salva posição anterior */
    real x_ant = estado->x;
    real y_ant = estado->y;

    /* atualiza velocidades */
    estado->vx += ax * cfg->dt;
    estado->vy += ay * cfg->dt;

    /* atualiza posições */
    estado->x += estado->vx * cfg->dt;
    estado->y += estado->vy * cfg->dt;

    /* atualiza tempo */
    estado->t += cfg->dt;

    /* acumula distância percorrida */
    real dx = estado->x - x_ant;
    real dy = estado->y - y_ant;
    *distancia_acumulada += sqrt(dx * dx + dy * dy);

    /* atualiza altura máxima */
    if (estado->y > *altura_maxima)
        *altura_maxima = estado->y;
}


/*ConCondições de Parada*/

int fisica_atingiu_solo(const EstadoFisico *estado) {
    return (estado->y <= 0.0 && estado->t > 0.0);
}


/*Simulação Completa*/
ResultadoSimulacao fisica_simular(const Configuracao *cfg) {

    EstadoFisico estado;
    ResultadoSimulacao resultado;

    real distancia_total = 0.0;
    real altura_maxima = 0.0;

    fisica_inicializar(&estado, cfg);

    while (!fisica_atingiu_solo(&estado)) {
        fisica_passo(&estado, cfg, &distancia_total, &altura_maxima);
    }

    resultado.tempo_total = estado.t;
    resultado.distancia_total = distancia_total;
    resultado.distancia_horizontal = estado.x;
    resultado.altura_maxima = altura_maxima;

    return resultado;
}
