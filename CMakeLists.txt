cmake_minimum_required(VERSION 3.14) # 3.14+ for FetchContent_MakeAvailable
project(EncryptDecryptProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# ------------------------------------------
# Use FetchContent to download OpenSSL if missing
# ------------------------------------------
include(FetchContent)

# Try to find system OpenSSL first
find_package(OpenSSL)

if(NOT OpenSSL_FOUND)
  message(STATUS "OpenSSL not found, downloading and building it...")

  FetchContent_Declare(
    openssl
    URL https://www.openssl.org/source/openssl-3.3.0.tar.gz
  )

  FetchContent_MakeAvailable(openssl)

  # On some systems, you may need to set OpenSSL_ROOT_DIR explicitly
  set(OPENSSL_ROOT_DIR ${openssl_SOURCE_DIR})
  set(OPENSSL_INCLUDE_DIR ${openssl_SOURCE_DIR}/include)
endif()

# Find OpenSSL again (now it should be present)
find_package(OpenSSL REQUIRED)

add_executable(EncryptDecryptProject 
src/main.cpp
src/MessageLogger.cpp
src/cryptoAlgo.cpp)

target_link_libraries(EncryptDecryptProject OpenSSL::Crypto)

message(STATUS "Using OpenSSL version: ${OpenSSL_VERSION}")
