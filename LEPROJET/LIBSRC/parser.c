#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 303 "parser.y"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "analyseur.h"
#include "parser.h"
#include "scanner.h"


/* return (0) */
#define LINE_PARSE_DONE YYACCEPT

/* return (1) */
#define FILE_PARSE_DONE YYABORT

/* Exported Variables: */

int parse_error_occurred;  /* Non-zero => parse resulted in error */


/* Local functions: */

#ifdef __STDC__
/*
static void check_imm_range (int32, int32, int32);
static void check_uimm_range (uint32, uint32, uint32);
*/
static void yywarn (char*);
static void store_double (double *value);
static void store_float (double *value);
static void dir_with_one_int_op(int directive_id , int operand);


#else
/*
static void check_imm_range();
static void check_uimm_range();
*/
static void yywarn ();
static void store_double ();
static void store_float ();
static void dir_with_one_int_op();
#endif

/* Static Global Variables: */

/*
Contains representation of the parsed line. See analyseur.h for the details
of a t_asm_line record
*/
static t_asm_line La_ligne ;

static int data_dir;                   /* Non-zero means item in data segment */

static int text_dir;                   /* Non-zero means item in text segment */

static	FILE *parsed_file = NULL ; /* File descriptor of the file to parse*/

static int null_term;		/* Non-zero means string terminate by \0 */

static void (*store_op) ();	/* Function to store items in an EXPR_LST */

static int noat_flag = 0;	/* Non-zero means program can use $1 */

static char *input_file_name;	/* Name of file being parsed */


static t_operand address_operand ; /* Stores the representation of the
					address expression when the non-terminal
					ADDRESS is recogonized                */
static t_operand imm_operand ; /* Stores the representation of the operand
					when the non-terminal
					IMM32(IMM32, IMM16, and their unsigned
					peers) is recogonized                */

static int_record *int_operands_queue; /* points to the queue of a list of 
					int operands (.byte, .half, .word
				 	directives 			   */
static float_record *float_operands_queue; /* points to the queue of a list of 
					int operands (.float directive)	   */
static double_record *double_operands_queue; /* points to the queue of a list of
					double operands (.double directive)    */

