SEND_OBJS   = sender.o 
SEND_BIN = sender

RECV_OBJS   = reciever.o 
RECV_BIN = reciever
 

CFLAGS = 

all: sender reciever

sender: ${SEND_OBJS}
	gcc  ${CFLAGS} ${SEND_OBJS}  -o ${SEND_BIN} 


reciever: ${RECV_OBJS}
	gcc  ${CFLAGS} ${RECV_OBJS}  -o ${RECV_BIN} 


clean:
	rm ${SEND_OBJS} ${SEND_BIN} ${RECV_OBJS} ${RECV_BIN} 
