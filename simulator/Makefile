TARGET  = sim
CC      = gcc
CFLAGS  = -ansi -pedantic -Wall -m32 
LDFLAGS = -lm 

all: $(TARGET) 

sim: $(TARGET).o
	gcc $< -o $@ -lm

$(TARGET).o: $(TARGET).c
	gcc -o $@ -c $<

clean:
	rm $(TARGET) 
	rm ./*.o 