#line 95 "parser.c"
#define Y_EOF 257
#define Y_NL 258
#define Y_INT 259
#define Y_ID 260
#define Y_REG 261
#define Y_FP_REG 262
#define Y_STR 263
#define Y_FP 264
#define Y_ABS_D_OP 265
#define Y_ABS_S_OP 266
#define Y_ADDIU_OP 267
#define Y_ADDI_OP 268
#define Y_ADDU_OP 269
#define Y_ADD_D_OP 270
#define Y_ADD_OP 271
#define Y_ADD_S_OP 272
#define Y_ANDI_OP 273
#define Y_AND_OP 274
#define Y_BC0F_OP 275
#define Y_BC0T_OP 276
#define Y_BC1F_OP 277
#define Y_BC1T_OP 278
#define Y_BC2F_OP 279
#define Y_BC2T_OP 280
#define Y_BC3F_OP 281
#define Y_BC3T_OP 282
#define Y_BEQ_OP 283
#define Y_BGEZAL_OP 284
#define Y_BGEZ_OP 285
#define Y_BGTZ_OP 286
#define Y_BLEZ_OP 287
#define Y_BLTZAL_OP 288
#define Y_BLTZ_OP 289
#define Y_BNE_OP 290
#define Y_BREAK_OP 291
#define Y_CFC0_OP 292
#define Y_CFC1_OP 293
#define Y_CFC2_OP 294
#define Y_CFC3_OP 295
#define Y_COP0_OP 296
#define Y_COP1_OP 297
#define Y_COP2_OP 298
#define Y_COP3_OP 299
#define Y_CTC0_OP 300
#define Y_CTC1_OP 301
#define Y_CTC2_OP 302
#define Y_CTC3_OP 303
#define Y_CVT_D_S_OP 304
#define Y_CVT_D_W_OP 305
#define Y_CVT_S_D_OP 306
#define Y_CVT_S_W_OP 307
#define Y_CVT_W_D_OP 308
#define Y_CVT_W_S_OP 309
#define Y_C_EQ_D_OP 310
#define Y_C_EQ_S_OP 311
#define Y_C_F_D_OP 312
#define Y_C_F_S_OP 313
#define Y_C_LE_D_OP 314
#define Y_C_LE_S_OP 315
#define Y_C_LT_D_OP 316
#define Y_C_LT_S_OP 317
#define Y_C_NGE_D_OP 318
#define Y_C_NGE_S_OP 319
#define Y_C_NGLE_D_OP 320
#define Y_C_NGLE_S_OP 321
#define Y_C_NGL_D_OP 322
#define Y_C_NGL_S_OP 323
#define Y_C_NGT_D_OP 324
#define Y_C_NGT_S_OP 325
#define Y_C_OLT_D_OP 326
#define Y_C_OLT_S_OP 327
#define Y_C_OLE_D_OP 328
#define Y_C_OLE_S_OP 329
#define Y_C_SEQ_D_OP 330
#define Y_C_SEQ_S_OP 331
#define Y_C_SF_D_OP 332
#define Y_C_SF_S_OP 333
#define Y_C_UEQ_D_OP 334
#define Y_C_UEQ_S_OP 335
#define Y_C_ULT_D_OP 336
#define Y_C_ULT_S_OP 337
#define Y_C_ULE_D_OP 338
#define Y_C_ULE_S_OP 339
#define Y_C_UN_D_OP 340
#define Y_C_UN_S_OP 341
#define Y_DIVU_OP 342
#define Y_DIV_D_OP 343
#define Y_DIV_OP 344
#define Y_DIV_S_OP 345
#define Y_JALR_OP 346
#define Y_JAL_OP 347
#define Y_JR_OP 348
#define Y_J_OP 349
#define Y_LBU_OP 350
#define Y_LB_OP 351
#define Y_LHU_OP 352
#define Y_LH_OP 353
#define Y_LUI_OP 354
#define Y_LWC0_OP 355
#define Y_LWC1_OP 356
#define Y_LWC2_OP 357
#define Y_LWC3_OP 358
#define Y_LWL_OP 359
#define Y_LWR_OP 360
#define Y_LW_OP 361
#define Y_MFC0_OP 362
#define Y_MFC1_OP 363
#define Y_MFC2_OP 364
#define Y_MFC3_OP 365
#define Y_MFHI_OP 366
#define Y_MFLO_OP 367
#define Y_MOV_D_OP 368
#define Y_MOV_S_OP 369
#define Y_MTC0_OP 370
#define Y_MTC1_OP 371
#define Y_MTC2_OP 372
#define Y_MTC3_OP 373
#define Y_MTHI_OP 374
#define Y_MTLO_OP 375
#define Y_MULTU_OP 376
#define Y_MULT_OP 377
#define Y_MUL_D_OP 378
#define Y_MUL_S_OP 379
#define Y_NEG_D_OP 380
#define Y_NEG_S_OP 381
#define Y_NOR_OP 382
#define Y_ORI_OP 383
#define Y_OR_OP 384
#define Y_PFW_OP 385
#define Y_RFE_OP 386
#define Y_SB_OP 387
#define Y_SH_OP 388
#define Y_SLLV_OP 389
#define Y_SLL_OP 390
#define Y_SLTIU_OP 391
#define Y_SLTI_OP 392
#define Y_SLTU_OP 393
#define Y_SLT_OP 394
#define Y_SRAV_OP 395
#define Y_SRA_OP 396
#define Y_SRLV_OP 397
#define Y_SRL_OP 398
#define Y_SUBU_OP 399
#define Y_SUB_D_OP 400
#define Y_SUB_OP 401
#define Y_SUB_S_OP 402
#define Y_SWC0_OP 403
#define Y_SWC1_OP 404
#define Y_SWC2_OP 405
#define Y_SWC3_OP 406
#define Y_SWL_OP 407
#define Y_SWR_OP 408
#define Y_SW_OP 409
#define Y_SYSCALL_OP 410
#define Y_TLBP_OP 411
#define Y_TLBR_OP 412
#define Y_TLBWI_OP 413
#define Y_TLBWR_OP 414
#define Y_XORI_OP 415
#define Y_XOR_OP 416
#define Y_ABS_POP 417
#define Y_BAL_POP 418
#define Y_BEQZ_POP 419
#define Y_BGEU_POP 420
#define Y_BGE_POP 421
#define Y_BGTU_POP 422
#define Y_BGT_POP 423
#define Y_BLEU_POP 424
#define Y_BLE_POP 425
#define Y_BLTU_POP 426
#define Y_BLT_POP 427
#define Y_BNEZ_POP 428
#define Y_B_POP 429
#define Y_LA_POP 430
#define Y_LD_POP 431
#define Y_LI_POP 432
#define Y_LI_D_POP 433
#define Y_LI_S_POP 434
#define Y_L_D_POP 435
#define Y_L_S_POP 436
#define Y_MFC1_D_POP 437
#define Y_MTC1_D_POP 438
#define Y_MOVE_POP 439
#define Y_MULOU_POP 440
#define Y_MULO_POP 441
#define Y_MUL_POP 442
#define Y_NEGU_POP 443
#define Y_NEG_POP 444
#define Y_NOP_POP 445
#define Y_NOT_POP 446
#define Y_REMU_POP 447
#define Y_REM_POP 448
#define Y_ROL_POP 449
#define Y_ROR_POP 450
#define Y_SD_POP 451
#define Y_SEQ_POP 452
#define Y_SGEU_POP 453
#define Y_SGE_POP 454
#define Y_SGTU_POP 455
#define Y_SGT_POP 456
#define Y_SLEU_POP 457
#define Y_SLE_POP 458
#define Y_SNE_POP 459
#define Y_S_D_POP 460
#define Y_S_S_POP 461
#define Y_ULHU_POP 462
#define Y_ULH_POP 463
#define Y_ULW_POP 464
#define Y_USH_POP 465
#define Y_USW_POP 466
#define Y_ALIAS_DIR 467
#define Y_ALIGN_DIR 468
#define Y_ASCII_DIR 469
#define Y_ASCIIZ_DIR 470
#define Y_ASM0_DIR 471
#define Y_AT_DIR 472
#define Y_BGNB_DIR 473
#define Y_BYTE_DIR 474
#define Y_COMM_DIR 475
#define Y_DATA_DIR 476
#define Y_DOUBLE_DIR 477
#define Y_ENDB_DIR 478
#define Y_ENDR_DIR 479
#define Y_END_DIR 480
#define Y_ENT_DIR 481
#define Y_ERR_DIR 482
#define Y_EXTERN_DIR 483
#define Y_FILE_DIR 484
#define Y_FLOAT_DIR 485
#define Y_FMASK_DIR 486
#define Y_FRAME_DIR 487
#define Y_GLOBAL_DIR 488
#define Y_HALF_DIR 489
#define Y_K_TEXT_DIR 490
#define Y_K_DATA_DIR 491
#define Y_LABEL_DIR 492
#define Y_LCOMM_DIR 493
#define Y_LIVEREG_DIR 494
#define Y_LOC_DIR 495
#define Y_MASK_DIR 496
#define Y_NOALIAS_DIR 497
#define Y_NOAT_DIR 498
#define Y_OPTIONS_DIR 499
#define Y_RDATA_DIR 500
#define Y_REPEAT_DIR 501
#define Y_SDATA_DIR 502
#define Y_SET_DIR 503
#define Y_SPACE_DIR 504
#define Y_STRUCT_DIR 505
#define Y_TEXT_DIR 506
#define Y_VERSTAMP_DIR 507
#define Y_VREG_DIR 508
#define Y_WORD_DIR 509
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    2,    0,    1,    1,    3,    3,    8,    4,   10,    4,
    4,    7,    7,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,   11,
   11,   11,   11,   11,   11,   11,   11,   11,   14,   14,
   14,   16,   20,   20,   21,   21,   21,   22,   22,   22,
   22,   22,   22,   24,   24,   24,   25,   25,   25,   27,
   27,   29,   29,   29,   29,   29,   29,   29,   31,   31,
   31,   32,   32,   32,   32,   33,   33,   33,   35,   35,
   35,   36,   37,   37,   38,   38,   38,   38,   39,   39,
   39,   41,   41,   42,   42,   43,   43,   44,   44,   40,
   40,   45,   45,   45,   45,   45,   45,   45,   45,   47,
   47,   47,   47,   47,   47,   48,   48,   49,   49,   51,
   51,   52,   52,   53,   53,   54,   54,   55,   55,   55,
   55,   57,   57,   58,   58,   59,   59,   61,   61,   62,
   62,   62,   62,   62,   62,   62,   62,   62,   62,   63,
   63,   63,   63,   63,   63,   63,   63,   64,   64,   65,
   65,   65,   65,   65,   65,   65,   65,   67,   67,   67,
   67,   67,   67,   68,   68,   69,   69,   69,   69,   69,
   69,   69,   69,   69,   69,   69,   69,   69,   69,   69,
   69,   69,   69,   69,   69,   69,   69,   69,   69,   69,
   69,   69,   69,   69,   69,   69,   69,    9,    9,   72,
    9,   73,    9,    9,    9,    9,    9,   75,    9,    9,
    9,    9,    9,    9,   77,    9,    9,    9,    9,    9,
    9,    9,    9,    9,   79,    9,    9,    9,    9,   81,
    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
    9,    9,    9,    9,    9,    9,    9,    9,    9,    9,
    9,    9,   83,    9,   85,   13,   84,   84,   84,   84,
   84,   84,   84,   84,   84,   84,   87,   50,   17,   34,
   18,   18,   18,   18,   18,   86,   86,   86,   12,   28,
   30,   56,   60,   23,   80,   19,   26,   66,   88,   15,
   15,   46,   89,   89,   71,   71,   91,   90,   70,   82,
   82,   74,   74,   74,   76,   76,   93,   78,   92,   92,
   94,    5,
};
short yylen[] = {                                         2,
    0,    2,    2,    1,    2,    3,    0,    3,    0,    3,
    1,    1,    1,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    1,    2,
    1,    3,    3,    3,    3,    3,    4,    4,    3,    4,
    4,    3,    4,    3,    4,    3,    4,    4,    4,    4,
    3,    4,    4,    3,    3,    4,    4,    4,    4,    3,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    2,    3,    3,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    2,    2,    3,    2,    3,
    2,    2,    3,    3,    3,    4,    3,    3,    3,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    3,    2,    0,
    3,    0,    3,    1,    1,    1,    2,    0,    3,    3,
    1,    2,    1,    2,    0,    3,    2,    2,    1,    2,
    3,    3,    1,    3,    0,    3,    3,    4,    2,    0,
    3,    2,    3,    3,    3,    3,    3,    2,    2,    1,
    2,    1,    2,    2,    2,    2,    1,    2,    1,    2,
    3,    4,    0,    3,    0,    2,    3,    1,    4,    1,
    4,    3,    3,    3,    6,    6,    0,    2,    1,    1,
    1,    6,    1,    3,    3,    1,    3,    2,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    2,    1,    1,    3,    0,    2,    1,    1,
    1,    2,    1,    3,    2,    1,    0,    2,    1,    0,
    0,    2,
};
short yydefred[] = {                                      1,
    0,    0,   13,   12,  229,  228,  143,  142,  133,  231,
  132,  230,  146,  134,  176,  172,  177,  173,  178,  174,
  179,  175,  188,  181,  180,  182,  183,  185,  184,  189,
    0,  220,  221,  222,  223,  224,  225,  226,  227,  238,
  239,  240,  241,  242,  243,  264,  248,  262,  246,  276,
  260,  274,  258,  275,  259,  271,  255,  273,  257,  277,
  261,  266,  250,  267,  251,  272,  256,  270,  254,  265,
  249,  268,  252,  269,  253,  263,  247,  156,  233,  155,
  232,  201,  200,  199,  198,  101,  100,  103,  102,  112,
  109,  115,  110,  111,  105,  106,  104,  210,  211,  213,
  214,  206,  207,  205,  204,  215,  216,  218,  219,  208,
  209,  171,  170,  235,  234,  245,  244,  152,  147,  136,
  108,  130,  118,  119,  139,  149,  145,  144,  138,  137,
  140,  150,  141,  151,  154,  237,  153,  236,  124,  127,
  125,  126,  121,  122,  120,  131,  148,  135,    0,  203,
  186,  193,  192,  191,  190,  197,  196,  195,  194,  187,
  202,    0,  107,    0,    0,    0,  117,  116,  212,  217,
    0,  161,  160,  159,    0,    0,   31,    0,  158,  157,
    0,    0,  123,  168,  167,  166,  165,  164,  163,  162,
  169,  129,  128,  114,  113,    0,    0,    0,    0,    0,
  280,  282,  286,  284,    0,  288,  391,    0,  295,    0,
  299,  387,  391,  303,  391,    0,  305,    0,    0,  391,
  310,    0,    0,  391,  391,    0,    0,    0,    0,  285,
  391,    0,    0,    0,  391,    0,    0,    0,    0,    0,
  333,    2,    0,    4,    0,    7,   11,    9,    0,    0,
    0,    0,    0,    0,    0,    0,   29,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  391,    0,    0,    0,    0,    0,    0,    0,    0,
  391,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   30,  365,    0,  359,  335,    0,  369,    0,
  366,    0,    0,    0,    0,    0,    0,    0,  335,  335,
  364,  335,    0,  379,  279,    0,    0,  287,  377,    0,
  292,    0,  298,  297,    0,    0,    0,    0,    0,    0,
    0,  309,  377,  330,  294,  312,    0,    0,    0,    0,
    0,  318,  321,  319,  323,  324,  325,  326,  328,    0,
    0,    0,    3,    5,    0,    0,    0,  335,  370,  371,
  335,    0,  335,  335,  335,  335,  335,  367,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  360,    0,
    0,    0,    0,  372,   73,  391,  391,    0,    0,    0,
    0,    0,   87,   86,    0,    0,   89,    0,   91,  363,
   92,    0,    0,    0,    0,    0,    0,    0,  392,   32,
   17,    0,    0,    0,    0,  353,   18,  351,   19,   20,
   36,   34,   33,   35,    0,    0,   21,   27,   26,  278,
    0,  281,  283,    0,    0,    0,  290,  386,    0,  389,
  388,  301,  302,  304,    0,  307,    0,    0,  313,  314,
  315,  316,  317,  331,    0,  380,    0,  334,    6,    8,
   10,   14,   15,   16,  349,   22,   23,   24,   25,   28,
   39,    0,   42,    0,   44,    0,  350,    0,   46,    0,
   51,    0,   54,    0,    0,    0,   60,  361,    0,    0,
    0,    0,   74,   75,  391,  391,    0,  391,  391,  391,
  391,  391,  391,  391,  391,   88,   90,   93,   94,   95,
    0,   97,  368,   98,   99,    0,    0,  336,    0,  358,
    0,    0,    0,    0,   64,   62,   63,   61,    0,  382,
    0,  378,  385,  308,  332,   38,   37,   41,   40,   43,
   45,   47,   48,   50,   49,   53,   52,   57,   56,   59,
   58,   66,   65,   68,   67,   70,   69,   72,   71,   76,
   77,  348,   78,   79,   80,   81,   82,   83,   84,   85,
   96,    0,    0,    0,    0,    0,  391,  357,  354,  355,
    0,  376,  384,    0,    0,    0,  337,    0,  343,    0,
  341,    0,    0,  339,    0,    0,    0,  352,  345,  346,
};
short yydgoto[] = {                                       1,
  242,    2,  243,  244,  416,  246,  247,  356,  248,  357,
  249,  295,  411,  250,  361,  251,  464,  465,  300,  252,
  253,  254,  310,  255,  256,  367,  257,  378,  258,  487,
  259,  260,  261,  479,  262,  263,  264,  265,  266,  267,
  268,  269,  270,  271,  272,  385,  273,  274,  275,  496,
  276,  277,  278,  279,  280,  395,  281,  282,  283,  399,
  284,  285,  286,  287,  288,  512,  289,  290,  291,  315,
  432,  316,  317,  434,  319,  439,  322,  324,  329,  379,
  333,  458,  352,  518,  412,  418,  497,  301,    0,  435,
  436,  441,  325,  292,
};
short yysindex[] = {                                      0,
    0,  276,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -240,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -232,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -232,    0, -232, -219, -219,    0,    0,    0,    0,
 -232,    0,    0,    0, -232, -232,    0, -232,    0,    0,
 -232, -232,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -232, -232, -232, -210, -196,
    0,    0,    0,    0, -193,    0,    0, -185,    0, -182,
    0,    0,    0,    0,    0, -153,    0, -136, -232,    0,
    0, -131, -124,    0,    0, -105,  -98,  -96, -191,    0,
    0,  -84, -196,  -72,    0, -196, -196,  -53,  -47, -232,
    0,    0,  276,    0,  -11,    0,    0,    0, -232, -163,
 -232, -232, -219, -232, -163, -219,    0, -232, -232, -232,
 -232, -232, -232, -232, -232, -232, -232, -232, -232, -232,
 -232,    0, -232, -232, -232, -232, -232, -232, -232, -232,
    0, -163, -232, -232, -232, -163, -219, -219, -219, -219,
 -219, -116,    0,    0, -232,    0,    0,  -29,    0, -160,
    0,  -83, -232, -232, -232, -232, -232, -232,    0,    0,
    0,    0,  -76,    0,    0,  -59,  -59,    0,    0, -196,
    0,  -48,    0,    0,    0,  -42, -196,  -43,  -48,  -38,
  -35,    0,    0,    0,    0,    0, -196,  -31,  -27,  -22,
  -21,    0,    0,    0,    0,    0,    0,    0,    0,  -10,
   -9,    0,    0,    0,   -8, -157, -157,    0,    0,    0,
    0,  -29,    0,    0,    0,    0,    0,    0,  -34, -246,
  -34,  -34, -232,  -34,  -34, -232, -232, -232,    0, -232,
 -232, -232, -232,    0,    0,    0,    0, -232, -232, -232,
 -232, -232,    0,    0, -232,    0,    0, -163,    0,    0,
    0, -163, -163, -219, -219, -219, -219, -219,    0,    0,
    0,  -24,  -40,   24,   -7,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -34,  -34,    0,    0,    0,    0,
  195,    0,    0,    0,  207, -196,    0,    0,    2,    0,
    0,    0,    0,    0,    2,    0, -232,    0,    0,    0,
    0,    0,    0,    0,    8,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -34,    0, -167,    0,  -29,    0,  -29,    0, -166,
    0,  -34,    0,  -34,  -34,  -34,    0,    0,  -34,  -34,
  -34,  -34,    0,    0,    0,    0,  -29,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -219,    0,    0,    0,    0,  -15, -232,    0,   21,    0,
    9,   -7,   -7,  228,    0,    0,    0,    0,   13,    0,
   14,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -232,   -7,   -7,  233, -232,    0,    0,    0,    0,
  213,    0,    0,  235,  237,  240,    0,  242,    0,  222,
    0, -232, -232,    0,   26,  245,  246,    0,    0,    0,
};
short yyrindex[] = {                                      0,
    0,   28,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -155,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -145, -115,    0,    0,    0,    0,    0,    0,    0,
    0, -110,    0,  -99,    0,    0,    0,  -91,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   28,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -198,  -89,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -86,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -17,  -17,  -17,
  -17,  -17,    0,    0,    0, -216,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -19,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -87,    0,    0, -177, -174,    0,    0,    0,  -80,    0,
    0,    0,    0,    0,  -78,    0,    0, -171,    0,    0,
    0,    0,    0,    0,    0,    0, -168,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -74,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -66,    0,    0,  -60,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -58,  -55,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,    0,    0,   47,   -2,    0, -147,    0,    0,    0,
    0,  143,   57,    0, -238,    0, -367, -296, -156,    0,
    0,    0, -189,    0,    0, -267,    0,   83,    0,   46,
    0,    0,    0, -187,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -241,    0,    0,    0, -334,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -70,
    0,    0,    0,    0,    0, -400,    0,    0,    0, -165,
  -28,    0,    0, -319,    0,  -37,    0,    0,    0, -144,
    0,    0,    0,    0,    0, -366,    0, -255,    0, -422,
    0,    0,    0,    0,
};
#define YYTABLESIZE 785
short yytable[] = {                                     245,
  368,  417,  521,  475,  296,  415,  514,  515,  312,  302,
  415,  530,  473,  448,  294,  517,  366,  296,  293,  296,
  356,  356,  347,  408,  572,  530,  296,  573,  294,  574,
  296,  296,  457,  296,  530,  368,  296,  296,  394,  397,
  360,  360,  299,  398,  362,  519,  354,  403,  524,  355,
  313,  296,  311,  311,  499,  501,  503,  505,  390,  390,
  576,  391,  314,  577,  365,  318,  522,  344,  523,  341,
  347,  348,  471,  321,  331,  477,  323,  481,  483,  289,
  289,  377,  383,  383,  383,  311,  311,  377,  381,  381,
  377,  538,  542,  294,  294,  351,  364,  359,  360,    3,
    4,  291,  291,  419,  296,  328,  296,  296,  540,  311,
  571,  329,  329,  296,  296,  296,  296,  296,  296,  296,
  296,  296,  330,  296,  296,  296,  296,  334,  525,  527,
  404,  405,  406,  407,  335,  396,  510,  511,  400,  400,
  400,  293,  293,  409,  493,  494,  320,  320,  368,  368,
  513,  513,  513,  338,  437,  579,  580,  322,  322,  507,
  339,  443,  340,  508,  509,  327,  327,  300,  300,  375,
  375,  449,  377,  391,  343,  536,  296,  296,  306,  306,
  420,  477,   55,   55,  430,  544,  345,  546,  548,  550,
  340,  340,  552,  554,  556,  558,  338,  338,  342,  342,
  562,  344,  344,  431,  320,  349,  585,  586,  460,  461,
  326,  350,  327,  401,  402,  438,  442,  332,  520,  444,
  446,  336,  337,  447,  413,  414,  294,  450,  342,  413,
  414,  451,  346,  488,  413,  516,  452,  356,  356,  453,
  356,  347,  347,  488,  488,  488,  488,  488,  454,  455,
  459,  413,  529,  560,  561,  513,  563,  564,  565,  566,
  567,  568,  569,  570,  531,  533,  535,  578,  581,  384,
  532,  582,  583,  587,  590,  591,  592,  384,  384,  593,
  488,  488,  594,  595,  598,  599,  600,  391,  433,  353,
  541,  445,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  534,    0,  297,    0,  298,    0,    0,    0,
    0,    0,    0,  303,    0,    0,    0,  304,  305,    0,
  306,    0,  440,  307,  308,    0,    0,  488,    0,  488,
    0,    0,    0,    0,    0,  488,    0,  488,  309,  488,
  488,  488,    0,    0,  488,  488,  488,  488,    0,  456,
    0,    0,    0,    0,    0,  386,  387,  388,  389,  390,
  391,  392,  393,    0,    0,  427,  428,    0,  429,    0,
    0,    0,  575,    0,    0,    0,    0,  410,    0,    0,
    0,    0,    0,  384,  384,  421,  422,  423,  424,  425,
  426,  358,    0,  362,  363,    0,    0,    0,    0,    0,
  369,  370,  371,  372,  373,  374,  375,  376,  377,    0,
  380,  381,  382,  383,  462,    0,    0,  463,    0,  466,
  467,  468,  469,  470,    0,    0,    0,  584,    0,    0,
    0,  588,    0,  495,  498,  500,  502,  504,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  596,  597,    0,
    0,  472,  474,  476,  478,  480,  482,  484,  485,  486,
    0,    0,  489,  490,  491,  492,    0,    0,    0,    0,
  526,  528,    0,    0,    0,    0,    0,  506,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  384,  384,    0,  384,  384,  384,  384,  384,
  384,  384,  384,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  537,    0,  539,
    0,    0,    0,    0,    0,  543,    0,  545,    0,  547,
  549,  551,    3,    4,  553,  555,  557,  559,    0,    0,
    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,
   25,   26,   27,   28,   29,   30,   31,   32,   33,   34,
   35,    0,    0,    0,  589,   36,   37,   38,   39,   40,
   41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
   51,   52,   53,   54,   55,   56,   57,   58,   59,   60,
   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
   71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
   91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
  101,  102,  103,  104,  105,  106,  107,  108,  109,  110,
  111,  112,  113,  114,  115,  116,  117,  118,  119,  120,
  121,  122,  123,  124,  125,  126,  127,  128,  129,  130,
  131,  132,  133,  134,  135,  136,  137,  138,  139,  140,
  141,  142,  143,  144,  145,  146,    0,    0,    0,    0,
  147,  148,  149,  150,  151,  152,  153,  154,  155,  156,
  157,  158,  159,  160,  161,  162,  163,  164,  165,  166,
  167,  168,  169,  170,  171,  172,  173,  174,  175,  176,
  177,  178,  179,  180,  181,  182,  183,  184,  185,  186,
  187,  188,  189,  190,  191,  192,  193,  194,  195,  196,
  197,  198,  199,  200,  201,  202,  203,  204,  205,  206,
  207,  208,  209,  210,  211,  212,  213,  214,  215,  216,
  217,  218,  219,  220,  221,  222,  223,  224,  225,  226,
  227,  228,  229,  230,  231,  232,  233,  234,  235,  236,
  237,  238,  239,  240,  241,
};
short yycheck[] = {                                       2,
  256,  298,   43,  371,  149,   40,  407,  408,  198,  166,
   40,  434,  259,  333,  261,   40,  255,  162,  259,  164,
   40,   41,   40,  291,   40,  448,  171,   43,  261,   45,
  175,  176,  352,  178,  457,  291,  181,  182,  280,  281,
  257,  258,  262,  282,  261,  412,   58,  286,  415,   61,
  261,  196,  197,  198,  389,  390,  391,  392,  257,  258,
   40,  260,  259,   43,  254,  259,   43,  233,   45,  261,
  236,  237,  369,  259,  219,  372,  259,  374,  375,  257,
  258,  259,  257,  258,  259,  257,  258,  259,  257,  258,
  259,  259,  259,  261,  261,  240,  253,  261,  262,  257,
  258,  257,  258,  264,  249,  259,  251,  252,  476,  254,
  511,  257,  258,  258,  259,  260,  261,  262,  263,  264,
  265,  266,  259,  268,  269,  270,  271,  259,  425,  426,
  287,  288,  289,  290,  259,  280,  404,  405,  283,  284,
  285,  257,  258,  260,  386,  387,  257,  258,  404,  405,
  406,  407,  408,  259,  320,  522,  523,  257,  258,  398,
  259,  327,  259,  402,  403,  257,  258,  257,  258,  257,
  258,  337,  259,  260,  259,  472,  257,  258,  257,  258,
  264,  478,  257,  258,  261,  482,  259,  484,  485,  486,
  257,  258,  489,  490,  491,  492,  257,  258,  257,  258,
  497,  257,  258,  263,  207,  259,  573,  574,  356,  357,
  213,  259,  215,  284,  285,  264,  259,  220,  259,  263,
  259,  224,  225,  259,  259,  260,  261,  259,  231,  259,
  260,  259,  235,  378,  259,  260,  259,  257,  258,  261,
  260,  259,  260,  388,  389,  390,  391,  392,  259,  259,
  259,  259,   58,  495,  496,  511,  498,  499,  500,  501,
  502,  503,  504,  505,   58,  264,  259,  259,   41,  272,
  436,  259,  259,   41,   62,   41,   40,  280,  281,   40,
  425,  426,   41,   62,  259,   41,   41,  260,  317,  243,
  478,  329,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  447,   -1,  162,   -1,  164,   -1,   -1,   -1,
   -1,   -1,   -1,  171,   -1,   -1,   -1,  175,  176,   -1,
  178,   -1,  325,  181,  182,   -1,   -1,  472,   -1,  474,
   -1,   -1,   -1,   -1,   -1,  480,   -1,  482,  196,  484,
  485,  486,   -1,   -1,  489,  490,  491,  492,   -1,  352,
   -1,   -1,   -1,   -1,   -1,  273,  274,  275,  276,  277,
  278,  279,  280,   -1,   -1,  309,  310,   -1,  312,   -1,
   -1,   -1,  517,   -1,   -1,   -1,   -1,  295,   -1,   -1,
   -1,   -1,   -1,  386,  387,  303,  304,  305,  306,  307,
  308,  249,   -1,  251,  252,   -1,   -1,   -1,   -1,   -1,
  258,  259,  260,  261,  262,  263,  264,  265,  266,   -1,
  268,  269,  270,  271,  358,   -1,   -1,  361,   -1,  363,
  364,  365,  366,  367,   -1,   -1,   -1,  572,   -1,   -1,
   -1,  576,   -1,  388,  389,  390,  391,  392,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  592,  593,   -1,
   -1,  369,  370,  371,  372,  373,  374,  375,  376,  377,
   -1,   -1,  380,  381,  382,  383,   -1,   -1,   -1,   -1,
  425,  426,   -1,   -1,   -1,   -1,   -1,  395,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  495,  496,   -1,  498,  499,  500,  501,  502,
  503,  504,  505,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  472,   -1,  474,
   -1,   -1,   -1,   -1,   -1,  480,   -1,  482,   -1,  484,
  485,  486,  257,  258,  489,  490,  491,  492,   -1,   -1,
  265,  266,  267,  268,  269,  270,  271,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
  285,  286,  287,  288,  289,  290,  291,  292,  293,  294,
  295,   -1,   -1,   -1,  577,  300,  301,  302,  303,  304,
  305,  306,  307,  308,  309,  310,  311,  312,  313,  314,
  315,  316,  317,  318,  319,  320,  321,  322,  323,  324,
  325,  326,  327,  328,  329,  330,  331,  332,  333,  334,
  335,  336,  337,  338,  339,  340,  341,  342,  343,  344,
  345,  346,  347,  348,  349,  350,  351,  352,  353,  354,
  355,  356,  357,  358,  359,  360,  361,  362,  363,  364,
  365,  366,  367,  368,  369,  370,  371,  372,  373,  374,
  375,  376,  377,  378,  379,  380,  381,  382,  383,  384,
  385,  386,  387,  388,  389,  390,  391,  392,  393,  394,
  395,  396,  397,  398,  399,  400,  401,  402,  403,  404,
  405,  406,  407,  408,  409,  410,   -1,   -1,   -1,   -1,
  415,  416,  417,  418,  419,  420,  421,  422,  423,  424,
  425,  426,  427,  428,  429,  430,  431,  432,  433,  434,
  435,  436,  437,  438,  439,  440,  441,  442,  443,  444,
  445,  446,  447,  448,  449,  450,  451,  452,  453,  454,
  455,  456,  457,  458,  459,  460,  461,  462,  463,  464,
  465,  466,  467,  468,  469,  470,  471,  472,  473,  474,
  475,  476,  477,  478,  479,  480,  481,  482,  483,  484,
  485,  486,  487,  488,  489,  490,  491,  492,  493,  494,
  495,  496,  497,  498,  499,  500,  501,  502,  503,  504,
  505,  506,  507,  508,  509,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 509
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,"'+'",0,"'-'",0,0,0,0,0,0,0,0,0,0,0,0,"':'",0,0,"'='",
"'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"Y_EOF","Y_NL","Y_INT","Y_ID","Y_REG","Y_FP_REG","Y_STR","Y_FP","Y_ABS_D_OP",
"Y_ABS_S_OP","Y_ADDIU_OP","Y_ADDI_OP","Y_ADDU_OP","Y_ADD_D_OP","Y_ADD_OP",
"Y_ADD_S_OP","Y_ANDI_OP","Y_AND_OP","Y_BC0F_OP","Y_BC0T_OP","Y_BC1F_OP",
"Y_BC1T_OP","Y_BC2F_OP","Y_BC2T_OP","Y_BC3F_OP","Y_BC3T_OP","Y_BEQ_OP",
"Y_BGEZAL_OP","Y_BGEZ_OP","Y_BGTZ_OP","Y_BLEZ_OP","Y_BLTZAL_OP","Y_BLTZ_OP",
"Y_BNE_OP","Y_BREAK_OP","Y_CFC0_OP","Y_CFC1_OP","Y_CFC2_OP","Y_CFC3_OP",
"Y_COP0_OP","Y_COP1_OP","Y_COP2_OP","Y_COP3_OP","Y_CTC0_OP","Y_CTC1_OP",
"Y_CTC2_OP","Y_CTC3_OP","Y_CVT_D_S_OP","Y_CVT_D_W_OP","Y_CVT_S_D_OP",
"Y_CVT_S_W_OP","Y_CVT_W_D_OP","Y_CVT_W_S_OP","Y_C_EQ_D_OP","Y_C_EQ_S_OP",
"Y_C_F_D_OP","Y_C_F_S_OP","Y_C_LE_D_OP","Y_C_LE_S_OP","Y_C_LT_D_OP",
"Y_C_LT_S_OP","Y_C_NGE_D_OP","Y_C_NGE_S_OP","Y_C_NGLE_D_OP","Y_C_NGLE_S_OP",
"Y_C_NGL_D_OP","Y_C_NGL_S_OP","Y_C_NGT_D_OP","Y_C_NGT_S_OP","Y_C_OLT_D_OP",
"Y_C_OLT_S_OP","Y_C_OLE_D_OP","Y_C_OLE_S_OP","Y_C_SEQ_D_OP","Y_C_SEQ_S_OP",
"Y_C_SF_D_OP","Y_C_SF_S_OP","Y_C_UEQ_D_OP","Y_C_UEQ_S_OP","Y_C_ULT_D_OP",
"Y_C_ULT_S_OP","Y_C_ULE_D_OP","Y_C_ULE_S_OP","Y_C_UN_D_OP","Y_C_UN_S_OP",
"Y_DIVU_OP","Y_DIV_D_OP","Y_DIV_OP","Y_DIV_S_OP","Y_JALR_OP","Y_JAL_OP",
"Y_JR_OP","Y_J_OP","Y_LBU_OP","Y_LB_OP","Y_LHU_OP","Y_LH_OP","Y_LUI_OP",
"Y_LWC0_OP","Y_LWC1_OP","Y_LWC2_OP","Y_LWC3_OP","Y_LWL_OP","Y_LWR_OP","Y_LW_OP",
"Y_MFC0_OP","Y_MFC1_OP","Y_MFC2_OP","Y_MFC3_OP","Y_MFHI_OP","Y_MFLO_OP",
"Y_MOV_D_OP","Y_MOV_S_OP","Y_MTC0_OP","Y_MTC1_OP","Y_MTC2_OP","Y_MTC3_OP",
"Y_MTHI_OP","Y_MTLO_OP","Y_MULTU_OP","Y_MULT_OP","Y_MUL_D_OP","Y_MUL_S_OP",
"Y_NEG_D_OP","Y_NEG_S_OP","Y_NOR_OP","Y_ORI_OP","Y_OR_OP","Y_PFW_OP","Y_RFE_OP",
"Y_SB_OP","Y_SH_OP","Y_SLLV_OP","Y_SLL_OP","Y_SLTIU_OP","Y_SLTI_OP","Y_SLTU_OP",
"Y_SLT_OP","Y_SRAV_OP","Y_SRA_OP","Y_SRLV_OP","Y_SRL_OP","Y_SUBU_OP",
"Y_SUB_D_OP","Y_SUB_OP","Y_SUB_S_OP","Y_SWC0_OP","Y_SWC1_OP","Y_SWC2_OP",
"Y_SWC3_OP","Y_SWL_OP","Y_SWR_OP","Y_SW_OP","Y_SYSCALL_OP","Y_TLBP_OP",
"Y_TLBR_OP","Y_TLBWI_OP","Y_TLBWR_OP","Y_XORI_OP","Y_XOR_OP","Y_ABS_POP",
"Y_BAL_POP","Y_BEQZ_POP","Y_BGEU_POP","Y_BGE_POP","Y_BGTU_POP","Y_BGT_POP",
"Y_BLEU_POP","Y_BLE_POP","Y_BLTU_POP","Y_BLT_POP","Y_BNEZ_POP","Y_B_POP",
"Y_LA_POP","Y_LD_POP","Y_LI_POP","Y_LI_D_POP","Y_LI_S_POP","Y_L_D_POP",
"Y_L_S_POP","Y_MFC1_D_POP","Y_MTC1_D_POP","Y_MOVE_POP","Y_MULOU_POP",
"Y_MULO_POP","Y_MUL_POP","Y_NEGU_POP","Y_NEG_POP","Y_NOP_POP","Y_NOT_POP",
"Y_REMU_POP","Y_REM_POP","Y_ROL_POP","Y_ROR_POP","Y_SD_POP","Y_SEQ_POP",
"Y_SGEU_POP","Y_SGE_POP","Y_SGTU_POP","Y_SGT_POP","Y_SLEU_POP","Y_SLE_POP",
"Y_SNE_POP","Y_S_D_POP","Y_S_S_POP","Y_ULHU_POP","Y_ULH_POP","Y_ULW_POP",
"Y_USH_POP","Y_USW_POP","Y_ALIAS_DIR","Y_ALIGN_DIR","Y_ASCII_DIR",
"Y_ASCIIZ_DIR","Y_ASM0_DIR","Y_AT_DIR","Y_BGNB_DIR","Y_BYTE_DIR","Y_COMM_DIR",
"Y_DATA_DIR","Y_DOUBLE_DIR","Y_ENDB_DIR","Y_ENDR_DIR","Y_END_DIR","Y_ENT_DIR",
"Y_ERR_DIR","Y_EXTERN_DIR","Y_FILE_DIR","Y_FLOAT_DIR","Y_FMASK_DIR",
"Y_FRAME_DIR","Y_GLOBAL_DIR","Y_HALF_DIR","Y_K_TEXT_DIR","Y_K_DATA_DIR",
"Y_LABEL_DIR","Y_LCOMM_DIR","Y_LIVEREG_DIR","Y_LOC_DIR","Y_MASK_DIR",
"Y_NOALIAS_DIR","Y_NOAT_DIR","Y_OPTIONS_DIR","Y_RDATA_DIR","Y_REPEAT_DIR",
"Y_SDATA_DIR","Y_SET_DIR","Y_SPACE_DIR","Y_STRUCT_DIR","Y_TEXT_DIR",
"Y_VERSTAMP_DIR","Y_VREG_DIR","Y_WORD_DIR",
};
char *yyrule[] = {
"$accept : LINE",
"$$1 :",
"LINE : $$1 LBL_CMD",
"LBL_CMD : OPT_LBL CMD",
"LBL_CMD : CMD",
"OPT_LBL : ID ':'",
"OPT_LBL : ID '=' Y_INT",
"$$2 :",
"CMD : ASM_CODE $$2 TERM",
"$$3 :",
"CMD : ASM_DIRECTIVE $$3 TERM",
"CMD : TERM",
"TERM : Y_NL",
"TERM : Y_EOF",
"ASM_CODE : LOAD_OP DEST_REG ADDRESS",
"ASM_CODE : LOAD_COP COP_REG ADDRESS",
"ASM_CODE : LOAD_IMM_OP DEST_REG IMM16",
"ASM_CODE : Y_LA_POP DEST_REG ADDRESS",
"ASM_CODE : Y_LI_POP DEST_REG IMM32",
"ASM_CODE : Y_LI_D_POP F_DEST Y_FP",
"ASM_CODE : Y_LI_S_POP F_DEST Y_FP",
"ASM_CODE : Y_ULW_POP DEST_REG ADDRESS",
"ASM_CODE : ULOADH_POP DEST_REG ADDRESS",
"ASM_CODE : LOADF_OP F_DEST ADDRESS",
"ASM_CODE : STORE_OP SOURCE ADDRESS",
"ASM_CODE : STORE_COP COP_REG ADDRESS",
"ASM_CODE : Y_USW_POP SOURCE ADDRESS",
"ASM_CODE : Y_USH_POP SOURCE ADDRESS",
"ASM_CODE : STOREF_OP F_SRC1 ADDRESS",
"ASM_CODE : SYS_OP",
"ASM_CODE : Y_BREAK_OP Y_INT",
"ASM_CODE : Y_NOP_POP",
"ASM_CODE : Y_ABS_POP DEST_REG SRC1",
"ASM_CODE : Y_NEG_POP DEST_REG SRC1",
"ASM_CODE : Y_NEGU_POP DEST_REG SRC1",
"ASM_CODE : Y_NOT_POP DEST_REG SRC1",
"ASM_CODE : Y_MOVE_POP DEST_REG SRC1",
"ASM_CODE : BINARY_OP_I DEST_REG SRC1 SRC2",
"ASM_CODE : BINARY_OP_I DEST_REG SRC1 IMM32",
"ASM_CODE : BINARY_OP_I DEST_REG IMM32",
"ASM_CODE : BINARY_OPR_I DEST_REG SRC1 SRC2",
"ASM_CODE : BINARY_OPR_I DEST_REG SRC1 Y_INT",
"ASM_CODE : BINARY_OPR_I DEST_REG Y_INT",
"ASM_CODE : BINARY_IMM_ARITH_OP DEST_REG SRC1 IMM16",
"ASM_CODE : BINARY_IMM_ARITH_OP DEST_REG IMM16",
"ASM_CODE : BINARY_IMM_LOGICAL_OP DEST_REG SRC1 UIMM16",
"ASM_CODE : BINARY_IMM_LOGICAL_OP DEST_REG UIMM16",
"ASM_CODE : SHIFT_OP DEST_REG SRC1 Y_INT",
"ASM_CODE : SHIFT_OP DEST_REG SRC1 SRC2",
"ASM_CODE : BINARY_OP_NOI DEST_REG SRC1 SRC2",
"ASM_CODE : BINARY_OP_NOI DEST_REG SRC1 IMM32",
"ASM_CODE : BINARY_OP_NOI DEST_REG IMM32",
"ASM_CODE : SUB_OP DEST_REG SRC1 SRC2",
"ASM_CODE : SUB_OP DEST_REG SRC1 IMM32",
"ASM_CODE : SUB_OP DEST_REG IMM32",
"ASM_CODE : DIV_POP DEST_REG SRC1",
"ASM_CODE : DIV_POP DEST_REG SRC1 SRC2",
"ASM_CODE : DIV_POP DEST_REG SRC1 IMM32",
"ASM_CODE : MUL_POP DEST_REG SRC1 SRC2",
"ASM_CODE : MUL_POP DEST_REG SRC1 IMM32",
"ASM_CODE : MULT_OP SRC1 SRC2",
"ASM_CODE : Y_ROR_POP DEST_REG SRC1 SRC2",
"ASM_CODE : Y_ROL_POP DEST_REG SRC1 SRC2",
"ASM_CODE : Y_ROR_POP DEST_REG SRC1 IMM32",
"ASM_CODE : Y_ROL_POP DEST_REG SRC1 IMM32",
"ASM_CODE : SET_LE_POP DEST_REG SRC1 SRC2",
"ASM_CODE : SET_LE_POP DEST_REG SRC1 IMM32",
"ASM_CODE : SET_GT_POP DEST_REG SRC1 SRC2",
"ASM_CODE : SET_GT_POP DEST_REG SRC1 IMM32",
"ASM_CODE : SET_GE_POP DEST_REG SRC1 SRC2",
"ASM_CODE : SET_GE_POP DEST_REG SRC1 IMM32",
"ASM_CODE : SET_EQ_POP DEST_REG SRC1 SRC2",
"ASM_CODE : SET_EQ_POP DEST_REG SRC1 IMM32",
"ASM_CODE : NULLARY_BR_OP LABEL",
"ASM_CODE : UNARY_BR_OP SRC1 LABEL",
"ASM_CODE : UNARY_BR_POP SRC1 LABEL",
"ASM_CODE : BINARY_BR_OP SRC1 SRC2 LABEL",
"ASM_CODE : BINARY_BR_OP SRC1 BR_IMM32 LABEL",
"ASM_CODE : BR_GT_POP SRC1 SRC2 LABEL",
"ASM_CODE : BR_GT_POP SRC1 BR_IMM32 LABEL",
"ASM_CODE : BR_GE_POP SRC1 SRC2 LABEL",
"ASM_CODE : BR_GE_POP SRC1 BR_IMM32 LABEL",
"ASM_CODE : BR_LT_POP SRC1 SRC2 LABEL",
"ASM_CODE : BR_LT_POP SRC1 BR_IMM32 LABEL",
"ASM_CODE : BR_LE_POP SRC1 SRC2 LABEL",
"ASM_CODE : BR_LE_POP SRC1 BR_IMM32 LABEL",
"ASM_CODE : J_OPS LABEL",
"ASM_CODE : J_OPS SRC1",
"ASM_CODE : J_OPS DEST SRC1",
"ASM_CODE : B_OP LABEL",
"ASM_CODE : MOVE_COP_OP COP_REG COP_REG",
"ASM_CODE : MOV_FROM_HILO_OP REG",
"ASM_CODE : MOV_TO_HILO_OP REG",
"ASM_CODE : MOV_COP_OP REG COP_REG",
"ASM_CODE : CTL_COP_OP COP_REG COP_REG",
"ASM_CODE : FP_ABS_OP F_DEST F_SRC1",
"ASM_CODE : FP_BINARY_OP F_DEST F_SRC1 F_SRC2",
"ASM_CODE : FP_CONVERT_OP F_DEST F_SRC2",
"ASM_CODE : FP_NEG_OP F_DEST F_SRC2",
"ASM_CODE : FP_CMP_OP F_SRC1 F_SRC2",
"LOAD_OP : Y_LB_OP",
"LOAD_OP : Y_LBU_OP",
"LOAD_OP : Y_LH_OP",
"LOAD_OP : Y_LHU_OP",
"LOAD_OP : Y_LW_OP",
"LOAD_OP : Y_LWL_OP",
"LOAD_OP : Y_LWR_OP",
"LOAD_OP : Y_LD_POP",
"LOAD_OP : Y_PFW_OP",
"LOAD_COP : Y_LWC0_OP",
"LOAD_COP : Y_LWC2_OP",
"LOAD_COP : Y_LWC3_OP",
"LOAD_IMM_OP : Y_LUI_OP",
"ULOADH_POP : Y_ULH_POP",
"ULOADH_POP : Y_ULHU_POP",
"LOADF_OP : Y_LWC1_OP",
"LOADF_OP : Y_L_S_POP",
"LOADF_OP : Y_L_D_POP",
"STORE_OP : Y_SB_OP",
"STORE_OP : Y_SH_OP",
"STORE_OP : Y_SW_OP",
"STORE_OP : Y_SWL_OP",
"STORE_OP : Y_SWR_OP",
"STORE_OP : Y_SD_POP",
"STORE_COP : Y_SWC0_OP",
"STORE_COP : Y_SWC2_OP",
"STORE_COP : Y_SWC3_OP",
"STOREF_OP : Y_SWC1_OP",
"STOREF_OP : Y_S_S_POP",
"STOREF_OP : Y_S_D_POP",
"SYS_OP : Y_RFE_OP",
"SYS_OP : Y_SYSCALL_OP",
"BINARY_OP_I : Y_ADD_OP",
"BINARY_OP_I : Y_ADDU_OP",
"BINARY_OP_I : Y_AND_OP",
"BINARY_OP_I : Y_XOR_OP",
"BINARY_OP_I : Y_OR_OP",
"BINARY_OP_I : Y_SLT_OP",
"BINARY_OP_I : Y_SLTU_OP",
"BINARY_OPR_I : Y_SLLV_OP",
"BINARY_OPR_I : Y_SRAV_OP",
"BINARY_OPR_I : Y_SRLV_OP",
"BINARY_IMM_ARITH_OP : Y_ADDI_OP",
"BINARY_IMM_ARITH_OP : Y_ADDIU_OP",
"BINARY_IMM_ARITH_OP : Y_SLTI_OP",
"BINARY_IMM_ARITH_OP : Y_SLTIU_OP",
"BINARY_IMM_LOGICAL_OP : Y_ANDI_OP",
"BINARY_IMM_LOGICAL_OP : Y_ORI_OP",
"BINARY_IMM_LOGICAL_OP : Y_XORI_OP",
"SHIFT_OP : Y_SLL_OP",
"SHIFT_OP : Y_SRA_OP",
"SHIFT_OP : Y_SRL_OP",
"BINARY_OP_NOI : Y_NOR_OP",
"SUB_OP : Y_SUB_OP",
"SUB_OP : Y_SUBU_OP",
"DIV_POP : Y_DIV_OP",
"DIV_POP : Y_DIVU_OP",
"DIV_POP : Y_REM_POP",
"DIV_POP : Y_REMU_POP",
"MUL_POP : Y_MUL_POP",
"MUL_POP : Y_MULO_POP",
"MUL_POP : Y_MULOU_POP",
"SET_LE_POP : Y_SLE_POP",
"SET_LE_POP : Y_SLEU_POP",
"SET_GT_POP : Y_SGT_POP",
"SET_GT_POP : Y_SGTU_POP",
"SET_GE_POP : Y_SGE_POP",
"SET_GE_POP : Y_SGEU_POP",
"SET_EQ_POP : Y_SEQ_POP",
"SET_EQ_POP : Y_SNE_POP",
"MULT_OP : Y_MULT_OP",
"MULT_OP : Y_MULTU_OP",
"NULLARY_BR_OP : Y_BC0T_OP",
"NULLARY_BR_OP : Y_BC1T_OP",
"NULLARY_BR_OP : Y_BC2T_OP",
"NULLARY_BR_OP : Y_BC3T_OP",
"NULLARY_BR_OP : Y_BC0F_OP",
"NULLARY_BR_OP : Y_BC1F_OP",
"NULLARY_BR_OP : Y_BC2F_OP",
"NULLARY_BR_OP : Y_BC3F_OP",
"UNARY_BR_OP : Y_BGEZ_OP",
"UNARY_BR_OP : Y_BGEZAL_OP",
"UNARY_BR_OP : Y_BGTZ_OP",
"UNARY_BR_OP : Y_BLEZ_OP",
"UNARY_BR_OP : Y_BLTZ_OP",
"UNARY_BR_OP : Y_BLTZAL_OP",
"UNARY_BR_POP : Y_BEQZ_POP",
"UNARY_BR_POP : Y_BNEZ_POP",
"BINARY_BR_OP : Y_BEQ_OP",
"BINARY_BR_OP : Y_BNE_OP",
"BR_GT_POP : Y_BGT_POP",
"BR_GT_POP : Y_BGTU_POP",
"BR_GE_POP : Y_BGE_POP",
"BR_GE_POP : Y_BGEU_POP",
"BR_LT_POP : Y_BLT_POP",
"BR_LT_POP : Y_BLTU_POP",
"BR_LE_POP : Y_BLE_POP",
"BR_LE_POP : Y_BLEU_POP",
"J_OPS : Y_J_OP",
"J_OPS : Y_JR_OP",
"J_OPS : Y_JAL_OP",
"J_OPS : Y_JALR_OP",
"B_OP : Y_B_POP",
"B_OP : Y_BAL_POP",
"MOVE_COP_OP : Y_MOV_S_OP",
"MOVE_COP_OP : Y_MOV_D_OP",
"MOV_FROM_HILO_OP : Y_MFHI_OP",
"MOV_FROM_HILO_OP : Y_MFLO_OP",
"MOV_TO_HILO_OP : Y_MTHI_OP",
"MOV_TO_HILO_OP : Y_MTLO_OP",
"MOV_COP_OP : Y_MFC0_OP",
"MOV_COP_OP : Y_MFC1_OP",
"MOV_COP_OP : Y_MFC1_D_POP",
"MOV_COP_OP : Y_MFC2_OP",
"MOV_COP_OP : Y_MFC3_OP",
"MOV_COP_OP : Y_MTC0_OP",
"MOV_COP_OP : Y_MTC1_OP",
"MOV_COP_OP : Y_MTC1_D_POP",
"MOV_COP_OP : Y_MTC2_OP",
"MOV_COP_OP : Y_MTC3_OP",
"CTL_COP_OP : Y_CFC0_OP",
"CTL_COP_OP : Y_CFC1_OP",
"CTL_COP_OP : Y_CFC2_OP",
"CTL_COP_OP : Y_CFC3_OP",
"CTL_COP_OP : Y_CTC0_OP",
"CTL_COP_OP : Y_CTC1_OP",
"CTL_COP_OP : Y_CTC2_OP",
"CTL_COP_OP : Y_CTC3_OP",
"FP_ABS_OP : Y_ABS_S_OP",
"FP_ABS_OP : Y_ABS_D_OP",
"FP_BINARY_OP : Y_ADD_S_OP",
"FP_BINARY_OP : Y_ADD_D_OP",
"FP_BINARY_OP : Y_DIV_S_OP",
"FP_BINARY_OP : Y_DIV_D_OP",
"FP_BINARY_OP : Y_MUL_S_OP",
"FP_BINARY_OP : Y_MUL_D_OP",
"FP_BINARY_OP : Y_SUB_S_OP",
"FP_BINARY_OP : Y_SUB_D_OP",
"FP_CONVERT_OP : Y_CVT_D_S_OP",
"FP_CONVERT_OP : Y_CVT_D_W_OP",
"FP_CONVERT_OP : Y_CVT_S_D_OP",
"FP_CONVERT_OP : Y_CVT_S_W_OP",
"FP_CONVERT_OP : Y_CVT_W_D_OP",
"FP_CONVERT_OP : Y_CVT_W_S_OP",
"FP_NEG_OP : Y_NEG_S_OP",
"FP_NEG_OP : Y_NEG_D_OP",
"FP_CMP_OP : Y_C_F_S_OP",
"FP_CMP_OP : Y_C_UN_S_OP",
"FP_CMP_OP : Y_C_EQ_S_OP",
"FP_CMP_OP : Y_C_UEQ_S_OP",
"FP_CMP_OP : Y_C_OLT_S_OP",
"FP_CMP_OP : Y_C_OLE_S_OP",
"FP_CMP_OP : Y_C_ULT_S_OP",
"FP_CMP_OP : Y_C_ULE_S_OP",
"FP_CMP_OP : Y_C_SF_S_OP",
"FP_CMP_OP : Y_C_NGLE_S_OP",
"FP_CMP_OP : Y_C_SEQ_S_OP",
"FP_CMP_OP : Y_C_NGL_S_OP",
"FP_CMP_OP : Y_C_LT_S_OP",
"FP_CMP_OP : Y_C_NGE_S_OP",
"FP_CMP_OP : Y_C_LE_S_OP",
"FP_CMP_OP : Y_C_NGT_S_OP",
"FP_CMP_OP : Y_C_F_D_OP",
"FP_CMP_OP : Y_C_UN_D_OP",
"FP_CMP_OP : Y_C_EQ_D_OP",
"FP_CMP_OP : Y_C_UEQ_D_OP",
"FP_CMP_OP : Y_C_OLT_D_OP",
"FP_CMP_OP : Y_C_OLE_D_OP",
"FP_CMP_OP : Y_C_ULT_D_OP",
"FP_CMP_OP : Y_C_ULE_D_OP",
"FP_CMP_OP : Y_C_SF_D_OP",
"FP_CMP_OP : Y_C_NGLE_D_OP",
"FP_CMP_OP : Y_C_SEQ_D_OP",
"FP_CMP_OP : Y_C_NGL_D_OP",
"FP_CMP_OP : Y_C_LT_D_OP",
"FP_CMP_OP : Y_C_NGE_D_OP",
"FP_CMP_OP : Y_C_LE_D_OP",
"FP_CMP_OP : Y_C_NGT_D_OP",
"ASM_DIRECTIVE : Y_ALIAS_DIR Y_REG Y_REG",
"ASM_DIRECTIVE : Y_ALIGN_DIR EXPR",
"$$4 :",
"ASM_DIRECTIVE : Y_ASCII_DIR $$4 STR",
"$$5 :",
"ASM_DIRECTIVE : Y_ASCIIZ_DIR $$5 STR",
"ASM_DIRECTIVE : Y_AT_DIR",
"ASM_DIRECTIVE : Y_NOAT_DIR",
"ASM_DIRECTIVE : Y_ASM0_DIR",
"ASM_DIRECTIVE : Y_BGNB_DIR Y_INT",
"$$6 :",
"ASM_DIRECTIVE : Y_BYTE_DIR $$6 EXPR_LST",
"ASM_DIRECTIVE : Y_COMM_DIR ID EXPR",
"ASM_DIRECTIVE : Y_DATA_DIR",
"ASM_DIRECTIVE : Y_DATA_DIR Y_INT",
"ASM_DIRECTIVE : Y_K_DATA_DIR",
"ASM_DIRECTIVE : Y_K_DATA_DIR Y_INT",
"$$7 :",
"ASM_DIRECTIVE : Y_DOUBLE_DIR $$7 FP_EXPR_LST",
"ASM_DIRECTIVE : Y_END_DIR OPTIONAL_ID",
"ASM_DIRECTIVE : Y_ENDB_DIR Y_INT",
"ASM_DIRECTIVE : Y_ENDR_DIR",
"ASM_DIRECTIVE : Y_ENT_DIR ID",
"ASM_DIRECTIVE : Y_ENT_DIR ID Y_INT",
"ASM_DIRECTIVE : Y_EXTERN_DIR ID EXPR",
"ASM_DIRECTIVE : Y_ERR_DIR",
"ASM_DIRECTIVE : Y_FILE_DIR Y_INT Y_STR",
"$$8 :",
"ASM_DIRECTIVE : Y_FLOAT_DIR $$8 FP_EXPR_LST",
"ASM_DIRECTIVE : Y_FMASK_DIR Y_INT Y_INT",
"ASM_DIRECTIVE : Y_FRAME_DIR REGISTER Y_INT REGISTER",
"ASM_DIRECTIVE : Y_GLOBAL_DIR ID",
"$$9 :",
"ASM_DIRECTIVE : Y_HALF_DIR $$9 EXPR_LST",
"ASM_DIRECTIVE : Y_LABEL_DIR ID",
"ASM_DIRECTIVE : Y_LCOMM_DIR ID EXPR",
"ASM_DIRECTIVE : Y_LIVEREG_DIR Y_INT Y_INT",
"ASM_DIRECTIVE : Y_LOC_DIR Y_INT Y_INT",
"ASM_DIRECTIVE : Y_MASK_DIR Y_INT Y_INT",
"ASM_DIRECTIVE : Y_NOALIAS_DIR Y_REG Y_REG",
"ASM_DIRECTIVE : Y_OPTIONS_DIR ID",
"ASM_DIRECTIVE : Y_REPEAT_DIR EXPR",
"ASM_DIRECTIVE : Y_RDATA_DIR",
"ASM_DIRECTIVE : Y_RDATA_DIR Y_INT",
"ASM_DIRECTIVE : Y_SDATA_DIR",
"ASM_DIRECTIVE : Y_SDATA_DIR Y_INT",
"ASM_DIRECTIVE : Y_SET_DIR ID",
"ASM_DIRECTIVE : Y_SPACE_DIR EXPR",
"ASM_DIRECTIVE : Y_STRUCT_DIR EXPR",
"ASM_DIRECTIVE : Y_TEXT_DIR",
"ASM_DIRECTIVE : Y_TEXT_DIR Y_INT",
"ASM_DIRECTIVE : Y_K_TEXT_DIR",
"ASM_DIRECTIVE : Y_K_TEXT_DIR Y_INT",
"ASM_DIRECTIVE : Y_VERSTAMP_DIR Y_INT Y_INT",
"ASM_DIRECTIVE : Y_VREG_DIR REGISTER Y_INT Y_INT",
"$$10 :",
"ASM_DIRECTIVE : Y_WORD_DIR $$10 W_EXPR_LST",
"$$11 :",
"ADDRESS : $$11 ADDR",
"ADDR : '(' REGISTER ')'",
"ADDR : ABS_ADDR",
"ADDR : ABS_ADDR '(' REGISTER ')'",
"ADDR : Y_ID",
"ADDR : Y_ID '(' REGISTER ')'",
"ADDR : Y_ID '+' ABS_ADDR",
"ADDR : ABS_ADDR '+' ID",
"ADDR : Y_ID '-' ABS_ADDR",
"ADDR : Y_ID '+' ABS_ADDR '(' REGISTER ')'",
"ADDR : Y_ID '-' ABS_ADDR '(' REGISTER ')'",
"$$12 :",
"BR_IMM32 : $$12 IMM32",
"IMM16 : IMM32",
"UIMM16 : IMM32",
"IMM32 : ABS_ADDR",
"IMM32 : '(' ABS_ADDR ')' '>' '>' Y_INT",
"IMM32 : ID",
"IMM32 : Y_ID '+' ABS_ADDR",
"IMM32 : Y_ID '-' ABS_ADDR",
"ABS_ADDR : Y_INT",
"ABS_ADDR : Y_INT '+' Y_INT",
"ABS_ADDR : Y_INT Y_INT",
"DEST_REG : REGISTER",
"SRC1 : REGISTER",
"SRC2 : REGISTER",
"DEST : REGISTER",
"REG : REGISTER",
"SOURCE : REGISTER",
"REGISTER : Y_REG",
"F_DEST : FP_REGISTER",
"F_SRC1 : FP_REGISTER",
"F_SRC2 : FP_REGISTER",
"FP_REGISTER : Y_FP_REG",
"COP_REG : Y_REG",
"COP_REG : Y_FP_REG",
"LABEL : ID",
"STR_LST : STR_LST STR",
"STR_LST : STR",
"STR : Y_STR",
"STR : Y_STR ':' Y_INT",
"$$13 :",
"EXPRESSION : $$13 EXPR",
"EXPR : Y_INT",
"W_EXPR_LST : ID",
"W_EXPR_LST : EXPR_LST",
"EXPR_LST : EXPR_LST EXPRESSION",
"EXPR_LST : EXPRESSION",
"EXPR_LST : EXPRESSION ':' Y_INT",
"FP_EXPR_LST : FP_EXPR_LST Y_FP",
"FP_EXPR_LST : Y_FP",
"$$14 :",
"OPTIONAL_ID : $$14 OPT_ID",
"OPT_ID : ID",
"OPT_ID :",
"$$15 :",
"ID : $$15 Y_ID",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 2282 "parser.y"


#ifdef __STDC__
void
initialize_parser (char *file_name)
#else
void
initialize_parser (file_name)
     char *file_name;
#endif
{
  input_file_name = file_name;
  only_id = 0;
  data_dir = 0;
  text_dir = 1;
  accept_pseudo_insts = 1 ;
   parsed_file = fopen(file_name,"rt");
   if (parsed_file == NULL)
   {
           error ("Cannot open file: `%s'\n", file_name);
           exit(1) ;
    }
    else
    {
        initialize_scanner (parsed_file);
    }
}

#ifdef __STDC__
void
parser_close_file ()
#else
void
parser_close_file ()
#endif
{
	if (parsed_file != NULL) fclose(parsed_file);
}

/*
#ifdef __STDC__
static void
check_imm_range(int32 value, int32 min, int32 max)
#else
static void
check_imm_range()
    int32 value ; 
     int32 min;
     int32 max;
#endif
{

      if (value < min || max < value)
	{
	  char str[200];
	  sprintf (str, "immediate value (%d) out of range (%d .. %d)",
		   value, min, max);
	  yywarn (str);
	}
}
*/

/*
#ifdef __STDC__
static void
check_uimm_range(uint32 value, uint32 min, uint32 max)
#else
static void
check_uimm_range()
     uint32 value;
     int32 umin;
     int32 umax;
#endif
{
      if (value < min || max < value)
	{
	  char str[200];
	  sprintf (str, "immediate value (%d) out of range (%d .. %d)",
		   value, min, max);
	  yywarn (str);
	}
}
*/


#ifdef __STDC__
void
yyerror (char *s)
#else
void
yyerror (s)
     char *s;
#endif
{
  parse_error_occurred = 1;
  yywarn (s);
}


#ifdef __STDC__
void
yywarn (char *s)
#else
void
yywarn (s)
     char *s;
#endif
{
  error ("analyseur: (parser) %s on line %d of file %s\n", s, line_no, input_file_name);
  print_erroneous_line ();
}


/* Process a .double  directive. */

#ifdef __STDC__
static void
store_double(double *value)
#else
static void
store_double(value)
     double *value;
#endif
{
        double_record *p;

        p= (double_record *)malloc(sizeof(double_record));
        if (p==NULL) {fatal_error("error : malloc returned a NULL pointer\n");}
        p->value = *value ;
        p->next = NULL ;
        if (La_ligne.inst.directive.operands.double_operands == NULL)
        {
          La_ligne.inst.directive.operands.double_operands = p;
        }
        else
        {
          double_operands_queue->next = p ;
        }
        double_operands_queue = p ;


}

/* Process a .float  directive. */

#ifdef __STDC__
static void
store_float(double *value)
#else
static void
store_float(value)
     double *value;
#endif
{
        float_record *p;

        p = (float_record *) malloc(sizeof(float_record));
        if (p==NULL) {fatal_error("error : malloc returned a NULL pointer\n");}
        p->value =(float) *value ;
        p->next = NULL ;
        if (La_ligne.inst.directive.operands.float_operands == NULL)
        {
          La_ligne.inst.directive.operands.float_operands = p;
        }
        else
        {
          float_operands_queue->next = p ;
        }
        float_operands_queue = p ;

}


/* Process a .word, .byte , .half  directive. */

#ifdef __STDC__
static void
store_int_word(int value)
#else
static void
store_int_word(value)
     int value;
#endif
{
	int_record *p;
	
	p= (int_record *)malloc(sizeof(int_record));
	if (p==NULL) {fatal_error("error : malloc returned a NULL pointer\n");}
	p->value = value ;
	p->next = NULL ;
	if (La_ligne.inst.directive.operands.int_operands == NULL)
	{
	  La_ligne.inst.directive.operands.int_operands = p;
	}
	else
	{
	  int_operands_queue->next = p ;
	}
	int_operands_queue = p ;
}


static void dir_with_one_int_op(int directive_id , int operand)
{
        int_record *p ;

        La_ligne.instruction_type = ASM_DIRECTIVE ;
        La_ligne.inst.directive.directive_id = directive_id ;
        p = (int_record *)malloc(sizeof(int_record)) ;
        p->value = operand ;
        p->next = NULL ;
        La_ligne.inst.directive.operands.int_operands = p ;

}

t_asm_line *get_pointer_to_parsed_line(void)
{
	return(&La_ligne);
}

void scanner_store_comment(char *str, int length)
{
     strncpy(La_ligne.comment, str, length);
}

/*-------------------------   end of file -------------------------------------*/
#line 1514 "parser.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])!=0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 391 "parser.y"
{parse_error_occurred = 0; scanner_start_line ();}
break;
case 5:
#line 398 "parser.y"
{
			strncpy(La_ligne.label, (char*)yyvsp[-1].p, MAX_LABEL_SIZE -1);
			if (yyvsp[-1].p) free(yyvsp[-1].p);
		 }
break;
case 6:
#line 404 "parser.y"
{
			yyerror("Erreur : Constantes nommees non supportees ");
		}
break;
case 7:
#line 411 "parser.y"
{
		}
break;
case 9:
#line 416 "parser.y"
{
		}
break;
case 12:
#line 425 "parser.y"
{
			LINE_PARSE_DONE;
		}
break;
case 13:
#line 430 "parser.y"
{
		  FILE_PARSE_DONE;
		}
break;
case 14:
#line 438 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = address_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 15:
#line 448 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = address_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 16:
#line 458 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = imm_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 17:
#line 469 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand1.value.i_value = 0 ;
		  La_ligne.inst.instruction.operand1.label[0] = 0 ;
		  La_ligne.inst.instruction.operand2 = address_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 18:
#line 482 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = imm_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 19:
#line 493 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2.mode = IMMEDIATE ;
		  La_ligne.inst.instruction.operand2.value.d_value = *((double *)yyvsp[0].p) ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		  
		}
