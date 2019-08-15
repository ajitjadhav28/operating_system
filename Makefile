CC = gcc
CFLAG = -Wall
COMPL = $(CC) $(CFLAG) $^ -o $@
BIN = ./bin/
mylibs = mylib.c

LIST = fork.bin forkp.bin pipe.bin shared_mem_consumer.bin shared_mem_producer.bin

PROGS = $(addprefix $(BIN), $(LIST))

all: $(PROGS)

$(BIN)fork.bin : fork.c $(mylibs)
	$(COMPL)

$(BIN)forkp.bin : forkp.c $(mylibs)
	$(COMPL)

$(BIN)pipe.bin : pipe.c $(mylibs)
	$(COMPL)

$(BIN)shared_mem_consumer.bin : ./producer_consumer_shared_mem/consumer.c $(mylibs)
	$(COMPL) -lrt

$(BIN)shared_mem_producer.bin : ./producer_consumer_shared_mem/producer.c $(mylibs)
	$(COMPL) -lrt

	
$(shell mkdir -p bin)

docs:
	@doxygen 
	@open ./docs/html/index.html

clean:
	rm -rf $(PROGS)

clean-docs:
	rm -rf ./docs

clean-all:
	rm -rf $(PROGS) ./docs
