#ifndef FONDONOCTURNO_H
#define FONDONOCTURNO_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QElapsedTimer>
#include <QPointF>

class FondoNocturno : public QWidget
{
    Q_OBJECT

public:
    explicit FondoNocturno(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

    void setSombraIzquierda(qreal fraccion);

private:
    void construirEscena();
    qreal alturaCresta(int capa, qreal x) const;
    void dibujarHelicoptero(QPainter &p, const QPointF &centro, qreal t);
    void dibujarReflector(QPainter &p, const QPointF &origen, qreal t);
    void dibujarBaliza(QPainter &p, qreal t, qreal luzReflector);

    QPixmap escena;
    QPixmap primerPlano;
    QTimer animacion;
    QElapsedTimer reloj;
    qreal sombraIzquierda;
    QPointF puntoLuz;
};

#endif