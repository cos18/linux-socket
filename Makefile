# Makefile

CSRC	= main.c address.c
SSRC	= main.c
USRC	= utils.c
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
RM		= rm -f

.c.o:
		$(GCC) -c $< -o $(<:.c=.o) -I$(INCDIR)
	
all:	client server

client:	$(COBJS) $(UOBJS)
		$(GCC) -o $(CNAME) $(COBJS) $(UOBJS)

server:	$(SOBJS) $(UOBJS)
		$(GCC) -o $(SNAME) $(SOBJS) $(UOBJS)

clean:
		$(RM) $(COBJS) $(SOBJS) $(UOBJS)

fclean:	clean
		$(RM) $(CNAME) $(SNAME)

re:		fclean all

.PHONY:	all client server clean fclean re