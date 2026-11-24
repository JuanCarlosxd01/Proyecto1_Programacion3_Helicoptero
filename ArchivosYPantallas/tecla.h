#ifndef TECLA_H
#define TECLA_H

#include <QWidget>

class Tecla : public QWidget
{
    Q_OBJECT

public:
    enum Flecha { Ninguna, Arriba, Abajo, Izquierda, Derecha };

    explicit Tecla(const QString &texto, QWidget *parent = nullptr);
    explicit Tecla(Flecha flecha, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString texto;
    Flecha flecha;
};

#endif