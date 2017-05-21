cmake_minimum_required(VERSION 2.8)
set(CMAKE_SUPPRESS_REGENERATION true)
project(exdental-lib)

set(VTK_DIR "C:/lib/VTK-7.1.1/VTK-7.1.1/")
set(ITK_DIR "C:/lib/InsightToolkit-4.8.1-64")
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


#Remoção de flags q n podem existir pra CLR funcionar
#if(CMAKE_CXX_FLAGS_DEBUG MATCHES "/RTC1")
#   string(REPLACE "/RTC1" " " CMAKE_CXX_FLAGS_DEBUG 
#"${CMAKE_CXX_FLAGS_DEBUG}")
#   message(STATUS ${PROJECT_NAME}  " CMAKE_CXX_FLAGS_DEBUG removing /RTC1")
#endif()
#if(CMAKE_CXX_FLAGS MATCHES "/EHsc")
#   string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#   message(STATUS ${PROJECT_NAME}  " CMAKE_CXX_FLAGS removing /EHsc")
#endif()
#SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/clr")  