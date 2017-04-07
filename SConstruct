import platform, os

baseEnv = Environment()

if(platform.system() == "Linux"):
   baseEnv.Append( CPPFLAGS = '-std=c++11 -fPIC -finput-charset=iso-8859-2' )
   #baseEnv.Append( LINKFLAGS = '-Wall -pthread' )
   baseEnv.Append( CPPPATH = ['/usr/include/boost'] )
   baseEnv.Append( LIBPATH = ['/usr/lib/x86_64-linux-gnu'] )
   qtdir = '/usr/lib/x86_64-linux-gnu'

elif(platform.system() == "Windows"):
   baseEnv.Append( CPPPATH = [ 'C:/Boost/boost_1_63_0'] )
   baseEnv.Append( LIBPATH = [ 'C:/Boost/boost_1_63_0/stage/lib'] )
   qtdir = 'C:/Qt/5.8/msvc2015_64/'

else:
   print platform.system() + " not supported"

qtEnv = baseEnv.Clone()
# Set QT5DIR and PKG_CONFIG_PATH
qtEnv['ENV']['PKG_CONFIG_PATH'] = os.path.join(qtdir, 'lib/pkgconfig')
qtEnv['QT5DIR'] = qtdir
# Add qt5 tool
qtEnv.Tool('qt5')

# Export environments
Export('baseEnv qtEnv')

tests = ARGUMENTS.get('tests', 1)
if int(tests):
	baseEnv.Program( source = Glob('tests/*.cpp'), target = 'Tests' )

SConscript('SConscript')
