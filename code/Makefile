LIBS=-lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui


all: threshold  resize

clean:
	rm threshold blur *.png

threshold: threshold.cpp
	g++ threshold.cpp $(LIBS) -o threshold


blur: blur.cpp
	g++ blur.cpp $(LIBS) -o blur

resize: resize.cpp
	g++ resize.cpp $(LIBS) -o resize

displayInfo: displayInfo.cpp
	g++ displayInfo.cpp $(LIBS) -o displayInfo

zoneOrigin: zoneOrigin.cpp
	g++ zoneOrigin.cpp -o zoneOrigin

populateOrigin: populateOrigin.cpp
	g++ populateOrigin.cpp -o populateOrigin
zone: zone.cpp
	g++  $(LIBS) zone.cpp -o zone
