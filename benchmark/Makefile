all: benchmark validate collision threadTest

benchmark: benchmark.c
	$(CC) -g -O0 benchmark.c -o benchmark -w -lckv
validate: validate.c
	$(CC) -g -O0 validate.c -o validate -w -lckv
collision: collision.c
	$(CC) -g -O0 collision.c -o collision -w -lckv

threadTest: threadTest.c
	$(CC) -g -O0 threadTest.c -o threadTest -w -lckv -lpthread

clean:
	rm -f benchmark validate collision threadTest
