SRC_DIR = srcs/normal/
SRC_DIR_BONUS = srcs/bonus/
SRC_LST = pipex.c parsing.c path.c types.c data_utils.c pipe.c fork2.c \
		secure_utils.c secure_utils2.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_LST))
SRCS_BONUS = $(addprefix $(SRC_DIR_BONUS), $(SRC_LST))

HDR_DIR = includes/
HDR_LST = pipex.h libft.h
HEADER = $(addprefix $(HDR_DIR), $(HDR_LST))

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

NAME = pipex
NAME_BONUS = pipex_bonus

CC = cc 
#CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)
bonus : $(NAME_BONUS)

$(NAME) : $(OBJS) $(HEADER)
	make bonus -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L libft -lft 

$(NAME_BONUS) : $(OBJS_BONUS) $(HEADER)
	make bonus -C libft
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) -L libft -lft 

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(HDR_DIR)

clean :
	rm -rf $(OBJS)
	rm -rf $(OBJS_BONUS)
	make clean -C libft

fclean : clean
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re : fclean all

.PHONY : all clean fclean re bonus
