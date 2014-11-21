CFLAGS=-I../../../libroi -m32 -static

susan: susan.c Makefile
	gcc $(CFLAGS) -o susan susan.c -lm 

profile: susan.c Makefile
	gcc $(CFLAGS) -pg -g -o susan susan.c -lm 

clean:
	rm -rf susan output*
