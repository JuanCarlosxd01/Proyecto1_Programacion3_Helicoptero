#include "tecla.h"
#include "fuentes.h"
#include "paleta.h"
#include <QPainter>
#include <QPainterPath>
#include <QFontMetrics>

Tecla::Tecla(const QString &texto, QWidget *parent)
    : QWidget(parent), texto(texto), flecha(Ninguna)
{
    QFontMetrics fm(Fuentes::textoFuerte(14));
    setFixedSize(qMax(34, fm.horizontalAdvance(texto) + 22), 34);
}

Tecla::Tecla(Flecha flecha, QWidget *parent)
    : QWidget(parent), flecha(flecha)
{
    setFixedSize(34, 34);
}

void Tecla::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const QRectF base = QRectF(rect()).adjusted(0.5, 0.5, -0.5, -0.5);
    const QRectF cara = base.adjusted(0, 0, 0, -4);

    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0x0b, 0x0a, 0x1a, 200));
    p.drawRoundedRect(base, 6, 6);

    p.setBrush(QColor(0x2a, 0x24, 0x48, 235));
    p.setPen(QPen(QColor(0x4a, 0x42, 0x70), 1));
    p.drawRoundedRect(cara, 6, 6);

    p.setPen(Paleta::hueso);
    p.setBrush(Paleta::hueso);

    if (flecha == Ninguna) {
        p.setFont(Fuentes::textoFuerte(14));
        p.drawText(cara, Qt::AlignCenter, texto);
        return;
    }

    const QPointF c = cara.center();
    const qreal k = 5.5;
    QPainterPath tri;
    switch (flecha) {
    case Arriba:
        tri.moveTo(c.x(), c.y() - k); tri.lineTo(c.x() + k, c.y() + k * 0.6); tri.lineTo(c.x() - k, c.y() + k * 0.6);
        break;
    case Abajo:
        tri.moveTo(c.x(), c.y() + k); tri.lineTo(c.x() + k, c.y() - k * 0.6); tri.lineTo(c.x() - k, c.y() - k * 0.6);
        break;
    case Izquierda:
        tri.moveTo(c.x() - k, c.y()); tri.lineTo(c.x() + k * 0.6, c.y() - k); tri.lineTo(c.x() + k * 0.6, c.y() + k);
        break;
    case Derecha:
        tri.moveTo(c.x() + k, c.y()); tri.lineTo(c.x() - k * 0.6, c.y() - k); tri.lineTo(c.x() - k * 0.6, c.y() + k);
        break;
    default:
        break;
    }
    tri.closeSubpath();
    p.setPen(Qt::NoPen);
    p.drawPath(tri);
}