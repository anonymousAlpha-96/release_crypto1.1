/*********************************************************************************
* Copyright reserved from 2025                                                   *
* SOURCE:src/main.cpp                                                            *
* AUTHOR: ANKIT                                                                  *
* DATE : 29-June-25                                                              *
* Description: This program demonstrates AES-256-CBC encryption and decryption   *
* using OpenSSL. It generates a random key and IV, encrypts a plaintext message, *
* and then decrypts it back to verify the process.                               *
* It prints the original message, key, IV, encrypted message in hex format,      *
* and the decrypted message.                                                     *
**********************************************************************************/

#include "cryptoAlgo.h"
#include <iostream>

int main() {
    Crypto crypto;

    std::string plaintext = "Ankit this side, your text message is decrypted using AES-256-CBC encryption!";
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];

    int ciphertext_len = crypto.encrypt(plaintext, ciphertext);

    std::cout << "Original: " << plaintext << std::endl;

    std::cout << "Key (hex): ";
    crypto.printHex(crypto.getKey(), 32);

    std::cout << "IV (hex): ";
    crypto.printHex(crypto.getIV(), 16);

    std::cout << "Encrypted (hex): ";
    crypto.printHex(ciphertext, ciphertext_len);

    int decrypted_len = crypto.decrypt(ciphertext, ciphertext_len, decryptedtext);
    decryptedtext[decrypted_len] = '\0';

    std::cout << "Decrypted: " << decryptedtext << std::endl;

    return 0;
}
