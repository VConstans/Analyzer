OPT= -g#-Wall -Werror -Wextra


analyzer: analyzer.o fct_ethernet.o fct_IPv4.o
	gcc $(OPT) analyzer.o fct_ethernet.o fct_IPv4.o -o analyzer -lpcap -lm

analyzer.o: analyzer.c
	gcc $(OPT) analyzer.c -c

fct_ethernet.o: fct_ethernet.c fct_ethernet.h
	gcc $(OPT) fct_ethernet.c -c

fct_IPv4.o: fct_IPv4.c fct_IPv4.h
	gcc $(OPT) fct_IPv4.c -c

#%.o: %.c %.h
#	gcc $(OPT) $< -c


clean:
	rm *.o analyzer
