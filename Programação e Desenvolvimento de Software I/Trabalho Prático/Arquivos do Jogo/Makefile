ALLEGRO_VERSION=5.0.10
MINGW_VERSION=4.7.0
FOLDER=C:

FOLDER_NAME=\allegro-$(ALLEGRO_VERSION)-mingw-$(MINGW_VERSION)
PATH_ALLEGRO=$(FOLDER)$(FOLDER_NAME)
LIB_ALLEGRO=\lib\liballegro-$(ALLEGRO_VERSION)-monolith-mt.a
INCLUDE_ALLEGRO=\include

all:tp_finalfantasy.exe


tp_finalfantasy.exe: tp_finalfantasy.o
	gcc -o tp_finalfantasy.exe tp_finalfantasy.o $(PATH_ALLEGRO)$(LIB_ALLEGRO)

tp_finalfantasy.o: tp_finalfantasy.c
	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -c tp_finalfantasy.c	


clean:
	
	del tp_finalfantasy.exe
	del tp_finalfantasy.o