break;
case 20:
#line 506 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2.mode = IMMEDIATE ;
		  La_ligne.inst.instruction.operand2.value.f_value = *((float *)yyvsp[0].p) ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 21:
#line 518 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = address_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 22:
#line 529 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = address_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 23:
#line 540 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = address_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 24:
#line 551 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = address_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 25:
#line 562 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = address_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 26:
#line 573 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = address_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 27:
#line 584 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = address_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 28:
#line 595 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = address_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 29:
#line 606 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[0].i ;
		  La_ligne.inst.instruction.operand1.mode = NONE;
		  La_ligne.inst.instruction.operand2.mode = NONE ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 30:
#line 616 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand1.mode = IMMEDIATE ;
		  La_ligne.inst.instruction.operand1.value.i_value = yyvsp[0].i ;
		  La_ligne.inst.instruction.operand2.mode =  NONE ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		  if (yyvsp[0].i == 1)
		    yyerror ("Breakpoint 1 is reserved for debugger");
		}
break;
case 31:
#line 629 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[0].i ;
		  La_ligne.inst.instruction.operand1.mode = NONE;
		  La_ligne.inst.instruction.operand2.mode = NONE ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 32:
#line 639 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 33:
#line 651 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 34:
#line 663 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 35:
#line 675 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 36:
#line 687 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 37:
#line 699 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;
		}
