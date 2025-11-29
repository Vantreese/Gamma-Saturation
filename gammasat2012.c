/* new Gammasat function
*/
#include <stdio.h>
#include <math.h>

#define xgr_min(a, b) ((a) < (b) ? (a) : (b))
#define xgr_max(a, b) ((a) > (b) ? (a) : (b))
#define xgr_max3(a, b, c)   (((a) > (b)) && ((a) > (c)) ? (a) : ((b) > (c) ? (b) : (c)))
#define xgr_min3(a, b, c)   (((a) < (b)) && ((a) < (c)) ? (a) : ((b) < (c) ? (b) : (c)))
#define gammacorrect(v, p)  ((v) <= 0.0 ? 0.0 : ((v) >= 1.0 ? 1.0 : pow((v), (p))))

int GammaSat(double sRGB[3], double gvalue)
{
	double hi, lo, md = -1.0;
	double newlo, newmd = -1.0;
	int iloop;

	/* Find hi, lo, md values */
	hi = xgr_max3(sRGB[0], sRGB[1], sRGB[2]);
	lo = xgr_min3(sRGB[0], sRGB[1], sRGB[2]);
	newlo = lo;
	for (iloop = 0; iloop < 3; ++iloop)
	{
		if ((sRGB[iloop] < hi) && (sRGB[iloop] > lo))
		{
			md = sRGB[iloop];
			newmd = md;
		}
		/* else md = -1.0 to indicate there is no middle value. */
	}

	/* Apply gamma value */
	if ((hi > lo) && (lo > 0.0))
	{
		newlo = pow(lo / hi, gvalue) * hi;

		if (md != -1.0)	/* (hi > md and md > lo) */
		{
			newmd = (((md - lo) / (hi - lo)) * (hi - newlo) + newlo);
		}
	}

	/*
	 * Direct comparisons with real numbers can me made here because
	 * they are taken from the source, used without being changed, and
	 * compared with the source. Comparison is without the risk of 
	 * comparing two numbers that are "almost" equal.
	 *
	 */

	/* Modify tuple before return */
	for (iloop = 0; iloop < 3; ++iloop)
	{
		if (sRGB[iloop] == lo) { sRGB[iloop] = newlo; }
		if (sRGB[iloop] == md) { sRGB[iloop] = newmd; }
	}

	return 0;
}


