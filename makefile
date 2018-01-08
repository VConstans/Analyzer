OPT= -g -Wall -Wextra -Iinclude #-Werror


bin/analyzer: obj/analyzer.o obj/fct_ethernet.o obj/fct_arp.o obj/fct_IPv4.o obj/fct_IPv6.o obj/fct_UDP.o obj/fct_tcp.o obj/fct_bootp.o obj/fct_http.o obj/fct_smtp.o obj/fct_pop.o obj/fct_imap.o obj/fct_ftp.o obj/fct_telnet.o obj/fct_dns.o obj/utile.o obj/listAffichage.o
	gcc $(OPT) $^ -o bin/analyzer -lpcap -lm

obj/%.o: src/%.c include/%.h
	gcc $(OPT) $< -o $@ -c

clean:
	rm obj/*.o bin/analyzer
