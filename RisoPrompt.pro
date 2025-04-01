QT       += core gui grpc sql

INCLUDEPATH += $$PWD/proto/generated

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

ICON = ./Contents/Resources/icon.icns

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DBUtils.cpp \
    conversationmessage.cpp \
    conversationmodel.cpp \
    conversationwidget.cpp \
    customplaintext.cpp \
    loadconversationdialog.cpp \
    main.cpp \
    messagedelegate.cpp \
    modelconfigdialog.cpp \
    promptrequest.cpp \
    risoprompt.cpp \
    ./proto/generated/google/ai/generativelanguage/v1/citation_protobuftyperegistrations.cpp \
    ./proto/generated/google/ai/generativelanguage/v1/content_protobuftyperegistrations.cpp \
    ./proto/generated/google/ai/generativelanguage/v1/generative_service.qpb.cpp \
    ./proto/generated/google/ai/generativelanguage/v1/generative_service_client.grpc.qpb.cpp \
    ./proto/generated/google/ai/generativelanguage/v1/safety.qpb.cpp \
    ./proto/generated/google/ai/generativelanguage/v1/safety_protobuftyperegistrations.cpp \
    ./proto/generated/google/ai/generativelanguage/v1/citation.qpb.cpp \
    ./proto/generated/google/ai/generativelanguage/v1/content.qpb.cpp \
    ./proto/generated/google/ai/generativelanguage/v1/generative_service_protobuftyperegistrations.cpp \
    ./proto/generated/google/api/field_behavior.qpb.cpp \
    ./proto/generated/google/api/client.qpb.cpp \
    ./proto/generated/google/api/launch_stage_protobuftyperegistrations.cpp \
    ./proto/generated/google/api/http_protobuftyperegistrations.cpp \
    ./proto/generated/google/api/resource_protobuftyperegistrations.cpp \
    ./proto/generated/google/api/launch_stage.qpb.cpp \
    ./proto/generated/google/api/resource.qpb.cpp \
    ./proto/generated/google/api/field_behavior_protobuftyperegistrations.cpp \
    ./proto/generated/google/api/annotations.qpb.cpp \
    ./proto/generated/google/api/client_protobuftyperegistrations.cpp \
    ./proto/generated/google/api/annotations_protobuftyperegistrations.cpp \
    ./proto/generated/google/api/http.qpb.cpp \
    ./proto/generated/google/protobuf/descriptor_protobuftyperegistrations.cpp \
    ./proto/generated/google/protobuf/duration.qpb.cpp \
    ./proto/generated/google/protobuf/descriptor.qpb.cpp \
    ./proto/generated/google/protobuf/duration_protobuftyperegistrations.cpp \
    saveconversationdialog.cpp


HEADERS += \
    conversationmessage.h \
    conversationmodel.h \
    conversationwidget.h \
    customplaintext.h \
    loadconversationdialog.h \
    messagedelegate.h \
    modelconfigdialog.h \
    promptrequest.h \
    risoprompt.h \
    ./proto/generated/google/ai/generativelanguage/v1/generative_service.qpb.h \
    ./proto/generated/google/ai/generativelanguage/v1/content.qpb.h \
    ./proto/generated/google/ai/generativelanguage/v1/citation.qpb.h \
    ./proto/generated/google/ai/generativelanguage/v1/generative_service_client.grpc.qpb.h \
    ./proto/generated/google/ai/generativelanguage/v1/safety.qpb.h \
    ./proto/generated/google/api/http.qpb.h \
    ./proto/generated/google/api/client.qpb.h \
    ./proto/generated/google/api/launch_stage.qpb.h \
    ./proto/generated/google/api/field_behavior.qpb.h \
    ./proto/generated/google/api/resource.qpb.h \
    ./proto/generated/google/api/annotations.qpb.h \
    ./proto/generated/google/protobuf/duration.qpb.h \
    ./proto/generated/google/protobuf/descriptor.qpb.h \
    saveconversationdialog.h

FORMS += \
    risoprompt.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
