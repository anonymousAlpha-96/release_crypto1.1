/*********************************************************************************
* Copyright reserved from 2025                                                   *
* SOURCE:src/cryptoAlgo.h                                                        *                       
* AUTHOR: ANKIT                                                                  *     
* DATE : 29-June-25                                                              *
**********************************************************************************/

#ifndef CRYPTOALGO_H
#define CRYPTOALGO_H

#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

class Crypto {
public:
    Crypto();
    ~Crypto();

    int encrypt(const std::string& plaintext, unsigned char* ciphertext);
    int decrypt(const unsigned char* ciphertext, int ciphertext_len, unsigned char* decryptedtext);

    void printHex(const unsigned char* data, int len) const;

    const unsigned char* getKey() const { return key; }
    const unsigned char* getIV() const { return iv; }

private:
    unsigned char key[32];
    unsigned char iv[16];
};

#endif
