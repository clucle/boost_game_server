CFLAGS := -std=c++14
BOOST_FLAGS := -lpthread -lboost_system -lboost_thread-mt

PROG := run
OBJS := main.o chat_message.o DispatcherQueue.o ServerSocket.o Task.o Connection.o
HDRS := chat_message.hpp DispatcherQueue.hpp ServerSocket.hpp Task.hpp Connection.hpp

all: $(PROG)
$(PROG): $(OBJS)
	g++ -o $(PROG) $(OBJS) $(CFLAGS) $(BOOST_FLAGS)

%.o: %.cpp $(HDRS)
	g++ $(CFLAGS) -c $< -o $@ -I.

clean:
	rm *.o
	rm run
