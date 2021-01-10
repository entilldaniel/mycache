

target:
	cc main.c proto/handler.c proto/protocol.c -lpthread

clean:
	rm a.out

