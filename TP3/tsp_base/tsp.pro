TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    data.cpp \
    node.cpp \
    solution.cpp \
    main.cpp \
    heuristics.cpp \
    bkr.cpp

HEADERS += \
    data.h \
    node.h \
    solution.h \
    chronometer.h \
    rng.h \
    heuristics.h \
    bkr.h
