This **Arkanoid**-like game was inspired by the following Youtube tutorial by 
Vittorio Romeo. It's a good introduction to the SFML library and uses C++ 11
features. 

* [Arkanoid Clone Tutorial](https://www.youtube.com/watch?v=_4K3tsKa1Uc)

After following the tutorial, I've enhanced the code and added the following
features:

* Stages
* Improved code structure
* Points
* Music and sound effects
* Randomization of ball mechanics

For those of you retro gaming nuts, you'll notice that this version differs 
pretty significantly from the original. The goal of the project isn't 
to create a clone of the original game, but to create a game in similar style
that's still enjoyable to play. 

If you'd like a true Arkanoid clone, you should take this project as a starting
point and build your own! ;)

[History of Arkanoid](https://en.wikipedia.org/wiki/Arkanoid)

###Build:

While this game is theoretically cross-platform, at this point I've done all
development on Linux (Ubuntu). To build the game on linux, install libsfml:

	sudo apt-get install libsfml-dev build-essential
	
There is a makefile in the root directory. From the root of the project:

	make
	
This will build the application. 

###License:

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

	// Copyright (c) 2015 Matthew MacGregor
	// License: Academic Free License ("AFL") v. 3.0
	// AFL License page: http://opensource.org/licenses/AFL-3.0
