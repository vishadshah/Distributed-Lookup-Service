README:
NAME: VISHAD SHAH
USC ID:9738981811

Functions performed :
-Search : It searched for the word and displays meaning of the entered input on command line.
-Prefix : It searched for the word entered in the command line and displays the words having corresponding prefix.

Source code files that I have used are
1)client.c
2)aws.c
3)serverA.c
4)serverB.c
5)serverC.c

2)Description:

client.c

- I have done creating binding and listening of the TCP socket is done through the socket(), bind(), listen() functions, the structure address was referred from Beej Guide.("http://beej.us/guide/bgnet/").
- The input fucntion is given in the command line which is read by and stored in a pointer to a char* and this is sent to AWS through write command.
- After this, the AWS server sends the message to the client through TCP connection which is received in the client.
- The received message from the AWS server is displayed.

 aws.c

- There is a common UDP Port which listens from all the backend servers which are serverA, serverB and serverC. there is a TCP connection with the client and it communicates with the client using the TCP port.
- The received message from the client is stored and then sent to all the backend servers. and the line by line string is stored in the "Seperate_Line_Message".(strtok() was referred to from the stack overflow link).(Code for seperating tokens was referred from stack overflow)
- After the iterations are done by serverA, serverB and serverC and received by thw AWS, the UDP sockets are closed and the message is sent to client through write function.

serverA.c, serverB.c and serverC.c

- UDP sockets are created for the respective servers. This message is seperated using the strtok() function based on "\n" delimiter. (strtok() was referred to from the stack overflow link).(Code for seperating tokens was referred from stack overflow)
- The line by line string is parsed and checked for the first " " delimter and checked if the first string is 'search' or 'prefix.
-Once it has identified which function it is, the server opens the file and reads line by line to check for a match of the word. This is done by function strncmp. Once the match is found, it sends the desired output to AWS.
-The function calls return and the operated result which contains the word and meaning for search function and matched words for the prefix function.
- This result is sent back to AWS through UDP socket.
  

3) Message Formats:
-The messages are displayed asnper the expectation or mentioned in the project PDF file except for the monitor and number if matches only in client.
-The messages are stored in string and sent in character pointer format as well as char string. 

4) Idiosyncrasy

-However, the search function at backend servers namely serverA, serverb and serverC are not able to search for a word divided by two spaces(i.e. search high mountain).
- All the servers need to be runned again and client terminal needs to be opened again for new operation.


5) References:
1)https://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c
2)Beej Guide: http://beej.us/guide/bgnet/
3)http://www.thegeekstuff.com/2011/12/c-socket-programming/
4)https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm

