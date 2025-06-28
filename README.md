# This is a Encryption and Decryption Project basically based on Cryptography

A simple cross-platform C++ AES-256-CBC encrypt/decrypt example using OpenSSL and CMake.

## Requirements

- CMake >= 3.10
- OpenSSL development libraries installed/ which needs to be installed:
  - Ubuntu: `sudo apt-get install libssl-dev`
  - macOS: `brew install openssl`
  - Windows: Use [vcpkg](https://vcpkg.io/) or manually build OpenSSL

## Build instructions

```bash
# Linux/macOS
git clone <your-repo-url>
cd CryptoProject
mkdir build
cd build
cmake ..
cmake --build .
./CryptoProject
