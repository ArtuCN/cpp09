SRC = main.cpp src/PmergeMe.cpp
OBJ_DIR = obj
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
CC = c++
CFLAGS = -Wall -Wextra -Werror -g -std=c++98
RM = rm -f
NAME = PmergeMe


FUCHSIA = '\033[0;95m'
CYAN = '\033[0;36m'
NONE = '\033[0m'

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)


$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@ echo $(CYAN)          "   ___            "$(NONE)
	@ echo $(FUCHSIA)       "  / __\ _     _   "$(NONE)
	@ echo $(CYAN)          " / /  _| |_ _| |_ "$(NONE)
	@ echo $(FUCHSIA)       "/ /__|_   _|_   _|"$(NONE)
	@ echo $(CYAN)          "\____/ |_|   |_|  "$(NONE)
	@ echo $(FUCHSIA)       "                  "$(NONE)

clean:
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_DIR)
	@echo "Removed object files"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -r $(OBJ_DIR)
	@echo "Removed $(NAME)"

re: fclean all

.PHONY: all clean fclean re
