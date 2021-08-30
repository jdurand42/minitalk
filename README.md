# minitalk
Project minitalk of 42

The client will send to the server a string and the server will display it;
The trick is they must only communicate with SIGUSR1 and SIGUSR2;
Client take the string and sends its binary bit by bit to the server -> SIGUSR1 = 0 and SIGUSR2 = 1;
Server takes it and display char by char the string;
For every Byte, the last one (8th) is used for the client to tell if the last byte sent is the last of the string or not;
