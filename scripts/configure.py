from ninja_syntax import Writer
from os import system, listdir
import os
from os.path import isfile, join
from sys import platform

# Note -s-d as part of the lib names. See SFML docs on that.
# constants.h           dorkanoid-cl\src\constants.h                   577
# main.cpp              dorkanoid-cl\src\main.cpp                     1804
# ball.cpp              dorkanoid-cl\src\entities\ball.cpp            1729
# ball.hpp              dorkanoid-cl\src\entities\ball.hpp             775
# brick.cpp             dorkanoid-cl\src\entities\brick.cpp           2262
# brick.hpp             dorkanoid-cl\src\entities\brick.hpp            896
# brickyard.cpp         dorkanoid-cl\src\entities\brickyard.cpp       1171
# brickyard.hpp         dorkanoid-cl\src\entities\brickyard.hpp        495
# paddle.cpp            dorkanoid-cl\src\entities\paddle.cpp          2065
# paddle.hpp            dorkanoid-cl\src\entities\paddle.hpp           854
# sound_manager.cpp     dorkanoid-cl\src\managers\sound_manager.cpp   1442
# sound_manager.hpp     dorkanoid-cl\src\managers\sound_manager.hpp    920
# stage_one.cpp         dorkanoid-cl\src\stages\stage_one.cpp         1885
# stage_one.hpp         dorkanoid-cl\src\stages\stage_one.hpp          813
# stage.hpp             dorkanoid-cl\src\stages\stage.hpp              459
# timer.cpp             dorkanoid-cl\src\util\timer.cpp                338
# timer.hpp             dorkanoid-cl\src\util\timer.hpp                438
# util_intersection.hpp dorkanoid-cl\src\util\util_intersection.hpp    641
# util_rand.hpp         dorkanoid-cl\src\util\util_rand.hpp            833
# util_str.cpp          dorkanoid-cl\src\util\util_str.cpp             306
# util_str.hpp          dorkanoid-cl\src\util\util_str.hpp             277

sources = (
    'src/main.cpp',
    'src/entities/ball.cpp',
    'src/entities/brick.cpp',
    'src/entities/brickyard.cpp',
    'src/entities/paddle.cpp',
    'src/managers/sound_manager.cpp',
    'src/stages/stage_one.cpp',
    'src/util/timer.cpp',
    'src/util/util_str.cpp'
)

includes = (
    'src',
    'src/entities',
    'src/managers',
    'src/stages',
    'src/util'
)

project_dir = os.path.abspath(join(os.path.dirname(__file__), '..'))
build_dir = os.path.join(project_dir, 'build')
media_dir = os.path.join(project_dir, 'media')

# https://docs.python.org/3/library/sys.html#sys.platform
# linux, darwin, win32, cygwin
# startswith('freebsd')
print(f'Platform: {platform}')
print(f'Project dir: {project_dir}')
print(f'Build dir: {build_dir}')
os.makedirs(build_dir, exist_ok=True)

sfml_include = ''
sfml_libpath = ''
if platform == 'win32':
    # TODO: improve this for other platforms
    sfml_include = os.path.join(project_dir, 'x64-windows-static\include')
    sfml_libpath = os.path.join(project_dir, 'x64-windows-static\lib')

media = [f for f in listdir(media_dir) if isfile(join(media_dir, f))]

def src_to_obj(src: str, builddir: str = '$builddir') -> str:
    src = '-'.join(src.split('/')[1:])
    return os.path.join(builddir, os.path.splitext(src)[0] + '.obj')

def configure_for_win32_msvc(ninja):
    libs = (
        # windows system libs
        'winmm.lib',
        'gdi32.lib',
        'user32.lib',
        'ole32.lib',
        'shell32.lib',
        'ogg.lib',
        'OpenAL32.lib',
        'brotlidec-static.lib',
        'brotlienc-static.lib',
        'brotlicommon-static.lib',
        'libpng16.lib',
        'opengl32.lib',
        'freetype.lib',
        'Advapi32.lib',
        'FLAC.lib',
        'bz2.lib',
        'vorbis.lib',
        'vorbisenc.lib',
        'vorbisfile.lib',
        'zlib.lib',
        'sfml-system-s.lib',
        'sfml-graphics-s.lib',
        'sfml-window-s.lib',
        'sfml-audio-s.lib',
        'sfml-network-s.lib',
    )

    ninja.variable('cc', 'cl')
    ninja.variable('link', 'link')
    ninja.variable('cppflags', '/EHsc /std:c++17 /MT /D SFML_STATIC')
    ninja.variable('incs', [f'/I "{i}"' for i in includes])
    ninja.variable('sfml_inc', sfml_include)
    ninja.variable('sfml_lib', sfml_libpath)
    ninja.variable('builddir', build_dir)
    ninja.variable('mediadir', media_dir)
    ninja.variable('exe', 'dorkanoid.exe')
    ninja.variable('sources', ' '.join(sources))
    ninja.variable('objects', ' '.join(objs))
    ninja.variable('libs', ' '.join(libs))

    ninja.rule('cc', '$cc $incs /I $sfml_inc $cppflags /c $in /Fo$out', )
    ninja.rule('link', '$link /LIBPATH:$sfml_lib $objects $libs /OUT:$builddir/$out /DEBUG')
    ninja.rule('cp', 'cmd /c copy $in $out')

    ninja.newline()
    for src in sources:
        obj = src_to_obj(src)
        ninja.build(obj, 'cc', src)

    ninja.newline()
    ninja.comment('Build the executable')
    ninja.build('$exe', 'link', objs)

    # Folder copy; prefer file copy below
    # ninja.build(join('$builddir', 'media'), 'cp', '$mediadir')

    ninja.newline()
    ninja.comment('Copy media files')
    for f in media:
        ninja.build(join('$builddir', 'media', f), 'cp', join('$mediadir', f))

def configure_for_linux_gcc(ninja):
    # g++ -Wall -Ibuild/include -g -std=c++11 -c {} -o {} -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio
    # g++ -o  {} {} -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio
    ninja.variable('cc', 'g++')
    ninja.variable('link', 'g++')
    ninja.variable('cppflags', '-Wall -g -std=c++11')
    ninja.variable('incs', [f'-I"{i}"' for i in includes])
    # ninja.variable('sfml_inc', sfml_include)
    # ninja.variable('sfml_lib', sfml_libpath)
    ninja.variable('builddir', build_dir)
    ninja.variable('mediadir', media_dir)
    ninja.variable('exe', 'dorkanoid')
    ninja.variable('sources', ' '.join(sources))
    ninja.variable('objects', ' '.join(objs))

    ninja.rule('cc', '$cc $incs $cppflags -c $in -o $out -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio', )
    ninja.rule('link', '$link -o $exe $objects -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio')
    ninja.rule('cp', 'cp $in $out')

    ninja.newline()
    for src in sources:
        obj = src_to_obj(src)
        ninja.build(obj, 'cc', src)

    ninja.newline()
    ninja.comment('Build the executable')
    ninja.build('$exe', 'link', objs)

    ninja.newline()
    ninja.comment('Copy media files')
    for f in media:
        ninja.build(join('$builddir', 'media', f), 'cp', join('$mediadir', f))

if __name__ == '__main__':
    print(f'Configuring build system for {platform}')

    with open('build.ninja', 'w') as f:
        ninja = Writer(f)

        objs = []
        for src in sources:
            obj = src_to_obj(src)
            objs.append(obj)

        if platform == 'win32':
            configure_for_win32_msvc(ninja)
