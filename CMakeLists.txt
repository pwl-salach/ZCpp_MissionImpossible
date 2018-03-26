cmake_minimum_required(VERSION 3.9)
project(ZCpp_MissionImpossible)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

if(WIN32)
    set(SDL2_INCLUDE_DIR  "E:/Cpp/SDL2/x86_64-w64-mingw32/include;E:/Cpp/SDL2/x86_64-w64-mingw32/include/SDL2")
    set(SDL2_IMAGE_DIR "E:/Cpp/SDL2_image/x86_64-w64-mingw32/include")
    set(SDL2_TTF_DIR "E:/Cpp/SDL2_ttf/x86_64-w64-mingw32/include")
    set(SDL2_LIB "E:/Cpp/SDL2/x86_64-w64-mingw32/lib")
    set(SDL2_IMAGE_LIB "E:/Cpp/SDL2_image/x86_64-w64-mingw32/lib")
    set(SDL2_TTF_LIB "E:/Cpp/SDL2_ttf/x86_64-w64-mingw32/lib")
endif(WIN32)


include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_DIR}
        ${SDL2_TTF_DIR}
        ${CMAKE_SOURCE_DIR}/include/
)

link_directories(
        ${SDL2_LIB}
        ${SDL2_IMAGE_LIB}
        ${SDL2_TTF_LIB}
)

add_executable(ZCpp_MissionImpossible
        src/main.cpp
        src/GUI/StartWindow.cpp
        src/GUI/StartWindow.h
        src/GUI/Window.cpp
        src/GUI/Window.h
        src/Logic/Game.cpp
        src/Logic/Game.h src/GUI/ImageElement.cpp src/GUI/ImageElement.h src/GUI/MenuElement.cpp src/GUI/MenuElement.h src/Utils/Dictionary.h src/Utils/Dictionary.cpp src/Logic/Settings.cpp src/Logic/Settings.h src/GUI/SettingElement.h src/GUI/GameWindow.cpp src/GUI/GameWindow.h src/Logic/Map.cpp src/Logic/Map.h src/Logic/Player.cpp src/Logic/Player.h src/Logic/Agent.cpp src/Logic/Agent.h src/Logic/Headquarters.cpp src/Logic/Headquarters.h src/Logic/PhysicalObject.cpp src/Logic/PhysicalObject.h src/Utils/FileManager.cpp src/Utils/FileManager.h src/Logic/Scanner.cpp src/Logic/Scanner.h src/Logic/Box.cpp src/Logic/Box.h src/Logic/Lake.cpp src/Logic/Lake.h src/Logic/Person.cpp src/Logic/Person.h src/Logic/Obstacle.cpp src/Logic/Obstacle.h src/GUI/Sprite.cpp src/GUI/Sprite.h src/Logic/Point.cpp src/Logic/Point.h src/Logic/Fence.cpp src/Logic/Fence.h src/Logic/Line.cpp src/Logic/Line.h src/Logic/SampledLine.cpp src/Logic/SampledLine.h)

target_link_libraries(
        ZCpp_MissionImpossible
        SDL2
        SDL2_image
        SDL2_ttf
)