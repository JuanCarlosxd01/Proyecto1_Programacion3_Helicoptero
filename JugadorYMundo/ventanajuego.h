#ifndef VENTANAJUEGO_H
#define VENTANAJUEGO_H

#include <QWidget>

class VistaJuego;
class QLabel;
class QProgressBar;

class VentanaJuego : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaJuego(QWidget *parent = nullptr);

    void iniciar();
    void detener();

signals:
    void volverAlMenu();

private:
    VistaJuego   *vista;
    QLabel       *lblTiempo;
    QProgressBar *barraCombustible;
};

#endif // VENTANAJUEGO_H