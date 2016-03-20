#ifndef STARPATH_H
#define STARPATH_H

#include <QMainWindow>
#include<QString>
#include<QTableWidgetItem>
#include<QFileDialog>
#include<QFile>
#include<QIntValidator>
#include<QDoubleValidator>
#include"celula.h"
#include "busca.h"

namespace Ui {
class StarPath;
}

class StarPath : public QMainWindow
{
    Q_OBJECT

public:
    explicit StarPath(QWidget *parent = 0);
    ~StarPath();
     Celula** mapa;
     void set_caracteristicas_mapa(int altura, int largura);
     int x_partida, x_chegada, y_chegada, y_partida;

private slots:
    void on_btn_confirmar_clicked();

    void on_actionAbrir_triggered();

    void carregar_arquivo(QString nome_do_arquivo);

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    static QString obstaculo_aleatorio();

   static  QString getObstaculo(int indice_do_obstaculo);

   static  int numero_aleatorio();

   void on_actionSalvar_triggered();

   void on_edt_horizontal_editingFinished();

   void on_edt_vertical_editingFinished();

  void on_actionCome_ar_triggered();

private:
    Ui::StarPath *ui;
    bool flag_partida;
    bool flag_chegada;
    bool flag_obs;
    int linha_partida;
    int coluna_partida;
    int linha_chegada;
    int coluna_chegada;
    int linha_obstaculo;
    int coluna_obstaculo;
    QIntValidator* int_validator;
    QDoubleValidator* double_validator;


};

#endif // STARPATH_H
