set(TARGET_NAME Viewer)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        OpenGL
        PrintSupport
        REQUIRED)
find_package (Eigen3 REQUIRED)
find_package(Boost COMPONENTS filesystem system thread REQUIRED)
find_package(qt5advanceddocking REQUIRED HINTS "D:/ThirdParty/QtADS")

file(GLOB_RECURSE CPP_HEAD_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE CPP_SOUCE_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE UI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
set(APPRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Resources/appicon.rc)
set(QRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Resources/resources.qrc)


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${CPP_HEAD_FILES} ${CPP_SOUCE_FILES} ${UI_FILES})

add_executable(${TARGET_NAME} ${CPP_HEAD_FILES} ${CPP_SOUCE_FILES} ${UI_FILES} ${APPRC_FILE} ${QRC_FILE})

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Apps)

target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/WX->")

target_link_libraries(${TARGET_NAME} PRIVATE 
${PROJECT_NAME}::Primitives
Qt5::Core
Qt5::Gui
Qt5::Widgets
Qt5::OpenGL
Qt5::PrintSupport
Eigen3::Eigen
Boost::system
Boost::filesystem
Boost::dynamic_linking
Boost::thread
ads::qt5advanceddocking
)

target_include_directories(
  ${TARGET_NAME} 
  PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
)