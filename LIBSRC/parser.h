/* SPIM S20 MIPS simulator.
   Interface to parser for instructions and assembler directives.

   Copyright (C) 1990-2000 by James Larus (larus@cs.wisc.edu).
   ALL RIGHTS RESERVED.

   SPIM is distributed under the following conditions:

     You may make copies of SPIM for your own use and modify those copies.

     All copies of SPIM must retain my name and copyright notice.

     You may not sell SPIM or distributed SPIM in conjunction with a
     commerical product or service without the expressed written consent of
     James Larus.

   THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   PURPOSE. */


/* $Header: /Software/SPIM/src/parser.h 6     12/24/00 1:37p Larus $
*/

/* Type declarations for portability.  They work for DEC's Alpha (64 bits)
   and 32 bit machines */

typedef int int32;
typedef unsigned int  uint32;
typedef union {int i; void* p;} intptr_union;

#define streq(s1, s2) !strcmp(s1, s2)


/* Minimum and maximum values that fit in instruction's imm field */
#define IMM_MIN -(1<<15)
#define IMM_MAX ((1<<15)-1)

#define UIMM_MIN  0
#define UIMM_MAX  ((1<<16)-1)



/* Exported functions: */

#ifdef __STDC__
void initialize_parser (char *file_name);
void yyerror (char *s);
int yyparse (void);
t_asm_line *get_pointer_to_parsed_line(void);
void parser_close_file(void) ;
void scanner_store_comment(char *str, int length);
#else
void initialize_parser ();
void yyerror ();
int yyparse ();
t_asm_line *get_pointer_to_parsed_line();
void parser_close_file() ;
void scanner_store_comment();
#endif


/* Exported Variables: */

extern int parse_error_occurred;  /* Non-zero => parse resulted in error */

/*--------------------------    end of file -------------------------------------*/
