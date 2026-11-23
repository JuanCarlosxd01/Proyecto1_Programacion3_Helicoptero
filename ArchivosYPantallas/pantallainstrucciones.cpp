#include "PantallaInstrucciones.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

PantallaInstrucciones::PantallaInstrucciones(QWidget *parent)
    : QWidget(parent)
{
    QLabel *titulo = new QLabel("INSTRUCCIONES", this);
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("color: #f5c542; font-size: 30px; font-weight: bold;");

    QLabel *texto = new QLabel(
        "Flechas o WASD: mover el helicóptero\n"
        "R: reiniciar\n"
        "Esc: volver al menú\n\n"
        "Esquiva los obstáculos: cada choque cuesta combustible.", this);
    texto->setAlignment(Qt::AlignCenter);
    texto->setStyleSheet("color: white; font-size: 18px;");

    QPushButton *btnVolver = new QPushButton("Volver al menú", this);

    setStyleSheet(
        "PantallaInstrucciones { background-color: #101820; }"
        "QPushButton { background-color: #1565c0; color: white; font-size: 16px;"
        "              padding: 8px; border-radius: 6px; min-width: 200px; }"
        "QPushButton:hover { background-color: #1e88e5; }");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(titulo);
    layout->addSpacing(20);
    layout->addWidget(texto);
    layout->addSpacing(20);
    layout->addWidget(btnVolver, 0, Qt::AlignCenter);
    layout->addStretch();

    connect(btnVolver, &QPushButton::clicked, this, &PantallaInstrucciones::volver);
}