TARGET=binarytree

OBJS=vichamasoft.o binarytree.o

REBUILDABLES= $(OBJS) $(TARGET)

all: $(TARGET)
	echo COMPLETED

$(TARGET): $(OBJS)
	g++ -o $@ $^ -l sqlite3 

%.o: %.cpp
	g++ -o $@ -c $<

clean:
	rm -f vichamasoft.db
	rm -f $(REBUILDABLES)
	echo CLEAN COMPLETE
