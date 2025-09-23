cmake_minimum_required(VERSION 3.16)

project(TrainSimulationApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
# find_package(Qt6 REQUIRED COMPONENTS Widgets Charts Core Network HttpServer)
# find_package(Qt6 REQUIRED COMPONENTS Concurrent)
find_package(Qt6 REQUIRED COMPONENTS Core Network HttpServer)

set(PROJECT_SOURCES
    main.cpp
    # mainwindow/mainwindow.cpp
    # mainwindow/mainwindow.h
    # mainwindow/mainwindow.ui
    core/appcontext.h
    core/appcontext.cpp
)

set(RESOURCE_SOURCES
    styles/colors.h
    styles/text_style.h
    resources/input_type.h
    resources/icon_paths.h
    resources/icons.qrc
    auth/auth.qrc
    auth/auth_data.h
    auth/auth_manager.h
    auth/auth_manager.cpp
    auth/user_manager.cpp
    auth/user_manager.h
)

set(MODEL_SOURCES
    models/train_data.h
    models/simulation_data.h
    models/constant_data.h
    models/mass_data.h
    models/energy_data.h
    models/power_data.h
    models/resistance_data.h
    models/moving_data.h
    models/load_data.h
    models/efficiency_data.h
    models/station_data.h
    models/train_motor_data.h
)

set(CONTROLLER_SOURCES
    controllers/simulation/train_simulation_handler.h
    controllers/simulation/train_simulation_handler.cpp
    controllers/simulation/mass_handler.h
    controllers/simulation/mass_handler.cpp
    controllers/simulation/resistance_handler.h
    controllers/simulation/resistance_handler.cpp
    controllers/simulation/tractive_effort_handler.h
    controllers/simulation/tractive_effort_handler.cpp
    controllers/simulation/traction_motor_handler.h
    controllers/simulation/traction_motor_handler.cpp
    controllers/simulation/energy_handler.h
    controllers/simulation/energy_handler.cpp
    controllers/simulation/power_handler.h
    controllers/simulation/power_handler.cpp
    controllers/simulation/moving_handler.h
    controllers/simulation/moving_handler.cpp
    controllers/simulation/simulation_track_handler.h
    controllers/simulation/simulation_track_handler.cpp
    controllers/simulation/utility_handler.h
    controllers/simulation/utility_handler.cpp
    controllers/simulation/current_handler.h
    controllers/simulation/current_handler.cpp
    controllers/output/csv_output_handler.h
    controllers/output/csv_output_handler.cpp
    # controllers/output/save_button_handler.h
    # controllers/output/save_button_handler.cpp
    # controllers/output/static_simulation_chart_handler.h
    # controllers/output/static_simulation_chart_handler.cpp
    # controllers/output/dynamic_simulation_chart_handler.h
    # controllers/output/dynamic_simulation_chart_handler.cpp
    # controllers/output/output_table_handler.h
    # controllers/output/output_table_handler.cpp
    controllers/simulation/csv_variables_handler.h
    controllers/simulation/csv_variables_handler.cpp
    controllers/data/electrical_data_handler.h
    controllers/data/electrical_data_handler.cpp
    controllers/data/running_data_handler.h
    controllers/data/running_data_handler.cpp
    controllers/data/track_data_handler.h 
    controllers/data/track_data_handler.cpp
    controllers/data/train_data_handler.h 
    controllers/data/train_data_handler.cpp
)

set(HTTP_SERVER
    http_server/http_server.cpp
    http_server/api_handler.cpp
    http_server/http_server.h
    http_server/api_handler.h
)

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TrainSimulationApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${MODEL_SOURCES}
        ${RESOURCE_SOURCES}
        ${CONTROLLER_SOURCES}
        ${HTTP_SERVER}
    )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET TrainSimulationApp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
# else()
#     if(ANDROID)
#         add_library(TrainSimulationApp SHARED
#             ${PROJECT_SOURCES}
#         )

#     # Define properties for Android with Qt 5 after find_package() calls as:
#     # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#     else()
#         add_executable(TrainSimulationApp
#             ${PROJECT_SOURCES}
#         )
#     endif()
# endif()

# target_link_libraries(TrainSimulationApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# target_link_libraries(TrainSimulationApp PRIVATE Qt6::Concurrent)
target_link_libraries(TrainSimulationApp PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::HttpServer
    # Qt6::Charts
)
target_include_directories(TrainSimulationApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
# if(${QT_VERSION} VERSION_LESS 6.1.0)
#     set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TrainSimulationApp)
# endif()

set_target_properties(TrainSimulationApp PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TrainSimulationApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TrainSimulationApp)
endif()
