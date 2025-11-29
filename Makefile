# gammasat

binary : gammasat.exe gammasat-g.exe gammasat-halfg.exe

gammasat.exe : gammasat.c gammasat2012.o
	gcc -O3 -o gammasat.exe gammasat.c gammasat2012.o

gammasat-g.exe : gammasat-g.c gammasat2012.o
	gcc -O3 -o gammasat-g.exe gammasat-g.c gammasat2012.o

gammasat-halfg.exe : gammasat-halfg.c gammasat2012.o
	gcc -O3 -o gammasat-halfg.exe gammasat-halfg.c gammasat2012.o

gammasat2012.o : gammasat2012.c
	gcc -O3 -c gammasat2012.c


