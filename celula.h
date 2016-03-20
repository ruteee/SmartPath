 #ifndef CELULA_H
#include <QString>
#include<QTableWidgetItem>
#include <functional>
#define CELULA_H

#define LIVRE 1
#define OBS 2
#define PARTIDA 3
#define CHEGADA 4

class Celula
{
public:
    Celula();
   // Celula(int linha, int coluna);

    void setPai(Celula* pai);
    Celula* getPai();

    Celula* getCelula(int linha, int coluna);

    Celula* vizinhos[8];
    void setTipo(int tipo);
    int getTipo();
    void set_h(double h);
    double get_h();
    void set_g(double g);
    double get_g();
    void set_f(double f);
    int get_x();
    int get_y();
    void set_x(int x);
    void set_y(int y);
    double get_f() const;
    QTableWidgetItem *get_item();
    void set_item(QTableWidgetItem *item);

    double f, g, h;


private:

   Celula* pai;
   QTableWidgetItem *item;
   //int linha;
   //int coluna;
   int tipo;
   int x, y;
};

struct avaliar_custo : public std::binary_function<Celula*, Celula*, bool>
{
    bool operator()(const Celula* lhs, const Celula* rhs) const
    {
        return lhs->get_f() > rhs->get_f();
    }
};

#endif // CELULA_H
