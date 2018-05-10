
# compiler flags for GTK usage
GTKINC	= `pkg-config --cflags gtk+-2.0`
GTKLIBS	= `pkg-config --libs gtk+-2.0`

# general compiler flags
#DEBUG	= -g -DDEBUG
DEBUG	= -O2
CFLAGS	= -Wall -ansi $(DEBUG) $(GTKINC) -c
LFLAGS	= -Wall -ansi $(DEBUG) $(GTKLIBS)
CC	= gcc

DESIGN = GuberClient GuberServer GuberClient_bin GuberServer_bin TestTaxi TestReader TestRoute
TEST = TestTaxi
OBJS = GuberClient.o Reader.o Taxi.o DrawMap.o DrawTaxi.o Belle.o
OBJS2 = GuberServer.o Reader.o Taxi.o DrawMap.o DrawTaxi.o Belle.o
DEPS = Reader.h Taxi.h GuberClient.h GuberServer.h Belle.h

#targets
all: GuberClient GuberServer

GuberClient: $(OBJS) 
	$(CC)  $(LFLAGS) $(FLAGS) $(OBJS) -o GuberClient
	
GuberClient_bin: $(OBJS) 
	$(CC)  $(LFLAGS) $(FLAGS) $(OBJS) -o ../bin/GuberClient
	
GuberServer: $(OBJS2) 
	$(CC)  $(LFLAGS) $(FLAGS) $(OBJS2) -o GuberServer
	
GuberServer_bin: $(OBJS2) 
	$(CC)  $(LFLAGS) $(FLAGS) $(OBJS2) -o ../bin/GuberServer
	
TestTaxi: TestTaxi.o Taxi.o Reader.o
	$(CC) -ansi -Wall TestTaxi.o Taxi.o Reader.o -o TestTaxi
	
TestReader: TestReader.o Reader.o 
	$(CC) -ansi -Wall TestReader.o Reader.o -o TestReader
	
TestRoute: TestRoute.o Route.o Reader.o
	$(CC) -ansi -Wall TestRoute.o Route.o Reader.o -o TestRoute

#################### generate object files ###################
	
GuberClient.o: GuberClient.c Reader.h Taxi.h 
	$(CC) GuberClient.c $(CFLAGS) -o GuberClient.o
	
GuberServer.o: GuberServer.c Reader.h Taxi.h GuberClient.h GuberServer.h
	$(CC) GuberServer.c $(CFLAGS) -o GuberServer.o

Reader.o: Reader.c Reader.h
	$(CC) $(CFLAGS) Reader.c -o Reader.o

Taxi.o: Taxi.c Taxi.h GuberClient.h
	$(CC) $(CFLAGS) Taxi.c -o Taxi.o
	
DrawMap.o: DrawMap.c GuberClient.h
	$(CC) $(CFLAGS) DrawMap.c -o DrawMap.o

DrawTaxi.o: DrawTaxi.c GuberClient.h
	$(CC) $(CFLAGS) DrawTaxi.c -o DrawTaxi.o
	
Route.o: Route.c Route.h
	$(CC) $(CFLAGS) Route.c -o Route.o

TestTaxi.o: TestTaxi.c Taxi.h Reader.h
	$(CC) $(CFLAGS) TestTaxi.c -o TestTaxi.o

TestReader.o: TestReader.c Reader.h
	$(CC) $(CFLAGS) TestReader.c -o TestReader.o

TestRoute.o: TestRoute.c Route.h
	$(CC) $(CFLAGS) TestRoute.c -o TestRoute.o
	
Belle.o: Belle.c Belle.h
	$(CC) $(CFLAGS) Belle.c -o Belle.o
	
clean: 
	rm -f *.o $(DESIGN) map.txt
	
	
	
	

	



