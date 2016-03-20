#include "starpath.h"
#include "ui_starpath.h"
#include"celula.h"
#include"mapa.h"
#include"stdlib.h"
#include"time.h"
#include <QTextStream>
#include <QDebug>
#include <QtMath>
#include <iostream>
#include <cstddef>

StarPath::StarPath(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StarPath)
{
    ui->setupUi(this);

    flag_partida = false;
    flag_chegada = false;
    flag_obs = false;
    linha_partida = -1;
    coluna_partida = -1;
    linha_chegada = -1;
    coluna_chegada = -1;
    linha_obstaculo = -1;
    coluna_obstaculo =-1;

    int_validator = new QIntValidator();
    double_validator = new QDoubleValidator();

    ui->edt_altura->setValidator(int_validator);
    ui->edt_largura->setValidator(int_validator);
    ui->edt_diagonal->setValidator(double_validator);
    ui->edt_vertical->setValidator(double_validator);
    ui->edt_horizontal->setValidator(double_validator);
}

StarPath::~StarPath()
{
    delete ui;
}

void StarPath::on_btn_confirmar_clicked(){
    flag_chegada = false;
    flag_obs = false;
    flag_partida = false;
    ui->tableWidget->setRowCount(ui->edt_altura->text().toInt());
    ui->tableWidget->setColumnCount(ui->edt_largura->text().toInt());

    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(50);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50);

    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();

    int altura = ui->edt_altura->text().toInt();
    int largura = ui->edt_largura->text().toInt();

    mapa = new Celula*[altura];

    for(int i = 0; i < altura; i++){
        mapa[i] = new Celula[largura];
    }

    set_caracteristicas_mapa(altura, largura);
}

void StarPath::on_actionAbrir_triggered()
{
    QString nome_do_arquivo = QFileDialog::getOpenFileName(this);
    if(!nome_do_arquivo.isEmpty())
        carregar_arquivo(nome_do_arquivo);
}


void StarPath::carregar_arquivo(QString nome_do_arquivo){
    QFile file(nome_do_arquivo);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream reader(&file);

    int altura, largura;
    float custo_horizontal, custo_vertical;
    reader >> altura >> largura >> custo_horizontal >> custo_vertical;
    int mapa_arquivo[altura][largura];

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            reader >> mapa_arquivo[i][j];
        }
    }

    ui->edt_altura->setText(QString::number(altura));
    ui->edt_largura->setText(QString::number(largura));
    ui->edt_horizontal->setText(QString::number(custo_horizontal));
    ui->edt_vertical->setText(QString::number(custo_vertical));
    ui->edt_diagonal->setText(QString::number(qSqrt(qPow(custo_horizontal, 2) + qPow(custo_vertical, 2)),'g', 3));

    flag_chegada = false;
    flag_obs = false;
    flag_partida = false;

    ui->tableWidget->setRowCount(ui->edt_altura->text().toInt());
    ui->tableWidget->setColumnCount(ui->edt_largura->text().toInt());
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();

    QIcon *icone;


    mapa = new Celula*[altura];
    for(int i = 0; i < altura; i++){
        mapa[i] = new Celula[largura];
    }

    set_caracteristicas_mapa(altura, largura);


    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            icone = new QIcon();
            if(mapa_arquivo[i][j] == 0){
                mapa[i][j].setTipo(LIVRE);
                icone->addFile((":"), QSize(), QIcon::Normal, QIcon::Off);

            }else if(mapa_arquivo[i][j] == 1){
                mapa[i][j].setTipo(OBS);
                QString obstaculo = obstaculo_aleatorio();
                QString caminho = ":/imagens/imagens/";
                icone->addFile(caminho.append(obstaculo), QSize(), QIcon::Normal, QIcon::Off);

            }else if(mapa_arquivo[i][j] == 2){
                mapa[i][j].setTipo(PARTIDA);
                icone->addFile(QStringLiteral(":/imagens/imagens/passada_1"), QSize(), QIcon::Normal, QIcon::Off);
                x_partida = i;
                y_partida = j;
             //   mapa[x_partida][y_partida].setPai(&mapa[x_partida][y_partida]);
            }
            else{
                mapa[i][j].setTipo(CHEGADA);
                icone->addFile(QStringLiteral(":/imagens/imagens/chegada_2"), QSize(), QIcon::Normal, QIcon::Off);
                x_chegada = i;
                y_chegada = j;
            }

            mapa[i][j].get_item()->setIcon(*icone);

        }


    }

    //     qDebug() << altura << " " << largura << " " << custo_horizontal << " " << custo_vertical << " ";
    //     for (int i = 0; i < altura; i++) {
    //         for (int j = 0; j < largura; j++) {
    //             qDebug() << mapa[i][j];
    //         }
    //     }
}

