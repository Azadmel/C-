# This class defines a node which has a value. It can form a tree by having another node as it's left and/or right child.
class Node(object):

	def __init__(self,value):
		self.value = value
		self.leftChild  = None
		self.rightChild = None
		self.parent = None
		print "node created"

	def setParent(self,parent):
		self.parent = parent

	def getParent(self):
		print self.parent.value