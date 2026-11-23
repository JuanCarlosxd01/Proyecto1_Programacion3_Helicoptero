#include "VistaJuego.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QFont>
#include <algorithm>

VistaJuego::VistaJuego(QWidget *parent)
    : QGraphicsView(parent),
    jugador(nullptr), obstaculos(nullptr), mensaje(nullptr),
    ultimoTick(0),
    arriba(false), abajo(false), izquierda(false), derecha(false),
    tiempo(0), combustible(100), jugando(false)
{
    setFixedSize(ANCHO + 2, ALTO + 2);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);
    setFocusPolicy(Qt::StrongFocus);

    escena = new QGraphicsScene(0, 0, ANCHO, ALTO, this);
    escena->setBackgroundBrush(QColor(40, 55, 80));
    setScene(escena);

    jugador = escena->addRect(0, 0, 40, 24, QPen(Qt::black), QBrush(QColor(90, 170, 100)));
    jugador->setZValue(2);

    mensaje = escena->addText("");
    mensaje->setDefaultTextColor(QColor(255, 220, 80));
    mensaje->setFont(QFont("Arial", 20, QFont::Bold));
    mensaje->setPos(ANCHO / 2 - 230, ALTO / 2 - 40);
    mensaje->setZValue(3);

    obstaculos = new QGraphicsRectItem*[NUM_OBSTACULOS];
    for (int i = 0; i < NUM_OBSTACULOS; i++)
        obstaculos[i] = nullptr;

    connect(&temporizador, &QTimer::timeout, this, &VistaJuego::bucleJuego);
}

VistaJuego::~VistaJuego()
{
    for (int i = 0; i < NUM_OBSTACULOS; i++)
        borrarObstaculo(i);
    delete[] obstaculos;
    obstaculos = nullptr;

}


void VistaJuego::iniciar()
{
    reiniciar();
    temporizador.start(16);
    reloj.start();
    ultimoTick = 0;
    setFocus();
}

void VistaJuego::detener()
{
    temporizador.stop();
    arriba = abajo = izquierda = derecha = false;
}

void VistaJuego::reiniciar()
{
    jugador->setPos(80, ALTO / 2.0);
    tiempo = 0;
    combustible = 100;
    jugando = true;
    mensaje->setPlainText("");
    arriba = abajo = izquierda = derecha = false;

    for (int i = 0; i < NUM_OBSTACULOS; i++) {
        borrarObstaculo(i);
        crearObstaculo(i, 400 + i * 180);
    }
    emit combustibleCambiado(100);
    emit tiempoCambiado(0);
}

void VistaJuego::crearObstaculo(int i, double x)
{
    int alto = 50 + QRandomGenerator::global()->bounded(120);
    int y    = QRandomGenerator::global()->bounded(ALTO - alto);

    obstaculos[i] = escena->addRect(0, 0, 30, alto, QPen(Qt::black),
                                    QBrush(QColor(150, 90, 70)));
    obstaculos[i]->setPos(x, y);
}

void VistaJuego::borrarObstaculo(int i)
{
    if (obstaculos[i] != nullptr) {
        escena->removeItem(obstaculos[i]);
        delete obstaculos[i];
        obstaculos[i] = nullptr;
    }
}

void VistaJuego::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) return;

    switch (event->key()) {
    case Qt::Key_Up:    case Qt::Key_W: arriba    = true; break;
    case Qt::Key_Down:  case Qt::Key_S: abajo     = true; break;
    case Qt::Key_Left:  case Qt::Key_A: izquierda = true; break;
    case Qt::Key_Right: case Qt::Key_D: derecha   = true; break;
    case Qt::Key_R:      reiniciar(); break;
    case Qt::Key_Escape: emit volverAlMenu(); break;
    default: QGraphicsView::keyPressEvent(event);
    }
}

void VistaJuego::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) return;

    switch (event->key()) {
    case Qt::Key_Up:    case Qt::Key_W: arriba    = false; break;
    case Qt::Key_Down:  case Qt::Key_S: abajo     = false; break;
    case Qt::Key_Left:  case Qt::Key_A: izquierda = false; break;
    case Qt::Key_Right: case Qt::Key_D: derecha   = false; break;
    default: QGraphicsView::keyReleaseEvent(event);
    }
}

void VistaJuego::bucleJuego()
{
    qint64 ahora = reloj.elapsed();
    double dt = (ahora - ultimoTick) / 1000.0;
    ultimoTick = ahora;
    if (dt > 0.05) dt = 0.05;

    if (!jugando) return;

    double dx = (derecha ? 1 : 0) - (izquierda ? 1 : 0);
    double dy = (abajo   ? 1 : 0) - (arriba    ? 1 : 0);
    double nx = jugador->x() + dx * VEL_JUGADOR * dt;
    double ny = jugador->y() + dy * VEL_JUGADOR * dt;
    nx = std::clamp(nx, 0.0, double(ANCHO) - jugador->rect().width());
    ny = std::clamp(ny, 0.0, double(ALTO)  - jugador->rect().height());
    jugador->setPos(nx, ny);

    for (int i = 0; i < NUM_OBSTACULOS; i++) {
        obstaculos[i]->moveBy(-VEL_OBSTACULO * dt, 0);

        if (obstaculos[i]->x() + obstaculos[i]->rect().width() < 0) {
            borrarObstaculo(i);
            crearObstaculo(i, ANCHO + QRandomGenerator::global()->bounded(120));
        }
        else if (jugador->collidesWithItem(obstaculos[i])) {
            combustible -= DANO_CHOQUE;
            borrarObstaculo(i);
            crearObstaculo(i, ANCHO + QRandomGenerator::global()->bounded(120));
        }
    }

    tiempo += dt;
    combustible -= GASTO_COMBUSTIBLE * dt;
    if (combustible <= 0) {
        combustible = 0;
        jugando = false;
        mensaje->setPlainText("¡Sin combustible!\nR: reintentar   Esc: menú");
    }


    emit tiempoCambiado(tiempo);
    emit combustibleCambiado(int(combustible));
}