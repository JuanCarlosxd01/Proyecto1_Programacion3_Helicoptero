#include "opcionmenu.h"
#include "fuentes.h"
#include "paleta.h"
#include <QPainter>
#include <QKeyEvent>
#include <QFontMetrics>

OpcionMenu::OpcionMenu(const QString &texto, QWidget *parent)
    : QAbstractButton(parent)
{
    setText(texto);
    setFont(Fuentes::opcion(30));
    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_Hover);
}

QSize OpcionMenu::sizeHint() const
{
    QFontMetrics fm(font());
    return QSize(SANGRIA + 10 + fm.horizontalAdvance(text()) + 4, fm.height() + 14);
}

void OpcionMenu::enterEvent(QEnterEvent *event)
{
    QAbstractButton::enterEvent(event);
    setFocus(Qt::MouseFocusReason);
}

void OpcionMenu::focusInEvent(QFocusEvent *event)
{
    QAbstractButton::focusInEvent(event);
    update();
}

void OpcionMenu::focusOutEvent(QFocusEvent *event)
{
    QAbstractButton::focusOutEvent(event);
    update();
}

void OpcionMenu::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Space:
        animateClick();
        break;
    case Qt::Key_Down:
        focusNextChild();
        break;
    case Qt::Key_Up:
        focusPreviousChild();
        break;
    default:
        QAbstractButton::keyPressEvent(event);
    }
}

void OpcionMenu::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::TextAntialiasing);

    const bool activa = hasFocus();
    const QRect r = rect();
    const int medio = r.height() / 2;

    if (activa) {
        p.setPen(Qt::NoPen);
        p.setBrush(isDown() ? Paleta::ambar : Paleta::rescate);
        p.drawRoundedRect(QRectF(SANGRIA - 30, medio - 2, 22, 4), 2, 2);
    }

    p.setFont(font());
    p.setPen(activa ? Paleta::hueso : Paleta::apagado);
    p.drawText(r.adjusted(activa ? SANGRIA + 8 : SANGRIA, 0, 0, 0), Qt::AlignVCenter | Qt::AlignLeft, text());
}