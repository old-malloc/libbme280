bme280test: bme280test.o
	gcc -Wall -L/home/pi/progetti/bme280test -Wl,-rpath . -o bme280test main.o -lbme280
bme280test.o: main.c 
	gcc -Wall -c main.c -std=gnu99
clean:
	rm main.o bme280test
	
	
