cmake_minimum_required(VERSION 3.20)

project(resolution-max
 	VERSION 1.0
  	DESCRIPTION "Resolution maximizer for MacOS"
  	LANGUAGES CXX
    	)

add_executable(resolution-max display.cc)

target_compile_features(resolution-max PRIVATE cxx_std_17)

target_link_libraries(resolution-max "-framework CoreGraphics -framework Foundation")

