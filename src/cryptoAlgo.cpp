/*********************************************************************************
* Copyright reserved from 2025                                                   *
* SOURCE:src/cryptoAlgo.cpp                                                            *
* AUTHOR: ANKIT                                                                  *
* DATE : 29-June-25                                                              *
* Description: This program demonstrates AES-256-CBC encryption and decryption   *
* using OpenSSL. It generates a random key and IV, encrypts a plaintext message, *
* and then decrypts it back to verify the process.                               *
* It prints the original message, key, IV, encrypted message in hex format,      *
* and the decrypted message.                                                     *
**********************************************************************************/


#include "cryptoAlgo.h"    

// Crypto class implementation
Crypto::Crypto() {
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(iv, sizeof(iv))) {
        std::cerr << "Error generating key/iv" << std::endl;
        std::exit(1);
    }
}

Crypto::~Crypto() {
    EVP_cleanup();
    ERR_free_strings();
}

void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}

int Crypto::encrypt(const std::string& plaintext, unsigned char* ciphertext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len,
                               reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length()))
        handleErrors();
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

int Crypto::decrypt(const unsigned char* ciphertext, int ciphertext_len, unsigned char* decryptedtext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    if (1 != EVP_DecryptUpdate(ctx, decryptedtext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, decryptedtext + len, &len))
        handleErrors();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}

void Crypto::printHex(const unsigned char* data, int len) const {
    for (int i = 0; i < len; i++) printf("%02x", data[i]);
    printf("\n");
}
