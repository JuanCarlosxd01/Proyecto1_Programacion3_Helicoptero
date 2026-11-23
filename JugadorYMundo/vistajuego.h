#ifndef VISTAJUEGO_H
#define VISTAJUEGO_H

#include <QGraphicsView>
#include <QElapsedTimer>
#include <QTimer>

class QGraphicsScene;
class QGraphicsRectItem;
class QGraphicsTextItem;
class QKeyEvent;


class VistaJuego : public QGraphicsView
{
    Q_OBJECT

public:
    explicit VistaJuego(QWidget *parent = nullptr);
    ~VistaJuego() override;

    void iniciar();
    void detener();

signals:
    void tiempoCambiado(double segundos);
    void combustibleCambiado(int porcentaje);
    void volverAlMenu();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void bucleJuego();

private:
    void reiniciar();
    void crearObstaculo(int indice, double x);
    void borrarObstaculo(int indice);

    static constexpr int    ANCHO = 800;
    static constexpr int    ALTO  = 450;
    static constexpr int    NUM_OBSTACULOS = 5;
    static constexpr double VEL_JUGADOR   = 250.0;
    static constexpr double VEL_OBSTACULO = 140.0;
    static constexpr double GASTO_COMBUSTIBLE = 4.0;
    static constexpr double DANO_CHOQUE = 20.0;

    QGraphicsScene    *escena;
    QGraphicsRectItem *jugador;
    QGraphicsRectItem **obstaculos;
    QGraphicsTextItem *mensaje;

    QTimer        temporizador;
    QElapsedTimer reloj;
    qint64        ultimoTick;

    bool arriba, abajo, izquierda, derecha;

    double tiempo;
    double combustible;
    bool   jugando;
};

#endif // VISTAJUEGO_H