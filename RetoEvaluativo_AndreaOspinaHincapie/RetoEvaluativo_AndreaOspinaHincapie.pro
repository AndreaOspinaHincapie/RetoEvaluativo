TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    pelicula.cpp

DISTFILES +=

HEADERS += \
    pelicula.h \
    manejoarchivos.h \
    administrarusuarios.h \
    manejopeliculas.h \
    ventaasientos.h \
    reporteventas.h \
    pago.h
