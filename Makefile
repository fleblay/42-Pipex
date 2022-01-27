SRC_DIR = srcs/
SRC_LST = pipex.c parsing.c path.c types.c data_utils.c pipe.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_LST))

HDR_DIR = includes/
HDR_LST = pipex.h libft.h
HEADER = $(addprefix $(HDR_DIR), $(HDR_LST))

OBJS = $(SRCS:.c=.o)

NAME = pipex

CC = cc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
#CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS) $(HEADER)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L libft -lft 

%.o : %.c
	$(CC) $(CFLAGS)	-o $@ -c $< -I $(HDR_DIR)

clean :
	rm -rf $(OBJS)
	make clean -C libft

fclean : clean
	make fclean -C libft
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
