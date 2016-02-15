add_executable(vmmap
    vmmap.cpp
    mainwindow.cpp
    mainwindow.ui
    selectprocessview.cpp
    selectprocessview.ui
    mapcategorymodel.cpp
    treeitem.cpp
    mapdetailtreemodel.cpp
)

target_link_libraries(vmmap
    sysinfo 
    Qt5::Widgets
)
