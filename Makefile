TARGET = list_test

CFLAGS = -g -Wall

LDFLAGS = -g -Wall

SOURCES = linked_list.c list_test.c

all: $(TARGET)

OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	gcc $(LDFLAGS) -o $@ $^

%.o : %.c 
	gcc $(CFLAGS) -c -o $@ $<

clean: 
	rm -rf $(TARGET) $(OBJECTS)
