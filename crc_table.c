/* Author: Luis Colorado <lc@luiscoloradosistemas.com>
 * Date: vie nov 28 22:09:05 EET 2014
 * Copyright: (C) 2014 LUIS COLORADO SISTEMAS S.L.U.
 *            All rights reserved.
 */

#include "crc.h"
#include "mkcrc.h"

struct mkcrc_table_s crc_table[] = {
	"crc01",				0x0000000000000001,
	"crc04itu",				0x000000000000000c,
	"crc05epc",				0x0000000000000012,
	"crc05usb",				0x0000000000000014,
	"crc05itu",				0x0000000000000015,
	"crc06cdma2000b",		0x0000000000000038,
	"crc06cdma2000a",		0x0000000000000039,
	"crc07",				0x0000000000000048,
	"crc07mvb",				0x0000000000000053,
	"crc08",				0x00000000000000ab,
	"crc08ccitt",			0x00000000000000e0,
	"crc08dallas",			0x000000000000008c,
	"crc08saej1850",		0x00000000000000b8,
	"crc08wcdma",			0x00000000000000d9,
	"crc10",				0x0000000000000331,
	"crc10cdma2000",		0x000000000000026f,
	"crc11",				0x000000000000050e,
	"crc12",				0x0000000000000f01,
	"crc12cdma2000",		0x0000000000000c8f,
	"crc13bbc",				0x00000000000015e7,
	"crc15can",				0x0000000000004cd1,
	"crc15mpt1327",			0x000000000000540b,
	"chakravarty",			0x000000000000a8f4,
	"crc16ccitt",			0x0000000000008408,
	"crc16arinc",			0x000000000000d405,
	"crc16cdma2000",		0x000000000000e613,
	"crc16dect",			0x00000000000091a0,
	"crc16t10dif",			0x000000000000edd1,
	"crc16dnp",				0x000000000000a6bc,
	"crc16ibm",				0x000000000000a001,
	"crc17can",				0x000000000001b42d,
	"crc21can",				0x0000000000132281,
	"crc24",				0x0000000000d3b6ba,
	"crc24radix64",			0x0000000000df3261,
	"crc30",				0x0000000038e74301,
	"crc32",				0x00000000edb88320,
	"crc32c",				0x0000000082f63b78,
	"crc32k",				0x00000000eb31d82e,
	"crc32q",				0x00000000d5828281,
	"crc40gsm",				0x0000009000412000,
	"crc64ecma",			0xc96c5795d7870f42,
	"crc64iso",				0xd800000000000000,
	/* ADD NEW POLINOMIES ABOVE THIS LINE */
	NULL, 0,
}; /* crc_table */
