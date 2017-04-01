import sys
import glob
import os

# Tries to detect the path to the installation of Qt with
# the highest version number
def detectLatestQtDir():
    if sys.platform.startswith("linux"):
        # Simple check: inspect only '/usr/local/Trolltech'
        paths = glob.glob('/usr/local/Trolltech/*')
        if len(paths):
            paths.sort()
            return paths[-1]
        else:
            return ""
    else:
        # Simple check: inspect only 'C:\Qt'
        paths = glob.glob('C:\\Qt\\5.8\\msvc2015_64*')
        if len(paths):
            paths.sort()
            return paths[-1]
        else:
            return os.environ.get("QTDIR","")

# Detect Qt version
qtdir = detectLatestQtDir()

# Create base environment
baseEnv = Environment()

# Clone Qt environment
qtEnv = baseEnv.Clone()
# Set QT5DIR and PKG_CONFIG_PATH
#qtEnv['ENV']['PKG_CONFIG_PATH'] = os.path.join(qtdir, 'lib/pkgconfig')
qtEnv['QT5DIR'] = qtdir
# Add qt5 tool
qtEnv.Tool('qt5')
#...further customization of qt env

# Export environments
Export('baseEnv qtEnv')

# Your other stuff...
# ...including the call to your SConscripts

SConscript('SConscript')