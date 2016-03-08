set(PROCCON_SRC_DBUS "")

# .h -> xml
qt5_generate_dbus_interface(connector.h)
# .xml -> adapter class
qt5_add_dbus_adaptor(PROCCON_SRC_DBUS
    connector.xml
    connector.h # parentheader
    Connector # classname
    ConnectorAdapter # [basename]
    ConnectorAdapter # [classname]
)
# .xml -> interface class
qt5_add_dbus_interface(PROCCON_SRC_DBUS
    connector.xml
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
