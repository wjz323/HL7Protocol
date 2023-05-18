QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp\
    src/Component.cpp \
    src/Field.cpp \
    src/HL7Encoding.cpp \
    src/HL7Protocol.cpp \
    src/Message.cpp \
    src/MessageElement.cpp \
    src/MsgHelper.cpp \
    src/Segment.cpp \
    src/SubComponent.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/Component.h \
    include/Field.h \
    include/HL7Encoding.h \
    include/HL7Exception.h \
    include/Message.h \
    include/MessageElement.h \
    include/MsgHelper.h \
    include/Segment.h \
    include/SubComponent.h