break;
case 38:
#line 712 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 39:
#line 724 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2.mode = IMMEDIATE ;
		  La_ligne.inst.instruction.operand2 = imm_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 40:
#line 736 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;
		}
break;
case 41:
#line 749 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3.mode = IMMEDIATE ;
		  La_ligne.inst.instruction.operand3.value.i_value = yyvsp[0].i ;
		}
break;
case 42:
#line 762 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2.mode = IMMEDIATE ;
		  La_ligne.inst.instruction.operand2.value.i_value = yyvsp[0].i ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 43:
#line 774 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 44:
#line 786 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = imm_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 45:
#line 796 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 46:
#line 808 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = imm_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 47:
#line 819 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3.mode = IMMEDIATE ;
		  La_ligne.inst.instruction.operand3.value.i_value = yyvsp[0].i ; 
		  if ((yyvsp[0].i < 0) || (31 < yyvsp[0].i))
		    yywarn("Shift distance can only be in the range 0..31");
		}
break;
case 48:
#line 834 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;
		}
break;
case 49:
#line 847 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;
		}
break;
case 50:
#line 860 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 51:
#line 872 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = imm_operand ;
		  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 52:
#line 883 "parser.y"
{
		  La_ligne.instruction_type = ASM_INSTRUCTION ;
		  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
		  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
		  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
		  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;
		}
