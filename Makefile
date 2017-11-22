LIBCURL=/usr/local/curl-7.56.0
LIBCURL_INCLUDE=$(LIBCURL)/include
LIBCURL_LIB=$(LIBCURL)/lib

INCLUDE_PATH=                   \
    -I$(LIBCURL_INCLUDE)        \

LIB_PATH=                       \
    -L$(LIBCURL_LIB)            \

LIBS=                           \
    -lcurl                      \

BIN_DIR=./bin
OBJECTS=                         \
    $(BIN_DIR)/jsoncpp.o         \
    $(BIN_DIR)/utils.o           \
    $(BIN_DIR)/exchange-api.o    \
    $(BIN_DIR)/binance-api.o     \
    $(BIN_DIR)/exchange.o        \

coin_exchange: $(BIN_DIR) $(OBJECTS)
	ld $(LIB_PATH) $(LIBS) $(OBJECTS) -o $@

$(BIN_DIR):
	mkdir -p $@

$(BIN_DIR)/jsoncpp.o: thirdparty/jsoncpp-1.8.3/jsoncpp.cpp thirdparty/jsoncpp-1.8.3/json.h
	g++ $(INCLUDE_PATH) -c thirdparty/jsoncpp-1.8.3/jsoncpp.cpp -o $@
$(BIN_DIR)/utils.o: utils/utils.cpp utils/utils.h 
	g++ $(INCLUDE_PATH) -c utils/utils.cpp -o $@
$(BIN_DIR)/exchange-api.o: exchange-api.cpp exchange-api.h
	g++ $(INCLUDE_PATH) -c exchange-api.cpp -o $@
$(BIN_DIR)/binance-api.o: binance-api/binance-api.cpp binance-api/binance-api.h
	g++ $(INCLUDE_PATH) -c binance-api/binance-api.cpp -o $@
$(BIN_DIR)/exchange.o: exchange.cpp
	g++ $(INCLUDE_PATH) -c exchange.cpp -o $@

clean:
	rm -fr $(BIN_DIR)

all: clean coin_exchange
