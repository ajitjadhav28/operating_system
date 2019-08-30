CC = gcc
CFLAG = -Wall
COMPL = $(CC) $(CFLAG) $^ -o $@
BIN = ./bin/
mylibs = mylib.c

LIST = fork.bin forkp.bin pipe.bin shared_mem_consumer.bin shared_mem_producer.bin \
		producer_consumer_bb.bin frw_writer.bin frw_reader.bin \
		paging_problm.bin paging_performance.bin vmm.bin

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

$(BIN)frw_writer.bin : ./first_reader_writer/writer.c $(mylibs)
	$(COMPL) -lrt -lpthread

$(BIN)frw_reader.bin : ./first_reader_writer/reader.c $(mylibs)
	$(COMPL) -lrt -lpthread

$(BIN)paging_problm.bin : paging_problm.cpp
	g++ $(CFLAG) $^ -o $@

$(BIN)paging_performance.bin : paging_performance.c $(mylibs)
	$(COMPL)

$(BIN)vmm.bin : ./virtual_mem_manager/tlb.cpp ./virtual_mem_manager/page_table.cpp ./virtual_mem_manager/backing_store.cpp ./virtual_mem_manager/main.cpp
	g++ $(CFLAG) $^ -o $@
	
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
