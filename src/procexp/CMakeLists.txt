add_subdirectory(proccon)


include_directories(proccon)
add_executable(procexp
    procexp.cpp
    mainwindow.cpp
    mainwindow.ui
    processtreemodel.cpp
    treeitem.cpp
    ${PROCCON_SRC_DBUS}
)

target_link_libraries(procexp
    sysinfo 
    Qt5::Widgets
    Qt5::DBus
)
