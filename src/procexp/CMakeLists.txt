add_subdirectory(proccon)

add_executable(procexp
    procexp.cpp
    mainwindow.cpp
    mainwindow.ui
    processtreemodel.cpp
    treeitem.cpp
    proccon/ConnectorInterface.cpp
)

target_link_libraries(procexp
    sysinfo 
    Qt5::Widgets
    Qt5::DBus
)
