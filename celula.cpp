#include "celula.h"

Celula::Celula()
{

}

/*Celula::Celula(int linha, int coluna){

    this->linha = linha;
    this->coluna = coluna;
}*/


void Celula::setPai(Celula *pai){
    this->pai = pai;
}

Celula* Celula::getPai(){
    return this->pai;
}

int Celula::get_x(){
    return this->x;
}

int Celula::get_y(){
    return this->y;

}

void Celula::set_x(int x){
    this->x = x;
}

void Celula::set_y(int y){
    this->y = y;
}

void Celula::setTipo(int tipo){

    if(tipo == 1)
        this->tipo = LIVRE;
    if(tipo == 2)
        this->tipo = OBS;
    if(tipo == 3)
        this->tipo = PARTIDA;
    if(tipo == 4)
        this->tipo = CHEGADA;
}


int Celula::getTipo(){
    return this->tipo;
}

void Celula::set_h(double h){
    this->h = h;
}

double Celula::get_h(){
    return this->h;
}

void Celula::set_g(double g){
    this->g = g;
}

double Celula::get_g(){
    return this->g;
}


void Celula::set_f(double f){
    this->f = f;
}

double Celula::get_f() const{
    return this->f;
}

QTableWidgetItem *Celula::get_item()
{
    return this->item;
}

void Celula::set_item(QTableWidgetItem *item)
{
    this->item = item;
}









