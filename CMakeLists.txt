cmake_minimum_required(VERSION 3.18)

project(CasinoHackUltimate2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost
  COMPONENTS program_options system
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

add_executable(bot
  ${CMAKE_CURRENT_SOURCE_DIR}/src/connection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/session.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
)

target_include_directories(bot
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(bot
  PRIVATE Threads::Threads
  Boost::boost Boost::program_options Boost::system
  OpenSSL::SSL OpenSSL::Crypto
)
