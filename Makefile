#OBJS specifies which files to compile as part of the project
OBJS_CORE =  emu_font_18.cpp fxcg_emu.cpp emu_main.cpp sprite.c
OBJS_WIDGETS =  $(OBJS_CORE) ./examples/widgets/example.cpp ./examples/widgets/button.cpp ./examples/widgets/menu.cpp ./examples/widgets/rect.cpp
OBJS_2048 =  $(OBJS_CORE) ./examples/2048-fxcg/Game.cpp ./examples/2048-fxcg/graphic_functions.cpp ./examples/2048-fxcg/main.cpp ./examples/2048-fxcg/renderer.cpp ./examples/2048-fxcg/rng.cpp  ./examples/2048-fxcg/SaveFile.cpp

OBJS = $(OBJS_2048)
#OBJS = $(OBJS_WIDGETS)


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
COMPILER_FLAGS = -w -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = emu

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)


clean:
	rm $(OBJ_NAME).exe
