rwildcard = $(wildcard $1$2)$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

CLIENT_SRC = $(call rwildcard,client/src/,*.cpp) $(call rwildcard,client/engine_src/,*.cpp) $(call rwildcard,common/src/,*.cpp)
SERVER_SRC = $(call rwildcard,server/src/,*.cpp) $(call rwildcard,common/src/,*.cpp)
SRC	= 	server/main.cpp\
		server/server.cpp \
		common/sockets.cpp \
		common/serialize.cpp \
		server/Game.cpp

CLIENT_OBJ = $(CLIENT_SRC:.cpp=.o)
SERVER_OBJ = $(SERVER_SRC:.cpp=.o)

CLIENT_OUT = r-type_client
SERVER_OUT = r-type_server

INCLUDES = -I./client/include/ -I./client/engine_include/ -I./common/include/ -I./server/include/

CC = g++

CXXFLAGS = -Wall -Wextra -Werror -Wno-missing-field-initializers

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -pthread -std=c++11

.SUFFIXES: .cpp

.cpp.o:
	$(CC) $(LDFLAGS) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

all:	$(CLIENT_OUT) $(SERVER_OUT)

$(CLIENT_OUT):	$(CLIENT_OBJ)
	$(CC) $(CXXFLAGS) $(CLIENT_OBJ) $(CLIENT_INCLUDES) $(LDFLAGS) -o $(CLIENT_OUT)

$(SERVER_OUT):	$(SERVER_OBJ)
	$(CC) $(CXXFLAGS) $(SERVER_OBJ) $(SERVER_INCLUDES) $(LDFLAGS) -o $(SERVER_OUT)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(OUT)
	clear

re:	fclean all
