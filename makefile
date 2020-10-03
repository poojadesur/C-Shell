#MACROS

OBJS = main.o display.o command.o builtIn.o shellstart.o ls.o pinfo.o nightswatch.o redirect.o EnvVar.o bgprocesses.o jobs.o pipe.o fg.o bg.o overkill.o kjob.o controlc.o controlz.o 
OBJ = main.c display.c command.c builtIn.c shellstart.c ls.c pinfo.c nightswatch.c redirect.c EnvVar.c bgprocesses.c jobs.c pipe.c fg.c bg.c overkill.c kjob.c controlc.c controlz.c 

code : $(OBJ)
	$(CC) $(CFLAGS) ${OBJ} $(LDFLAGS) -o $@
