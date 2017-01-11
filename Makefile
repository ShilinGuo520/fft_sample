main:main.o
	gcc -o $@ $^ -lm
.c.o:
	gcc -c $<

clean:
	rm main *.o
