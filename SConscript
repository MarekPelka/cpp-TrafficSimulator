Import('qtEnv')
env = qtEnv.Clone()
env.EnableQt5Modules([
                      'QtGui',
                      'QtCore',
					  'QtWidgets'
                     ])

env.Program('SconsTest', Glob('*.cpp'))
