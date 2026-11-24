#include <QApplication>
#include "ventanaprincipal.h"
#include "fuentes.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Fuentes::cargar();

    VentanaPrincipal ventana;
    ventana.show();
    return app.exec();
}