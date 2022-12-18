CC 			= gcc
CFLAGS 		= -O2 -Wall 
OUT_PATH 	= ./build

all:
	make build

build: 
	mkdir -p $(OUT_PATH)
	make wifibot
	
rebuild:
	make clean
	make build

run:
	$(OUT_PATH)/wifibot

clean:
	rm -rf $(OUT_PATH)

dev:
	make rebuild && make run 

wifibot: wifibot.o
	$(CC) -o $(OUT_PATH)/wifibot $(OUT_PATH)/wifibot.o

wifibot.o:
	$(CC) -o $(OUT_PATH)/wifibot.o -c src/wifibot.c
