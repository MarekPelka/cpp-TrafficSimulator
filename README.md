#	Linux ubuntu 16.04 packages installation and building project:

- if boost libraries not installed:
	'''
	sudo apt-get install libboost-all-dev
	'''
- if scons not installed:
	'''
	sudo apt-get install scons
	'''
- Qt compilator installation:
	'''
	sudo apt-get install qt5-default
	'''
-to build full project with tests:
	'''
	scons
	'''
-to build project without tests:
	'''
	scons tests=0
	'''
- to run main application:
	'''
	./TrafficSimulator
	'''
- to run tests:
	'''
	./Tests
	'''

#	Scenariusz użycia aplikacji:
1. Wybierz 'scenariusz1' z menu 'Plik' aby załadować miasto.
2. Wybierz 'Ruch losowy' z menu 'Plik' aby wygenerować ruch losowy w mieście.
3. Wybierz 'Start' z menu 'Plik' aby rozpocząć symulację.