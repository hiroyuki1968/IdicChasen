#include "stdafx.h"
#include "ConvKCode.h"

#define	Z_BEGIN		0xa1	/* Zenkaku Begin */
#define	Z_END		0xfe	/* Zenkaku END */
#define SS2    		0x8e	/* Hankaku Kana */

/*
 *	EUC --> Sift_JIS  Convert Routine
 */

static void JIS_IBM(unsigned jis1, unsigned jis2, unsigned *ibm1, unsigned *ibm2)
{
        if(jis1 >= 0x5f)    jis1 += 0x80;
 
        if((jis1 % 2) == 0) {
                *ibm1 = (jis1 - 0x30)/2 + 0x88;
                *ibm2 = jis2 + 0x7e;
        }
        else {
                if(jis2 >= 0x60)
                        jis2 = jis2 + 0x01;
                *ibm1 = (jis1 - 0x31)/2 + 0x89;
                *ibm2 = jis2 + 0x1f;
        }
        *ibm1 &= 0xff;
        *ibm2 &= 0xff;
}

void EucToSJis(const char *lpszSrc, char *lpszDst)
{
	const unsigned char *pSrcStr = (const unsigned char *)lpszSrc;
	unsigned char *pDstStr = (unsigned char *)lpszDst;
	int stat;
	unsigned c, c1, c2;
	unsigned s1, s2;
	const unsigned char *p;
	int nDstStrIdx;

	p = pSrcStr;
	nDstStrIdx = 0;
	c1 = c2 = 0;
	stat = 0;
	while ((c = *(p++)) != '\0') {
		switch (stat) {
		case 0:
			if (Z_BEGIN <= c  && c <= Z_END) { /* Zenkaku */
				c1 = c & 0x7f;
				stat = 1;
			}
			else if (c == SS2) {	 /* Hankaku Kana */
				c = *(p++);
				pDstStr[nDstStrIdx++] = c;
			}
			else /* ASCII */
				pDstStr[nDstStrIdx++] = c;
			break;
		case 1:
			stat = 0;
			c2 = c & 0x7f;
			JIS_IBM(c1, c2, &s1, &s2); /* Convert JIS to Sift_JIS */
			pDstStr[nDstStrIdx++] = s1;
			pDstStr[nDstStrIdx++] = s2;
			break;
		}
	}
	pDstStr[nDstStrIdx] = '\0';
}