break;
case 53:
#line 896 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 54:
#line 908 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand2 = imm_operand ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 55:
#line 918 "parser.y"
{
		  /* The hardware divide operation (ignore 1st arg) */
		  if (yyvsp[-2].i != Y_DIV_OP && yyvsp[-2].i != Y_DIVU_OP)
		    yyerror ("Syntax error");
	
          	  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 56:
#line 933 "parser.y"
{
		  /* Pseudo divide operations */
          	  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;
		}
break;
case 57:
#line 946 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
		  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 58:
#line 958 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;

		}
break;
case 59:
#line 971 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 60:
#line 983 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;

		}
break;
case 61:
#line 996 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;

		}
break;
case 62:
#line 1010 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;

		}
break;
case 63:
#line 1024 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 64:
#line 1036 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 65:
#line 1049 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;
		}
break;
case 66:
#line 1061 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 67:
#line 1073 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;
		}
break;
case 68:
#line 1085 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 69:
#line 1098 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;
		}
break;
case 70:
#line 1110 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 71:
#line 1122 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;
		}
break;
case 72:
#line 1134 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER ;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3 = imm_operand ;
		}
break;
case 73:
#line 1146 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand1 = address_operand ;
                  La_ligne.inst.instruction.operand2.mode = NONE;
                  La_ligne.inst.instruction.operand3.mode = NONE;
		}
