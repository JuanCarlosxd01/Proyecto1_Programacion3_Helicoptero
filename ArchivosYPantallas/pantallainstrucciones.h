#ifndef PANTALLAINSTRUCCIONES_H
#define PANTALLAINSTRUCCIONES_H

#include "fondonocturno.h"

class OpcionMenu;

class PantallaInstrucciones : public FondoNocturno
{
    Q_OBJECT

public:
    explicit PantallaInstrucciones(QWidget *parent = nullptr);

signals:
    void volver();

protected:
    void showEvent(QShowEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    OpcionMenu *btnVolver;
};

#endif