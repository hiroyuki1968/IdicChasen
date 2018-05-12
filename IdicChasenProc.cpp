#include "stdafx.h"
#include "IdicChasenProc.h"

#include "IdicChasenDef.h"

const _TCHAR* pszPfAppGeneral = PF_APP_GENERAL;

const char* ppszPfKey[] = {
	PF_KEY_VER,
	PF_KEY_SHOWCMD,
	PF_KEY_WIDTH,
	PF_KEY_HEIGHT,
	PF_KEY_CHASEN,
	PF_KEY_IDIC,
	PF_KEY_NAME,
	PF_KEY_SEX,

	PF_KEY_BIRTHDATETIME,
	PF_KEY_BIRTHPREFECTURE,
	PF_KEY_BIRTHLONG,
	PF_KEY_BIRTHLAT,
	PF_KEY_TIMEDIFF,
	PF_KEY_SUMMERTIME,
	PF_KEY_DAILY,
	PF_KEY_OPPOSITESEX,

	PF_KEY_YAHOO,
	PF_KEY_MINAGE,
	PF_KEY_MAXAGE,
	PF_KEY_BLOODTYPEA,
	PF_KEY_BLOODTYPEB,
	PF_KEY_BLOODTYPEO,
	PF_KEY_BLOODTYPEAB,
	PF_KEY_EXENOTES,

	NULL
};

const int ppnPrefectureLongLat[][4] = {
	{141, 21, 43,  4},
	{140, 45, 40, 49},
	{141,  9, 39, 42},
	{140, 53, 38, 16},
	{140,  6, 39, 43},
	{140, 22, 38, 14},
	{140, 28, 37, 45},
	{140, 29, 36, 22},
	{139, 53, 36, 34},
	{139,  4, 36, 23},
	{139, 39, 35, 51},
	{140,  8, 35, 36},
	{139, 42, 35, 41},
	{139, 39, 35, 27},
	{139,  2, 37, 54},
	{137, 13, 36, 42},
	{136, 40, 36, 34},
	{136, 13, 36,  4},
	{138, 34, 35, 40},
	{138, 11, 36, 39},
	{136, 44, 35, 23},
	{138, 23, 34, 58},
	{136, 55, 35, 11},
	{136, 31, 34, 44},
	{135, 52, 35,  0},
	{135, 46, 35,  1},
	{135, 31, 34, 41},
	{135, 11, 34, 41},
	{135, 50, 34, 41},
	{135, 10, 34, 13},
	{134, 14, 35, 30},
	{133,  3, 35, 28},
	{133, 56, 34, 40},
	{132, 28, 34, 24},
	{131, 29, 34, 11},
	{134, 34, 34,  4},
	{134,  3, 34, 20},
	{132, 46, 33, 50},
	{133, 32, 33, 33},
	{130, 25, 33, 36},
	{130, 18, 33, 15},
	{129, 53, 32, 45},
	{130, 45, 32, 47},
	{131, 37, 33, 14},
	{131, 26, 31, 54},
	{130, 34, 31, 36},
	{127, 41, 26, 13}
};

const POINT PointMainPanel = {285, 190};

const char pszUrl0[] = "http://dir.yahoo.co.jp/Entertainment/TV_People/Complete_Listing/";
const char pszUrl1[] = "http://dir.yahoo.co.jp/Entertainment/Music/Genres/J_POP/Artists/Complete_Listing/";
