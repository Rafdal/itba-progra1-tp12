main: main.o ledwrapper.o
	gcc main.o ledwrapper.o pin_handler.o puerto.o led.o -o main

main.o: main.c ledwrapper.h
	gcc main.c -c -Wall

ledwrapper.o:ledwrapper.c ledwrapper.h pin_handler.h puerto.h led.h
	gcc ledwrapper.c -c -Wall

led.o: led.c led.h pin_handler.h
	gcc led.c -c -Wall

pin_handler.o: pin_handler.c pin_handler.h
	gcc pin_handler.c -c -Wall

puerto.o: puerto.c puerto.h
	gcc puerto.c -c -Wall

