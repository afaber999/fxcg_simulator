

#OBJS specifies which files to compile as part of the project
OBJS_WIDGETS =  ./examples/widgets/example.cpp ./examples/widgets/button.cpp ./examples/widgets/menu.cpp ./examples/widgets/rect.cpp
OBJS_GAME_2048 =  ./examples/2048-fxcg/Game.cpp ./examples/2048-fxcg/graphic_functions.cpp ./examples/2048-fxcg/main.cpp ./examples/2048-fxcg/renderer.cpp ./examples/2048-fxcg/rng.cpp  ./examples/2048-fxcg/SaveFile.cpp
OBJS_MANDELBROT =  ./examples/mandelbrot/main.c

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
#INCLUDE_PATHS = -I../SDL2-2.26.4/x86_64-w64-mingw32/include -I../ -I.
INCLUDE_PATHS = -I./include 

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L../SDL2-2.26.4/x86_64-w64-mingw32/lib

#COMPILER_FLAGS specifies the additional compilation options we                                                                                                            're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
#COMPILER_FLAGS = -w -Wl,-subsystem,windows
COMPILER_FLAGS = -w -g -Dmain=fxcg_main -nostdinc

FXCG_SIM = fxcg_sim
FXCG_SIM_FULL = sim/lib$(FXCG_SIM).a

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME_WIDGETS = widgets
OBJ_NAME_GAME_2048 = game_2048
OBJ_NAME_MANDELBROT = mandelbrot


$(FXCG_SIM_FULL):
	make -C sim
	
widgets : $(OBJS_WIDGETS) $(FXCG_SIM_FULL)
	$(CC) $(OBJS_WIDGETS) $(FXCG_SIM_FULL) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME_WIDGETS)

game_2048 : $(OBJS_GAME_2048) $(FXCG_SIM_FULL)
	$(CC) $(OBJS_GAME_2048) $(FXCG_SIM_FULL) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME_GAME_2048)

mandelbrot : $(OBJS_MANDELBROT)
	$(CC) $(OBJS_MANDELBROT) $(FXCG_SIM_FULL) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME_MANDELBROT)

#This is the target that compiles our executable
all : $(OBJ_NAME_WIDGETS) $(OBJ_NAME_GAME_2048) $(OBJ_NAME_MANDELBROT)
	echo "ALL"


clean:
	make -C sim clean
	rm -rF $(OBJ_NAME_WIDGETS).exe
	rm -rF $(OBJ_NAME_GAME_2048).exe
	rm -rF $(OBJ_NAME_MANDELBROT).exe
