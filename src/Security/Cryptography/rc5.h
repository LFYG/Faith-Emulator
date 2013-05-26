/**
 * ****** Faith Emulator - Closed Source ******
 * Copyright (C) 2012 - 2013 Jean-Philippe Boivin
 *
 * Please read the WARNING, DISCLAIMER and PATENTS
 * sections in the LICENSE file.
 */

#ifndef _FAITH_EMULATOR_RC5_H
#define _FAITH_EMULATOR_RC5_H

#include "common.h"

/**
 * Rivest Cipher 5 (RC5) implementation for Era of Faith. The game uses the
 * RC5-32/12/16 version of the cipher.
 *
 * RC5 is a simple block cipher, designed in 1994 by Ronald Rivest.
 *
 * RC5 has a 32, 64 or 128-bit block size and a variable key length from
 * 1 bit up to 2040 bits. It is a Feistel-like cipher using between 1 to
 * 255 rounds. The suggested values are respectively 128, 64 and 12, although
 * 12-round RC5 (with 64-bit blocks) is susceptible to a differential attack
 * using 2 ^ 44 chosen plaintexts. To be still an effective cipher, 18-20 rounds
 * are now suggested.
 *
 * The following implementation has a memory footprint of
 * (KEY_SIZE + (((ROUNDS * 2) + 2) * 4)) byte. (120 bytes by default)
 */
class RC5
{
public:
    /** The key size of the algorithm in bytes (0 - 255, 16 suggested) */
    static const size_t KEY_SIZE = 16;
    /** The block size of the algorithm in bytes (4, 8 or 16, 8 suggested) */
    static const size_t BLOCK_SIZE = 8; // size * 2
    /** The number of round of the algorithm (1 - 255, 12 suggested) */
    static const size_t ROUNDS = 12;

public:
    /* constructor */
    RC5();

    /* destructor */
    ~RC5();

public:
    /**
     * Generate the key based on the seed. The seed must be n-bytes as
     * specified by the KEY_SIZE constant.
     *
     * @param[in] aSeed  the seed of the cipher
     */
    void generateKey(uint8_t aSeed[KEY_SIZE]);

    /**
     * Encrypt n octet(s) with the cipher.
     * The length must be a multiple of the BLOCK_SIZE constant.
     *
     *
     * @param[in,out] aBuf          the buffer that will be encrypted
     * @param[in]     aLen          the number of octets to encrypt
     */
    void encrypt(uint8_t* aBuf, size_t aLen);

    /**
     * Decrypt n octet(s) with the cipher.
     * The length must be a multiple of the BLOCK_SIZE constant.
     *
     *
     * @param[in,out] aBuf          the buffer that will be decrypted
     * @param[in]     aLen          the number of octets to decrypt
     */
    void decrypt(uint8_t* aBuf, size_t aLen);

private:
    /* magic values */
    static const uint32_t RC5_PW32 = 0xB7E15163;
    static const uint32_t RC5_QW32 = 0x61C88647;

    /* internal key sizes for uint32_t arrays */
    static const size_t RC5_SUB = ((ROUNDS * 2) + 2);
    static const size_t RC5_KEY = (KEY_SIZE / 4);

private:
    /* left rotation of the bits */
    inline uint32_t rotl(uint32_t aValue, uint32_t aCount)
    {
        aCount %= 32;
        uint32_t high = aValue >> (32 - (int32_t)aCount);
        return (aValue << (int32_t)aCount) | high;
    }

    /* right rotation of the bits */
    inline uint32_t rotr(uint32_t aValue, uint32_t aCount)
    {
        aCount %= 32;
        uint32_t low = aValue << (32 - (int32_t)aCount);
        return (aValue >> (int32_t)aCount) | low;
    }

private:
    uint32_t mKey[RC5_KEY]; //!< the generated key used to generate the sub key
    uint32_t mSub[RC5_SUB]; //!< the generated key used to encrypt/decrypt the data
};

#endif // _FAITH_EMULATOR_RC5_H