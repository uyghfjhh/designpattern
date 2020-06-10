CPPFLAGS +=  -std=c++11 -g -Wall
LDFLAGS += 

BINARIES := singleton builder factory prototype

HEADERS=$(wildcard *.h)
all: $(BINARIES)
$(BINARIES): $(HEADERS)
	$(CXX) $(CPPFLAGS) -o $@ $(filter %.cpp, $^) $(LDFLAGS)

singleton: SingletonDemo.cpp
factory: FactoryDemo.cpp
builder: BuilderDemo.cpp
prototype: ProtoTypeDemo.cpp

.PHONY: all clean print

clean:
	-rm -rf ${BINARIES}

print:
	@echo $(BINARIES)