break;
case 74:
#line 1156 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand2 = address_operand ;
                  La_ligne.inst.instruction.operand3.mode = NONE;
		}
break;
case 75:
#line 1167 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand2 = address_operand ;
                  La_ligne.inst.instruction.operand3.mode = NONE;
		}
break;
case 76:
#line 1178 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3 = address_operand ;
		}
break;
case 77:
#line 1189 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2 = imm_operand ;
                  La_ligne.inst.instruction.operand3 = address_operand ;
		}
break;
case 78:
#line 1200 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3 = address_operand ;
		}
break;
case 79:
#line 1211 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2 = imm_operand ;
                  La_ligne.inst.instruction.operand3 = address_operand ;
		}
break;
case 80:
#line 1222 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3 = address_operand ;
		}
break;
case 81:
#line 1233 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2 = imm_operand ;
                  La_ligne.inst.instruction.operand3 = address_operand ;
		}
break;
case 82:
#line 1244 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3 = address_operand ;
		}
break;
case 83:
#line 1255 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2 = imm_operand ;
                  La_ligne.inst.instruction.operand3 = address_operand ;
		}
break;
case 84:
#line 1266 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3 = address_operand ;
		}
break;
case 85:
#line 1277 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2 = imm_operand ;
                  La_ligne.inst.instruction.operand3 = address_operand ;
		}
