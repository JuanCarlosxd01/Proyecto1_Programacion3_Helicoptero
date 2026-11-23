#include "VentanaJuego.h"
#include "VistaJuego.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>

VentanaJuego::VentanaJuego(QWidget *parent)
    : QWidget(parent)
{
    // --- HUD (widgets normales) ---
    lblTiempo = new QLabel("Tiempo: 0.0 s", this);
    lblTiempo->setStyleSheet("color: white; font-size: 16px; font-weight: bold;");

    QLabel *lblComb = new QLabel("Combustible:", this);
    lblComb->setStyleSheet("color: white; font-size: 16px;");

    barraCombustible = new QProgressBar(this);
    barraCombustible->setRange(0, 100);
    barraCombustible->setValue(100);
    barraCombustible->setFixedWidth(220);

    QHBoxLayout *hud = new QHBoxLayout();
    hud->addWidget(lblTiempo);
    hud->addStretch();
    hud->addWidget(lblComb);
    hud->addWidget(barraCombustible);

    vista = new VistaJuego(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(hud);
    layout->addWidget(vista, 0, Qt::AlignCenter);

    setStyleSheet("VentanaJuego { background-color: #101820; }");

    connect(vista, &VistaJuego::tiempoCambiado, this, [this](double s) {
        lblTiempo->setText(QString("Tiempo: %1 s").arg(s, 0, 'f', 1));
    });
    connect(vista, &VistaJuego::combustibleCambiado,
            barraCombustible, &QProgressBar::setValue);

    connect(vista, &VistaJuego::volverAlMenu, this, &VentanaJuego::volverAlMenu);
}

void VentanaJuego::iniciar() { vista->iniciar(); }
void VentanaJuego::detener() { vista->detener(); }