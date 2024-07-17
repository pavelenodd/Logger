cmake_minimum_required(VERSION 3.28)

# Название проекта
project(Boost_logger)

# Установите стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
cmake_policy(SET CMP0167 NEW)

set(Boost_USE_STATIC_LIBS OFF)  # Только для использования динамических библиотек
set(Boost_USE_MULTITHREADED ON)
# Найти пакеты Boost
find_package(Boost  REQUIRED COMPONENTS system filesystem)

# Указать директории для поиска заголовочных файлов Boost
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})


# Добавить исполняемый файл
add_executable(Boost_logger 
    src/main.cpp
    src/logger.cpp
    src/logger.h
)


# Линковка библиотек Boost
target_link_libraries(Boost_logger ${Boost_LIBRARIES})

# Показать сообщения, если библиотеки Boost не найдены
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost libraries. Please make sure Boost is installed and accessible.")
endif()

