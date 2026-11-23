TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
QT += core gui widgets

INCLUDEPATH += \
        ArchivosYPantallas \
        ElementosJuego \
        EstructurasDeDatos \
        HiloYLogica \
        JugadorYMundo \


SOURCES += \
        ArchivosYPantallas/gestorarchivos.cpp \
        ArchivosYPantallas/jugador.cpp \
        ArchivosYPantallas/menuprincipal.cpp \
        ArchivosYPantallas/pantallainstrucciones.cpp \
        ArchivosYPantallas/pantallarecords.cpp \
        ArchivosYPantallas/pantallaresultado.cpp \
        ArchivosYPantallas/seleccionmision.cpp \
        ArchivosYPantallas/ventanaprincipal.cpp \
        ElementosJuego/civil.cpp \
        ElementosJuego/enemigo.cpp \
        ElementosJuego/proyectil.cpp \
        ElementosJuego/zonarepostaje.cpp \
        EstructurasDeDatos/colarescate.cpp \
        EstructurasDeDatos/listaproyectiles.cpp \
        EstructurasDeDatos/pilaeventos.cpp \
        HiloYLogica/hilofisica.cpp \
        HiloYLogica/hud.cpp \
        HiloYLogica/nivel.cpp \
        JugadorYMundo/helicoptero.cpp \
        JugadorYMundo/obstaculo.cpp \
        JugadorYMundo/terreno.cpp \
        JugadorYMundo/ventanajuego.cpp \
        JugadorYMundo/vistajuego.cpp \
        main.cpp

HEADERS += \
    ArchivosYPantallas/gestorarchivos.h \
    ArchivosYPantallas/jugador.h \
    ArchivosYPantallas/menuprincipal.h \
    ArchivosYPantallas/pantallainstrucciones.h \
    ArchivosYPantallas/pantallarecords.h \
    ArchivosYPantallas/pantallaresultado.h \
    ArchivosYPantallas/seleccionmision.h \
    ArchivosYPantallas/ventanaprincipal.h \
    ElementosJuego/civil.h \
    ElementosJuego/enemigo.h \
    ElementosJuego/proyectil.h \
    ElementosJuego/zonarepostaje.h \
    EstructurasDeDatos/colarescate.h \
    EstructurasDeDatos/listaproyectiles.h \
    EstructurasDeDatos/pilaeventos.h \
    HiloYLogica/hilofisica.h \
    HiloYLogica/hud.h \
    HiloYLogica/nivel.h \
    JugadorYMundo/helicoptero.h \
    JugadorYMundo/obstaculo.h \
    JugadorYMundo/terreno.h \
    JugadorYMundo/ventanajuego.h \
    JugadorYMundo/vistajuego.h
