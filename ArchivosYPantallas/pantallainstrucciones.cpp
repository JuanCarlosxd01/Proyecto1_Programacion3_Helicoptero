#include "pantallainstrucciones.h"
#include "opcionmenu.h"
#include "tecla.h"
#include "fuentes.h"
#include "paleta.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>

namespace {
QLabel *crearEtiqueta(const QString &texto, const QFont &fuente, const QColor &color, QWidget *padre)
{
    QLabel *l = new QLabel(texto, padre);
    l->setFont(fuente);
    l->setStyleSheet(QString("color: %1; background: transparent;").arg(color.name()));
    return l;
}

QHBoxLayout *filaTeclas(std::initializer_list<QWidget *> teclas)
{
    QHBoxLayout *fila = new QHBoxLayout();
    fila->setSpacing(6);
    for (QWidget *t : teclas)
        fila->addWidget(t, 0, Qt::AlignVCenter);
    fila->addStretch();
    return fila;
}
}

PantallaInstrucciones::PantallaInstrucciones(QWidget *parent) : FondoNocturno(parent)
{
    setSombraIzquierda(0.78);

    QLabel *titulo = crearEtiqueta("INSTRUCCIONES", Fuentes::titulo(64), Paleta::hueso, this);

    QGridLayout *controles = new QGridLayout();
    controles->setHorizontalSpacing(24);
    controles->setVerticalSpacing(12);
    controles->setColumnMinimumWidth(0, 150);

    auto accion = [this](const QString &t) {
        QLabel *l = crearEtiqueta(t, Fuentes::textoFuerte(16), Paleta::hueso, this);
        l->setContentsMargins(0, 3, 0, 0);
        return l;
    };

    QWidget *separador = new QWidget(this);
    separador->setFixedWidth(14);

    controles->addWidget(accion("Mover"), 0, 0, Qt::AlignVCenter);
    controles->addLayout(filaTeclas({new Tecla("W", this), new Tecla("A", this),
                                     new Tecla("S", this), new Tecla("D", this), separador,
                                     new Tecla(Tecla::Arriba, this), new Tecla(Tecla::Izquierda, this),
                                     new Tecla(Tecla::Abajo, this), new Tecla(Tecla::Derecha, this)}), 0, 1);
    controles->addWidget(accion("Reiniciar"), 1, 0, Qt::AlignVCenter);
    controles->addLayout(filaTeclas({new Tecla("R", this)}), 1, 1);
    controles->addWidget(accion("Volver al menú"), 2, 0, Qt::AlignVCenter);
    controles->addLayout(filaTeclas({new Tecla("Esc", this)}), 2, 1);

    QLabel *subtitulo = crearEtiqueta("Cómo se juega", Fuentes::textoFuerte(17), Paleta::hueso, this);
    QLabel *objetivo = crearEtiqueta(
        "El combustible baja con cada segundo de vuelo y cada choque con un obstáculo "
        "te quita una parte extra. Esquiva todo lo que puedas: cuando el tanque llega "
        "a cero, la partida termina.",
        Fuentes::texto(15), Paleta::lavanda, this);
    objetivo->setWordWrap(true);
    objetivo->setFixedWidth(440);

    btnVolver = new OpcionMenu("VOLVER", this);

    QVBoxLayout *contenido = new QVBoxLayout();
    contenido->setContentsMargins(OpcionMenu::SANGRIA, 0, 0, 0);
    contenido->setSpacing(0);
    contenido->addWidget(titulo);
    contenido->addSpacing(26);
    contenido->addLayout(controles);
    contenido->addSpacing(30);
    contenido->addWidget(subtitulo);
    contenido->addSpacing(8);
    contenido->addWidget(objetivo);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(72 - OpcionMenu::SANGRIA, 56, 40, 36);
    layout->setSpacing(0);
    layout->addLayout(contenido);
    layout->addStretch(1);
    layout->addWidget(btnVolver, 0, Qt::AlignLeft);

    connect(btnVolver, &OpcionMenu::clicked, this, &PantallaInstrucciones::volver);
}

void PantallaInstrucciones::showEvent(QShowEvent *event)
{
    FondoNocturno::showEvent(event);
    QTimer::singleShot(0, btnVolver, [this]() { btnVolver->setFocus(Qt::OtherFocusReason); });
}

void PantallaInstrucciones::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_Backspace) {
        emit volver();
        return;
    }
    FondoNocturno::keyPressEvent(event);
}