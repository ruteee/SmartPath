#ifndef MAPA_H
#define MAPA_H
#include <celula.h>


class Mapa
{
public:
    Mapa();
    Mapa(int altura, int largura);


private:
    Celula** celula;

};

#endif // MAPA_H
