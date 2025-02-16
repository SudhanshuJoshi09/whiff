

run_server:
	./main

run_client:
	./client

server:
	gcc main.c -o output/main && ./output/main

client:
	gcc client.c -o output/client && ./output/client
