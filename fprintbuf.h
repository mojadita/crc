/* $Id: fprintbuf.h,v 2.1 2005/11/05 17:51:36 luis Exp $
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Thu Aug 18 15:47:09 CEST 2005
 * Copyright: (C) 2005-2021 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#ifndef FPRINTBUF_H
#define FPRINTBUF_H

int fprintbuf (FILE *f,	/* fichero de salida */
	int t,				/* tamano del buffer */
	unsigned char *b,	/* puntero al buffer */
	char *fmt, ...);	/* rotulo de cabecera */

#endif /* FPRINTBUF_H */
