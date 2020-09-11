cmake_minimum_required(VERSION 3.10)

project(3dlib2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(
   3dlib2
   ./Source/plane.cpp
   ./Source/hexahedr.cpp
   ./Source/ellipsod.cpp
   ./Source/demo.cpp
   ./Source/mouse.cpp
   ./Source/pix.cpp
   ./Source/3ddemo.cpp
   ./Source/linsegax.cpp
   ./Source/ckey.cpp
   ./Source/mode.cpp
   ./Source/misc.cpp
   ./Source/intrfmou.cpp
   ./Source/vobjbase.cpp
   ./Source/coeff.cpp
   ./Source/pnt.cpp
   ./Include/pix.h
   ./Include/3d.h
   ./Include/plane.h
   ./Include/ckey.h
   ./Include/mouse.h
   ./Include/linsegax.h
   ./Include/vobjbase.h
   ./Include/misc.h
   ./Include/demo.h
   ./Include/solve.h
   ./Include/coeff.h
   ./Include/pt.h
   ./Include/mode.h
   ./Include/ellipsod.h
   ./Include/intrfmou.h
   ./Include/hexahedr.h
   ./Include/pnt.h
   ./Include/rot.h 
)

target_include_directories(3dlib2 PUBLIC "${PROJECT_SOURCE_DIR}/Include")

