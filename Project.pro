TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    asset.cpp \
    portfolio.cpp \
    matrix.cpp \
    view.cpp \
    rview.cpp \
    aview.cpp \
    functions.cpp \
    idzorek.cpp \
    timeseries.cpp \
    impliedMVreturns.cpp \
    averagereturns.cpp \
    blacklitterman.cpp \
    expectedreturns.cpp \
    meanvarianceoptimization.cpp \
    propvarprior.cpp \
    stdvdirectly.cpp \
    viewscombiner.cpp \
    reportmaker.cpp \
    omegacomputer.cpp \
    questions.cpp \
    multiplechoice.cpp

HEADERS += \
    asset.h \
    portfolio.h \
    matrix.h \
    view.h \
    rview.h \
    aview.h \
    functions.h \
    idzorek.h \
    timeseries.h \
    impliedMVreturns.h \
    averagereturns.h \
    expectedreturns.h \
    meanvarianceoptimization.h \
    blacklitterman.h \
    propvarprior.h \
    stdvdirectly.h \
    viewscombiner.h \
    reportmaker.h \
    omegacomputer.h \
    questions.h \
    multiplechoice.h
