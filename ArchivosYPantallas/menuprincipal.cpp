#include "menuprincipal.h"
#include "opcionmenu.h"
#include "fuentes.h"
#include "paleta.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>

namespace {
QLabel *crearEtiqueta(const QString &texto, const QFont &fuente, const QColor &color, QWidget *padre)
{
    QLabel *l = new QLabel(texto, padre);
    l->setFont(fuente);
    l->setStyleSheet(QString("color: %1; background: transparent;").arg(color.name()));
    return l;
}
}

MenuPrincipal::MenuPrincipal(QWidget *parent) : FondoNocturno(parent)
{
    QLabel *titulo = crearEtiqueta("<div style=\"line-height:86%;\">HELICOPTER<br>RESCUE</div>",
                                   Fuentes::titulo(84), Paleta::hueso, this);
    titulo->setTextFormat(Qt::RichText);

    QLabel *bajada = crearEtiqueta("Vuela entre las montañas y no te quedes sin combustible.",
                                   Fuentes::texto(17), Paleta::lavanda, this);
    bajada->setWordWrap(true);

    btnJugar = new OpcionMenu("JUGAR", this);
    OpcionMenu *btnInstr = new OpcionMenu("INSTRUCCIONES", this);
    OpcionMenu *btnSalir = new OpcionMenu("SALIR", this);

    QLabel *ayuda = crearEtiqueta("Flechas para elegir, Enter para confirmar",
                                  Fuentes::texto(13), Paleta::apagado, this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(72 - OpcionMenu::SANGRIA, 56, 40, 36);
    layout->setSpacing(0);
    layout->addWidget(titulo);
    layout->addSpacing(22);
    layout->addWidget(bajada);
    layout->addStretch(1);
    layout->addSpacing(18);
    layout->addWidget(btnJugar, 0, Qt::AlignLeft);
    layout->addSpacing(4);
    layout->addWidget(btnInstr, 0, Qt::AlignLeft);
    layout->addSpacing(4);
    layout->addWidget(btnSalir, 0, Qt::AlignLeft);
    layout->addStretch(1);
    layout->addWidget(ayuda);

    for (QLabel *l : {titulo, bajada, ayuda})
        l->setContentsMargins(OpcionMenu::SANGRIA, 0, 0, 0);
    bajada->setFixedWidth(330 + OpcionMenu::SANGRIA);

    setTabOrder(btnJugar, btnInstr);
    setTabOrder(btnInstr, btnSalir);

    connect(btnJugar, &OpcionMenu::clicked, this, &MenuPrincipal::jugar);
    connect(btnInstr, &OpcionMenu::clicked, this, &MenuPrincipal::instrucciones);
    connect(btnSalir, &OpcionMenu::clicked, this, &MenuPrincipal::salir);
}

void MenuPrincipal::showEvent(QShowEvent *event)
{
    FondoNocturno::showEvent(event);
    QTimer::singleShot(0, btnJugar, [this]() { btnJugar->setFocus(Qt::OtherFocusReason); });
}