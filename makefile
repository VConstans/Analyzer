OPT= -g -Wall -Wextra -Iinclude #-Werror


analyzer: obj/analyzer.o obj/fct_ethernet.o obj/fct_IPv4.o obj/fct_UDP.o obj/fct_tcp.o obj/fct_bootp.o obj/utile.o
	gcc $(OPT) $^ -o bin/analyzer -lpcap -lm

obj/%.o: src/%.c include/%.h
	gcc $(OPT) $< -o $@ -c

clean:
	rm obj/*.o bin/analyzer
