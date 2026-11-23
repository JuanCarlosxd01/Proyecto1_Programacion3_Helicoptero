#include "VentanaPrincipal.h"
#include "MenuPrincipal.h"
#include "PantallaInstrucciones.h"
#include "VentanaJuego.h"
#include <QStackedWidget>
#include <QVBoxLayout>

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Ejemplo Qt - Pantallas, escena y teclado");
    resize(900, 560);

    menu = new MenuPrincipal(this);
    instrucciones = new PantallaInstrucciones(this);
    juego = new VentanaJuego(this);

    pila = new QStackedWidget(this);
    pila->addWidget(menu);
    pila->addWidget(instrucciones);
    pila->addWidget(juego);
    pila->setCurrentWidget(menu);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(pila);

    connect(menu, &MenuPrincipal::jugar, this, [this]() {
        pila->setCurrentWidget(juego);
        juego->iniciar();
    });
    connect(menu, &MenuPrincipal::instrucciones, this, [this]() {
        pila->setCurrentWidget(instrucciones);
    });
    connect(menu, &MenuPrincipal::salir, this, &QWidget::close);

    connect(instrucciones, &PantallaInstrucciones::volver, this, [this]() {
        pila->setCurrentWidget(menu);
    });
    connect(juego, &VentanaJuego::volverAlMenu, this, [this]() {
        juego->detener();
        pila->setCurrentWidget(menu);
    });
}