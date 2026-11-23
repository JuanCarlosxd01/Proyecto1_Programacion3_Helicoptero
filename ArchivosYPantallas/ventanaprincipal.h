#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QWidget>

class QStackedWidget;
class MenuPrincipal;
class PantallaInstrucciones;
class VentanaJuego;

class VentanaPrincipal : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget *parent = nullptr);

private:
    QStackedWidget *pila;
    MenuPrincipal *menu;
    PantallaInstrucciones *instrucciones;
    VentanaJuego *juego;
};

#endif // VENTANAPRINCIPAL_H
