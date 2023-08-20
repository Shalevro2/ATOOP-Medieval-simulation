cmake_minimum_required(VERSION 3.25)
project(ex3)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex3 main.cpp SimObject.cpp SimObject.h Point.h Structure.cpp Structure.h Farm.cpp Farm.h Castle.cpp Castle.h Agent.cpp Agent.h Peasant.cpp Peasant.h Knight.cpp Knight.h Thug.cpp Thug.h Model.cpp Model.h Controller.cpp Controller.h Task.cpp Task.h View.cpp View.h)
