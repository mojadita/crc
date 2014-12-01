/* Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: vie nov 28 22:03:32 EET 2014
 * Disclaimer: (C) 2014 LUIS COLORADO SISTEMAS S.L.U.
 * All rights reserved.
 */

#ifndef _MKCRC_H
#define _MKCRC_H

#define BITS_PER_BYTE	CRC_BYTE_SIZE
#define BYTE_VALUES		CRC_TABLE_SIZE
#define N_PER_LINE		4

#define CRC32_IEEE_802_3	0xedb88320
#define CRC32_CASTAGNOLLI	0x82f63b78
#define CRC16_CCITT			0x8408
#define CRC15_IBM			0x6051
#define CRC12				0xd01
#define CRC8				0xe0
#define CRC7				0x48
#define CRC1				0x1

#define DEFAULT_POL			CRC32_IEEE_802_3

#define FLAGS_LIST		0x01
#define FLAGS_GEN		0x02
#define FLAGS_VERBOSE	0x04
#define FLAGS_LISTCRCS	0x08

struct mkcrc_table_s {
	char *name;
	CRC_STATE pol;
};

extern struct mkcrc_table_s crc_table[];

#endif /* _MKCRC_H */
