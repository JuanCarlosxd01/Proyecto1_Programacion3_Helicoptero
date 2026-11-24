#include "fondonocturno.h"
#include "paleta.h"
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QRandomGenerator>
#include <QtMath>
#include <cmath>

namespace {
const qreal BASE[4]     = {0.64, 0.72, 0.82, 0.93};
const qreal AMPLITUD[4] = {0.20, 0.16, 0.12, 0.09};
const QColor CAPA[4]    = {QColor(0x3a, 0x2c, 0x4f), QColor(0x2a, 0x22, 0x44),
                        QColor(0x1b, 0x17, 0x33), QColor(0x11, 0x0e, 0x24)};
const QColor SILUETA(0x0b, 0x0a, 0x1a);
}

FondoNocturno::FondoNocturno(QWidget *parent)
    : QWidget(parent), sombraIzquierda(0.62)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
    animacion.setInterval(33);
    connect(&animacion, &QTimer::timeout, this, QOverload<>::of(&QWidget::update));
    reloj.start();
}

void FondoNocturno::setSombraIzquierda(qreal fraccion)
{
    sombraIzquierda = fraccion;
    update();
}

void FondoNocturno::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    animacion.start();
}

void FondoNocturno::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);
    animacion.stop();
}

void FondoNocturno::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    construirEscena();
}

qreal FondoNocturno::alturaCresta(int capa, qreal x) const
{
    const qreal w = qMax(1, width());
    const qreal h = height();
    const qreal u = x / w * 6.2831;
    const qreal fase = capa * 2.3;
    const qreal f = 0.9 + capa * 0.25;

    qreal grande  = 1.0 - qAbs(qSin(u * f + fase));
    qreal media   = 1.0 - qAbs(qSin(u * f * 2.3 + fase * 1.7 + 0.8));
    qreal detalle = 0.5 + 0.5 * qSin(u * f * 7.1 + fase * 3.1);
    qreal roca    = 0.5 + 0.5 * qSin(u * f * 19.0 + fase * 5.3);

    qreal valor = 0.62 * qPow(grande, 1.3)
                  + 0.26 * media
                  + 0.08 * detalle
                  + 0.04 * roca;
    return h * BASE[capa] - h * AMPLITUD[capa] * valor * 1.5;
}

void FondoNocturno::construirEscena()
{
    if (width() <= 0 || height() <= 0)
        return;

    const qreal dpr = devicePixelRatioF();
    const int w = width();
    const int h = height();

    escena = QPixmap(QSize(w, h) * dpr);
    escena.setDevicePixelRatio(dpr);
    escena.fill(Paleta::nocheAlta);

    QPainter p(&escena);
    p.setRenderHint(QPainter::Antialiasing);

    QLinearGradient cielo(0, 0, 0, h);
    cielo.setColorAt(0.00, Paleta::nocheAlta);
    cielo.setColorAt(0.45, Paleta::indigo);
    cielo.setColorAt(0.62, QColor(0x4a, 0x2d, 0x4a));
    cielo.setColorAt(1.00, QColor(0x2a, 0x1c, 0x38));
    p.fillRect(QRect(0, 0, w, h), cielo);

    QRadialGradient horizonte(w * 0.70, h * 0.62, w * 0.65);
    QColor brasa = Paleta::brasa;
    brasa.setAlpha(150);
    horizonte.setColorAt(0.0, brasa);
    brasa.setAlpha(0);
    horizonte.setColorAt(1.0, brasa);
    p.fillRect(QRect(0, 0, w, h), horizonte);

    QRandomGenerator semilla(20251123);
    p.setPen(Qt::NoPen);
    for (int i = 0; i < 90; ++i) {
        qreal x = semilla.bounded(w);
        qreal y = semilla.bounded(h * 0.48);
        qreal r = 0.5 + semilla.bounded(1.1);
        int a = 40 + semilla.bounded(150) * (1.0 - y / (h * 0.48));
        p.setBrush(QColor(0xef, 0xe6, 0xd6, a));
        p.drawEllipse(QPointF(x, y), r, r);
    }

    auto pintarCapa = [&](QPainter &pp, int capa) {
        QPainterPath cresta;
        cresta.moveTo(0, h);
        for (int x = 0; x <= w + 3; x += 3)
            cresta.lineTo(x, alturaCresta(capa, x));
        cresta.lineTo(w, h);
        cresta.closeSubpath();

        qreal tope = h * (BASE[capa] - AMPLITUD[capa]);
        QLinearGradient relleno(0, tope, 0, h);
        QColor arriba = CAPA[capa];
        QColor abajo = CAPA[capa].darker(135);
        relleno.setColorAt(0.0, arriba);
        relleno.setColorAt(1.0, abajo);
        pp.fillPath(cresta, relleno);

        QColor bruma = Paleta::brasa;
        bruma.setAlpha(capa == 0 ? 70 : 34 - capa * 8);
        pp.setPen(QPen(bruma, 1.2));
        pp.setBrush(Qt::NoBrush);
        QPainterPath borde;
        borde.moveTo(0, alturaCresta(capa, 0));
        for (int x = 3; x <= w + 3; x += 3)
            borde.lineTo(x, alturaCresta(capa, x));
        pp.drawPath(borde);
    };

    for (int capa = 0; capa < 3; ++capa)
        pintarCapa(p, capa);
    p.end();

    primerPlano = QPixmap(QSize(w, h) * dpr);
    primerPlano.setDevicePixelRatio(dpr);
    primerPlano.fill(Qt::transparent);
    QPainter q(&primerPlano);
    q.setRenderHint(QPainter::Antialiasing);
    pintarCapa(q, 3);
    q.end();
}

