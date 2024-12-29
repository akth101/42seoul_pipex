# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 21:37:24 by seongjko          #+#    #+#              #
#    Updated: 2024/02/26 13:09:12 by seongjko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = pipex

B_NAME = pipex_bonus

SRCS = ./mandatory/parsing/parsing_main.c \
		./mandatory/parsing/parsing_preset.c \
		./mandatory/process/handling_child_process.c \
		./mandatory/process/handling_parent_process.c \
		./mandatory/process/transfer_data_to_file2.c \
		./mandatory/process/wait_child_process.c \
		./mandatory/main.c
		
		
B_SRCS =  ./bonus/parsing/parsing_main_bonus.c \
		./bonus/parsing/parsing_preset_bonus.c \
		./bonus/process/get_here_doc_input_bonus.c \
		./bonus/process/handling_child_process_bonus.c \
		./bonus/process/handling_parent_process_bonus.c \
		./bonus/process/transfer_data_to_file2_bonus.c \
		./bonus/process/wait_child_process_bonus.c \
		./bonus/main_bonus.c \
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c
		

OBJS = $(SRCS:.c=.o)

B_OBJS = ${B_SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

INCLUDE = -I

all : $(NAME)

LIBFTA = ./libft/libft.a

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME) : $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) ${LIBFTA} $^ -o ${NAME}
	
bonus : ${B_NAME}

${B_NAME} : ${B_OBJS}
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) ${LIBFTA} $^ -o ${B_NAME}

clean:
	rm -f ${OBJS}
	rm -f ${B_OBJS}
	$(MAKE) -C libft clean

fclean : clean
	rm -f ${NAME}
	rm -f ${B_NAME}
	$(MAKE) -C libft fclean

re : 
	$(MAKE) fclean 
	$(MAKE) all

.PHONY : bonus
.PHONY : all
.PHONY : clean
.PHONY : fclean
.PHONY : re