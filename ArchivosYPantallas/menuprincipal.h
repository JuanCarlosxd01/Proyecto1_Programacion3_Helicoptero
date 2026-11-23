#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QWidget>

class MenuPrincipal : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPrincipal(QWidget *parent = nullptr);

signals:
    void jugar();
    void instrucciones();
    void salir();
};

#endif // MENUPRINCIPAL_H