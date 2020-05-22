# Makefile

CSRC	= test.c
SSRC	= test.c
CDIR	= ./client/
SDIR	= ./server/
INCDIR	= includes

CSRCS	= $(addprefix $(CDIR), $(CSRC))
SSRCS	= $(addprefix $(SDIR), $(SSRC))

COBJS	= $(CSRCS:.c=.o)
SOBJS	= $(SSRCS:.c=.o)

CNAME	= socket_client
SNAME	= socket_server

GCC		= gcc
GCCFLAG	= -Wall -Wextra -Werror
RM		= rm -f

.c.o:
		$(GCC) $(GCCFLAG) -c $< -o $(<:.c=.o) -I$(INCDIR)
	
all:	client server

client:	$(COBJS)
		$(GCC) $(GCCFLAG) -o $(CNAME) $(COBJS)

server:	$(SOBJS)
		$(GCC) $(GCCFLAG) -o $(SNAME) $(SOBJS)

clean:
		$(RM) $(COBJS) $(SOBJS)

fclean:	clean
		$(RM) $(CNAME) $(SNAME)

re:		fclean all

.PHONY:	all client server clean fclean re