#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "fondonocturno.h"

class OpcionMenu;

class MenuPrincipal : public FondoNocturno
{
    Q_OBJECT

public:
    explicit MenuPrincipal(QWidget *parent = nullptr);

signals:
    void jugar();
    void instrucciones();
    void salir();

protected:
    void showEvent(QShowEvent *event) override;

private:
    OpcionMenu *btnJugar;
};

#endif