cmake_minimum_required(VERSION 3.17)

project(ThreeDPainterTask)

#======================= INCLUSION OF Qt =======================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(OpenGL)
find_package(Qt6Core REQUIRED)
find_package(Qt6Gui REQUIRED)
find_package(Qt6OpenGL REQUIRED)
find_package(Qt6Xml REQUIRED)
find_package(Qt6Widgets REQUIRED)

#======================= INCLUSION OF VTK ======================#
set(VTK_DIR $ENV{VTK_DIR})
find_package(VTK REQUIRED)

include(${VTK_USE_FILE})


#find_package (VTK REQUIRED NO_MODULE)
#include_directories ($ {VTK_INCLUDE_DIRS})
#add_executable (YourExecutableName YourSourceFile.cxx)
#target_link_libraries (YourExecutableName $ {VTK_LIBRARIES})

#======================= INCLUSION OF Our Code ======================#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "${FORMS_DIR}/*.ui"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

# Add the executable
if (WIN32) 
    add_executable(ThreeDPainterTask WIN32 ${SOURCES})
elseif(UNIX)
    add_executable(ThreeDPainterTask ${SOURCES})
endif()

# Add the target includes
target_include_directories(ThreeDPainterTask PRIVATE ${FORMS_DIR})
target_include_directories(ThreeDPainterTask PRIVATE ${INCLUDE_DIR})
target_include_directories(ThreeDPainterTask PRIVATE ${SOURCE_DIR})

#===================== LINKING LIBRARIES =======================#
target_link_libraries( ThreeDPainterTask Qt6::OpenGL)
target_link_libraries( ThreeDPainterTask Qt6::Xml)
target_link_libraries( ThreeDPainterTask Qt6::Widgets)
target_link_libraries( ThreeDPainterTask ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
target_link_libraries( ThreeDPainterTask ${VTK_LIBRARIES})