from ninja_syntax import Writer
from os import system, listdir
import os
from os.path import isfile, join
from sys import platform
import argparse

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
print(f'Platform = {platform}')
print(f'Project dir = {project_dir}')
print(f'Build dir = {build_dir}')
os.makedirs(build_dir, exist_ok=True)

media = [f for f in listdir(media_dir) if isfile(join(media_dir, f))]

def src_to_obj(src: str, builddir: str = '$builddir') -> str:
    src = '-'.join(src.split('/')[1:])
    return os.path.join(builddir, os.path.splitext(src)[0] + '.obj')

def configure_for_win32_msvc(ninja, args):
    libs = (
        # windows system libs
        'gdi32.lib',
        'user32.lib',
        'ole32.lib',
        'shell32.lib',
        'winmm.lib',

        # sfml libraries
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
        'sfml-main.lib',
        # 'sfml-network-s.lib',
        # 'ws2_32.lib',
    )

    sfml_root_path = args.sfml_path if args.sfml_path else join(project_dir, 'x64-windows-static')
    sfml_include_path = join(sfml_root_path, 'include')
    sfml_libpath = join(sfml_root_path, 'lib')
    print(f'sfml_include_path = {sfml_include_path}')
    print(f'sfml_libpath = {sfml_libpath}')

    ninja.variable('cc', 'cl')
    ninja.variable('link', 'link')
    ninja.variable('cppflags', '/EHsc /std:c++17 /MT /D SFML_STATIC')
    ninja.variable('incs', [f'/I "{i}"' for i in includes])
    ninja.variable('sfml_inc', sfml_include_path)
    ninja.variable('sfml_lib', sfml_libpath)
    ninja.variable('sfml_lib_man', join(sfml_libpath, 'manual-link')) # sfml-main
    ninja.variable('builddir', build_dir)
    ninja.variable('mediadir', media_dir)
    ninja.variable('projectdir', project_dir)
    ninja.variable('exe', 'dorkanoid.exe')
    ninja.variable('sources', ' '.join(sources))
    ninja.variable('objects', ' '.join(objs))
    ninja.variable('libs', ' '.join(libs))
    ninja.variable('icon_res', '$builddir/icon.res')

    ninja.rule('cc', '$cc $incs /I $sfml_inc $cppflags /c $in /Fo$out', )
    ninja.rule('link', '$link /SUBSYSTEM:windows /LIBPATH:$sfml_lib /LIBPATH:$sfml_lib_man $in $libs /OUT:$builddir/$out')
    ninja.rule('cp', 'cmd /c copy $in $out')
    ninja.rule('rc', 'rc /fo $out /r $in ')

    ninja.newline()
    for src in sources:
        obj = src_to_obj(src)
        ninja.build(obj, 'cc', src)

    ninja.newline()
    ninja.comment('Create res file')
    ninja.build('$icon_res', 'rc', '$mediadir\icon.rc')

    ninja.newline()
    ninja.comment('Build the executable')
    ninja.build('$exe', 'link', objs + ['$icon_res'], order_only = ['$icon_res',])

    ninja.newline()
    ninja.comment('Copy media files')
    for f in media:
        if f in ('icon.res', 'icon.rc', 'orb-g5023d71b4_1280.png',): continue
        ninja.build(join('$builddir', 'media', f), 'cp', join('$mediadir', f))

def configure_for_linux_gcc(ninja, args):
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

    parser = argparse.ArgumentParser(description='Configure ninja.build')

    parser.add_argument('--sfml-path', help='Path to the SFML library and headers (x64-windows-static).')
    args = parser.parse_args()

    with open('build.ninja', 'w') as f:
        ninja = Writer(f)

        objs = []
        for src in sources:
            obj = src_to_obj(src)
            objs.append(obj)

        if platform == 'win32':
            configure_for_win32_msvc(ninja, args)
        elif platform == 'linux':
            configure_for_linux_gcc(ninja, args)
        else:
            print(f'Sorry, {platform} is not yet supported.')
