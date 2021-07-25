cmake_minimum_required(VERSION 3.19)

project(Clib)

set(CMAKE_CXX_STANDARD 11)

add_library(untitled1 library.cpp library.h)
add_library(nativetest SHARED src/com_wang_testapp_ccp_NativeTest.h src/com_wang_testapp_ccp_NativeTest.c)
add_library(nativetest2 SHARED src/NativeTest.c)

