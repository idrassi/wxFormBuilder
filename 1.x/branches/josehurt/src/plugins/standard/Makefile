CXX = g++

LIBCOMMON = libcommon.so
LIBLAYOUT = liblayout.so

CXXFLAGS = `wx-config --cxxflags` -I. -g
CFLAGS = `wx-config --cflags` -I. -g
LDFLAGS = `wx-config --libs`

all: $(LIBCOMMON) $(LIBLAYOUT)

$(LIBCOMMON): common.o
	$(CXX) -L. -shared -o $(LIBCOMMON) common.o $(LDFLAGS)
	strip $(LIBCOMMON)

common.o: common.cpp
	$(CXX) -c $(CXXFLAGS) -o common.o common.cpp

$(LIBLAYOUT): layout.o
	$(CXX) -L. -shared -o $(LIBLAYOUT) layout.o $(LDFLAGS)
	strip $(LIBLAYOUT)

layout.o: layout.cpp
	$(CXX) -c $(CXXFLAGS) -o layout.o layout.cpp


clean:
	rm -rf *.o *.so
