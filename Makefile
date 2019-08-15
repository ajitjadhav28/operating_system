CC = gcc
CFLAG = -Wall
COMPL = $(CC) $(CFLAG) $^ -o $@
BIN = ./bin/
mylibs = mylib.c

LIST = fork.bin forkp.bin pipe.bin shared_mem_consumer.bin shared_mem_producer.bin \
		producer_consumer_bb.bin

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

$(BIN)producer_consumer_bb.bin : ./producer_consumer_bb/main.c ./producer_consumer_bb/producer.c \
									./producer_consumer_bb/consumer.c ./producer_consumer_bb/buffer.c $(mylibs)
	$(COMPL) -lrt -lpthread

	
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
