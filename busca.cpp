#include "busca.h"
#include <vector>
#include <iostream>
#include <queue>
#include<stack>
#include <vector>
#include<functional>
#include<iostream>
#include<celula.h>
#include<QDebug>

using namespace std;

Busca::Busca()
{

}


void Busca::marcar_rota(Celula *celula)
{
    QIcon icon;
    Celula *p = celula->getPai();
    if (p->getTipo() != PARTIDA)
    {
        if (p->get_y() > celula->get_y())
        {
            if (p->get_x() > celula->get_x())
            {
                icon.addFile(QStringLiteral(":/imagens/imagens/no.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
            else if (p->get_x() < celula->get_x())
            {
                icon.addFile(QStringLiteral(":/imagens/imagens/so.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
            else
            {
                icon.addFile(QStringLiteral(":/imagens/imagens/o.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
        }
        else if (p->get_y() < celula->get_y())
        {
            if (p->get_x() > celula->get_x())
            {
                icon.addFile(QStringLiteral(":/imagens/imagens/nd.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
            else if (p->get_x() < celula->get_x())
            {
                icon.addFile(QStringLiteral(":/imagens/imagens/sd.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
            else
            {
                icon.addFile(QStringLiteral(":/imagens/imagens/l.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
        }
        else
        {
            if (p->get_x() > celula->get_x())
            {
                icon.addFile(QStringLiteral(":/imagens/imagens/n.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
            else
            {
                icon.addFile(QStringLiteral(":/imagens/imagens/s.png"), QSize(), QIcon::Normal, QIcon::Off);
            }
        }

        celula->getPai()->get_item()->setIcon(icon);
        celula->getPai()->get_item()->setBackgroundColor(Qt::green);
        if (celula->getTipo() == CHEGADA)
        {
            icon.addFile(QStringLiteral(":/imagens/imagens/chegada_2.png"), QSize(), QIcon::Normal, QIcon::Off);
            celula->get_item()->setIcon(icon);
            celula->get_item()->setBackgroundColor(Qt::green);
        }
        marcar_rota(celula->getPai());
    }
    else
    {
        icon.addFile(QStringLiteral(":/imagens/imagens/passada_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        p->get_item()->setIcon(icon);
        p->get_item()->setBackgroundColor(Qt::green);
    }
}

void Busca::A_estrela(Celula *partida, Celula* chegada, double peso_horizontal, double peso_vertical, double peso_diagonal){
    priority_queue<Celula*, std::vector<Celula*>, avaliar_custo> fila;

    std::queue<Celula*> lista_de_abertos;
    std::queue<Celula*> lista_de_fechados;

    Celula *aux;
    fila.push(partida);
    double custo_horizontal = peso_horizontal; //recebo da interface
    double custo_vertical = peso_vertical;
    double custo_diagonal = peso_diagonal;
    double g, f;
    QIcon visto;
    QIcon visitado;

    visitado.addFile(QStringLiteral(":/imagens/imagens/visitado.png"),QSize(), QIcon::Normal, QIcon::Off);
    visto.addFile(QStringLiteral(":/imagens/imagens/visto.png"),QSize(), QIcon::Normal, QIcon::Off);

    aux = fila.top();
    while(aux->getTipo()!= CHEGADA)
    {
        aux = fila.top();
        fila.pop();

        aux->get_item()->setToolTip("f: "+ QString::number(aux->get_f())+"\ng: "+ QString::number(aux->get_g())+"\nh: "+ QString::number(aux->get_h()));
        aux->get_item()->setIcon(visitado);
        aux->get_item()->setBackgroundColor(Qt::darkGreen);
        for(int i = 0; i < 8; i++){
            if(aux->vizinhos[i] != nullptr && aux->vizinhos[i]->getTipo() != OBS && aux->vizinhos[i]->getTipo()!= PARTIDA)
            {


                if(i == 0 || i == 4){
                    g = custo_vertical + aux->get_g();
                }else if(i == 2 || i == 6){
                    g = custo_horizontal + aux->get_g();
                }else{
                    g = custo_diagonal + aux->get_g();
                }


                aux->vizinhos[i]->set_h(calcular_heuristica(aux->vizinhos[i]->get_x(), aux->vizinhos[i]->get_y(), chegada->get_x(), chegada->get_y()));
                f = g + aux->vizinhos[i]->get_h();
                if(aux->vizinhos[i]->getPai() == nullptr
                        || (aux->vizinhos[i]->getPai()!= nullptr
                            && aux->vizinhos[i]->get_g() > g)){
                    if(aux->vizinhos[i] != aux->getPai()){

                        aux->vizinhos[i]->get_item()->setIcon(visto);
                        aux->vizinhos[i]->get_item()->setBackgroundColor(Qt::darkCyan);
                        aux->vizinhos[i]->setPai(aux);
                        aux->vizinhos[i]->set_g(g);
                        aux->vizinhos[i]->set_f(f);
                        aux->vizinhos[i]->get_item()->setToolTip("f: "+ QString::number(aux->vizinhos[i]->get_f())
                                                                 +"\ng: "+ QString::number(aux->vizinhos[i]->get_g())
                                                                 +"\nh: "+ QString::number(aux->vizinhos[i]->get_h()));
                        fila.push(aux->vizinhos[i]);

                    }
                }

            }
        }
        if(fila.empty()){
            break;
        }
    }
}

double Busca::calcular_heuristica(int x, int y, int x_chegada, int y_chegada){
    return sqrt(pow((x - x_chegada), 2) + pow((y - y_chegada), 2));
}
