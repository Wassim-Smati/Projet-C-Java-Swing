##########################################
#
#  Makefile TP C++
#
##########################################

PROG = myprog

SOURCES = main.cpp multimediaobject.cpp photo.cpp video.cpp film.cpp groupe.cpp multimediamanager.cpp
HEADERS = multimediaobject.h photo.h video.h film.h groupe.h multimediamanager.h
OBJETS = ${SOURCES:%.cpp=%.o}

CXX = c++
CXXFLAGS = -std=c++11 -Wall -g
LDFLAGS =

ifeq ($(OS),Windows_NT)
LDLIBS = -lws2_32
else
LDLIBS =
endif

all: ${PROG}

run: ${PROG}
	./${PROG}

${PROG}: depend-${PROG} ${OBJETS}
	${CXX} -o $@ ${CXXFLAGS} ${LDFLAGS} ${OBJETS} ${LDLIBS}

clean:
	-@$(RM) *.o depend-${PROG} core media_table.txt group_table.txt 1>/dev/null 2>&1

clean-all: clean
	-@$(RM) ${PROG} 1>/dev/null 2>&1

depend-${PROG}: ${SOURCES}
	${CXX} ${CXXFLAGS} -MM ${SOURCES} > depend-${PROG}

.SUFFIXES: .cpp .cxx .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

-include depend-${PROG}
