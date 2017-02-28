CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic
DIRECT = bin
SRCS = src
SRC := $(wildcard src/*.cpp) 
OBJS := $(addprefix bin/, $(notdir $(SRC:.cpp=.o))) #object file list


all: rshell

rshell: $(DIRECT)/rshell

$(DIRECT)/rshell: $(DIRECT)/ $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(DIRECT)/%.o: $(SRCS)/%.cpp #rule for building objects
	$(CC) $(CFLAGS) -c -o $@ $<

$(DIRECT)/:
	mkdir -p $@

clean:
	rm -r $(DIRECT)