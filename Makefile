LIBCURL=/usr/local/curl-7.56.0
LIBCURL_INCLUDE=$(LIBCURL)/include
LIBCURL_LIB=$(LIBCURL)/lib

#JSON=/usr/local/jsoncpp-1.8.3
#JSON_INCLUDE=$(JSON)/include
#JSON_LIB=$(JSON)/lib64

INCLUDE_PATH=                   \
    -I$(LIBCURL_INCLUDE)        \

LIB_PATH=                       \
    -L$(LIBCURL_LIB)            \

LINK_LIBS=                      \
    -lcurl                      \
    -lcrypto                    \

EXE=coin_exchange


BIN_DIR=./bin
OBJECTS=                         \
    $(BIN_DIR)/jsoncpp.o         \
    $(BIN_DIR)/utils.o           \
    $(BIN_DIR)/exchange-api.o    \
    $(BIN_DIR)/binance-api.o     \
    $(BIN_DIR)/liqui-api.o       \
    $(BIN_DIR)/executor.o        \
    $(BIN_DIR)/exchange.o        \


$(EXE): $(BIN_DIR) $(OBJECTS)
	g++ $(LIB_PATH) $(LINK_LIBS) $(OBJECTS) -o $@

$(BIN_DIR):
	mkdir -p $@

$(BIN_DIR)/jsoncpp.o: thirdparty/jsoncpp-1.8.3/jsoncpp.cpp thirdparty/jsoncpp-1.8.3/json.h
	g++ $(INCLUDE_PATH) -c thirdparty/jsoncpp-1.8.3/jsoncpp.cpp -o $@
$(BIN_DIR)/utils.o: utils/utils.cpp utils/utils.h 
	g++ $(INCLUDE_PATH) -c utils/utils.cpp -o $@
$(BIN_DIR)/exchange-api.o:  exchange-api.cpp exchange-api.h
	g++ $(INCLUDE_PATH) -c exchange-api.cpp -o $@
$(BIN_DIR)/binance-api.o: binance-api/binance-api.cpp binance-api/binance-api.h
	g++ $(INCLUDE_PATH) -c binance-api/binance-api.cpp -o $@
$(BIN_DIR)/liqui-api.o: liqui-api/liqui-api.cpp liqui-api/liqui-api.h
	g++ $(INCLUDE_PATH) -c liqui-api/liqui-api.cpp -o $@
$(BIN_DIR)/executor.o: executor.cpp executor.h
	g++ $(INCLUDE_PATH) -c executor.cpp -o $@
$(BIN_DIR)/exchange.o: exchange.cpp
	g++ $(INCLUDE_PATH) -c exchange.cpp -o $@

test:
	export LD_LIBRARY_PATH=$(LIBCURL_LIB) ; ./$(EXE)

clean:
	rm -fr $(BIN_DIR)
	rm -f $(EXE) 

all: clean $(EXE) test
