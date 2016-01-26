/*
	define.h - Yevheniy Chuba - 01/25/2016
	This file contains define statements for use with the
	demo program define.c
*/

// simple constants
#define PI 					3.14159
#define PIE_TIN_DEPTH		2.5
#define UNIT_VOLUME_COST	0.86

// fancier defines - not recommended for casual use
// as it can promote poor style
#define newline 				printf("\n")
#define output(text)			printf(text), newline
#define inquiry(prompt, answer) printf(prompt), scanf("%f", &answer)
