cmake_minimum_required(VERSION 2.8)
set(CMAKE_SUPPRESS_REGENERATION true)
project(exdental-lib)

set(VTK_DIR "C:/libs/VTK-7.0.0-64bits")
set(ITK_DIR "C:/libs/InsightToolkit-4.8.1-64bits")
# Find VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
# Find ITK
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

file(GLOB my_source_files "*.h" "*.cpp" "*.cxx")
add_library(exdental-lib ${my_source_files} )  
#bota vtk e ITK
target_link_libraries(exdental-lib  ${VTK_LIBRARIES} ${ITK_LIBRARIES})
#bota minhas bibliotecas:
#o carregador de imagens 3d
add_subdirectory(C:/src/myItkImageLoader  C:/libs/myItkImageLoader) #C:\libs\myItkImageLoader
include_directories(${myItkImageLoader_INCLUDE_DIRS})
target_link_libraries(exdental-lib myItkImageLoader)

add_definitions(-D_SCL_SECURE_NO_WARNINGS)


