CPPFLAGS +=  -std=c++11 -g -Wall
LDFLAGS += 

BINARIES := fasade proxy decorator adapter1 adapter2 composite flyweight bridge

HEADERS=$(wildcard *.h)
all: $(BINARIES)
$(BINARIES): $(HEADERS)
	$(CXX) $(CPPFLAGS) -o $@ $(filter %.cpp, $^) $(LDFLAGS)

fasade: Fasadedemo.cpp
proxy: ProxyDemo.cpp
decorator: DecoratorDemo.cpp
adapter1: AdapterDemo.cpp
adapter2: AdapterDemo1.cpp
composite: CompositeDemo.cpp
flyweight: FlyweightDemo.cpp
bridge: BridgeDemo.cpp

.PHONY: all clean print

clean:
	-rm -rf ${BINARIES}

print:
	@echo $(BINARIES)

