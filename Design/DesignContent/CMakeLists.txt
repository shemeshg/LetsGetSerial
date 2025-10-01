
    qt_add_library(DesignContent STATIC)
    qt6_add_qml_module(DesignContent
        URI "DesignContent"
        VERSION 1.0
        RESOURCE_PREFIX "/qt/qml"
        QML_FILES
            App.qml
Screen01.qml
        RESOURCES
            
        )
    