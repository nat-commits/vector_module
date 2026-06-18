cmake_minimum_required(VERSION 3.12)
project(my_vector_module VERSION 1.0 LANGUAGES CXX)

# Устанавливаем стандарт C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пытаемся найти pybind11 через стандартный поиск CMake или через Python
find_package(pybind11 CONFIG)

if(NOT pybind11_FOUND)
    # Если пакет не найден глобально, пробуем вытащить его из установленного pip-пакета
    execute_process(
        COMMAND python3 -m pybind11 --cmake
        OUTPUT_VARIABLE pybind11_CMake_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(pybind11_CMake_DIR)
        find_package(pybind11 REQUIRED PATHS ${pybind11_CMake_DIR})
    else()
        message(FATAL_ERROR "pybind11 not found. Please run: pip install pybind11")
    endif()
endif()

# Создаем модуль pybind11
# Имя модуля должно строго совпадать с PYBIND11_MODULE(my_vector_module, m) в C++ коде
pybind11_add_module(my_vector_module vector_module.cpp)

# Настройка вывода бинарника прямо в текущую директорию (удобно для локальных тестов)
set_target_properties(my_vector_module PROPERTIES
    PREFIX ""
    SUFFIX ".so"
)
