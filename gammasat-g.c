#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int GammaSat(double sRGB[3], double gvalue);

int main(int argc, char *argv[])
{
	double gvalue;
	int xloop, yloop;
	FILE *i, *o;
	int readstat;
	char pkey[4];
	int xsize, ysize, maxvalue;
	unsigned char *imagerow;
	double sRGB[3];
	double dmaxvalue, drestorevalue;
	double epsilon = 1.0 / 65536.0;	// Smallest number > 0.
	int xpos;

	if (argc < 3)
	{
		fprintf(stderr, "%s: gamma in_file out_file\n",
				argv[0]);
		return (1);
	}

	gvalue = atof(argv[1]);
	i = fopen(argv[2], "rb");

	readstat = fscanf(i, "%s %i %i %i", pkey, &xsize, &ysize, &maxvalue);
	fgetc(i);

	if (readstat == EOF)
	{
		fprintf(stderr, "%s: Read error on %s\n",
				argv[0], argv[2]);
		return readstat;
	}

	o = fopen(argv[3], "wb");
	fprintf(o, "%s\n%d %d\n%d\n", pkey, xsize, ysize, maxvalue);
	dmaxvalue = (double) maxvalue;
	drestorevalue = dmaxvalue + 1.0 - epsilon;

	imagerow = calloc(3, xsize);
	for (yloop = 0; yloop < ysize; ++yloop)
	{
		xpos = 0;
		fread(imagerow, 3, xsize, i);
		for (xloop = 0; xloop < xsize; ++xloop)
		{
			sRGB[0] = (double) imagerow[xpos+0] / dmaxvalue;
			sRGB[1] = (double) imagerow[xpos+1] / dmaxvalue;
			sRGB[2] = (double) imagerow[xpos+2] / dmaxvalue;

			GammaSat(sRGB, gvalue);
			sRGB[0] = pow(sRGB[0], 1.0/gvalue);
			sRGB[1] = pow(sRGB[1], 1.0/gvalue);
			sRGB[2] = pow(sRGB[2], 1.0/gvalue);


			sRGB[0] *= drestorevalue;
			sRGB[1] *= drestorevalue;
			sRGB[2] *= drestorevalue;

			imagerow[xpos+0] = (unsigned char) sRGB[0];
			imagerow[xpos+1] = (unsigned char) sRGB[1];
			imagerow[xpos+2] = (unsigned char) sRGB[2];

			xpos += 3;
		}
		fwrite(imagerow, 3, xsize, o);
		fflush(o);
	}

	fclose(i);
	fclose(o);

	return 0;
}
