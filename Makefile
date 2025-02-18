

run_server:
	./output/server

run_client:
	./output/client

server:
	gcc -Wall -Wextra -pedantic server.c -o ./output/server && ./output/server

client:
	gcc -Wall -Wextra -pedantic client.c -o ./output/client && ./output/client
