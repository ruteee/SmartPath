#ifndef BUSCA_H
#define BUSCA_H
#include<QString>
#include<celula.h>

#include <queue>
#include<stack>
#include <vector>
#include<functional>
#include<iostream>

class Busca
{
public:
    Busca();

    void marcar_rota(Celula *celula);
    void A_estrela(Celula* partida, Celula* chegada, double peso_vertical, double peso_horizontal, double peso_diagonal);
    double calcular_heuristica(int x, int y_, int x_chegada, int y_chegada);

};

#endif // BUSCA_H
