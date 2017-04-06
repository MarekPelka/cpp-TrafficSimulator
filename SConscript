Import('qtEnv')
env = qtEnv.Clone()
env.EnableQt5Modules([
                      'QtGui',
                      'QtCore',
					  'QtWidgets'
                     ])

#env.Program('TrafficSimulator', Glob('src/*.cpp'))
env.Program(target = 'TrafficSimulator', source = [ Glob('src/*.cpp') ,
	Glob('src/models/*.cpp'),
	Glob('src/viewmodels/*.cpp'),
	Glob('src/views*.cpp')] ) 
