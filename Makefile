OBJS := twosh.o twosh_utils.o
INCLUDE_PATH := ./
CC := gcc
TWOSH := twosh

all: $(TWOSH)
	
$(TWOSH): $(OBJS)
	$(CC) $(OBJS) -I$(INCLUDE_PATH) -o $(TWOSH)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f twosh

.PHONY: all clean
