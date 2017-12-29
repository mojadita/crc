/* Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: vie nov 28 22:03:32 EET 2014
 * Disclaimer: (C) 2014 LUIS COLORADO SISTEMAS S.L.U.
 * All rights reserved.
 */

#ifndef _MKCRC_H
#define _MKCRC_H

#define BITS_PER_BYTE	CRC_BYTE_SIZE
#define BYTE_VALUES		CRC_TABLE_SIZE
#define N_PER_LINE		4

#define DEFAULT_POL_MASK		0x01
#define DEFAULT_NAME            "default_crc_table_name"

#define FLAGS_LIST		0x01
#define FLAGS_GEN		0x02
#define FLAGS_VERBOSE	0x04
#define FLAGS_LISTCRCS	0x08

#endif /* _MKCRC_H */
