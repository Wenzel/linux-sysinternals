# we are not using cmake macros since their crash the compilation

# set(CONNECTOR_XML_PATH "${CMAKE_CURRENT_BINARY_DIR}/connector.xml")

# .h -> xml
# qt5_generate_dbus_interface(connector.h ${CONNECTOR_XML_PATH})
# .xml -> adapter class
# qt5_add_dbus_adaptor(PROCCON_SRC_DBUS
#     ${CONNECTOR_XML_PATH}
#     connector.h # parentheader
#     Connector # classname
#     ConnectorAdapter # [basename]
#     ConnectorAdapter # [classname]
# )
# # .xml -> interface class
# qt5_add_dbus_interface(PROCCON_SRC_DBUS
#     ${CONNECTOR_XML_PATH}
#     ConnectorInterface
# )

# commands used to generate xml and classes :
# qdbuscpp2xml-qt5 -A -o procexphelper.xml procexphelper.h
# qdbusxml2cpp-qt5 -a ProcexpHelperAdaptor -c ProcexpHelperAdaptor procexphelper.xml
# qdbusxml2cpp-qt5 -c ProcexpHelperInterface -p ProcexpHelperInterface procexphelper.xml

add_executable(procexp_helper
    main.cpp
)

target_link_libraries(procexp_helper
    sysinfo
    Qt5::Core
    Qt5::DBus
)
