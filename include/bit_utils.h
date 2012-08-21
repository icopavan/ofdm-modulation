/*
 * Copyright (c) 2012 Michele Segata
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Michele Segata <michele.segata@uibk.ac.at>
 * Description: utilities for bit level functionalities
 *
 */

#ifndef _BIT_UTILS_H_
#define _BIT_UTILS_H_

#define ERR_CANNOT_READ_FILE -1
#define ERR_INVALID_FORMAT   -2

/**
 * Print the bit string composing one byte
 *
 * \param b the byte to print
 */
void print_bits(char b);

/**
 * Print the bit string composing a byte array
 *
 * \param b the byte array to print
 * \param size the length of the array
 */
void print_bits_array(const char *b, int size);

/**
 * Returns the i-th bit of a byte.
 * NOTICE that the bit 0 is the LSB, while the
 * bit 7 is the MSB
 *
 * \param b the byte
 * \param i the bit index
 * \return value of the i-th bit of b
 */
inline int get_bit(char b, int i);

/**
 * Sets the i-th bit of a byte.
 * NOTICE that the bit 0 is the LSB, while the
 * bit 7 is the MSB
 *
 * \param b the byte
 * \param i the bit index
 * \param bit value of the bit to set
 */
inline void set_bit(char *b, int i, int bit);

/**
 * Returns the i-th bit in a string of bytes.
 * The function treats an array of byte as a vector
 * of bits, where bit 0 is the MSB of the first byte
 * and bit n-1 is the LSB of the last one.
 *
 * \param b array of bytes
 * \param i index of the bit
 * \return the value of the bit
 */
int get_ith_bit(const char *b, int i);

/**
 * Computes the result of a polynomial generator.
 *
 * \param reg input register
 * \param generator polynomial generator
 * \param size size of the register in bit
 * \return xor of the bits of the register indicated by the generator
 */
char get_polynomial(char reg, char generator, int size);

/**
 * Read a bit-string from a file. The file must contain the bits
 * written in little-endian, i.e., from the MSB to the LSB.
 * The file can also contain comments, determined by a # at the
 * beginning of the line. Bits must be written in groups, and
 * the size of each group must be a multiple of eight. Each byte
 * or group of bytes can be separated by spaces or new line.
 * For example:
 *
 * #this is a sample bit file
 * 00101101 11001011 0111000011000010
 * 11010100
 *
 * is a valid bit file. The function will read 5 bytes
 *
 * \param filename the file to read
 * \param bytes array where to store the read bits
 * \param size maximum size of the bytes array
 * \return the number of bytes read, or -1 in case
 * of an error
 */
int read_bits_from_file(const char *filename, char *bytes, int size);

/**
 * Return the integer value of a group of bits inside a bit
 * string. For example, if input is byte=01011100 and the value
 * for the range [1, 3] is requested (101), then 5 is returned.
 * This is particularly useful when modulating bits with QPSK
 * or QAM, to get I and Q values from groups of modulated
 * bits.
 *
 * \param bytes array of input bytes
 * \param size size of the bytes array (in bytes)
 * \param a index of the first bit to be considered (MSB)
 * \param length number of bits to be taken starting from a
 * \return the decimal value of bits in range [a, b]
 */
char get_bit_group_value(const char *bytes, int size, int a, int length);

#endif
