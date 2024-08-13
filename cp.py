# -*- coding: utf-8 -*-
from genericpath import isfile
import os
from queue import Empty
import re
import sys
import shutil

def isLinux():
    if sys.platform == 'linux':
        return True
    return False

def isWin():
    if sys.platform == 'win32':
        return True
    return False

def mkdir(dest):
    if os.path.exists(dest) == False:
        os.makedirs(dest)

# adding exception handling
def copyDo(source, target):        
    try:
        shutil.copy(os.path.abspath(source), os.path.abspath(target))
        print(source, target)
    except IOError as e:
        print("Unable to copy file. %s" % e)
    except:
        print("Unexpected error:", sys.exc_info())

def copydir(source, dest):
    source = os.path.abspath(source)
    dest = os.path.abspath(dest)
    for dirPath, subDir, files in os.walk(source):
        if os.path.abspath(dirPath) != dest:
            destDir = os.path.join(dirPath).replace(source, dest)
            mkdir(destDir)
            for file in files:
                sourceFile = os.path.join(dirPath, file)
                destFile = sourceFile.replace(source, dest)
                copyDo(sourceFile, destFile)


def copy(source, dest):
    if os.path.exists(dest) != True:
        os.makedirs(dest)
    if os.path.isdir(source):
        if source == dest:
            dest += '_copy'
        copydir(source, dest)
    elif os.path.isfile(source):
        copyDo(source, dest)

def exec():
    source = ''
    dest = ''
    if len(sys.argv) == 3:
        path1 = sys.argv[1]
        path2 = sys.argv[2]
        if isWin():
            source = path1.replace('\\', '/')
            dest = path2.replace('\\', '/')
    
    elif len(sys.argv) == 2:
        path1 = sys.argv[1]
        source = path1
        if isWin():
            source = path1.replace('\\', '/')
        dest = source
    if source != '' and dest != '':
        copy(source, dest)

exec()
