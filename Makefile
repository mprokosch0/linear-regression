NAME = prog1
NAME2 = prog2

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -g -Iincludes -MMD -MP

SRCS = prog1-srcs/main.cpp \

SRCS2 = prog2-srcs/main.cpp \

OBJS_DIR = objs

DEPS	= $(OBJS:.o=.d) $(OBJS2:.o=.d)

OBJS =	$(SRCS:%.cpp=$(OBJS_DIR)/%.o)

OBJS2 =	$(SRCS2:%.cpp=$(OBJS_DIR)/%.o)

all : $(NAME) $(NAME2)

$(OBJS_DIR)/%.o:%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

$(NAME2) : $(OBJS2)
	$(CXX) $(CXXFLAGS) -o $(NAME2) $(OBJS2)

clean :
	rm -rf $(OBJS_DIR)

fclean : clean
	rm -f $(NAME) $(NAME2)

re : fclean all

-include $(DEPS)

.PHONY : all clean fclean re