void FondoNocturno::dibujarReflector(QPainter &p, const QPointF &origen, qreal t)
{
    const qreal w = width();
    const qreal barrido = qSin(t * 2.0 * M_PI / 11.0);
    const qreal xObjetivo = w * (0.74 + 0.20 * barrido);
    puntoLuz = QPointF(xObjetivo, alturaCresta(2, xObjetivo) + height() * 0.015);

    const qreal mitad = height() * 0.13;
    const QPointF fin = origen + (puntoLuz - origen) * 1.6;
    const qreal mitadFin = mitad * 1.6;
    QPainterPath cono;
    cono.moveTo(origen + QPointF(-3, 0));
    cono.lineTo(fin + QPointF(-mitadFin, 0));
    cono.lineTo(fin + QPointF(mitadFin, 0));
    cono.lineTo(origen + QPointF(3, 0));
    cono.closeSubpath();

    QLinearGradient luz(origen, fin);
    QColor c = Paleta::ambar;
    c.setAlpha(125);
    luz.setColorAt(0.0, c);
    c.setAlpha(50);
    luz.setColorAt(0.42, c);
    c.setAlpha(16);
    luz.setColorAt(0.6, c);
    c.setAlpha(0);
    luz.setColorAt(0.78, c);

    p.save();
    p.setCompositionMode(QPainter::CompositionMode_Screen);
    p.fillPath(cono, luz);

    p.translate(puntoLuz);
    p.scale(1.0, 0.32);
    QRadialGradient charco(QPointF(0, 0), mitad * 1.5);
    c.setAlpha(120);
    charco.setColorAt(0.0, c);
    c.setAlpha(40);
    charco.setColorAt(0.5, c);
    c.setAlpha(0);
    charco.setColorAt(1.0, c);
    p.setBrush(charco);
    p.setPen(Qt::NoPen);
    p.drawEllipse(QPointF(0, 0), mitad * 1.5, mitad * 1.5);
    p.restore();
}

void FondoNocturno::dibujarBaliza(QPainter &p, qreal t, qreal luzReflector)
{
    const qreal x = width() * 0.86;
    const QPointF pos(x, alturaCresta(2, x) + 4);
    const bool encendida = std::fmod(t, 1.4) < 0.22;
    const qreal intensidad = qMax(encendida ? 1.0 : 0.25, luzReflector);

    QColor halo = Paleta::rescate;
    halo.setAlpha(int(110 * intensidad));
    QRadialGradient g(pos, 16);
    g.setColorAt(0.0, halo);
    halo.setAlpha(0);
    g.setColorAt(1.0, halo);

    p.save();
    p.setPen(Qt::NoPen);
    p.setBrush(g);
    p.drawEllipse(pos, 16, 16);
    QColor nucleo = Paleta::rescate.lighter(100 + int(40 * intensidad));
    nucleo.setAlpha(int(140 + 115 * intensidad));
    p.setBrush(nucleo);
    p.drawEllipse(pos, 2.8, 2.8);
    p.restore();
}

