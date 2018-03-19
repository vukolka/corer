cmake_minimum_required(VERSION 3.9)
project(CorewarVis)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/CorewarVis.cpp
        src/CorewarVis.h
        src/OnLoop.cpp
        src/OnRender.cpp
        src/OnCleanup.cpp
        src/OnLoad.cpp
        src/OnExecute.cpp
        src/OnInit.cpp
        src/OnEvent.cpp
        src/Map.cpp
        src/Map.h
        src/TextureObj.cpp
        src/TextureObj.h
        src/op.h
        src/UserInterface.cpp
        src/UserInterface.h
        src/Process.cpp
        src/Process.h
        src/Player.cpp
        src/Player.h)


if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

add_executable(CorewarVis ${SOURCE_FILES})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")

if (APPLE)
    include_directories(/Users/mkoniev/.brew/Cellar/sdl2_image/2.0.3/include)
    include_directories(/Users/mkoniev/.brew/Cellar/sdl2_ttf/2.0.14/include)
    include_directories(/Users/mkoniev/.brew/Cellar/sdl2/2.0.8/include)
    include_directories(/Users/mkoniev/.brew/Cellar/sdl2/2.0.8/include/SDL2)
    include_directories(/Users/mkoniev/.brew/cellar/sdl2_mixer/2.0.2_3/include/SDL2)

    target_link_libraries(CorewarVis -L/Users/mkoniev/.brew/Cellar/sdl2/2.0.8/lib -L/Users/mkoniev/.brew/Cellar/sdl2_ttf/2.0.14/lib -L/Users/mkoniev/.brew/Cellar/sdl2_image/2.0.3/lib -L/Users/mkoniev/.brew/Cellar/sdl2_mixer/2.0.2_3/lib -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer)
endif()
if (LINUX)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
    target_link_libraries(CorewarVis -lSDL2 -lSDL2_ttf -lSDL2_image)
endif()
