CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = EDA_Assess
SRCS = main.cpp parser.cpp place.cpp exporter.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS)