int StarPath::numero_aleatorio(){
    srand(time(NULL));
    return rand()%9 + 1;
}

QString StarPath::getObstaculo(int indice_do_obstaculo){

    QString obstaculo;
    switch(indice_do_obstaculo){

    case 1:
        obstaculo = "obs_1";
        break;

    case 2:
        obstaculo = "obs_2";
        break;

    case 3:
        obstaculo = "obs_3";
        break;

    case 4:
        obstaculo ="obs_4";
        break;

    case 5:
        obstaculo = "obs_5";
        break;

    case 6:
        obstaculo = "obs_6";
        break;

    case 7:
        obstaculo = "obs_7";
        break;

    case 8:
        obstaculo = "obs_8";
        break;

    case 9:
        obstaculo = "obs_9";
        break;
    }
    return obstaculo;
}

QString StarPath::obstaculo_aleatorio(){

    return getObstaculo(numero_aleatorio());
}


void StarPath::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    QIcon icone;

    int x  = item->row();
    int y = item->column();

    if(ui->radioBtn_partida->isChecked()&&linha_partida == item->row()
            && coluna_partida == item->column() &&flag_partida){
        flag_partida = false;
        icone.addFile((":"), QSize(), QIcon::Normal, QIcon::Off);
        mapa[x][y].setTipo(1);
        x_partida = -1;
        y_partida = -1;

    }else if(ui->radioBtn_partida->isChecked()&&!flag_partida){
        icone.addFile(QStringLiteral(":/imagens/imagens/passada_1"), QSize(), QIcon::Normal, QIcon::Off);
        flag_partida = true;
        linha_partida = item->row();
        coluna_partida = item->column();
        mapa[x][y].setTipo(3);
     //   mapa[x][y].setPai(&mapa[x][y]);
        x_partida = x;
        y_partida = y;
    }

    if(ui->radioBtn_chegada->isChecked()&&linha_chegada == item->row()
            && coluna_chegada == item->column() &&flag_chegada){
        flag_chegada = false;
        icone.addFile((":"), QSize(), QIcon::Normal, QIcon::Off);
        mapa[x][y].setTipo(1);
        x_chegada= -1;
        y_chegada = -1;
    }else if (ui->radioBtn_chegada->isChecked()&&!flag_chegada){
        icone.addFile(QStringLiteral(":/imagens/imagens/chegada_2"), QSize(), QIcon::Normal, QIcon::Off);
        flag_chegada = true;
        mapa[x][y].setTipo(4);
        linha_chegada = item->row();
        coluna_chegada = item->column();

        x_chegada = x;
        y_chegada = y;
    }

    if(ui->raadioBtn_Obstaculos->isChecked()&&linha_obstaculo == item->row()
            && coluna_obstaculo == item->column() &&flag_obs){
        flag_obs = false;
        icone.addFile((":"), QSize(), QIcon::Normal, QIcon::Off);
        mapa[x][y].setTipo(1);
    }else if (ui->raadioBtn_Obstaculos->isChecked()){
        QString obstaculo = obstaculo_aleatorio();
        QString caminho = ":/imagens/imagens/";
        icone.addFile(caminho.append(obstaculo), QSize(), QIcon::Normal, QIcon::Off);
        linha_obstaculo = item->row();
        coluna_obstaculo = item->column();

        mapa[x][y].setTipo(2);
        flag_obs = true;
    }

    item->setIcon(icone);


}


