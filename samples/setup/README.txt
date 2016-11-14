How To Build:

1. modify "dcg_build_system/config.json":
	a. set the "lib_directories" list to whatever is appropriate for your system.
	
	b. set the "include_directories" list to whatever is appropriate for your system.
					
	c. set the "libs" list:
		if you're using Windows: 
			replace:
				"dl", "Xinerama", "X11", "Xxf86vm", "Xrandr", "pthread", "Xi", "Xcursor"
			with:
				"opengl32"
		I haven't tested this on windows, so I'm not sure this will work.

run "dcg_build_system/scripts/buildSys -build".

the executable will be located in "dcg_build_system/build/DEBUG/bin/"
