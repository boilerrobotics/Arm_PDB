.PHONY: test memory

%.o: %.c 
	gcc -c -g $<
hw07: hw07.o matrix_algebra.o
	gcc -g -o hw07 $^

memory: hw07
	valgrind --leak-check=full ./hw07 -t

test: hw07
	rm -f tests/out*.b
	./hw07 -t
