#FILES = *.cpp *.h
#all:
#	g++ $(FILES) -o main -Wall -std=gnu++0x -lglut -lGL -lGLU -lX11 -lm #-L/usr/X11R6/lib 
#clean:
#	rm main
	
$(VERBOSE).SILENT:


PROGNAME = m

CC = gcc
CC += -c
CPP = g++
CPP += -c
LD = g++
LIBS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLU -lX11 -lm  -L/usr/X11R6/lib 
SRC = src/
OBJ = obj/

OBJFILES += $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(PROGNAME)

clean:
	@echo "Cleaning object files"
	rm -f *.o
	@echo "Cleaning backups"
	@echo "    rm -f     *~"
	rm -f *~
	@echo "Removing programme"
	@echo "    rm -f     "$(PROGNAME)
	rm -f $(PROGNAME)

%.o: %.cpp
	@echo "Compiling "$@
	@echo "    CPP       "$<
	$(CPP) $< $(LIBS)

$(PROGNAME): $(OBJFILES)
	@echo "Linking "$@
	@echo "    LD        -o "$(PROGNAME)"        "$(OBJFILES)
	$(LD) -o $(PROGNAME) $(OBJFILES) $(LIBS)

strip: $(PROGNAME)
	@echo "Stripping "$(PROGNAME)
	echo -n "Size of "$(PROGNAME)" before strip is "
	ls -sh $(PROGNAME) | cut -d' ' -f1
	@echo "    strip     "$(PROGNAME)
	strip $(PROGNAME)
	echo -n "Size of "$(PROGNAME)" after strip is "
	ls -sh $(PROGNAME) | cut -d' ' -f1

nothing:
	@echo "Nothing to do; quitting  :("
	@echo "HINT: Try make all"
