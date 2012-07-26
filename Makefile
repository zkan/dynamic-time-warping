CC = g++

EXPENDABLES = runDTW

CPPFLAGS = -gstabs+ $(INC) $(LIB)
#INC = -I /usr/include/opencv
#LIB = -lcxcore -lcv -lhighgui -lcvaux -lml
#BLOB_LIB = -Iblobheaders -Lbloblibs -lblob

all: $(EXPENDABLES)

dirent.o: dirent.cc utility.h
	$(CC) -c dirent.cc

runDTW: runDTW.o dtw.o dirent.o
	$(CC) $(CPPFLAGS) -o runDTW runDTW.o dtw.o dirent.o -lm

clean:
	rm -f *.o $(EXPENDABLES)

