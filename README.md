﻿#	cpp-TrafficSimulator
##	Installation
###	Windows 10
####	Required programs:
- Compiled BOOST libraries located in `C:/Boost/boost_1_63_0`;
- `SCONS`
- Qt compiler located in `C:/Qt/5.8/msvc2015_64`;
- sqlite3 for database lookup

Before compiling project run copyDlls.bat to copy qt dlls used in project

###	Linux ubuntu 16.04
####	Packages installation and building project:
- If boost libraries not installed:
	```
	sudo apt-get install libboost-all-dev
	```
- If scons not installed:
	```
	sudo apt-get install scons
	```
- Qt compilator installation:
	```
	sudo apt-get install qt5-default
	```
- SQLite installation:
	```
	sudo apt install sqlite3
	```
- To build full project with tests:
	```
	scons
	```
- To build project without tests:
	```
	scons tests=0
	```
- To run main application:
	```
	./TrafficSimulator
	```
- To run tests:
	```
	./Tests
	```

#	Scenariusz użycia aplikacji:
1. Wybierz `scenariusz1` z menu `Plik` aby załadować miasto.
2. Wybierz `Ruch losowy` z menu `Plik` aby wygenerować ruch losowy w mieście.
3. Wybierz `Start` z menu `Plik` aby rozpocząć symulację.