void StarPath::on_actionSalvar_triggered()
{
    QString nomeArquivo = QFileDialog::getSaveFileName(this);
    QFile file(nomeArquivo);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    int altura = ui->edt_altura->text().toInt(), largura = ui->edt_largura->text().toInt();

    out << ui->edt_altura->text() << " "
        << ui->edt_largura->text() << " "
        << ui->edt_horizontal->text() << " "
        << ui->edt_vertical->text() << "\n";

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++){


            out << mapa[i][j].getTipo() - 1 << " ";
        }
        out << "\n";
    }
}

void StarPath::on_edt_horizontal_editingFinished()
{
    if(ui->edt_vertical->text() != ""){
        ui->edt_diagonal->setText(QString::number(qSqrt(qPow(ui->edt_vertical->text().toDouble(), 2) + qPow(ui->edt_horizontal->text().toDouble(), 2)),'g', 3));
    }
}

void StarPath::on_edt_vertical_editingFinished()
{
    if(ui->edt_horizontal->text() != ""){
        ui->edt_diagonal->setText(QString::number(qSqrt(qPow(ui->edt_vertical->text().toDouble(), 2) + qPow(ui->edt_horizontal->text().toDouble(), 2)),'g', 3));
    }
}

void StarPath::on_actionCome_ar_triggered()
{
    Busca *busca = new Busca();
    busca->A_estrela(&mapa[x_partida][y_partida], &mapa[x_chegada][y_chegada], ui->edt_horizontal->text().toDouble(),
                     ui->edt_vertical->text().toDouble(), ui->edt_diagonal->text().toDouble());

    if(mapa[x_chegada][y_chegada].getPai() != nullptr)
        busca->marcar_rota(&mapa[x_chegada][y_chegada]);

}