break;
case 86:
#line 1288 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand1 = address_operand ;
                  La_ligne.inst.instruction.operand2.mode = NONE ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 87:
#line 1298 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand2.mode = NONE ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 88:
#line 1309 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 89:
#line 1321 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand1 = address_operand ;
                  La_ligne.inst.instruction.operand2.mode = NONE ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 90:
#line 1332 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 91:
#line 1344 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand2.mode = NONE ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 92:
#line 1355 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand2.mode = NONE ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 93:
#line 1366 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 94:
#line 1378 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 95:
#line 1390 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 96:
#line 1402 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-3].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand3.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand3.reg_number = yyvsp[0].i ;
		}
break;
case 97:
#line 1415 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 98:
#line 1427 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 99:
#line 1439 "parser.y"
{
                  La_ligne.instruction_type = ASM_INSTRUCTION ;
                  La_ligne.inst.instruction.operation_id = yyvsp[-2].i ;
                  La_ligne.inst.instruction.operand1.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand1.reg_number = yyvsp[-1].i ;
                  La_ligne.inst.instruction.operand2.mode = DIRECT_REGISTER;
                  La_ligne.inst.instruction.operand2.reg_number = yyvsp[0].i ;
                  La_ligne.inst.instruction.operand3.mode = NONE ;
		}
break;
case 279:
#line 1724 "parser.y"
{
	 	  dir_with_one_int_op(yyvsp[-1].i, yyvsp[0].i) ;	
		}
break;
case 280:
#line 1728 "parser.y"
{null_term = 0;}
break;
case 281:
#line 1729 "parser.y"
{
        	  La_ligne.instruction_type = ASM_DIRECTIVE ;
        	  La_ligne.inst.directive.directive_id = yyvsp[-2].i ;
        	  strncpy(La_ligne.inst.directive.string_operand,(char *) yyvsp[0].p,MAX_STRING_SIZE -1) ;
		  if (yyvsp[0].p) free(yyvsp[0].p); 

		  if (text_dir)
		    yyerror ("Can't put data in text segment");
		}
break;
case 282:
#line 1739 "parser.y"
{null_term = 1;}
break;
case 283:
#line 1740 "parser.y"
{
        	  La_ligne.instruction_type = ASM_DIRECTIVE ;
        	  La_ligne.inst.directive.directive_id = yyvsp[-2].i ;
        	  strncpy(La_ligne.inst.directive.string_operand,(char *)yyvsp[0].p, MAX_STRING_SIZE -1) ;
		  if (yyvsp[0].p) free(yyvsp[0].p); 
		  if (text_dir)
		    yyerror ("Can't put data in text segment");
		}
break;
case 284:
#line 1751 "parser.y"
{
                  La_ligne.instruction_type = ASM_DIRECTIVE ;
                  La_ligne.inst.directive.directive_id = yyvsp[0].i ;
                }
break;
case 285:
#line 1757 "parser.y"
{
                  La_ligne.instruction_type = ASM_DIRECTIVE ;
                  La_ligne.inst.directive.directive_id = yyvsp[0].i ;
                }
break;
case 288:
#line 1768 "parser.y"
{
		  La_ligne.instruction_type = ASM_DIRECTIVE ;
		  La_ligne.inst.directive.directive_id = yyvsp[0].i ;
		  La_ligne.inst.directive.operands.int_operands = NULL ;
		  int_operands_queue = NULL ;
		   store_op = store_int_word;
		}
break;
case 289:
#line 1776 "parser.y"
{
		  if (text_dir)
		    yyerror ("Can't put data in text segment");
		}
break;
case 290:
#line 1783 "parser.y"
{
		}
break;
case 291:
#line 1788 "parser.y"
{
		  data_dir = 1; text_dir = 0;
		  La_ligne.instruction_type = ASM_DIRECTIVE ;
		  La_ligne.inst.directive.directive_id = yyvsp[0].i ;
		}
break;
case 292:
#line 1795 "parser.y"
{
		}
break;
case 293:
#line 1800 "parser.y"
{
		}
break;
case 294:
#line 1804 "parser.y"
{
		}
break;
case 295:
#line 1809 "parser.y"
{
		  La_ligne.instruction_type = ASM_DIRECTIVE ;
		  La_ligne.inst.directive.directive_id = yyvsp[0].i ;
		  La_ligne.inst.directive.operands.double_operands = NULL ;
		  double_operands_queue = NULL ;
		  store_op = store_double;
		}
break;
case 296:
#line 1817 "parser.y"
{
		  if (text_dir)
		    yyerror ("Can't put data in text segment");
		}
break;
case 302:
#line 1835 "parser.y"
{
		}
break;
case 303:
#line 1840 "parser.y"
{
		  fatal_error ("File contains an .err directive\n");
		}
break;
case 305:
#line 1849 "parser.y"
{
		  La_ligne.instruction_type = ASM_DIRECTIVE ;
		  La_ligne.inst.directive.directive_id = yyvsp[0].i ;
		  La_ligne.inst.directive.operands.float_operands = NULL ;
		  float_operands_queue = NULL ;
		  store_op = store_float;
		}
break;
case 306:
#line 1857 "parser.y"
{
		  if (text_dir)
		    yyerror ("Can't put data in text segment");
		}
