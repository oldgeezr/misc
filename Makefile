TARGET = list_test

CFLAGS = -g -Wall

LDFLAGS = -g

SOURCES = list_test.c linked_list.c 

all: $(TARGET)

OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	gcc $(LDFLAGS) -o $@ $^

%.o : %.c 
	gcc $(CFLAGS) -c -o $@ $<

clean: 
	rm -rf $(TARGET) $(OBJECTS)
