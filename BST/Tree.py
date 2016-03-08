from Node import Node

class Tree(object):

    def __init__(self):
        self.root = None
        self.height = 0

    #get input number and convert it to node.
    def InputNumber(self,inputArray):
        # number = int(input())
        for number in inputArray:
            newNode = Node(number)
            if self.root is None:
                self.root = newNode
            else:
                # This function is only called once a tree begins to exist
                self.InsertNodeinTree(newNode,self.root)

    def InsertNodeinTree(self,newNode,root):
        currentNode = root
        if newNode.value < currentNode.value:
            # go to left subtree
            if currentNode.leftChild is not None:
                self.InsertNodeinTree(newNode,currentNode.leftChild)
            else:
                currentNode.leftChild = newNode
                newNode.setParent(currentNode)
        else:
            # go to right subtree
            if currentNode.rightChild is not None:
                self.InsertNodeinTree(newNode,currentNode.rightChild)
            else:
                currentNode.rightChild = newNode
                newNode.setParent(currentNode)

    def InorderTraversal(self,root):
        if root is None:
            return
        else:
            leftval = self.InorderTraversal(root.leftChild)
            if leftval is not None:
                print "left value = ",leftval
            print root.value
            rightval = self.InorderTraversal(root.rightChild)
            if rightval is not None:
                print rightval

    def PreorderTraversal(self,root):
        if root is None:
            return
        else:
            leftval = self.PreorderTraversal(root.leftChild)
            if leftval is not None:
                print leftval
            rightval = self.PreorderTraversal(root.rightChild)
            if rightval is not None:
                print rightval



    def PostorderTraversal(self,root):
        if root is None:
            return
        else:
            rightval = self.PreorderTraversal(root.rightChild)
            if rightval is not None:
                print rightval
            print root.value
            leftval = self.PreorderTraversal(root.leftChild)
            if leftval is not None:
                print leftval

if __name__ == "__main__":
    inputs = [3,1,2,5,4]
    tree = Tree()
    tree.InputNumber(inputs)
    print "in order traversal"
    tree.InorderTraversal(tree.root)
    print "pre order traversal"
    tree.PreorderTraversal(tree.root)
    print "post order traversal"
    tree.PostorderTraversal(tree.root)
