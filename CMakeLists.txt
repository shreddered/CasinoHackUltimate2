cmake_minimum_required(VERSION 3.18)

project(CasinoHackUltimate2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost
  COMPONENTS system
  CONFIG REQUIRED)

find_package(Threads)

find_package(OpenSSL)
if (NOT OpenSSL_FOUND)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(SSL REQUIRED IMPORTED_TARGET libssl)
  pkg_check_modules(Crypto REQUIRED IMPORTED_TARGET libcrypto)
  add_library(OpenSSL::SSL ALIAS PkgConfig::SSL)
  add_library(OpenSSL::Crypto ALIAS PkgConfig::Crypto)
endif()

find_package(Tesseract)
if (NOT Tesseract_FOUND)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(Tesseract REQUIRED IMPORTED_TARGET tesseract lept)
  add_library(Tesseract::tesseract ALIAS PkgConfig::Tesseract)
endif()

find_package(OpenCV CONFIG REQUIRED)

find_package(nlohmann_json REQUIRED)

add_executable(bot
  ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/connection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/eval.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/miner.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/session.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
)

target_include_directories(bot
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(bot
  PRIVATE Threads::Threads
  Boost::boost Boost::system
  OpenSSL::SSL OpenSSL::Crypto
  Tesseract::tesseract
  nlohmann_json::nlohmann_json
  ${OpenCV_LIBS}
)

install(TARGETS bot
  RUNTIME DESTINATION bin/
)
