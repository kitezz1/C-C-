obj=client.o wrap.o
target=client

CC = gcc
#CPPFLAGS = -I

$(target):$(obj)
	$(CC) $(obj) -o $(target)

%.o:%.c
	$(CC) -c $< -o $@
