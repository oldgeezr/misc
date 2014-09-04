TARGET = counter

TARGET2 = pos_thread

TARGET3 = mut_thread

TARGET4 = dining_phils

CFLAGS = -g -Wall

LDFLAGS = -g

SOURCE = counter.c

SOURCE2 = pos_thread.c

SOURCE3 = mut_thread.c

SOURCE4 = dining_phils.c

all: $(TARGET) $(TARGET2) $(TARGET3) $(TARGET4)

OBJECTS = $(SOURCE:.c=.o)

OBJECTS2 = $(SOURCE2:.c=.o)

OBJECTS3 = $(SOURCE3:.c=.o)

OBJECTS4 = $(SOURCE4:.c=.o)

$(TARGET): $(OBJECTS)
	gcc $(LDFLAGS) -pthread -o $@ $^

$(TARGET2): $(OBJECTS2)
	gcc $(LDFLAGS) -pthread -o $@ $^

$(TARGET3): $(OBJECTS3)
	gcc $(LDFLAGS) -pthread -o $@ $^

$(TARGET4): $(OBJECTS4)
	gcc $(LDFLAGS) -pthread -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -pthread -c -o $@ $<

clean:
	rm -rf $(TARGET) $(OBJECTS) $(TARGET2) $(OBJECTS2) $(TARGET3) $(OBJECTS3) $(TARGET4) $(OBJECTS4)
