#ifndef PANTALLAINSTRUCCIONES_H
#define PANTALLAINSTRUCCIONES_H

#include <QWidget>

class PantallaInstrucciones : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaInstrucciones(QWidget *parent = nullptr);

signals:
    void volver();
};

#endif // PANTALLAINSTRUCCIONES_H