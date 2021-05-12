/* $Id: crc.h,v 2.1 2005/11/05 17:51:35 luis Exp $
 * AUTHOR: Luis Colorado <luiscoloradourcola@gmail.com>
 * DATE: Fri Nov  4 12:06:21 CET 2005
 * Copyright: (C) 2005-2021 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#ifndef CRC_H
#define CRC_H

#include <stdlib.h>
#include <stdint.h>

#define CRC_TABLE_SIZE	256
#define CRC_BYTE_SIZE	8
#define CRC_BYTE_MASK	0xff

typedef uint8_t         CRC_BYTE;
typedef uint64_t        CRC_STATE;

typedef struct crc_table_s {
	char      *cr_name;
    char      *cr_strpolin;
    size_t     cr_size;
    size_t     cr_bytesize;
    CRC_STATE  cr_polin;
    CRC_STATE  cr_mask;
	CRC_STATE  cr_table[CRC_TABLE_SIZE];
} *CRC_TABLE;

CRC_STATE do_crc(
	CRC_STATE  state,
	CRC_BYTE  *buff,
	size_t     nbytes,
	CRC_TABLE  table);

CRC_STATE add_crc(
	CRC_STATE  state,
	CRC_BYTE  *buff,
	size_t     nbytes,
    CRC_TABLE  table);

extern CRC_TABLE crc_alltables[];

#endif /* CRC_H */
