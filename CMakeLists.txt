
project(XKHyperCom)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(VERSION_MAJOR    0)
set(VERSION_MINOR    0)
set(VERSION_REVISION 1)

set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_REVISION})

set(hypercom_target xkhypercom-v${VERSION})

find_package(Qt4 REQUIRED)
find_package(QextSerialPort REQUIRED)

include(${QT_USE_FILE})

include_directories(${CMAKE_BINARY_DIR} . )

set(hypercom_sources
    mainwindow.cpp
    serial.cpp
    serialconsole.cpp
    serialutils.cpp
    portsettings.cpp
    main.cpp   
)

set(hypercom_headers
    serialutils.h
)

set(hypercom_moc_headers
    mainwindow.h
    serial.h
    serialconsole.h
    portsettings.h
)

set(hypercom_files
    CHANGELOG
    TODO
    README
)

set(hypercom_ui_files
    mainwindow.ui
    portsettings.ui
)

configure_file(defines.h.in ${CMAKE_CURRENT_SOURCE_DIR}/defines.h)

qt4_wrap_cpp(hypercom_sources ${hypercom_moc_headers})
qt4_wrap_ui(hypercom_sources ${hypercom_ui_files})

add_executable(${hypercom_target} ${hypercom_sources} ${hypercom_headers} ${hypercom_files})
target_link_libraries(${hypercom_target} ${QT_LIBRARIES} ${QEXTSERIALPORT_LIBRARY})

