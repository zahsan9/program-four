CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRCS = main.cpp movie.cpp comedy.cpp drama.cpp classic.cpp \
       bstree.cpp customer.cpp hashtable.cpp transaction.cpp \
       borrow.cpp return_txn.cpp inventory_txn.cpp history_txn.cpp \
       store.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = store

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
