#include "fuentes.h"
#include <QFontDatabase>
#include <QStringList>

namespace {
QString familiaTitulo;
QString familiaOpcion;
QString familiaTexto;
QString familiaTextoFuerte;

QString registrar(const QString &ruta)
{
    int id = QFontDatabase::addApplicationFont(ruta);
    if (id < 0)
        return QString();
    QStringList familias = QFontDatabase::applicationFontFamilies(id);
    return familias.isEmpty() ? QString() : familias.first();
}

QFont crear(const QString &familia, int pixeles, qreal espaciado)
{
    QFont f;
    if (!familia.isEmpty())
        f.setFamily(familia);
    f.setPixelSize(pixeles);
    f.setLetterSpacing(QFont::AbsoluteSpacing, espaciado);
    f.setHintingPreference(QFont::PreferNoHinting);
    return f;
}
}

void Fuentes::cargar()
{
    familiaTitulo      = registrar(":/recursos/fuentes/vanguardcf-heavy.otf");
    familiaOpcion      = registrar(":/recursos/fuentes/vanguardcf-bold.otf");
    familiaTexto       = registrar(":/recursos/fuentes/clashdisplay-medium.otf");
    familiaTextoFuerte = registrar(":/recursos/fuentes/clashdisplay-semibold.otf");
}

QFont Fuentes::titulo(int pixeles)      { return crear(familiaTitulo, pixeles, 1.0); }
QFont Fuentes::opcion(int pixeles)      { return crear(familiaOpcion, pixeles, 1.5); }
QFont Fuentes::texto(int pixeles)       { return crear(familiaTexto, pixeles, 0.2); }
QFont Fuentes::textoFuerte(int pixeles) { return crear(familiaTextoFuerte, pixeles, 0.3); }