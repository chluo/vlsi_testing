#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# ifndef YYLMAX 
# define YYLMAX BUFSIZ
# endif 
#ifndef __cplusplus
# define output(c) (void)putc(c,yyout)
#else
# define lex_output(c) (void)putc(c,yyout)
#endif

#if defined(__cplusplus) || defined(__STDC__)

#if defined(__cplusplus) && defined(__EXTERN_C__)
extern "C" {
#endif
	int yyback(int *, int);
	int yyinput(void);
	int yylook(void);
	void yyoutput(int);
	int yyracc(int);
	int yyreject(void);
	void yyunput(int);
	int yylex(void);
#ifdef YYLEX_E
	void yywoutput(wchar_t);
	wchar_t yywinput(void);
#endif
#ifndef yyless
	int yyless(int);
#endif
#ifndef yywrap
	int yywrap(void);
#endif
#ifdef LEXDEBUG
	void allprint(char);
	void sprint(char *);
#endif
#if defined(__cplusplus) && defined(__EXTERN_C__)
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
	void exit(int);
#ifdef __cplusplus
}
#endif

#endif
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
#ifndef __cplusplus
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
#else
# define lex_input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
#endif
#define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng;
#define YYISARRAY
char yytext[YYLMAX];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;

# line 4 "blif.l"
/******************************************************************\
 *
 * This is free software, licensed under the GNU Public License V2.
 * See the file COPYING for details.
 *
 * This code is provided as is, with no warranty implied or expressed.
 * Use at your own risk.  This software may contain bugs which could
 * cause it to malfunction in possibly dangerous ways.
 *  
 * Neither the author, nor any affiliates of the author are responsible for 
 * any damages caused by use of this software.
 *
 * Copyright:  Narayanan Krishnamurthy, Heling Yi, 1997
 *
\******************************************************************/



# line 21 "blif.l"
/******************************************************************\
 *
 * This code was developed as part of a project in the digital system 
 * simulation class (Spring 1997 ) taught by 
 * Dr. Nur Touba at The University of Texas at Austin.
 * The project is Path Delay Fault simulation. This file is a "lex" 
 * file that creates the "lex.yy.c" file which contains the 
 * token scanner used to read the  BLIF file that has 
 * been mapped to a technology library containing only 2-input or less
 * combinational gates. The scanner communicates with the "yacc"
 * file to parse  the BLIF file 
\******************************************************************/



# line 35 "blif.l"
/*
 * Definition Section
 */

#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


# line 44 "blif.l"
/******************************************************************\
 * nameBuf: passes the pointer to the signal name to yacc
 * funcCover: passes the pointer to the function cover to yacc
\******************************************************************/
char *nameBuf;
char *funcCover;

# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
#ifdef __cplusplus
/* to avoid CC and lint complaining yyfussy not being used ...*/
static int __lex_hack = 0;
if (__lex_hack) goto yyfussy;
#endif
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:

# line 60 "blif.l"
	;
break;
case 2:

# line 61 "blif.l"
              ;
break;
case 3:

# line 63 "blif.l"
		{ return (BLIF_MODEL); }
break;
case 4:

# line 64 "blif.l"
               { return (BLIF_INPUTS); }
break;
case 5:

# line 65 "blif.l"
              { return (BLIF_OUTPUTS); }
break;
case 6:

# line 66 "blif.l"
		{ return (BLIF_NAMES); }
break;
case 7:

# line 67 "blif.l"
		{ return (BLIF_END); }
break;
case 8:

# line 68 "blif.l"
			{ return (LINE_CONT); }
break;
case 9:

# line 69 "blif.l"
                { return (BLIF_SEQ); }
break;
case 10:

# line 70 "blif.l"
                 ;
break;
case 11:

# line 71 "blif.l"
               ;
break;
case 12:

# line 72 "blif.l"
                { return (BLIF_SEQ); }
break;
case 13:

# line 73 "blif.l"
                 ;
break;
case 14:

# line 74 "blif.l"
               ;
break;
case 15:

# line 75 "blif.l"
               ;
break;
case 16:

# line 76 "blif.l"
           { return (BLIF_FSM); }
break;
case 17:

# line 77 "blif.l"
          { return (BLIF_SEQ); }
break;
case 18:

# line 78 "blif.l"
                { return (BLIF_SEQ); }
break;
case 19:

# line 79 "blif.l"
          { return (BLIF_SEQ); }
break;
case 20:

# line 80 "blif.l"
                 { return (BLIF_FSM); }
break;
case 21:

# line 81 "blif.l"
                 							;
break;
case 22:

# line 82 "blif.l"
                							;
break;
case 23:

# line 83 "blif.l"
                 					;
break;
case 24:

# line 84 "blif.l"
                 							;
break;
case 25:

# line 85 "blif.l"
        							;
break;
case 26:

# line 86 "blif.l"
		;
break;
case 27:

# line 87 "blif.l"
    				;
break;
case 28:

# line 88 "blif.l"
		;
break;
case 29:

# line 89 "blif.l"
          			;
break;
case 30:

# line 90 "blif.l"
  			;
break;
case 31:

# line 91 "blif.l"
          			;
break;
case 32:

# line 92 "blif.l"
  			;
break;
case 33:

# line 93 "blif.l"
   		;
break;
case 34:

# line 96 "blif.l"
	{
                          nameBuf = (char *)malloc((yyleng+1)*sizeof(char));
                          strcpy(nameBuf, yytext);
                          yylval.sval = nameBuf;
                          return (NAME); 
                        }
break;
case 35:

# line 102 "blif.l"
		{ 
                          funcCover = (char *)malloc((yyleng+1)*sizeof(char));
                          strcpy(funcCover, yytext);
                          yylval.sval = funcCover;
                          return (GATE_COVER); 
                        }
break;
case 36:

# line 109 "blif.l"
		;
