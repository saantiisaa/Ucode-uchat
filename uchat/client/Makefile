export DISPLAY=:0

NAME = uchat
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -pthread -Wno-unused-command-line-argument -Wno-unused-variable \
    -Wno-unused-function -Wno-unused-parameter -rdynamic -lm `pkg-config --cflags gtk+-3.0`
LIBS = -lsqlite3 `pkg-config --libs gtk+-3.0`
INC = inc
SRCDIR = src
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(NAME)

.PHONY: all clean

reinstall:
	make clean
	make
