bme280lib.so: bme280.o bme280func.o linux_userspace.o
	gcc -Wall -shared -o libbme280.so bme280.o linux_userspace.o bme280func.o
libbme280.o: bme280.c bme280.h bme280_defs.h linux_userspace.h bme280.func.h 
	gcc -Wall -c bme280.c linux_userspace.c bme280func.c -std=gnu99
clean:
	rm libbme280.o libbme280lib.so bme280.o linux_userspace.o bme280func.o
	
	
