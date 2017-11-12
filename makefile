OPT= -g -Wall -Wextra #-Werror


analyzer: analyzer.o fct_ethernet.o fct_IPv4.o fct_UDP.o fct_tcp.o fct_bootp.o utile.o
	gcc $(OPT) $^ -o analyzer -lpcap -lm

%.o: %.c %.h
	gcc $(OPT) $< -c


clean:
	rm *.o analyzer
