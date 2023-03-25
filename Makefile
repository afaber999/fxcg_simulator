#OBJS specifies which files to compile as part of the project
OBJS =  fxcg_emu.cpp emu_main.cpp gui_test.cpp ./src/example.cpp ./src/button.cpp ./src/menu.cpp ./src/rect.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I../SDL2-2.26.4/x86_64-w64-mingw32/include -I../ -I.

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L../SDL2-2.26.4/x86_64-w64-mingw32/lib 

#COMPILER_FLAGS specifies the additional compilation options we                                                                                                            're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
#COMPILER_FLAGS = -w -Wl,-subsystem,windows
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = emu

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)


