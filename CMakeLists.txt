cmake_minimum_required(VERSION 3.17)
project(LudumDare2020)

set(CMAKE_CXX_STANDARD 20)

add_executable(LudumDare2020 main.cpp Physics.cpp Physics.hpp AsteroidsGame.cpp AsteroidsGame.hpp Geometry.cpp Geometry.hpp FrameTicker.cpp FrameTicker.hpp )



add_subdirectory(Willow)


target_link_libraries(LudumDare2020 PRIVATE Willow)
target_include_directories(LudumDare2020 PRIVATE Willow/include)

add_executable(CollisionTest CollisionTest.cpp Geometry.cpp Geometry.hpp)
target_link_libraries(CollisionTest PRIVATE Willow)
target_include_directories(CollisionTest PRIVATE Willow/include)

#target_compile_options(LudumDare2020 PUBLIC -Werror)