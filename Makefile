ifeq ($(OS),Windows_NT)
	INCLUDE_DIR_SDL = -I extern/SDL2-w64/include

	LIBS_SDL = -Lextern/SDL2-w64/lib\
			-lmingw32 -lSDL2main -lSDL2.dll -lSDL2_ttf.dll -lSDL2_image.dll -lSDL2_mixer.dll

else
	INCLUDE_DIR_SDL = -I/usr/include/SDL2
	LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
endif


#A l'ajout d'un nouveau fichier : L'ajouter dans SRC_SDL (ou CORE) puis dans OBJS_SDL et ensuite sa ligne de compilation plus bas
CORE 	 = 
SRCS_SDL = $(CORE) sdl2/sdlJeu.cpp sdl2/main_sdl.cpp sdl2/ObjetSDL.cpp sdl2/Bouton.cpp sdl2/Jeu.cpp sdl2/Pion.cpp
OBJS_SDL = obj/main_sdl.o obj/sdlJeu.o obj/ObjetSDL.o obj/Bouton.o obj/Jeu.o obj/Pion.o

OBJ_DIR 		= obj
SRC_DIR 		= src
INCLUDE_DIR		= -Isrc -Isrc/core -Isrc/sdl2

all: bin/quarto2.exe

bin/quarto2.exe: $(SRCS_TXT:%.cpp) $(OBJS_SDL)
	g++ $(OBJS_SDL) -o bin/quarto2.exe $(LIBS_SDL)

obj/main_sdl.o: src/sdl2/main_sdl.cpp
	g++ -g -Wall -c src/sdl2/main_sdl.cpp $(INCLUDE_DIR_SDL) -o obj/main_sdl.o

obj/sdlJeu.o: src/sdl2/sdlJeu.cpp src/sdl2/sdlJeu.h
	g++ -g -Wall -c src/sdl2/sdlJeu.cpp $(INCLUDE_DIR_SDL) -o obj/sdlJeu.o

obj/ObjetSDL.o: src/sdl2/ObjetSDL.cpp src/sdl2/ObjetSDL.h
	g++ -g -Wall -c src/sdl2/ObjetSDL.cpp $(INCLUDE_DIR_SDL) -o obj/ObjetSDL.o

obj/Bouton.o: src/sdl2/Bouton.cpp src/sdl2/Bouton.h
	g++ -g -Wall -c src/sdl2/Bouton.cpp $(INCLUDE_DIR_SDL) -o obj/Bouton.o

obj/Jeu.o: src/sdl2/Jeu.cpp src/sdl2/Jeu.h
	g++ -g -Wall -c src/sdl2/Jeu.cpp $(INCLUDE_DIR_SDL) -o obj/Jeu.o

obj/Pion.o: src/sdl2/Pion.cpp src/sdl2/Pion.h
	g++ -g -Wall -c src/sdl2/Pion.cpp $(INCLUDE_DIR_SDL) -o obj/Pion.o

clean:
	rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/core/*.o $(OBJ_DIR)/txt/*.o $(OBJ_DIR)/sdl2/*.o

veryclean: clean
	rm -rf $(DEP_DIR) $(BIN_DIR)/quarto2.exe