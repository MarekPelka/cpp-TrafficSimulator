import platform, os

baseEnv = Environment()

if(platform.system() == "Linux"):
   baseEnv.Append( CPPFLAGS = '-Wall -pedantic -pthread -Wno-long-long' )
   baseEnv.Append( LINKFLAGS = '-Wall -pthread' )
   baseEnv.Append( CPPPATH = ['/usr/include/python3.5'] )
   baseEnv.Append( LIBPATH = ['/usr/lib/python3.5'] )
   baseEnv.Append( LIBS = [ 'boost_python3' ] )
   qtdir = ""

elif(platform.system() == "Windows"):
   baseEnv.Append( CPPPATH = [ 'C:/Boost/boost_1_63_0'] )
   baseEnv.Append( LIBPATH = [ 'C:/Boost/boost_1_63_0/stage/lib'] )
   qtdir = 'C:/Qt/5.8/msvc2015_64/'

else:
   print platform.system() + " not supported"

qtEnv = baseEnv.Clone()
# Set QT5DIR and PKG_CONFIG_PATH
#qtEnv['ENV']['PKG_CONFIG_PATH'] = os.path.join(qtdir, 'lib/pkgconfig')
qtEnv['QT5DIR'] = qtdir
# Add qt5 tool
qtEnv.Tool('qt5')

# Export environments
Export('baseEnv qtEnv')

SConscript('SConscript')