void StarPath::set_caracteristicas_mapa(int altura, int largura){

    QTableWidgetItem* item;
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            item = new QTableWidgetItem();
            ui->tableWidget->setItem(i, j, item);
            mapa[i][j].set_item(item);
            mapa[i][j].set_x(i);
            mapa[i][j].set_y(j);
            mapa[i][j].setPai(nullptr);
            mapa[i][j].setTipo(LIVRE);
            mapa[i][j].set_g(0);
            //mapa[i][i].set_f(0);

            if( (j - 1) < 0 && (i -1) < 0){
                mapa[i][j].vizinhos[0] = nullptr;
                mapa[i][j].vizinhos[1] = nullptr;
                mapa[i][j].vizinhos[2] = &mapa[i][j+1];
                mapa[i][j].vizinhos[3] = &mapa[i+1][j+1];
                mapa[i][j].vizinhos[4] = &mapa[i+1][j];
                mapa[i][j].vizinhos[5] = nullptr;
                mapa[i][j].vizinhos[6] = nullptr;
                mapa[i][j].vizinhos[7] = nullptr;
            }else if((j+1) > largura && (i-1) < 0){

                mapa[i][j].vizinhos[0] = nullptr;
                mapa[i][j].vizinhos[1] = nullptr;
                mapa[i][j].vizinhos[2] = nullptr;
                mapa[i][j].vizinhos[3] = nullptr;
                mapa[i][j].vizinhos[4] = &mapa[i+1][j];
                mapa[i][j].vizinhos[5] = &mapa[i+1][j-1];
                mapa[i][j].vizinhos[6] = &mapa[i][j-1];
                mapa[i][j].vizinhos[7] = nullptr;

            }else if(((i+1) > altura -1) && (j+ 1) > (largura -1)){

                mapa[i][j].vizinhos[0] = &mapa[i-1][j];
                mapa[i][j].vizinhos[1] = nullptr;
                mapa[i][j].vizinhos[2] = nullptr;
                mapa[i][j].vizinhos[3] = nullptr;
                mapa[i][j].vizinhos[4] = nullptr;
                mapa[i][j].vizinhos[5] = nullptr;
                mapa[i][j].vizinhos[6] = &mapa[i][j-1];
                mapa[i][j].vizinhos[7] = &mapa[i-1][j-1];

            }else if((j -1) < 0 && (i+1) > altura -1){

                mapa[i][j].vizinhos[0] = &mapa[i-1][j];
                mapa[i][j].vizinhos[1] = &mapa[i-1][j+1];
                mapa[i][j].vizinhos[2] = &mapa[i][j+1];
                mapa[i][j].vizinhos[3] = nullptr;
                mapa[i][j].vizinhos[4] = nullptr;
                mapa[i][j].vizinhos[5] = nullptr;
                mapa[i][j].vizinhos[6] = nullptr;
                mapa[i][j].vizinhos[7] = nullptr;

            }else if((i -1) < 0 && (j-1) >= 0){

                mapa[i][j].vizinhos[0] = nullptr;
                mapa[i][j].vizinhos[1] = nullptr;
                mapa[i][j].vizinhos[2] = &mapa[i][j+1];
                mapa[i][j].vizinhos[3] = &mapa[i+1][j+1];
                mapa[i][j].vizinhos[4] = &mapa[i+1][j];
                mapa[i][j].vizinhos[5] = &mapa[i+1][j-1];
                mapa[i][j].vizinhos[6] = &mapa[i][j-1];
                mapa[i][j].vizinhos[7] = nullptr;

            }else if((i+1) > (altura - 1) && (j-1) >= 0){

                mapa[i][j].vizinhos[0] = &mapa[i-1][j];
                mapa[i][j].vizinhos[1] = &mapa[i-1][j+1];
                mapa[i][j].vizinhos[2] = &mapa[i][j+1];
                mapa[i][j].vizinhos[3] = nullptr;
                mapa[i][j].vizinhos[4] = nullptr;
                mapa[i][j].vizinhos[5] = nullptr;
                mapa[i][j].vizinhos[6] = &mapa[i][j-1];
                mapa[i][j].vizinhos[7] = &mapa[i-1][j-1];
            }else if((j-1) < 0 && (i +1) > 0){

                mapa[i][j].vizinhos[0] = &mapa[i-1][j];
                mapa[i][j].vizinhos[1] = &mapa[i-1][j+1];
                mapa[i][j].vizinhos[2] = &mapa[i][j+1];
                mapa[i][j].vizinhos[3] = &mapa[i+1][j+1];
                mapa[i][j].vizinhos[4] = &mapa[i+1][j];
                mapa[i][j].vizinhos[5] = nullptr;
                mapa[i][j].vizinhos[6] = nullptr;
                mapa[i][j].vizinhos[7] = nullptr;

            }else if((j+1) > (largura -1) && (i+1) > 0){

                mapa[i][j].vizinhos[0] = nullptr;
                mapa[i][j].vizinhos[1] = nullptr;
                mapa[i][j].vizinhos[2] = nullptr;
                mapa[i][j].vizinhos[3] = &mapa[i+1][j+1];
                mapa[i][j].vizinhos[4] = &mapa[i+1][j];
                mapa[i][j].vizinhos[5] = &mapa[i+1][j-1];
                mapa[i][j].vizinhos[6] = &mapa[i][j-1];
                mapa[i][j].vizinhos[7] = &mapa[i-1][j-1];
            }else{

                mapa[i][j].vizinhos[0] = &mapa[i-1][j];
                mapa[i][j].vizinhos[1] = &mapa[i-1][j+1];
                mapa[i][j].vizinhos[2] = &mapa[i][j+1];
                mapa[i][j].vizinhos[3] = &mapa[i+1][j+1];
                mapa[i][j].vizinhos[4] = &mapa[i+1][j];
                mapa[i][j].vizinhos[5] = &mapa[i+1][j-1];
                mapa[i][j].vizinhos[6] = &mapa[i][j-1];
                mapa[i][j].vizinhos[7] = &mapa[i-1][j-1];
            }

        }
    }
}
