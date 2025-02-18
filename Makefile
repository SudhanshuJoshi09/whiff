

run_server:
	./output/main

run_client:
	./output/client

server:
	gcc -Wall -Wextra -pedantic main.c -o ./output/main && ./output/main

client:
	gcc -Wall -Wextra -pedantic client.c -o ./output/client && ./output/client
