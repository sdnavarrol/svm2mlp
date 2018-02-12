LIBS=-lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui


all: clean threshold blur

clean:
	rm threshold blur

threshold: threshold.cpp
	g++ threshold.cpp $(LIBS) -o threshold


blur: blur.cpp
	g++ blur.cpp $(LIBS) -o blur

