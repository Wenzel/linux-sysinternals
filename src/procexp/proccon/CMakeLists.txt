set(CONNECTOR_XML_PATH "${CMAKE_CURRENT_BINARY_DIR}/connector.xml")

# .h -> xml
qt5_generate_dbus_interface(connector.h ${CONNECTOR_XML_PATH})
# .xml -> adapter class
qt5_add_dbus_adaptor(PROCCON_SRC_DBUS
    ${CONNECTOR_XML_PATH}
    connector.h # parentheader
    Connector # classname
    ConnectorAdapter # [basename]
    ConnectorAdapter # [classname]
)
# .xml -> interface class
qt5_add_dbus_interface(PROCCON_SRC_DBUS
    ${CONNECTOR_XML_PATH}
    ConnectorInterface
)

add_executable(proccon
    proccon.cpp
    connector.h
    ${PROCCON_SRC_DBUS}
)

target_link_libraries(proccon
    sysinfo
    Qt5::Core
    Qt5::DBus
)

# sent back to parent cmakelists
set(PROCCON_SRC_DBUS ${PROCCON_SRC_DBUS} PARENT_SCOPE)
