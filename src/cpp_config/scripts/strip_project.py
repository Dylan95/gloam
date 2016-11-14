
import sys

from core.CppConfig import *

str_cppConfigDir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
str_projectDir = os.path.dirname(str_cppConfigDir)
#
str_configDir = os.path.join(
	str_cppConfigDir,
	"config"
)

def main():
	str_usage = "usage:"
	#
	#verify python version:
	if(sys.version_info[0] != 3):
		print(
			"buildSys.py: fatal error: python major version is \"" + 
			str(sys.version_info[0]) + 
			"\".  The script must be run with python major version 3."
		)
		sys.exit(2)
	#
	if(len(sys.argv) == 1):
		CppConfig(str_projectDir, str_configDir).stripAll()
	else:
		print(str_usage)
		sys.exit(1)

#

main()

