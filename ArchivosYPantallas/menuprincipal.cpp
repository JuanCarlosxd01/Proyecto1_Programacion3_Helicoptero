#include "MenuPrincipal.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

MenuPrincipal::MenuPrincipal(QWidget *parent) : QWidget(parent){
    QLabel *titulo = new QLabel("HELICOPTER RESCUE", this);
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("color: #f5c542; font-size: 36px; font-weight: bold;");

    QPushButton *btnJugar  = new QPushButton("Iniciar misión", this);
    QPushButton *btnInstr  = new QPushButton("Instrucciones", this);
    QPushButton *btnSalir  = new QPushButton("Salir", this);

    setStyleSheet(
        "MenuPrincipal { background-color: #101820; }"
        "QPushButton { background-color: #2e7d32; color: white; font-size: 18px;"
        "              padding: 10px; border-radius: 6px; min-width: 240px; }"
        "QPushButton:hover { background-color: #43a047; }");
    btnSalir->setStyleSheet("background-color: #c62828;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(titulo);
    layout->addSpacing(30);
    layout->addWidget(btnJugar,  0, Qt::AlignCenter);
    layout->addWidget(btnInstr,  0, Qt::AlignCenter);
    layout->addWidget(btnSalir,  0, Qt::AlignCenter);
    layout->addStretch();

    connect(btnJugar, &QPushButton::clicked, this, &MenuPrincipal::jugar);
    connect(btnInstr, &QPushButton::clicked, this, &MenuPrincipal::instrucciones);
    connect(btnSalir, &QPushButton::clicked, this, &MenuPrincipal::salir);
}