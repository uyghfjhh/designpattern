CPPFLAGS +=  -std=c++11 -g -Wall
LDFLAGS += 

BINARIES := observerdemo iteratordemo singletondemo strategydemo fasadedemo chanofresponsibilitydemo builderdemo  factorydemo prototypedemo proxydemo decoratordemo adapterdemo adapterdemo1 compositedemo flyweightdemo templatemethoddemo statedemo statedemo2

HEADERS=$(wildcard *.h)
all: $(BINARIES)
$(BINARIES): $(HEADERS)
	$(CXX) $(CPPFLAGS) -o $@ $(filter %.cpp, $^) $(LDFLAGS)

observerdemo:  ObserverDemo.cpp
iteratordemo:  IteratorDemo.cpp
chanofresponsibilitydemo: ChanOfResponsibilityDemo.cpp
singletondemo: SingletonDemo.cpp
strategydemo: StrategyDemo.cpp
fasadedemo: Fasadedemo.cpp
factorydemo: Factory.cpp
builderdemo: BuilderDemo.cpp
prototypedemo: ProtoTypeDemo.cpp
proxydemo: ProxyDemo.cpp
decoratordemo: DecoratorDemo.cpp
adapterdemo: AdapterDemo.cpp
adapterdemo1: AdapterDemo1.cpp
compositedemo: CompositeDemo.cpp
flyweightdemo: FlyweightDemo.cpp
templatemethoddemo: TemplateMethodDemo.cpp
statedemo: StateDemo.cpp
statedemo2: StateDemo2.cpp

.PHONY: all clean print

clean:
	-rm -rf ${BINARIES}

print:
	@echo $(BINARIES)