break;
case 309:
#line 1869 "parser.y"
{
		  La_ligne.instruction_type = ASM_DIRECTIVE ;
		  La_ligne.inst.directive.directive_id = yyvsp[-1].i ;
		  strncpy(La_ligne.inst.directive.string_operand,yyvsp[0].p, MAX_STRING_SIZE -1);
		}
break;
case 310:
#line 1877 "parser.y"
{
		  La_ligne.instruction_type = ASM_DIRECTIVE ;
		  La_ligne.inst.directive.directive_id = yyvsp[0].i ;
		  La_ligne.inst.directive.operands.int_operands = NULL ;
		  int_operands_queue = NULL ;
		  store_op = store_int_word;
		}
break;
case 311:
#line 1885 "parser.y"
{
		  if (text_dir)
		    yyerror ("Can't put data in text segment");
		}
break;
case 312:
#line 1892 "parser.y"
{
		}
break;
case 313:
#line 1897 "parser.y"
{
		}
break;
case 319:
#line 1914 "parser.y"
{
		  yyerror ("Warning: repeat directive ignored");
		}
break;
case 320:
#line 1920 "parser.y"
{
		/* directive non supportee */
		}
break;
case 321:
#line 1925 "parser.y"
{
		/* directive non supportee */
		}
break;
case 322:
#line 1931 "parser.y"
{
		}
break;
case 323:
#line 1935 "parser.y"
{
		}
break;
case 324:
#line 1940 "parser.y"
{
		  La_ligne.instruction_type = ASM_DIRECTIVE ;
		  La_ligne.inst.directive.directive_id = yyvsp[-1].i ;
		  strncpy(La_ligne.inst.directive.string_operand,yyvsp[0].p,MAX_STRING_SIZE -1);
		  
		  if (streq ((char*)yyvsp[0].p, "noat"))
		    noat_flag = 1;
		  else if (streq ((char*)yyvsp[0].p, "at"))
		    noat_flag = 0;
		}
break;
case 325:
#line 1953 "parser.y"
{
	 	  dir_with_one_int_op(yyvsp[-1].i, yyvsp[0].i) ;	
		}
break;
case 326:
#line 1959 "parser.y"
{
		  yyerror ("Warning: struct directive ignored");
		}
break;
case 327:
#line 1965 "parser.y"
{
		  data_dir = 0; text_dir = 1;
		  La_ligne.instruction_type = ASM_DIRECTIVE ;
		  La_ligne.inst.directive.directive_id = yyvsp[0].i ;
		}
break;
case 328:
#line 1972 "parser.y"
{
		}
break;
case 329:
#line 1977 "parser.y"
{
		}
break;
case 330:
#line 1981 "parser.y"
{
		}
break;
case 333:
#line 1991 "parser.y"
{ 
		  La_ligne.instruction_type = ASM_DIRECTIVE ;
		  La_ligne.inst.directive.directive_id = yyvsp[0].i ;
		  La_ligne.inst.directive.operands.int_operands = NULL ;
		  int_operands_queue = NULL ;
		  store_op = store_int_word;
		}
break;
case 335:
#line 2004 "parser.y"
{only_id = 1; }
break;
case 336:
#line 2004 "parser.y"
{only_id = 0; yyval = yyvsp[0];}
break;
case 337:
#line 2007 "parser.y"
{
		  address_operand.mode = OTHER ;
		  address_operand.reg_number = yyvsp[-1].i ;
		  address_operand.value.i_value = 0 ;
		  strcpy(address_operand.label,""); 
		}
break;
case 338:
#line 2015 "parser.y"
{
		  address_operand.mode = IMMEDIATE ;
		  address_operand.reg_number = NONE ;
		  address_operand.value.i_value = yyvsp[0].i ;
		}
break;
case 339:
#line 2022 "parser.y"
{
		  address_operand.mode = OTHER ;
		  address_operand.reg_number = yyvsp[-1].i ;
		  address_operand.value.i_value = yyvsp[-3].i ;
		  strcpy(address_operand.label,""); 
		}
break;
case 340:
#line 2030 "parser.y"
{
		  address_operand.mode = OTHER ;
		  address_operand.reg_number = NONE ;
		  address_operand.value.i_value = 0 ;
		  strncpy(address_operand.label,(char *)yyvsp[0].p,MAX_LABEL_SIZE -1); 
		  if (yyvsp[0].p) free (yyvsp[0].p);
		}
break;
case 341:
#line 2039 "parser.y"
{
		  address_operand.mode = OTHER ;
		  address_operand.reg_number = yyvsp[-1].i ;
		  address_operand.value.i_value = 0 ;
		  strncpy(address_operand.label,(char *)yyvsp[-3].p,MAX_LABEL_SIZE -1); 
		  if (yyvsp[-3].p) free (yyvsp[-3].p);
		}
break;
case 342:
#line 2048 "parser.y"
{
		  address_operand.mode = OTHER ;
		  address_operand.reg_number = NONE;
		  address_operand.value.i_value = yyvsp[0].i ;
		  strncpy(address_operand.label,(char *)yyvsp[-2].p, MAX_LABEL_SIZE -1); 
		  if (yyvsp[-2].p) free (yyvsp[-2].p);
		}
break;
case 343:
#line 2057 "parser.y"
{
		  address_operand.mode = OTHER ;
		  address_operand.reg_number = NONE;
		  address_operand.value.i_value = yyvsp[-2].i ;
		  strncpy(address_operand.label,(char *)yyvsp[0].p,MAX_LABEL_SIZE -1); 
		  if (yyvsp[0].p) free (yyvsp[0].p);
		}
break;
case 344:
#line 2066 "parser.y"
{
		  address_operand.mode = OTHER ;
		  address_operand.reg_number = NONE;
		  address_operand.value.i_value = - yyvsp[0].i ;
		  strncpy(address_operand.label,(char *)yyvsp[-2].p,MAX_LABEL_SIZE -1); 
		  if (yyvsp[-2].p) free (yyvsp[-2].p);
		}
break;
case 345:
#line 2075 "parser.y"
{
		  address_operand.mode = OTHER ;
		  address_operand.reg_number = yyvsp[-1].i ;
		  address_operand.value.i_value = yyvsp[-3].i ;
		  strncpy(address_operand.label,(char *)yyvsp[-5].p,MAX_LABEL_SIZE -1); 
		  if (yyvsp[-5].p) free (yyvsp[-5].p);
		}
break;
case 346:
#line 2084 "parser.y"
{
		  address_operand.mode = OTHER ;
		  address_operand.reg_number = yyvsp[-1].i;
		  address_operand.value.i_value = - yyvsp[-3].i ;
		  strncpy(address_operand.label,(char *)yyvsp[-5].p,MAX_LABEL_SIZE -1); 
		  if (yyvsp[-5].p) free (yyvsp[-5].p);
		}
break;
case 347:
#line 2094 "parser.y"
{only_id = 1;}
break;
case 348:
#line 2094 "parser.y"
{only_id = 0; yyval = yyvsp[0];}
break;
case 349:
#line 2097 "parser.y"
{
/*
		  check_imm_range(imm_operand.value.i_value, IMM_MIN, IMM_MAX);
*/
		  yyval = yyvsp[0];
		}
break;
case 350:
#line 2105 "parser.y"
{
/*
		  check_uimm_range(imm_operand.value.i_value, UIMM_MIN, UIMM_MAX);
*/
		  yyval = yyvsp[0];
		}
break;
case 351:
#line 2114 "parser.y"
{
		  imm_operand.mode = IMMEDIATE ;
		  imm_operand.value.i_value = yyvsp[0].i ;
		}
break;
case 352:
#line 2120 "parser.y"
{
		  imm_operand.mode = IMMEDIATE ;
		  imm_operand.value.i_value = (yyvsp[-4].i >> yyvsp[0].i );
		}
break;
case 353:
#line 2126 "parser.y"
{
		  imm_operand.mode = OTHER ;
		  imm_operand.reg_number = NONE ;
		  imm_operand.value.i_value = 0;
		  strncpy(imm_operand.label, (char *)yyvsp[0].p,MAX_LABEL_SIZE -1);
		  if (yyvsp[0].p) free(yyvsp[0].p) ;
		}
break;
case 354:
#line 2135 "parser.y"
{
		  imm_operand.mode = OTHER ;
		  imm_operand.reg_number = NONE ;
		  imm_operand.value.i_value = yyvsp[0].i;
		  strncpy(imm_operand.label, (char *)yyvsp[-2].p,MAX_LABEL_SIZE -1);
		  if (yyvsp[-2].p) free(yyvsp[-2].p) ;
		}
break;
case 355:
#line 2144 "parser.y"
{
		  imm_operand.mode = OTHER ;
		  imm_operand.reg_number = NONE ;
		  imm_operand.value.i_value = - yyvsp[0].i;
		  strncpy(imm_operand.label, (char *)yyvsp[-2].p,MAX_LABEL_SIZE -1);
		  if (yyvsp[-2].p) free(yyvsp[-2].p) ;
		}
break;
case 357:
#line 2157 "parser.y"
{yyval.i = yyvsp[-2].i + yyvsp[0].i;}
break;
case 358:
#line 2160 "parser.y"
{
		  /* Y_INT '-' Y_INT */
		  if (yyvsp[0].i >= 0)
		    yyerror ("Syntax error");
		  yyval.i = yyvsp[-1].i - yyvsp[0].i;
		}
break;
case 365:
#line 2181 "parser.y"
{
		  if (yyvsp[0].i < 0 || yyvsp[0].i > 31)
		    yyerror ("Register number out of range");
/*		  if ($1.i == 1 && !noat_flag)
		    yyerror ("Register 1 is reserved for assembler");
*/
		  yyval = yyvsp[0];
		}
break;
case 369:
#line 2197 "parser.y"
{
		  if (yyvsp[0].i < 0 || yyvsp[0].i > 31)
		    yyerror ("FP register number out of range");
		  yyval = yyvsp[0];
		}
break;
case 372:
#line 2212 "parser.y"
{
		  address_operand.mode = OTHER ;
		  address_operand.reg_number = NONE ;
		  address_operand.value.i_value = 0 ;
		  strncpy(address_operand.label,(char *)yyvsp[0].p,MAX_LABEL_SIZE -1); 
		}
break;
case 375:
#line 2226 "parser.y"
{
		}
break;
case 376:
#line 2229 "parser.y"
{
		}
break;
case 377:
#line 2234 "parser.y"
{only_id = 1;}
break;
case 378:
#line 2234 "parser.y"
{only_id = 0; yyval = yyvsp[0];}
break;
case 380:
#line 2239 "parser.y"
{
                  strncpy(La_ligne.inst.directive.string_operand, (char *)yyvsp[0].p, MAX_LABEL_SIZE);
		  if (yyvsp[0].p) free (yyvsp[0].p) ;
                }
break;
case 382:
#line 2246 "parser.y"
{
		  store_op(yyvsp[0].p);
		}
break;
case 383:
#line 2250 "parser.y"
{
		  store_op(yyvsp[0].p);
		}
break;
case 384:
#line 2254 "parser.y"
{
		  yyerror (" Variante de la directive non supportee ");
		}
break;
case 385:
#line 2261 "parser.y"
{
		  store_op(yyvsp[0].p);
		}
break;
case 386:
#line 2265 "parser.y"
{
		  store_op(yyvsp[0].p);
		}
break;
case 387:
#line 2271 "parser.y"
{only_id = 1;}
break;
case 388:
#line 2271 "parser.y"
{only_id = 0; yyval = yyvsp[0];}
break;
case 390:
#line 2274 "parser.y"
{yyval.p = (void*)NULL;}
break;
case 391:
#line 2278 "parser.y"
{only_id = 1;}
break;
case 392:
#line 2278 "parser.y"
{only_id = 0; yyval = yyvsp[0];}
break;
#line 3272 "parser.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
