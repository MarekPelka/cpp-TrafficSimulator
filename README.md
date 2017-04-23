linux ubuntu 16.04 packages installation and building project:

- if boost libraries not installed:
	sudo apt-get install libboost-all-dev
- if scons not installed:
	sudo apt-get install scons
- Qt installation:
	sudo apt-get install qt5-default
-to build full project with tests:
	scons
-to build project without tests:
	scons tests=0
- to run main application:
	./TrafficSimulator
- to run tests:
	./Tests

Application scenario:
1. select scenariusz1 from Plik menu to generate city
2. select Ruch losowy from Plik menu to generate vehicle movement in city
3. select start from Plik menu to start animation