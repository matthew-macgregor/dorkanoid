### Dorkanoid

This **Arkanoid**-like game was inspired by the following Youtube tutorial by
Vittorio Romeo. It's a good introduction to the SFML library and uses C++ 11
features.

* [Arkanoid Clone Tutorial](https://www.youtube.com/watch?v=_4K3tsKa1Uc)
* [Github](https://github.com/SuperV1234/Tutorials)

After following the tutorial, I've enhanced the code and added the following
features:

* Stages
* Improved code structure
* Points
* Music and sound effects
* Randomization of ball mechanics

![Screenshot](media/screenshot.jpeg)

### Media Credits

Music created by freesound user [dAmbient](http://www.freesound.org/people/dAmbient/)
and licensed under the [CC Attribution License](http://creativecommons.org/licenses/by/3.0/).

Sound effects created using the awesome [JSFXR](http://github.grumdrig.com/jsfxr/).

### Arkanoid

For those of you retro gaming nuts, you'll notice that this version differs
pretty significantly from the original. The goal of the project isn't
to create a clone of the original game, but to create a game in similar style
that's still enjoyable to play.

If you'd like a true Arkanoid clone, you should take this project as a starting
point and build your own! ;)

[History of Arkanoid](https://en.wikipedia.org/wiki/Arkanoid)

### Instructions to Build:

#### Windows

To build the game on Windows 10, install the following:

- MSVC C++ Build Tools (or Visual Studio 2019-2022 with C++ Desktop installed)
- Build or install `ninja`: https://ninja-build.org
- Python 3 (tested with Python 3.10)
- `vcpkg` to install SFML: https://github.com/microsoft/vcpkg
	- `vcpkg install sfml x64-windows-static`
	- You can also use a standalone directory with the same `lib` and `include` structure as vcpkg uses.

Run the following:

```ps1
python scripts/configure.py --sfml-path 'C:\path-to-sfml\x64-windows-static'
ninja
```

##### Using a standalone directory:

You can provide a standalone directory with the same structure as vcpkg's `x64-windows-static` folder:

TBD

#### Linux (Ubuntu)

To build the game on linux, install the following:

	sudo apt-get install libsfml-dev build-essential ninja-build

I use a python script for building the project. It works with Python 3:

	python3 scripts/configure.py

As with make, this script will only build the source files that have been
modified.

### License:

Original code distributed under the following license terms:

	// Inspired by https://github.com/SuperV1234/Tutorials
	//
	// Original source code Copyright (c) 2013-2015 Vittorio Romeo
	// License: Academic Free License ("AFL") v. 3.0
	// AFL License page: http://opensource.org/licenses/AFL-3.0
	//
	// NOTICE: According to the terms of the AFL-3.0, this code has
	// been substantially altered from the original by Matthew MacGregor.

Some code files are new/original, and these I have licensed conveniently
using the AFL-3.0 as well:

	// Copyright (c) 2015-2022 Matthew MacGregor
	// License: Academic Free License ("AFL") v. 3.0
	// AFL License page: http://opensource.org/licenses/AFL-3.0
