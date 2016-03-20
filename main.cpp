#include "starpath.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StarPath w;
    w.show();

    return a.exec();
}
