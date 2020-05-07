CC = gcc
OBJ = find_util

$(OBJ):$(OBJ).o
	$(CC) -o $@ $^

%.o:%.c
	$(CC) -c -o $@ $^

clean: 
	rm -f $(OBJ) *.o

