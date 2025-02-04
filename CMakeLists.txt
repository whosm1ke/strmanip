cmake_minimum_required(VERSION 3.30)
project(StringManipulator)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Знаходимо необхідні пакети
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Автоматично додаємо всі файли з папки src
file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.h)

# Створюємо виконуваний файл strmanip
add_executable(strmanip ${SRC_FILES})

# Лінкуємо бібліотеки
target_link_libraries(strmanip PRIVATE cpr::cpr nlohmann_json::nlohmann_json)

# Включаємо заголовочні файли
target_include_directories(strmanip PRIVATE src)

# Повідомлення для перевірки
message(STATUS "CPR and nlohmann-json successfully linked with StringManipulator")
message(STATUS "Source files added to the project: ${SRC_FILES}")
