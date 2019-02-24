/* $Id: main.c,v 1.3 2006-01-02 18:15:10 quentin Exp $ */

/*
 * Implementation of the md5 algorithm described in RFC1321
 * Copyright (C) 2005 Quentin Carbonneaux <crazyjoke@free.fr>
 * 
 * This file is part of md5sum.
 *
 * md5sum is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Softawre Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * md5sum is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should hav received a copy of the GNU General Public License
 * along with md5sum; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

static void MDString (unsigned char *str)
{
	int i;
	unsigned char digest [16];

	md5 (str, strlen ((char *)str), digest);

	/* Display the md5 sum */
	for (i=0; i<16; i++)
		printf ("%02x", digest [i]);
}

static void TestSuite (void) /* Test suite with md5 vectors presents in the RFC1321 */
{
	printf ("MD5(\"\") = ");
	MDString ((unsigned char *)"");
	printf ("\nMD5(\"a\") = ");
	MDString ((unsigned char *)"a");
	printf ("\nMD5(\"abc\") = ");
	MDString ((unsigned char *)"abc");
	printf ("\nMD5(\"message digest\") = ");
	MDString ((unsigned char *)"message digest");
	printf ("\nMD5(\"abcdefghijklmnopqrstuvwxyz\") = ");
	MDString ((unsigned char *)"abcdefghijklmnopqrstuvwxyz");
	printf ("\nMD5(\"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\") = ");
	MDString ((unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	printf ("\nMD5(\"12345678901234567890123456789012345678901234567890123456789012345678901234567890\") = ");
	MDString ((unsigned char *)"12345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

static void MDFile (FILE *f, struct md5_ctx *ctx)
{
	int i;
	unsigned char digest [16];
	
	md5_init (ctx);
	while (!feof (f)) {
		ctx->size += fread (ctx->buf + ctx->size, 1, MD5_BUFFER - ctx->size, f);
		md5_update (ctx);
	}
	md5_final (digest, ctx);

	for (i=0; i<16; i++)
		printf ("%02x", digest [i]);
}

int main (int argc, char **argv)
{
	struct md5_ctx ctx;
	FILE *f;
	
	if (argc > 1)
		if (strcmp (argv [1], "-x") == 0) {
			printf ("md5sum test suite\n");
			TestSuite ();
			printf ("\n");
			return 0;
		}

	if (argc > 1) {
		while (*(++argv)) {
			if ((*argv) [0] == '-') {
				printf ("Argument unknown : %s\n", *argv);
				continue;
			}
			if ((f = fopen (*argv, "r")) == NULL)
				perror ("md5sum");
			else {
				MDFile (f, &ctx);
				printf ("  %s\n", *argv);
			}
		}
		return 0;
	}
	
	MDFile (stdin, &ctx);
	printf ("  -\n");

	return 0;
}
