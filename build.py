#!/usr/bin/env python
import os, os.path
import shutil, glob

def cpp_to_obj(src):
    return os.path.basename(src.replace(".cpp", ".o"))

def find_cpp_files(path):
    src = []
    hpp = []
    
    for root, dirs, files in os.walk(path):
        # print( root, dirs, files )
        for f in files:
            if f.endswith('.cpp'):
                src.append( os.path.join(root, f) )
            if f.endswith('.hpp') or f.endswith('.h'):
                hpp.append( os.path.join(root, f) )
            
    return (src, hpp)
    
def is_modified(src, dest):
    if not os.path.exists(dest):
        return True
    
    srctm = os.path.getmtime(src)
    objtm = os.path.getmtime(dest)
    
    return srctm > objtm

def mkdirectories(obj_dir = 'build/obj', hpp_dir = 'build/include'):    
    # script_d = os.path.dirname(os.path.realpath(__file__))
    # od = os.path.join(script_d, obj_dir)
    # hd = os.path.join(script_d, hpp_dir)
    od, hd = (obj_dir, hpp_dir)
    if not os.path.exists(od):
        os.makedirs(od)
    if not os.path.exists(hd):
        os.makedirs(hd)
        
    return (od, hd)

def copy_headers(header_list, hpp_dir):
    print("Copying headers to {}...".format(hpp_dir))
    changes = False
    for hpp in header_list:
        dest = os.path.join(hpp_dir, os.path.basename(hpp))
        if is_modified(hpp, dest):
            shutil.copyfile(hpp, dest)
            print("Copying {}".format(hpp))
            changes = True
        else:
            print("Nothing to do for {}".format(hpp))
    return changes

def build_modules(src_list, obj_dir):
    print("Building source...")
    changes = False
    for cpp in src_list:
        obj = os.path.join(obj_dir, cpp_to_obj(cpp))
        if is_modified(cpp, obj):
            gpp = "g++ -Wall -Ibuild/include -g -std=c++11 -c {} -o {} -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio".format(cpp, obj)
            print(gpp)
            os.system(gpp)
            changes = True
        else:
            print("Nothing to do for {}".format(cpp))
    
    return changes

def link_objects(src_list, obj_dir):
    objs = []
    for cpp in src_list:
        o = os.path.join(obj_dir, cpp_to_obj(cpp))
        objs.append(o)
        
    gpp = "g++ -o  dorkanoid {} -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio".format(" ".join(objs))
    print(gpp)
    os.system(gpp)

if __name__ == '__main__':
    script_dir = os.path.dirname(os.path.realpath(__file__))
    source_dir = os.path.join(script_dir, 'src')
    obj_dir, hpp_dir = mkdirectories()
    impls, headers = find_cpp_files(source_dir)
    print(source_dir)
    changes1 = copy_headers(headers, hpp_dir)
    changes2 = build_modules(impls, obj_dir)
    if changes1 and changes2:
        link_objects(impls, obj_dir)
    else:
        print("Nothing to do.")
