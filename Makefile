LFLAGS = -lwiringPi 
CC = g++
INCFOLDER = include
SRCFOLDER = src
OBJFOLDER = obj
CFLAGS = -std=c++17 -c -w -Wall -Wextra -pedantic -I$(INCFOLDER) 
SRC = $(wildcard $(SRCFOLDER)/*.cpp $(LDFLAGS))
OBJ = $(patsubst $(SRCFOLDER)/%.cpp, $(OBJFOLDER)/%.o, $(SRC))
EXE = bin/bin

all: clean $(EXE) 
    
$(EXE): $(OBJ) 
	$(CC) $(OBJFOLDER)/*.o $(LFLAGS) -o $@ 

$(OBJFOLDER)/%.o : $(SRCFOLDER)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@ 

clean:
	-rm -f $(OBJFOLDER)/*.o $(EXE)

run:
	./$(EXE)