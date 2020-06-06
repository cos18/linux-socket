# Makefile

CSRC	= main.c connect_to_server.c split_recv.c
SSRC	= main.c create_ipv4_server.c accept_connection.c split_send.c
USRC	= utils.c encoding.c recvall.c sendall.c get_next_line.c \
			send_string.c recv_string.c
CDIR	= ./client/
SDIR	= ./server/
UDIR	= ./includes/
INCDIR	= includes

CSRCS	= $(addprefix $(CDIR), $(CSRC))
SSRCS	= $(addprefix $(SDIR), $(SSRC))
USRCS	= $(addprefix $(UDIR), $(USRC))

COBJS	= $(CSRCS:.c=.o)
SOBJS	= $(SSRCS:.c=.o)
UOBJS	= $(USRCS:.c=.o)

CNAME	= socket_client
SNAME	= socket_server

GCC		= gcc
GCCOP	= -Werror -Wextra -Wall
RM		= rm -f

.c.o:
		$(GCC) $(GCCOP) -c $< -o $(<:.c=.o) -I$(INCDIR)
	
all:	client server

client:	$(COBJS) $(UOBJS)
		$(GCC) $(GCCOP) -o $(CNAME) $(COBJS) $(UOBJS)

server:	$(SOBJS) $(UOBJS)
		$(GCC) $(GCCOP) -o $(SNAME) $(SOBJS) $(UOBJS)

clean:
		$(RM) $(COBJS) $(SOBJS) $(UOBJS)

fclean:	clean
		$(RM) $(CNAME) $(SNAME)

re:		fclean all

.PHONY:	all client server clean fclean re