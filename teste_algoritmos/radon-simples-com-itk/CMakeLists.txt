cmake_minimum_required(VERSION 2.8)
set(CMAKE_SUPPRESS_REGENERATION true)
project(radon-simples-itk)

set(VTK_DIR "C:/libs/VTK-7.0.0-64bits")
set(ITK_DIR "C:/libs/InsightToolkit-4.8.1-64bits")
# Find VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
# Find ITK
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

file(GLOB my_source_files "*.h" "*.cpp" "*.cxx")
add_executable(radon-simples-itk ${my_source_files} )  

#bota vtk e ITK
target_link_libraries(radon-simples-itk ${VTK_LIBRARIES} ${ITK_LIBRARIES})
#O speed log (https://github.com/gabime/spdlog)
include_directories(C:/libs/spdlog/include/spdlog)

add_definitions(-D_SCL_SECURE_NO_WARNINGS)