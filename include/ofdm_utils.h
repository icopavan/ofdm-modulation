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
 * Description: utilities for OFDM
 *
 */

#ifndef _OFDM_UTILS_H_
#define _OFDM_UTILS_H_

/**
 * Define coding rates for the puncturing function
 */
enum CODING_RATE {
    RATE_2_3, //r=2/3
    RATE_3_4  //r=3/4
};

/**
 * Perform the scrambling of a set of bytes, as mandated by
 * 802.11-2007, 17.3.5.4.
 * The initial state of the register is set to all ones.
 * For a different initial state see scramble_with_initial_state
 *
 * \param in array of bytes to be scrambled
 * \param out array of bytes where to write scrambled bits
 * \param size size of in and out arrays
 */
void scramble(const char *in, char *out, int size);

/**
 * Perform the scrambling of a set of bytes, as mandated by
 * 802.11-2007, 17.3.5.4.
 *
 * \param in array of bytes to be scrambled
 * \param out array of bytes where to write scrambled bits
 * \param size size of in and out arrays
 * \param initial_state initial state of the 7-bit shift register
 */
void scramble_with_initial_state(const char *in, char *out, int size, char initial_state);

/**
 * Perform the convolutional encoding of a set of bytes, as
 * mandated by 802.11-2007, 17.3.5.5.
 * The encoder uses the two generator polynomial 133 and 171
 * base 8. The bits generated by the first polynomial are mapped
 * onto output bits 2 * i, while bits generated by the second
 * polynomial are mapped onto output bits 2 * i + 1.
 * To obtain a coding rate of 2/3 or 3/4, the output bits must
 * be passed to the puncturing() function.
 *
 * \param in array of bytes to be encoded
 * \param out array of bytes where to write bits of encoded
 * data (rate = 1/2)
 * \param size of the input array. Output array size must be twice
 * as much
 */
void convolutional_encoding(const char *in, char *out, int size);

/**
 * Perform the puncturing function on the output of the
 * convolutional encoder, in order to obtain the data bits
 * encoded with the desired coding rate.
 *
 * \param in array of the bits output by the convolutional encoder
 * at rate 1/2
 * \param out array of bytes where to store punctured bytes
 * \param size size of the in array. Notice that the size of the
 * out array depends on the coding rate r. For r = 2/3 it is
 * size * 3 / 4, for r = 3/4 it is size * 2 / 3
 * \param rate coding rate (i.e., 2/3 or 3/4)
 */
void pucturing(const char *in, char *out, int size, enum CODING_RATE rate);

/**
 * Perform the interleaving of a set of data bits
 *
 * \param in array of input bits
 * \param out array of bytes where to store interleaved databits
 * \param size size of the input array in bytes. The size of the output
 * array must be equal
 * \param n_cbps number of coded bits per symbol, i.e., how many bits
 * will be included into one OFDM symbol. Notice that size must be a
 * multiple of n_cbps
 * \param n_bpsc number of bits per subcarrier
 */
void interleave(const char *in, char *out, int size, int n_cbps, int n_bpsc);

#endif
