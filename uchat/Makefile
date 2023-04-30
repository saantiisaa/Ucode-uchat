.PHONY: all clean reinstall

all: uchat uchat_server move

uchat:
	@make -sC client

uchat_server:
	@make -sC server

clean:
	@make -sC client clean
	@make -sC server clean

reinstall:
	@make -sC client reinstall
	@mv client/uchat .
	@make -sC server reinstall
	@mv server/uchat_server .

move:
	@mv client/uchat .
	@mv server/uchat_server .
	
