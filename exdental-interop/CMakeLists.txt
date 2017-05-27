cmake_minimum_required(VERSION 2.8)
set(CMAKE_SUPPRESS_REGENERATION true)
project(exdental-interop)

set(VTK_DIR "C:/libs/VTK-7.0.0-64bits")
set(ITK_DIR "C:/libs/InsightToolkit-4.8.1-64bits")
# Find VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
# Find ITK
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

file(GLOB my_source_files "*.h" "*.cpp" "*.cxx")
add_library(exdental-interop SHARED ${my_source_files} )  
#bota vtk e ITK
target_link_libraries(exdental-interop ${VTK_LIBRARIES} ${ITK_LIBRARIES})

set (EXDENTAL_LIB_INCLUDE_DIR "C:/src/exdental/exdental-lib")
set (EXDENTAL_LIB_DEBUG_LIB "C:/src/exdental/exdental-lib/Debug/exdental-lib.lib")
set (EXDENTAL_LIB_RELEASE_LIB "C:/src/exdental/exdental-lib/Release/exdental-lib.lib")
target_include_directories(exdental-interop PUBLIC "C:/src/exdental/exdental-lib/")
target_link_libraries(exdental-interop debug ${EXDENTAL_LIB_DEBUG_LIB} )
target_link_libraries(exdental-interop optimized ${EXDENTAL_LIB_RELEASE_LIB} )


#o carregador de imagens 3d
add_subdirectory(C:/src/myItkImageLoader  C:/libs/myItkImageLoader) #C:\libs\myItkImageLoader
include_directories(${myItkImageLoader_INCLUDE_DIRS})
target_link_libraries(exdental-interop myItkImageLoader)

#Remoção de flags q n podem existir pra CLR funcionar
if(CMAKE_CXX_FLAGS_DEBUG MATCHES "/RTC1")
   string(REPLACE "/RTC1" " " CMAKE_CXX_FLAGS_DEBUG 
"${CMAKE_CXX_FLAGS_DEBUG}")
   message(STATUS ${PROJECT_NAME}  " CMAKE_CXX_FLAGS_DEBUG removing /RTC1")
endif()
if(CMAKE_CXX_FLAGS MATCHES "/EHsc")
   string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
   message(STATUS ${PROJECT_NAME}  " CMAKE_CXX_FLAGS removing /EHsc")
endif()
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/clr")  

add_definitions(-D_SCL_SECURE_NO_WARNINGS)