cmake_minimum_required(VERSION 3.9)
project(ZCpp_MissionImpossible)

set(CMAKE_CXX_STANDARD 11)

if(WIN32)
    set(SDL2_INCLUDE_DIR  "E:/Cpp/SDL2/i686-w64-mingw32/include;E:/Cpp/SDL2/i686-w64-mingw32/include/SDL2")
    set(SDL2_IMAGE_DIR "E:/Cpp/SDL2_image/i686-w64-mingw32/include")
    set(SDL2_TTF_DIR "E:/Cpp/SDL2_ttf/i686-w64-mingw32/include")
    set(SDL2_LIB "E:/Cpp/SDL2/i686-w64-mingw32/lib")
    set(SDL2_IMAGE_LIB "E:/Cpp/SDL2_image/i686-w64-mingw32/lib")
    set(SDL2_TTF_LIB "E:/Cpp/SDL2_ttf/i686-w64-mingw32/lib")
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
        ${SDL2_TTF_LIB} #moze sie przyda
)

add_executable(ZCpp_MissionImpossible
        src/main.cpp
        src/GUI/StartWindow.cpp
        src/GUI/StartWindow.h
        src/GUI/Window.cpp
        src/GUI/Window.h
        src/Game.cpp
        src/Game.h src/GUI/ImageElement.cpp src/GUI/ImageElement.h src/GUI/MenuElement.cpp src/GUI/MenuElement.h src/Utils/Dictionary.h src/Utils/Dictionary.cpp)

target_link_libraries(
        ZCpp_MissionImpossible
        SDL2
        SDL2_image
        SDL2_ttf
)