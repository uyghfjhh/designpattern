CPPFLAGS +=  -std=c++11 -g -Wall
LDFLAGS += 
BINARIES := iterator strategy chanofresponsibility templatemethod state1 state2 mediator visitor command 

HEADERS=$(wildcard *.h)
all: $(BINARIES)
$(BINARIES): $(HEADERS)
	$(CXX) $(CPPFLAGS) -o $@ $(filter %.cpp, $^) $(LDFLAGS)

observer: ObserverDemo.cpp
iterator: IteratorDemo.cpp
chanofresponsibility: ChanOfResponsibilityDemo.cpp
strategy: StrategyDemo.cpp
templatemethod: TemplateMethodDemo.cpp
state1: StateDemo.cpp
state2: StateDemo2.cpp
mediator: MediatorDemo.cpp
visitor: VisitorDemo.cpp
command: CommandDemo.cpp


.PHONY: all clean print

clean:
	-rm -rf ${BINARIES}

print:
	@echo $(BINARIES)