break;
case -1:
break;
default:
(void)fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */
int yyvstop[] = {
0,

34,
36,
0, 

1,
36,
0, 

1,
0, 

34,
36,
0, 

8,
36,
0, 

1,
35,
36,
0, 

1,
35,
0, 

34,
36,
0, 

34,
36,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

35,
0, 

35,
0, 

34,
0, 

2,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

7,
34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

21,
34,
0, 

34,
0, 

20,
34,
0, 

34,
0, 

34,
0, 

34,
0, 

10,
34,
0, 

13,
34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

24,
34,
0, 

9,
34,
0, 

18,
34,
0, 

34,
0, 

22,
34,
0, 

34,
0, 

12,
34,
0, 

34,
0, 

3,
34,
0, 

6,
34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

4,
34,
0, 

34,
0, 

14,
34,
0, 

34,
0, 

15,
34,
0, 

34,
0, 

11,
34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

5,
34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

16,
34,
0, 

34,
0, 

19,
34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

17,
34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

25,
34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

29,
0, 

31,
0, 

34,
0, 

23,
34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

27,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

34,
0, 

30,
0, 

32,
0, 

34,
0, 

26,
0, 

33,
0, 

28,
0, 
0};
# define YYTYPE unsigned char
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	1,3,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,4,	1,5,	
3,12,	12,0,	12,0,	0,0,	
2,8,	2,9,	182,190,	6,12,	
3,0,	3,0,	15,0,	15,0,	
0,0,	10,27,	0,0,	6,0,	
6,0,	11,12,	0,0,	8,25,	
8,25,	10,28,	10,29,	0,0,	
12,0,	11,25,	11,25,	13,0,	
13,0,	182,190,	2,10,	3,0,	
0,0,	15,0,	1,3,	1,6,	
0,0,	1,3,	6,0,	1,3,	
2,11,	2,6,	8,25,	2,11,	
3,12,	14,0,	14,0,	3,12,	
0,0,	3,12,	13,0,	6,12,	
16,0,	16,0,	6,12,	8,26,	
6,12,	10,27,	8,26,	8,26,	
10,27,	11,30,	10,27,	183,191,	
11,30,	212,218,	11,12,	0,0,	
14,0,	18,0,	18,0,	17,0,	
17,0,	19,0,	19,0,	16,0,	
26,26,	20,0,	20,0,	26,26,	
26,26,	1,7,	30,0,	0,0,	
12,0,	0,0,	183,191,	28,28,	
212,218,	21,0,	21,0,	3,0,	
18,0,	15,0,	17,0,	0,0,	
19,0,	232,238,	6,0,	0,0,	
20,0,	234,240,	15,35,	6,13,	
10,28,	6,14,	6,15,	6,16,	
11,0,	6,17,	13,0,	6,18,	
21,0,	0,0,	6,19,	6,20,	
6,21,	6,22,	22,0,	22,0,	
232,238,	6,23,	23,0,	23,0,	
234,240,	6,24,	24,0,	24,0,	
14,0,	0,0,	0,0,	28,28,	
13,31,	0,0,	28,28,	16,0,	
28,28,	0,0,	0,0,	242,246,	
0,0,	22,0,	31,0,	31,0,	
14,32,	23,0,	0,0,	14,33,	
247,250,	24,0,	32,0,	32,0,	
18,0,	16,36,	17,0,	251,252,	
19,0,	14,34,	0,0,	17,38,	
20,0,	19,40,	242,246,	16,37,	
0,0,	31,0,	33,0,	33,0,	
34,0,	34,0,	18,39,	247,250,	
21,0,	32,0,	0,0,	0,0,	
20,41,	21,43,	251,252,	20,42,	
35,0,	35,0,	0,0,	36,0,	
36,0,	37,0,	37,0,	38,0,	
38,0,	33,0,	0,0,	34,0,	
39,0,	39,0,	40,0,	40,0,	
0,0,	41,0,	41,0,	0,0,	
0,0,	22,0,	0,0,	35,0,	
0,0,	23,0,	36,0,	0,0,	
37,0,	24,0,	38,0,	0,0,	
0,0,	0,0,	23,45,	39,0,	
0,0,	40,0,	0,0,	0,0,	
41,0,	0,0,	24,48,	42,0,	
42,0,	31,0,	22,44,	43,0,	
43,0,	23,46,	23,47,	0,0,	
0,0,	32,0,	31,49,	0,0,	
44,0,	44,0,	45,0,	45,0,	
0,0,	46,0,	46,0,	0,0,	
0,0,	0,0,	42,0,	0,0,	
0,0,	33,0,	43,0,	34,0,	
32,50,	0,0,	0,0,	47,0,	
47,0,	33,51,	34,52,	44,0,	
0,0,	45,0,	0,0,	35,0,	
46,0,	0,0,	36,0,	0,0,	
37,0,	0,0,	38,0,	0,0,	
0,0,	35,53,	36,55,	39,0,	
37,56,	40,0,	47,0,	35,54,	
41,0,	48,0,	48,0,	0,0,	
0,0,	41,60,	49,0,	49,0,	
50,0,	50,0,	51,0,	51,0,	
52,0,	52,0,	38,57,	39,58,	
0,0,	53,0,	53,0,	0,0,	
0,0,	40,59,	0,0,	0,0,	
48,0,	0,0,	42,0,	54,0,	
54,0,	49,0,	43,0,	50,0,	
0,0,	51,0,	42,61,	52,0,	
55,0,	55,0,	0,0,	44,0,	
53,0,	45,0,	56,0,	56,0,	
46,0,	0,0,	45,64,	43,62,	
0,0,	46,65,	54,0,	57,0,	
57,0,	58,0,	58,0,	59,0,	
59,0,	0,0,	47,0,	55,0,	
0,0,	0,0,	0,0,	44,63,	
47,66,	56,0,	0,0,	60,0,	
60,0,	66,0,	66,0,	0,0,	
0,0,	0,0,	57,0,	0,0,	
58,0,	0,0,	59,0,	0,0,	
61,0,	61,0,	0,0,	0,0,	
48,0,	62,0,	62,0,	0,0,	
0,0,	49,0,	60,0,	50,0,	
66,0,	51,0,	49,68,	52,0,	
0,0,	0,0,	50,69,	0,0,	
53,0,	0,0,	51,70,	61,0,	
0,0,	53,72,	48,67,	0,0,	
62,0,	0,0,	54,0,	52,71,	
63,0,	63,0,	0,0,	54,73,	
64,0,	64,0,	0,0,	55,0,	
0,0,	65,0,	65,0,	68,0,	
68,0,	56,0,	67,0,	67,0,	
70,0,	70,0,	69,0,	69,0,	
56,74,	0,0,	57,0,	63,0,	
58,0,	0,0,	59,0,	64,0,	
0,0,	71,0,	71,0,	57,75,	
65,0,	59,77,	68,0,	72,0,	
72,0,	67,0,	60,0,	70,0,	
66,0,	69,0,	0,0,	73,0,	
73,0,	74,0,	74,0,	66,84,	
0,0,	58,76,	0,0,	61,0,	
71,0,	75,0,	75,0,	0,0,	
62,0,	0,0,	72,0,	0,0,	
61,79,	0,0,	60,78,	76,0,	
76,0,	62,80,	73,0,	0,0,	
74,0,	0,0,	77,0,	77,0,	
0,0,	78,0,	78,0,	0,0,	
75,0,	79,0,	79,0,	80,0,	
80,0,	81,0,	81,0,	63,0,	
82,0,	82,0,	76,0,	64,0,	
83,0,	83,0,	84,0,	84,0,	
65,0,	77,0,	68,0,	0,0,	
78,0,	67,0,	0,0,	70,0,	
79,0,	69,0,	80,0,	63,81,	
81,0,	0,0,	67,85,	82,0,	
0,0,	64,82,	0,0,	83,0,	
71,0,	84,0,	65,83,	0,0,	
69,86,	0,0,	72,0,	85,0,	
85,0,	71,87,	0,0,	0,0,	
86,0,	86,0,	73,0,	0,0,	
74,0,	87,0,	87,0,	88,0,	
88,0,	0,0,	89,0,	89,0,	
75,0,	0,0,	90,0,	90,0,	
0,0,	0,0,	85,0,	72,88,	
0,0,	0,0,	76,0,	86,0,	
0,0,	91,0,	91,0,	0,0,	
87,0,	77,0,	88,0,	73,89,	
78,0,	89,0,	92,0,	92,0,	
79,0,	90,0,	80,0,	78,92,	
81,0,	77,91,	0,0,	82,0,	
93,0,	93,0,	76,90,	83,0,	
91,0,	84,0,	82,96,	0,0,	
79,93,	94,0,	94,0,	0,0,	
0,0,	92,0,	0,0,	95,0,	
95,0,	80,94,	96,0,	96,0,	
84,98,	81,95,	0,0,	93,0,	
97,0,	97,0,	0,0,	83,97,	
98,0,	98,0,	0,0,	0,0,	
94,0,	0,0,	85,0,	99,0,	
99,0,	85,99,	95,0,	86,0,	
0,0,	96,0,	86,100,	0,0,	
87,0,	0,0,	88,0,	97,0,	
0,0,	89,0,	0,0,	98,0,	
0,0,	90,0,	100,0,	100,0,	
90,102,	0,0,	99,0,	101,0,	
101,0,	0,0,	88,101,	0,0,	
91,0,	102,0,	102,0,	91,104,	
103,0,	103,0,	0,0,	104,0,	
104,0,	92,0,	105,0,	105,0,	
90,103,	100,0,	0,0,	106,0,	
106,0,	0,0,	101,0,	93,0,	
0,0,	92,105,	107,0,	107,0,	
102,0,	108,0,	108,0,	103,0,	
94,0,	0,0,	104,0,	0,0,	
0,0,	105,0,	95,0,	0,0,	
0,0,	96,0,	106,0,	109,0,	
109,0,	110,0,	110,0,	97,0,	
0,0,	107,0,	97,108,	98,0,	
108,0,	96,107,	0,0,	111,0,	
111,0,	0,0,	99,0,	0,0,	
112,0,	112,0,	95,106,	0,0,	
0,0,	0,0,	109,0,	0,0,	
110,0,	113,0,	113,0,	0,0,	
114,0,	114,0,	99,110,	98,109,	
0,0,	100,0,	111,0,	0,0,	
115,0,	115,0,	101,0,	112,0,	
116,0,	116,0,	100,111,	0,0,	
102,0,	0,0,	0,0,	103,0,	
113,0,	102,113,	104,0,	114,0,	
102,114,	105,0,	117,0,	117,0,	
0,0,	0,0,	106,0,	115,0,	
0,0,	106,116,	101,112,	116,0,	
0,0,	107,0,	118,0,	118,0,	
108,0,	104,115,	119,0,	119,0,	
120,0,	120,0,	121,0,	121,0,	
0,0,	117,0,	122,0,	122,0,	
0,0,	106,117,	109,0,	108,118,	
110,0,	0,0,	123,0,	123,0,	
0,0,	118,0,	124,0,	124,0,	
0,0,	119,0,	111,0,	120,0,	
0,0,	121,0,	0,0,	112,0,	
0,0,	122,0,	112,121,	110,119,	
125,0,	125,0,	126,0,	126,0,	
113,0,	123,0,	0,0,	114,0,	
0,0,	124,0,	0,0,	0,0,	
0,0,	127,0,	127,0,	115,0,	
111,120,	128,0,	128,0,	116,0,	
129,0,	129,0,	0,0,	125,0,	
0,0,	126,0,	113,122,	130,0,	
130,0,	114,123,	0,0,	0,0,	
0,0,	117,0,	0,0,	116,125,	
127,0,	115,124,	0,0,	0,0,	
128,0,	116,126,	0,0,	129,0,	
0,0,	118,0,	0,0,	0,0,	
0,0,	119,0,	130,0,	120,0,	
0,0,	121,0,	119,128,	0,0,	
0,0,	122,0,	118,127,	0,0,	
120,129,	131,0,	131,0,	132,0,	
132,0,	123,0,	121,130,	133,0,	
133,0,	124,0,	121,131,	0,0,	
121,132,	0,0,	134,0,	134,0,	
0,0,	124,135,	123,134,	122,133,	
0,0,	135,0,	135,0,	125,0,	
131,0,	126,0,	132,0,	0,0,	
0,0,	0,0,	133,0,	136,0,	
136,0,	0,0,	126,137,	0,0,	
127,0,	134,0,	0,0,	0,0,	
128,0,	0,0,	125,136,	129,0,	
135,0,	0,0,	137,0,	137,0,	
128,139,	0,0,	130,0,	138,0,	
138,0,	0,0,	136,0,	139,0,	
139,0,	140,0,	140,0,	127,138,	
0,0,	129,140,	141,0,	141,0,	
142,0,	142,0,	0,0,	0,0,	
130,141,	137,0,	143,0,	143,0,	
144,0,	144,0,	138,0,	145,0,	
145,0,	0,0,	139,0,	0,0,	
140,0,	0,0,	0,0,	0,0,	
131,0,	141,0,	132,0,	142,0,	
0,0,	131,142,	133,0,	0,0,	
0,0,	143,0,	0,0,	144,0,	
0,0,	134,0,	145,0,	146,0,	
146,0,	147,0,	147,0,	133,144,	
135,0,	148,0,	148,0,	149,0,	
149,0,	0,0,	0,0,	132,143,	
0,0,	135,146,	136,0,	0,0,	
150,0,	150,0,	0,0,	136,147,	
151,0,	151,0,	146,0,	134,145,	
147,0,	152,0,	152,0,	0,0,	
148,0,	137,0,	149,0,	153,0,	
153,0,	0,0,	138,0,	0,0,	
154,0,	154,0,	139,0,	150,0,	
140,0,	139,150,	0,0,	151,0,	
0,0,	141,0,	0,0,	142,0,	
152,0,	0,0,	137,148,	157,0,	
157,0,	143,0,	153,0,	144,0,	
0,0,	138,149,	145,0,	154,0,	
155,0,	155,0,	156,165,	156,0,	
140,151,	141,152,	0,0,	145,156,	
159,0,	159,0,	158,166,	158,0,	
160,0,	160,0,	157,0,	142,153,	
0,0,	143,154,	0,0,	161,0,	
161,0,	144,155,	146,0,	155,0,	
147,0,	0,0,	0,0,	0,0,	
148,0,	0,0,	149,0,	159,0,	
147,158,	162,0,	162,0,	160,0,	
0,0,	0,0,	156,12,	150,0,	
0,0,	156,12,	161,0,	151,0,	
146,157,	0,0,	158,12,	0,0,	
152,0,	158,12,	0,0,	0,0,	
0,0,	148,159,	153,0,	0,0,	
162,0,	153,162,	0,0,	154,0,	
0,0,	0,0,	150,160,	163,0,	
163,0,	0,0,	164,0,	164,0,	
0,0,	167,0,	167,0,	0,0,	
0,0,	152,161,	157,0,	168,0,	
168,0,	169,0,	169,0,	154,163,	
0,0,	0,0,	0,0,	155,0,	
0,0,	156,0,	163,0,	0,0,	
155,164,	164,0,	0,0,	159,0,	
167,0,	158,0,	165,165,	160,0,	
170,0,	170,0,	168,0,	0,0,	
169,0,	0,0,	161,0,	0,0,	
159,167,	0,0,	0,0,	0,0,	
0,0,	171,0,	171,0,	160,168,	
0,0,	0,0,	0,0,	0,0,	
162,0,	165,165,	0,0,	170,0,	
0,0,	172,0,	172,0,	0,0,	
0,0,	0,0,	161,169,	0,0,	
0,0,	162,170,	0,0,	165,173,	
171,0,	165,174,	165,174,	165,174,	
165,174,	165,174,	165,174,	165,174,	
165,174,	165,174,	165,174,	166,166,	
172,0,	0,0,	163,0,	0,0,	
0,0,	164,0,	0,0,	0,0,	
167,0,	0,0,	0,0,	178,0,	
178,0,	0,0,	168,0,	0,0,	
169,0,	0,0,	0,0,	169,179,	
0,0,	164,172,	166,166,	0,0,	
0,0,	0,0,	0,0,	163,171,	
177,0,	177,0,	167,177,	0,0,	
0,0,	168,178,	178,0,	170,0,	
166,175,	0,0,	166,176,	166,176,	
166,176,	166,176,	166,176,	166,176,	
166,176,	166,176,	166,176,	166,176,	
171,0,	0,0,	0,0,	177,0,	
0,0,	170,180,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
172,0,	173,182,	173,182,	173,182,	
173,182,	173,182,	173,182,	173,182,	
173,182,	173,182,	173,182,	174,173,	
171,181,	174,174,	174,174,	174,174,	
174,174,	174,174,	174,174,	174,174,	
174,174,	174,174,	174,174,	175,183,	
175,183,	175,183,	175,183,	175,183,	
175,183,	175,183,	175,183,	175,183,	
175,183,	176,175,	178,0,	176,176,	
176,176,	176,176,	176,176,	176,176,	
176,176,	176,176,	176,176,	176,176,	
176,176,	179,0,	179,0,	180,0,	
180,0,	181,0,	181,0,	177,0,	
0,0,	0,0,	178,185,	184,0,	
184,0,	185,0,	185,0,	0,0,	
177,184,	186,0,	186,0,	0,0,	
187,0,	187,0,	0,0,	0,0,	
179,0,	0,0,	180,0,	0,0,	
181,0,	188,0,	188,0,	189,0,	
189,0,	0,0,	184,0,	0,0,	
185,0,	192,199,	192,0,	0,0,	
186,0,	193,0,	193,0,	187,0,	
194,0,	194,0,	195,0,	195,0,	
196,0,	196,0,	0,0,	0,0,	
188,0,	0,0,	189,0,	197,0,	
197,0,	0,0,	198,0,	198,0,	
200,0,	200,0,	201,0,	201,0,	
193,0,	0,0,	0,0,	194,0,	
0,0,	195,0,	0,0,	196,0,	
0,0,	192,12,	0,0,	0,0,	
192,12,	0,0,	197,0,	0,0,	
0,0,	198,0,	0,0,	200,0,	
179,0,	201,0,	180,0,	0,0,	
181,0,	179,186,	0,0,	181,189,	
179,187,	0,0,	184,0,	0,0,	
185,0,	0,0,	0,0,	0,0,	
186,0,	0,0,	184,192,	187,0,	
0,0,	185,193,	180,188,	0,0,	
0,0,	202,0,	202,0,	0,0,	
188,0,	0,0,	189,0,	0,0,	
203,0,	203,0,	0,0,	0,0,	
192,0,	199,199,	186,194,	0,0,	
193,0,	187,195,	0,0,	194,0,	
0,0,	195,0,	189,197,	196,0,	
202,0,	0,0,	0,0,	0,0,	
189,198,	188,196,	197,0,	203,0,	
0,0,	198,0,	195,201,	200,0,	
199,199,	201,0,	0,0,	204,0,	
204,0,	194,200,	198,204,	214,220,	
214,0,	0,0,	0,0,	196,202,	
200,207,	197,203,	199,205,	0,0,	
199,206,	199,206,	199,206,	199,206,	
199,206,	199,206,	199,206,	199,206,	
199,206,	199,206,	204,0,	201,208,	
205,212,	205,212,	205,212,	205,212,	
205,212,	205,212,	205,212,	205,212,	
205,212,	205,212,	0,0,	0,0,	
0,0,	0,0,	0,0,	214,12,	
0,0,	0,0,	214,12,	0,0,	
202,0,	207,0,	207,0,	202,209,	
208,0,	208,0,	0,0,	203,0,	
209,0,	209,0,	0,0,	206,205,	
203,210,	206,206,	206,206,	206,206,	
206,206,	206,206,	206,206,	206,206,	
206,206,	206,206,	206,206,	0,0,	
207,0,	210,0,	210,0,	208,0,	
211,0,	211,0,	0,0,	209,0,	
213,0,	213,0,	0,0,	215,0,	
215,0,	0,0,	204,0,	216,222,	
216,0,	0,0,	214,0,	217,0,	
217,0,	219,0,	219,0,	0,0,	
210,0,	224,231,	224,0,	211,0,	
0,0,	0,0,	0,0,	213,0,	
0,0,	0,0,	215,0,	204,211,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	217,0,	0,0,	
219,0,	0,0,	0,0,	0,0,	
221,0,	221,0,	0,0,	216,12,	
227,0,	227,0,	216,12,	223,0,	
223,0,	0,0,	0,0,	0,0,	
207,0,	224,12,	0,0,	208,0,	
224,12,	0,0,	0,0,	209,0,	
0,0,	0,0,	0,0,	221,0,	
208,214,	0,0,	0,0,	227,0,	
0,0,	0,0,	223,0,	0,0,	
0,0,	0,0,	220,220,	209,215,	
210,0,	0,0,	207,213,	211,0,	
0,0,	0,0,	0,0,	213,0,	
210,216,	0,0,	215,0,	0,0,	
213,219,	0,0,	216,0,	0,0,	
0,0,	0,0,	217,0,	0,0,	
219,0,	220,220,	0,0,	0,0,	
224,0,	222,222,	0,0,	0,0,	
211,217,	215,221,	0,0,	217,223,	
0,0,	0,0,	0,0,	220,225,	
219,224,	220,226,	220,226,	220,226,	
220,226,	220,226,	220,226,	220,226,	
220,226,	220,226,	220,226,	221,0,	
222,222,	0,0,	0,0,	227,0,	
221,227,	0,0,	223,0,	0,0,	
0,0,	0,0,	0,0,	227,233,	
0,0,	0,0,	222,228,	0,0,	
222,229,	222,229,	222,229,	222,229,	
222,229,	222,229,	222,229,	222,229,	
222,229,	222,229,	0,0,	0,0,	
223,230,	225,232,	225,232,	225,232,	
225,232,	225,232,	225,232,	225,232,	
225,232,	225,232,	225,232,	226,225,	
0,0,	226,226,	226,226,	226,226,	
226,226,	226,226,	226,226,	226,226,	
226,226,	226,226,	226,226,	228,234,	
228,234,	228,234,	228,234,	228,234,	
228,234,	228,234,	228,234,	228,234,	
228,234,	229,228,	231,231,	229,229,	
229,229,	229,229,	229,229,	229,229,	
229,229,	229,229,	229,229,	229,229,	
229,229,	230,0,	230,0,	233,239,	
233,0,	235,0,	235,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	231,231,	236,242,	236,242,	
236,242,	236,242,	236,242,	236,242,	
236,242,	236,242,	236,242,	236,242,	
230,0,	241,245,	241,0,	231,236,	
235,0,	231,237,	231,237,	231,237,	
231,237,	231,237,	231,237,	231,237,	
231,237,	231,237,	231,237,	233,12,	
0,0,	237,236,	233,12,	237,237,	
237,237,	237,237,	237,237,	237,237,	
237,237,	237,237,	237,237,	237,237,	
237,237,	0,0,	0,0,	0,0,	
0,0,	0,0,	239,239,	0,0,	
0,0,	241,12,	0,0,	0,0,	
241,12,	243,247,	243,247,	243,247,	
243,247,	243,247,	243,247,	243,247,	
243,247,	243,247,	243,247,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	239,239,	0,0,	0,0,	
230,0,	0,0,	233,0,	0,0,	
235,0,	0,0,	0,0,	0,0,	
0,0,	230,235,	0,0,	239,243,	
235,241,	239,244,	239,244,	239,244,	
239,244,	239,244,	239,244,	239,244,	
239,244,	239,244,	239,244,	244,243,	
241,0,	244,244,	244,244,	244,244,	
244,244,	244,244,	244,244,	244,244,	
244,244,	244,244,	244,244,	245,245,	
248,251,	248,251,	248,251,	248,251,	
248,251,	248,251,	248,251,	248,251,	
248,251,	248,251,	249,248,	0,0,	
249,249,	249,249,	249,249,	249,249,	
249,249,	249,249,	249,249,	249,249,	
249,249,	249,249,	245,245,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
245,248,	0,0,	245,249,	245,249,	
245,249,	245,249,	245,249,	245,249,	
245,249,	245,249,	245,249,	245,249,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		0,	
yycrank+-7,	yysvec+1,	0,	
yycrank+-11,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+4,
yycrank+0,	0,		yyvstop+7,
yycrank+-18,	0,		yyvstop+9,
yycrank+0,	0,		yyvstop+12,
yycrank+22,	0,		yyvstop+15,
yycrank+0,	yysvec+8,	yyvstop+19,
yycrank+-24,	0,		yyvstop+22,
yycrank+-28,	0,		yyvstop+25,
yycrank+-4,	yysvec+3,	yyvstop+28,
yycrank+-30,	yysvec+3,	yyvstop+30,
yycrank+-48,	yysvec+3,	yyvstop+32,
yycrank+-13,	yysvec+3,	yyvstop+34,
yycrank+-55,	yysvec+3,	yyvstop+36,
yycrank+-74,	yysvec+3,	yyvstop+38,
yycrank+-72,	yysvec+3,	yyvstop+40,
yycrank+-76,	yysvec+3,	yyvstop+42,
yycrank+-80,	yysvec+3,	yyvstop+44,
yycrank+-92,	yysvec+3,	yyvstop+46,
yycrank+-121,	yysvec+3,	yyvstop+48,
yycrank+-125,	yysvec+3,	yyvstop+50,
yycrank+-129,	yysvec+3,	yyvstop+52,
yycrank+0,	yysvec+8,	yyvstop+54,
yycrank+43,	0,		yyvstop+56,
yycrank+0,	yysvec+10,	yyvstop+58,
yycrank+-98,	yysvec+10,	0,	
yycrank+0,	0,		yyvstop+60,
yycrank+-2,	yysvec+11,	yyvstop+62,
yycrank+-145,	yysvec+3,	yyvstop+64,
yycrank+-153,	yysvec+3,	yyvstop+66,
yycrank+-169,	yysvec+3,	yyvstop+68,
yycrank+-171,	yysvec+3,	yyvstop+70,
yycrank+-183,	yysvec+3,	yyvstop+72,
yycrank+-186,	yysvec+3,	yyvstop+74,
yycrank+-188,	yysvec+3,	yyvstop+76,
yycrank+-190,	yysvec+3,	yyvstop+78,
yycrank+-195,	yysvec+3,	yyvstop+80,
yycrank+-197,	yysvec+3,	yyvstop+82,
yycrank+-200,	yysvec+3,	yyvstop+84,
yycrank+-226,	yysvec+3,	yyvstop+86,
yycrank+-230,	yysvec+3,	yyvstop+88,
yycrank+-239,	yysvec+3,	yyvstop+90,
yycrank+-241,	yysvec+3,	yyvstop+92,
yycrank+-244,	yysvec+3,	yyvstop+94,
yycrank+-258,	yysvec+3,	yyvstop+96,
yycrank+-284,	yysvec+3,	yyvstop+98,
yycrank+-289,	yysvec+3,	yyvstop+100,
yycrank+-291,	yysvec+3,	yyvstop+102,
yycrank+-293,	yysvec+3,	yyvstop+104,
yycrank+-295,	yysvec+3,	yyvstop+106,
yycrank+-300,	yysvec+3,	yyvstop+108,
yycrank+-310,	yysvec+3,	yyvstop+110,
yycrank+-319,	yysvec+3,	yyvstop+112,
yycrank+-325,	yysvec+3,	yyvstop+115,
yycrank+-334,	yysvec+3,	yyvstop+117,
yycrank+-336,	yysvec+3,	yyvstop+119,
yycrank+-338,	yysvec+3,	yyvstop+121,
yycrank+-350,	yysvec+3,	yyvstop+123,
yycrank+-363,	yysvec+3,	yyvstop+125,
yycrank+-368,	yysvec+3,	yyvstop+127,
yycrank+-395,	yysvec+3,	yyvstop+129,
yycrank+-399,	yysvec+3,	yyvstop+131,
yycrank+-404,	yysvec+3,	yyvstop+133,
yycrank+-352,	yysvec+3,	yyvstop+135,
yycrank+-409,	yysvec+3,	yyvstop+137,
yycrank+-406,	yysvec+3,	yyvstop+139,
yycrank+-413,	yysvec+3,	yyvstop+142,
yycrank+-411,	yysvec+3,	yyvstop+144,
yycrank+-424,	yysvec+3,	yyvstop+147,
yycrank+-430,	yysvec+3,	yyvstop+149,
yycrank+-438,	yysvec+3,	yyvstop+151,
yycrank+-440,	yysvec+3,	yyvstop+153,
yycrank+-448,	yysvec+3,	yyvstop+156,
yycrank+-458,	yysvec+3,	yyvstop+159,
yycrank+-465,	yysvec+3,	yyvstop+161,
yycrank+-468,	yysvec+3,	yyvstop+163,
yycrank+-472,	yysvec+3,	yyvstop+165,
yycrank+-474,	yysvec+3,	yyvstop+167,
yycrank+-476,	yysvec+3,	yyvstop+169,
yycrank+-479,	yysvec+3,	yyvstop+171,
yycrank+-483,	yysvec+3,	yyvstop+173,
yycrank+-485,	yysvec+3,	yyvstop+175,
yycrank+-514,	yysvec+3,	yyvstop+177,
yycrank+-519,	yysvec+3,	yyvstop+180,
yycrank+-524,	yysvec+3,	yyvstop+183,
yycrank+-526,	yysvec+3,	yyvstop+186,
yycrank+-529,	yysvec+3,	yyvstop+188,
yycrank+-533,	yysvec+3,	yyvstop+191,
yycrank+-544,	yysvec+3,	yyvstop+193,
yycrank+-553,	yysvec+3,	yyvstop+196,
yycrank+-563,	yysvec+3,	yyvstop+198,
yycrank+-572,	yysvec+3,	yyvstop+201,
yycrank+-578,	yysvec+3,	yyvstop+204,
yycrank+-581,	yysvec+3,	yyvstop+206,
yycrank+-587,	yysvec+3,	yyvstop+208,
yycrank+-591,	yysvec+3,	yyvstop+210,
yycrank+-598,	yysvec+3,	yyvstop+212,
yycrank+-617,	yysvec+3,	yyvstop+214,
yycrank+-622,	yysvec+3,	yyvstop+216,
yycrank+-628,	yysvec+3,	yyvstop+218,
yycrank+-631,	yysvec+3,	yyvstop+220,
yycrank+-634,	yysvec+3,	yyvstop+223,
yycrank+-637,	yysvec+3,	yyvstop+225,
yycrank+-642,	yysvec+3,	yyvstop+228,
yycrank+-649,	yysvec+3,	yyvstop+230,
yycrank+-652,	yysvec+3,	yyvstop+233,
yycrank+-666,	yysvec+3,	yyvstop+235,
yycrank+-668,	yysvec+3,	yyvstop+238,
yycrank+-678,	yysvec+3,	yyvstop+240,
yycrank+-683,	yysvec+3,	yyvstop+242,
yycrank+-692,	yysvec+3,	yyvstop+244,
yycrank+-695,	yysvec+3,	yyvstop+246,
yycrank+-703,	yysvec+3,	yyvstop+248,
yycrank+-707,	yysvec+3,	yyvstop+250,
yycrank+-721,	yysvec+3,	yyvstop+252,
yycrank+-733,	yysvec+3,	yyvstop+255,
yycrank+-737,	yysvec+3,	yyvstop+257,
yycrank+-739,	yysvec+3,	yyvstop+259,
yycrank+-741,	yysvec+3,	yyvstop+261,
yycrank+-745,	yysvec+3,	yyvstop+263,
yycrank+-753,	yysvec+3,	yyvstop+265,
yycrank+-757,	yysvec+3,	yyvstop+267,
yycrank+-771,	yysvec+3,	yyvstop+269,
yycrank+-773,	yysvec+3,	yyvstop+271,
yycrank+-784,	yysvec+3,	yyvstop+273,
yycrank+-788,	yysvec+3,	yyvstop+275,
yycrank+-791,	yysvec+3,	yyvstop+277,
yycrank+-798,	yysvec+3,	yyvstop+279,
yycrank+-832,	yysvec+3,	yyvstop+281,
yycrank+-834,	yysvec+3,	yyvstop+283,
yycrank+-838,	yysvec+3,	yyvstop+285,
yycrank+-845,	yysvec+3,	yyvstop+287,
yycrank+-852,	yysvec+3,	yyvstop+289,
yycrank+-862,	yysvec+3,	yyvstop+291,
yycrank+-877,	yysvec+3,	yyvstop+293,
yycrank+-882,	yysvec+3,	yyvstop+295,
yycrank+-886,	yysvec+3,	yyvstop+297,
yycrank+-888,	yysvec+3,	yyvstop+299,
yycrank+-893,	yysvec+3,	yyvstop+301,
yycrank+-895,	yysvec+3,	yyvstop+303,
yycrank+-901,	yysvec+3,	yyvstop+305,
yycrank+-903,	yysvec+3,	yyvstop+307,
yycrank+-906,	yysvec+3,	yyvstop+309,
yycrank+-930,	yysvec+3,	yyvstop+311,
yycrank+-932,	yysvec+3,	yyvstop+313,
yycrank+-936,	yysvec+3,	yyvstop+315,
yycrank+-938,	yysvec+3,	yyvstop+317,
yycrank+-947,	yysvec+3,	yyvstop+320,
yycrank+-951,	yysvec+3,	yyvstop+322,
yycrank+-956,	yysvec+3,	yyvstop+325,
yycrank+-962,	yysvec+3,	yyvstop+327,
yycrank+-967,	yysvec+3,	yyvstop+329,
yycrank+-991,	yysvec+3,	yyvstop+331,
yycrank+-993,	yysvec+11,	yyvstop+333,
yycrank+-982,	yysvec+3,	yyvstop+335,
yycrank+-1001,	yysvec+11,	yyvstop+338,
yycrank+-999,	yysvec+3,	yyvstop+340,
yycrank+-1003,	yysvec+3,	yyvstop+342,
yycrank+-1010,	yysvec+3,	yyvstop+344,
yycrank+-1024,	yysvec+3,	yyvstop+346,
yycrank+-1054,	yysvec+3,	yyvstop+348,
yycrank+-1057,	yysvec+3,	yyvstop+350,
yycrank+1085,	0,		0,	
yycrank+1134,	0,		0,	
yycrank+-1060,	yysvec+3,	yyvstop+352,
yycrank+-1066,	yysvec+3,	yyvstop+354,
yycrank+-1068,	yysvec+3,	yyvstop+356,
yycrank+-1087,	yysvec+3,	yyvstop+358,
yycrank+-1100,	yysvec+3,	yyvstop+360,
yycrank+-1112,	yysvec+3,	yyvstop+362,
yycrank+1157,	0,		0,	
yycrank+1169,	0,		0,	
yycrank+1179,	0,		0,	
yycrank+1191,	0,		0,	
yycrank+-1163,	yysvec+3,	yyvstop+365,
yycrank+-1146,	yysvec+3,	yyvstop+367,
yycrank+-1240,	yysvec+3,	yyvstop+369,
yycrank+-1242,	yysvec+3,	yyvstop+371,
yycrank+-1244,	yysvec+3,	yyvstop+373,
yycrank+9,	yysvec+173,	0,	
yycrank+66,	yysvec+175,	0,	
yycrank+-1250,	yysvec+3,	yyvstop+375,
yycrank+-1252,	yysvec+3,	yyvstop+377,
yycrank+-1256,	yysvec+3,	yyvstop+379,
yycrank+-1259,	yysvec+3,	yyvstop+381,
yycrank+-1268,	yysvec+3,	yyvstop+383,
yycrank+-1270,	yysvec+3,	yyvstop+385,
yycrank+0,	yysvec+174,	yyvstop+387,
yycrank+0,	yysvec+176,	yyvstop+389,
yycrank+-1276,	yysvec+11,	yyvstop+391,
yycrank+-1280,	yysvec+3,	yyvstop+393,
yycrank+-1283,	yysvec+3,	yyvstop+396,
yycrank+-1285,	yysvec+3,	yyvstop+398,
yycrank+-1287,	yysvec+3,	yyvstop+400,
yycrank+-1294,	yysvec+3,	yyvstop+402,
yycrank+-1297,	yysvec+3,	yyvstop+404,
yycrank+1360,	0,		0,	
yycrank+-1299,	yysvec+3,	yyvstop+406,
yycrank+-1301,	yysvec+3,	yyvstop+408,
yycrank+-1348,	yysvec+3,	yyvstop+410,
yycrank+-1355,	yysvec+3,	yyvstop+412,
yycrank+-1386,	yysvec+3,	yyvstop+414,
yycrank+1372,	0,		0,	
yycrank+1405,	0,		0,	
yycrank+-1432,	yysvec+3,	yyvstop+416,
yycrank+-1435,	yysvec+3,	yyvstop+418,
yycrank+-1439,	yysvec+3,	yyvstop+420,
yycrank+-1456,	yysvec+3,	yyvstop+422,
yycrank+-1459,	yysvec+3,	yyvstop+424,
yycrank+68,	yysvec+205,	0,	
yycrank+-1463,	yysvec+3,	yyvstop+426,
yycrank+-1390,	yysvec+11,	yyvstop+428,
yycrank+-1466,	yysvec+3,	yyvstop+430,
yycrank+-1470,	yysvec+11,	yyvstop+432,
yycrank+-1474,	yysvec+3,	yyvstop+434,
yycrank+0,	yysvec+206,	yyvstop+436,
yycrank+-1476,	yysvec+3,	yyvstop+438,
yycrank+1537,	0,		0,	
yycrank+-1503,	yysvec+3,	yyvstop+440,
yycrank+1564,	0,		0,	
yycrank+-1510,	yysvec+3,	yyvstop+442,
yycrank+-1480,	yysvec+11,	yyvstop+444,
yycrank+1577,	0,		0,	
yycrank+1589,	0,		0,	
yycrank+-1507,	yysvec+3,	yyvstop+446,
yycrank+1599,	0,		0,	
yycrank+1611,	0,		0,	
yycrank+-1660,	yysvec+3,	yyvstop+448,
yycrank+1649,	0,		0,	
yycrank+100,	yysvec+225,	0,	
yycrank+-1662,	yysvec+11,	yyvstop+450,
yycrank+104,	yysvec+228,	0,	
yycrank+-1664,	yysvec+3,	yyvstop+452,
yycrank+1634,	0,		0,	
yycrank+1663,	0,		0,	
yycrank+0,	yysvec+226,	yyvstop+454,
yycrank+1717,	0,		0,	
yycrank+0,	yysvec+229,	yyvstop+456,
yycrank+-1684,	yysvec+11,	yyvstop+458,
yycrank+142,	yysvec+236,	0,	
yycrank+1685,	0,		0,	
yycrank+1729,	0,		0,	
yycrank+1778,	0,		0,	
yycrank+0,	yysvec+237,	yyvstop+460,
yycrank+151,	yysvec+243,	0,	
yycrank+1740,	0,		0,	
yycrank+1752,	0,		0,	
yycrank+0,	yysvec+244,	yyvstop+462,
yycrank+158,	yysvec+248,	0,	
yycrank+0,	yysvec+249,	yyvstop+464,
0,	0,	0};
struct yywork *yytop = yycrank+1835;
struct yysvf *yybgin = yysvec+1;
char yymatch[] = {
  0,   1,   1,   1,   1,   1,   1,   1, 
  1,   9,  10,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  9,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,  45,   1,   1, 
 48,  48,  50,  50,  50,  50,  50,  50, 
 50,  50,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,  92,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
0};
char yyextra[] = {
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
/*	Copyright (c) 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#pragma ident	"@(#)ncform	6.12	97/12/08 SMI"

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
#if defined(__cplusplus) || defined(__STDC__)
int yylook(void)
#else
yylook()
#endif
{
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych, yyfirst;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	yyfirst=1;
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank && !yyfirst){  /* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
#ifndef __cplusplus
			*yylastch++ = yych = input();
#else
			*yylastch++ = yych = lex_input();
#endif
#ifdef YYISARRAY
			if(yylastch > &yytext[YYLMAX]) {
				fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
				exit(1);
			}
#else
			if (yylastch >= &yytext[ yytextsz ]) {
				int	x = yylastch - yytext;

				yytextsz += YYTEXTSZINC;
				if (yytext == yy_tbuf) {
				    yytext = (char *) malloc(yytextsz);
				    memcpy(yytext, yy_tbuf, sizeof (yy_tbuf));
				}
				else
				    yytext = (char *) realloc(yytext, yytextsz);
				if (!yytext) {
				    fprintf(yyout,
					"Cannot realloc yytext\n");
				    exit(1);
				}
				yylastch = yytext + x;
			}
#endif
			yyfirst=0;
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (uintptr_t)yyt > (uintptr_t)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((uintptr_t)yyt < (uintptr_t)yycrank) {	/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
#ifndef __cplusplus
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
#else
		yyprevious = yytext[0] = lex_input();
		if (yyprevious>0)
			lex_output(yyprevious);
#endif
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
#if defined(__cplusplus) || defined(__STDC__)
int yyback(int *p, int m)
#else
yyback(p, m)
	int *p;
#endif
{
	if (p==0) return(0);
	while (*p) {
		if (*p++ == m)
			return(1);
	}
	return(0);
}
	/* the following are only used in the lex library */
#if defined(__cplusplus) || defined(__STDC__)
int yyinput(void)
#else
yyinput()
#endif
{
#ifndef __cplusplus
	return(input());
#else
	return(lex_input());
#endif
	}
#if defined(__cplusplus) || defined(__STDC__)
void yyoutput(int c)
#else
yyoutput(c)
  int c; 
#endif
{
#ifndef __cplusplus
	output(c);
#else
	lex_output(c);
#endif
	}
#if defined(__cplusplus) || defined(__STDC__)
void yyunput(int c)
#else
yyunput(c)
   int c; 
#endif
{
	unput(c);
	}
