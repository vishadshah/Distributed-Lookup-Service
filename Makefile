  # the compiler: gcc for C program, define as g++ for C++
  CC = gcc

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  #CFLAGS  = -g -Wall

  # the build target executable:

  all: client serverAobj serverBobj serverCobj awsobj

  client:
	gcc -o client client.c

  serverAobj:
	gcc -o serverAobj serverA.c

  serverBobj:
	gcc -o serverBobj serverB.c

  serverCobj:
	gcc -o serverCobj serverC.c

  awsobj:
	gcc -o awsobj aws.c

  serverA: serverA
	./serverAobj

  serverB:
	./serverBobj

  serverC:
	./serverCobj

  aws:
	./awsobj

  clean:
	rm -rf serverAobj serverBobj serverCobj awsobj 
