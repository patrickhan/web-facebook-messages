#!/usr/bin/env python

from PyQt4.QtGui import *
from PyQt4 import QtCore, QtGui

from copy import deepcopy

class PredefindedServices(object):
    __svc_list = [];
    def __init__(self, parent=None):
        self.__svc_list.append("HackJacket1")
        self.__svc_list.append("HackJacket2")
        self.__svc_list.append("HackJacket3")
        self.__svc_list.append("HackJacket4")
        self.__svc_list.append("HackJacket5")
    def getlist(self, ):
        return self.__svc_list;
    
class SelectedServices(object):
    __svc_list = [];
    def __init__(self, parent=None):
        pass
    def getlist(self, ):
        return self.__svc_list
    def add(aname ):
        if isinstance(aname, basestring) :
            self.__svc_list.append(aname)
    def remove(aname):
        if isinstance(aname, basestring) and aname in self.__svc_list:
            self.__svc_list.remove(aname)


class MainWindow(QtGui.QWidget):
    ''' a list to store the service'''
    #__svc_list = [] #private
    
    __predefined_svc_list = None  #protected  for the selected service
    __selected_svc_list = None  #protected  for the selected service
    
    _mainLayout =  None
    
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)


        self._mainLayout =  QtGui.QGridLayout()
        listWidget = QListWidget()
        listWidget2 = QListWidget()
        self.init_servicelist();
        
        #for i in range(10):
        #    item = QListWidgetItem("Item %i" % i)
        #    listWidget.addItem(item)
        for item in self.__predefined_svc_list:
            listWidget.addItem(item)
            listWidget2.addItem(item)
		
		#quitButton = QtGui.QPushButton("->")
		#quitButton.clicked.connect(self.onselect)
		
        #self._mainLayout.addWidget(quitButton, 0, 1) 
        self._mainLayout.addWidget(listWidget2, 0, 2)
        
        self.setLayout(self._mainLayout)
        
        self.setWindowTitle("Close the services")

    def init_servicelist(self, ):
        self.__predefined_svc_list = PredefindedServices().getlist()  #protected  for the selected service
        self.__selected_svc_list = SelectedServices().getlist()
	
	def onselect(self,):
		pass
        
if __name__ == '__main__':
    import sys
    app = QtGui.QApplication(sys.argv)
    
    mainWindow = MainWindow()
    mainWindow.show()

    sys.exit(app.exec_())

