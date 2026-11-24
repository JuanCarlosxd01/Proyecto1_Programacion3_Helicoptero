#ifndef OPCIONMENU_H
#define OPCIONMENU_H

#include <QAbstractButton>

class OpcionMenu : public QAbstractButton
{
    Q_OBJECT

public:
    static constexpr int SANGRIA = 40;

    explicit OpcionMenu(const QString &texto, QWidget *parent = nullptr);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
};

#endif