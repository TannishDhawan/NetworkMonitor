
objects = main.o pinger.o metrics.o gui.o Database.o

network_monitor:$(objects)
	g++ -o network_monitor $(objects) -lncurses -lsqlite3

main.o:main.cc pinger.h metrics.h gui.h Database.h
	g++ -c main.cc

pinger.o: pinger.h pinger.cc
	g++ -c pinger.cc

metrics.o: metrics.h metrics.cc
	g++ -c metrics.cc

gui.o: gui.h gui.cc
	g++ -c gui.cc

Database.o: Database.h Database.cc
	g++ -c Database.cc

clean:
	rm -f network_monitor *.o *.db