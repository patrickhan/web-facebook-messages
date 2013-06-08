#!/usr/bin/env python
# tools '''

''' copy a files to another folder '''

from os import listdir
from os.path import isfile, join
import shutil, errno


def listfile(dir):
    onlyfiles = [ f for f in listdir(dir) if isfile(join(dir,f)) ]
    print onlyfiles

def copytofolder(src, dst):
    try:
        shutil.copytree(src, dst)
    except OSError as exc: # python >2.5
        if exc.errno == errno.ENOTDIR:
            shutil.copy(src, dst)
        else: raise


def copytofolder2(src, dst):
    fileList = listdir(src )
    fileList = [src+filename for filename in fileList]

    for f in fileList:
        shutil.copy2(f, dst)
    print 'it is ok'

dir_src = ur"D:/ffaddonsdk110/addon-sdk-1.11/addon-sdk-1.11/web-facebook-messages/data/facebook/"
dir_dest = ur"C:/Program Files/Federated Networks/HackJacket/HackJacketA/extensions/facebook@jetpack/resources/facebook/data/facebook/"

''''
can not use string like this
dir1 = "D:\ffaddonsdk110\addon-sdk-1.11\addon-sdk-1.11\web-facebook-messages\data\facebook"
dir1 = ur"D:\ffaddonsdk110\addon-sdk-1.11\addon-sdk-1.11\web-facebook-messages\data\facebook"
'''
#copytofolder(dir01, dir02) //shutil.copytree has error in Windows 7
copytofolder2(dir_src, dir_dest)


dir_scr1 = "D:/ffaddonsdk110/addon-sdk-1.11/addon-sdk-1.11/web-facebook-messages/59/"
dir_dest1 = "C:/Program Files/Federated Networks/HackJacket/HackJacketA/extensions/{594D0C6A-C6BB-4875-8164-3776586BB9A2}/content/webpgjs/"

copytofolder2(dir_scr1, dir_dest1)





