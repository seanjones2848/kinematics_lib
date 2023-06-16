NAME = libkinematics.a

SRC_PATH = src
SRC_FILES = fix_util.c \
			fix_math.c

SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))

OBJ = $(SRC_FILES:.c=.o)

TEST_FILES = test_fix.c

TEST = $(addprefix $(SRC_PATH)/, $(TEST_FILES))

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) -c $(SRC) -I$(SRC_PATH)
	@ar -rcs $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)
	@echo "removed objects"

fclean:	clean
	@rm -rf $(NAME)
	@echo "library removed"

test: all clean
	@gcc $(FLAGS) $(TEST) -L. -lkinematics -o test
	@./test
	@rm -f test

re: fclean all
