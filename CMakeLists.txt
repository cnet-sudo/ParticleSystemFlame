cmake_minimum_required(VERSION 3.21)
project(ParticleSystemFlame VERSION 0.0.1 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


add_executable(ParticleSystemFlame ParticleSystemFlame.cpp Fire.cpp Fire.h )

target_link_libraries(ParticleSystemFlame PRIVATE sfml-graphics sfml-system sfml-window sfml-audio )

target_compile_features(ParticleSystemFlame PRIVATE cxx_std_14)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ParticleSystemFlame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:ParticleSystemFlame> $<TARGET_FILE_DIR:ParticleSystemFlame> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS ParticleSystemFlame)

# Директория с СMakeLists.txt
# cmake -S . -B build
# cmake --build build --config Release
# cmake --build build --config Debug
# Для запуска проекта выбрать активный проект