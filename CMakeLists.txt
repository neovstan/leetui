cmake_minimum_required(VERSION 3.10)

project(leetui)

add_library(leetui STATIC
	include/leetui/color.h
	include/leetui/cond_behavior.h
	include/leetui/controller.h
	include/leetui/easing_curves.h
	include/leetui/font.h
	include/leetui/frame.h
	include/leetui/image.h
	include/leetui/keyboard.h
	include/leetui/label.h
	include/leetui/layout.h
	include/leetui/mouse_action.h
	include/leetui/movie.h
	include/leetui/painter.h
	include/leetui/point.h
	include/leetui/resource.h
	include/leetui/rgb.h
	include/leetui/signal.h
	include/leetui/size.h
	include/leetui/text.h
	include/leetui/vector.h
	include/leetui/viewport.h
	include/leetui/window.h
	include/leetui/tree.h

	src/color.cpp
	src/cond_behavior.cpp
	src/controller.cpp
	src/easing_curves.cpp
	src/font.cpp
	src/frame.cpp
	src/image.cpp
	src/keyboard.cpp
	src/label.cpp
	src/layout.cpp
	src/mouse_action.cpp
	src/movie.cpp
	src/painter.cpp
	src/point.cpp
	src/resource.cpp
	src/rgb.cpp
	src/signal.cpp
	src/size.cpp
	src/text.cpp
	src/vector.cpp
	src/viewport.cpp
	src/window.cpp
	src/tree.cpp

	third-party/stb/stb_image.h
)

target_include_directories(leetui PRIVATE include/leetui third-party/stb)
target_include_directories(leetui PUBLIC include)

set_target_properties(leetui PROPERTIES CXX_STANDARD 11)

