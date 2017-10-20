OPT= -g -Wall -Wextra #-Werror


analyzer: analyzer.o fct_ethernet.o fct_IPv4.o fct_UDP.o fct_bootp.o
	gcc $(OPT) $^ -o analyzer -lpcap -lm

analyzer.o: analyzer.c
	gcc $(OPT) analyzer.c -c

fct_ethernet.o: fct_ethernet.c fct_ethernet.h
	gcc $(OPT) fct_ethernet.c -c

fct_IPv4.o: fct_IPv4.c fct_IPv4.h
	gcc $(OPT) fct_IPv4.c -c

fct_UDP.o: fct_UDP.c fct_UDP.h
	gcc $(OPT) fct_UDP.c -c

fct_bootp.o: fct_bootp.c fct_bootp.h
	gcc $(OPT) fct_bootp.c -c

#%.o: %.c %.h
#	gcc $(OPT) $< -c


clean:
	rm *.o analyzer
