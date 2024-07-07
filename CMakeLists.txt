cmake_minimum_required(VERSION 3.28)

# Название проекта
project(LoggerApp)

# Установите стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Найти пакеты Boost
find_package(Boost REQUIRED COMPONENTS system filesystem)

# Добавить исполняемый файл
add_executable(logger src/main.cpp)

# Указать директории для поиска заголовочных файлов Boost
include_directories(${Boost_INCLUDE_DIRS})

# Линковка библиотек Boost
target_link_libraries(logger ${Boost_LIBRARIES})

# Показать сообщения, если библиотеки Boost не найдены
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost libraries. Please make sure Boost is installed and accessible.")
endif()