void FondoNocturno::dibujarHelicoptero(QPainter &p, const QPointF &centro, qreal t)
{
    const qreal s = height() / 560.0;

    p.save();
    p.translate(centro);
    p.scale(s, s);
    p.rotate(-5);

    QPen contorno(QColor(0x5a, 0x3e, 0x58), 1.2);
    p.setPen(contorno);
    p.setBrush(SILUETA);

    QPainterPath cola;
    cola.moveTo(24, -10);
    cola.lineTo(104, -14);
    cola.lineTo(104, -8);
    cola.lineTo(24, 4);
    cola.closeSubpath();
    p.drawPath(cola);

    QPainterPath aleta;
    aleta.moveTo(96, -12);
    aleta.lineTo(110, -34);
    aleta.lineTo(116, -34);
    aleta.lineTo(108, -9);
    aleta.closeSubpath();
    p.drawPath(aleta);

    QPainterPath cuerpo;
    cuerpo.moveTo(-42, 4);
    cuerpo.cubicTo(-42, -16, -22, -24, 2, -24);
    cuerpo.cubicTo(26, -24, 36, -12, 36, 0);
    cuerpo.cubicTo(36, 12, 22, 18, 0, 18);
    cuerpo.lineTo(-28, 18);
    cuerpo.cubicTo(-38, 18, -42, 12, -42, 4);
    p.drawPath(cuerpo);

    QPainterPath cabina;
    cabina.moveTo(-38, 2);
    cabina.cubicTo(-37, -12, -24, -19, -8, -19);
    cabina.lineTo(-8, 2);
    cabina.closeSubpath();
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0x2e, 0x2a, 0x52));
    p.drawPath(cabina);

    p.setPen(QPen(SILUETA, 3, Qt::SolidLine, Qt::RoundCap));
    p.drawLine(QPointF(-24, 18), QPointF(-26, 28));
    p.drawLine(QPointF(14, 18), QPointF(16, 28));
    p.setPen(QPen(QColor(0x5a, 0x3e, 0x58), 3, Qt::SolidLine, Qt::RoundCap));
    p.drawLine(QPointF(-44, 28), QPointF(30, 28));

    p.setPen(QPen(SILUETA, 4, Qt::SolidLine, Qt::RoundCap));
    p.drawLine(QPointF(0, -24), QPointF(0, -31));

    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0xef, 0xe6, 0xd6, 22));
    p.drawEllipse(QPointF(0, -32), 92, 5);

    const qreal giro = t * 38.0;
    p.setPen(QPen(QColor(0x14, 0x12, 0x28), 2.6, Qt::SolidLine, Qt::RoundCap));
    for (int i = 0; i < 2; ++i) {
        qreal largo = 92 * qCos(giro + i * M_PI / 2.0);
        p.drawLine(QPointF(-largo, -32), QPointF(largo, -32));
    }

    p.save();
    p.translate(108, -12);
    p.setPen(QPen(QColor(0xef, 0xe6, 0xd6, 50), 1.5));
    p.setBrush(Qt::NoBrush);
    p.drawEllipse(QPointF(0, 0), 10, 10);
    p.restore();

    if (std::fmod(t, 1.0) < 0.12) {
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(0xff, 0x40, 0x40));
        p.drawEllipse(QPointF(114, -34), 2.4, 2.4);
    }

    p.setPen(Qt::NoPen);
    p.setBrush(Paleta::ambar);
    p.drawEllipse(QPointF(-22, 20), 3.6, 3.0);

    p.restore();
}

void FondoNocturno::paintEvent(QPaintEvent *)
{
    if (escena.isNull())
        construirEscena();

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    const qreal t = reloj.elapsed() / 1000.0;
    const qreal w = width();
    const qreal h = height();

    p.drawPixmap(0, 0, escena);

    const QPointF centroHeli(w * 0.80, h * 0.22 + 4.0 * qSin(t * 1.3));
    const qreal s = h / 560.0;
    const qreal ang = qDegreesToRadians(-5.0);
    const QPointF lamparaLocal(-22 * s, 20 * s);
    const QPointF lampara = centroHeli + QPointF(
                                lamparaLocal.x() * qCos(ang) - lamparaLocal.y() * qSin(ang),
                                lamparaLocal.x() * qSin(ang) + lamparaLocal.y() * qCos(ang));

    dibujarReflector(p, lampara, t);

    const qreal xBaliza = w * 0.86;
    const qreal distancia = qAbs(puntoLuz.x() - xBaliza) / (h * 0.13);
    dibujarBaliza(p, t, qBound(0.0, 1.0 - distancia, 1.0));

    p.drawPixmap(0, 0, primerPlano);

    QLinearGradient sombra(0, 0, w * sombraIzquierda, 0);
    QColor c = Paleta::nocheAlta;
    c.setAlpha(225);
    sombra.setColorAt(0.0, c);
    c.setAlpha(150);
    sombra.setColorAt(0.55, c);
    c.setAlpha(0);
    sombra.setColorAt(1.0, c);
    p.fillRect(rect(), sombra);

    dibujarHelicoptero(p, centroHeli, t);
}