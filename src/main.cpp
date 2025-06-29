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
/*================================================================================
|    ID         |   DATE        |   AUTHOR     |   DESCRIPTION                   |
|================================================================================|
|    001        |   29-June-25  |   ANKIT      | Created MessageLogger class     |
|================================================================================|  
==================================================================================*/

#include "cryptoAlgo.h"
#include "MessageLogger.h"
#include <iostream>
#include <exception>

int main() {

    auto& logger = MessageLogger::getInstance();

    try{
        Crypto crypto;
        std::string message ="";
        std::cout << "Welcome to the AES-256-CBC Encryption/Decryption Program!" << std::endl;

        std::cout << "Enter the message to encrypt: ";
        std::getline(std::cin, message);
        if (message.empty()) {
            logger.logError("No message provided for encryption");
            std::cerr << "No message provided for encryption" << std::endl;
            return 1;
        }
        logger.logInfo("Starting encryption process");

        unsigned char ciphertext[256];
        unsigned char decryptedtext[256];

        int ciphertext_len = crypto.encrypt(message, ciphertext);

        logger.logInfo("Cryptography initialized successfully");
        if (ciphertext_len < 0) {
            logger.logError("Encryption failed");
            return 1;
        }
        logger.logInfo("Ciphertext length: " + std::to_string(ciphertext_len));

        // Print the original plaintext, key, IV, ciphertext, and decrypted text
        logger.logInfo("Original plaintext: " + message);
        logger.logInfo("Key (hex): ");
        //crypto.printHex(crypto.getKey(), 32); // hidden for security
        logger.logInfo("IV (hex): ");
        //crypto.printHex(crypto.getIV(), 16); // hidden for security
        logger.logInfo("Ciphertext (hex): ");
        //crypto.printHex(ciphertext, ciphertext_len); // hidden for security
        logger.logInfo("Decrypted text: " + std::string(reinterpret_cast<char*>(decryptedtext), ciphertext_len));


        int decryptedtext_len = crypto.decrypt(ciphertext, ciphertext_len, decryptedtext);
        if (decryptedtext_len < 0) {
            logger.logError("Decryption failed");
            std::cerr << "Decryption failed" << std::endl;
            return 1;
        }  

        decryptedtext[decryptedtext_len] = '\0'; // Null-terminate the decrypted text
        logger.logInfo("Decryption successful");
        logger.logInfo("Decrypted text: " + std::string(reinterpret_cast<char*>(decryptedtext), decryptedtext_len));
        std::cout << "Decrypted text: " << std::string(reinterpret_cast<char*>(decryptedtext), decryptedtext_len) << std::endl;
        logger.logInfo("Program completed successfully");
    }
    catch(const std::exception& e) {
        logger.logError(std::string("Exception occurred: ") + e.what());
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return 1;
    }
    catch(...) {
        logger.logError("Unknown error occurred");
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }

    return 0;
}

