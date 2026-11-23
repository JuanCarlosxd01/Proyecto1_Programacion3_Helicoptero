#include <QApplication>
#include "VentanaPrincipal.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    VentanaPrincipal ventana;
    ventana.show();
    return app.exec();
}
