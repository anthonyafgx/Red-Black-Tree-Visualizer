"""
Implementacion de RED BLACK TREE en python con: Insert, Remove, Find y Traversal,
Grupo:
Javier Carrillo
Anthony Ferrer 
"""
from Nodo import Nodo
import sys

class RedBlackT(): # ARBOL RED BLACK

    def __init__(self): # self es utilizado para hacer referencial al objeto que se este llamando
        self.Null = Nodo(0) # Se inicia el arbol estando este vacio y sin valores en este momento
        self.Null.redBlack = 1
        self.Null.left = None
        self.Null.right = None
        self.root = self.Null
    
    def Find(self, valor): # Creamos el metodo find ya que este es el mas facil
        temp = self.root
        while temp != self.Null and valor != temp.valor:
            if valor < temp.valor:
                temp = temp.left
            else:
                temp = temp.right
        if temp.valor == valor:
            print("El nodo existe")
            return temp
        else:
            return "El nodo no existe" 
        
    def rojoNegro(self, valor): # Creamos otro metodo extra 
        temp = self.Find(valor)
        if temp.redBlack == 1:
            print("Es negro")
        else:
            print("Es rojo")
    #Creamos la funcion del valor mas pequeño y el mas alto que pueden ser de ayuda en un futuro
    def lowest(self, Nodo):
        while Nodo.left != self.TNULL:
            Nodo = Nodo.left
        return Nodo

    def highest(self, Nodo):
        while Nodo.right != self.TNULL:
            Nodo = Nodo.right
        return Nodo
    
     # Creamos las rotaciones para balancear el arbol luego de un remove o un insert
    def rightRotation(self, nodoX):
        temp = nodoX.left
        nodoX.left = temp.right
        if temp.right != self.Null:
            temp.right.parentNode = nodoX
        temp.parentNode = nodoX.parentNode
        #dependiento del nodo padre del de nodoX nuestro nodo temporal sera asignado
        if nodoX.parentNode == None:
            self.root = temp
        elif nodoX == nodoX.parentNode.right:
            nodoX.parentNode.right = temp
        else: 
            nodoX.parentNode.right = temp
        #aqui completamos la rotacion
        temp.right = nodoX
        nodoX.parentNode = temp

    # Rotacion a la izquierda   
    def leftRotation(self, nodoX):
        temp = nodoX.right
        nodoX.right = temp.left
        if temp.left != self.Null:
            temp.left.parentNode = nodoX
        temp.parentNode = nodoX.parentNode    
        if nodoX.parentNode == None:
            self.root = temp
        elif nodoX == nodoX.parentNode.left:
            nodoX.parentNode.left = temp
        else:
            nodoX.parentNode.right  = temp
        temp.left = nodoX
        nodoX.parentNode = temp

     #Con las rotaciones ahora podemos implementar el Insert y el Remove
    def Insert(self, valor):
        newNode = Nodo(valor) 
        newNode.parentNode = None
        newNode.left = self.Null
        newNode.right = self.Null
        newNode.redBlack = 0 # Al insertarse debe ser rojo

        parentNode = None
        temp = self.root
        while temp != self.Null:
            parentNode = temp
            if newNode.valor < temp.valor:
                temp = temp.left
            elif newNode.valor > temp.valor:
                temp = temp.right
            else:
                return

         # Se coloca el nodo padre si no es root al nuevo nodo
        newNode.parentNode = parentNode
        if parentNode == None:
            self.root = newNode
        elif newNode.valor < parentNode.valor:
            parentNode.left = newNode
        else:
            parentNode.right = newNode 

        #Ahora debemos arreglar el arbol luego de insertar el nuevo nodo
        self.insertFixed(newNode)

    # Con este metodo balaceamos el RedBlack Tree
    def insertFixed(self, newNode):
        while newNode != self.root and newNode.parentNode.redBlack == 0:
            if newNode.parentNode == newNode.parentNode.parentNode.right:
                uncleNode = newNode.parentNode.parentNode.left  # Nodo tio
                if uncleNode.redBlack == 0:
                    uncleNode.redBlack = 1
                    newNode.parentNode.redBlack = 1
                    newNode.parentNode.parentNode.redBlack = 0
                    newNode = newNode.parentNode.parentNode
                else:
                    if newNode == newNode.parentNode.left:
                        newNode = newNode.parentNode
                        self.rightRotation(newNode)
                    newNode.parentNode.redBlack = 1
                    newNode.parentNode.parentNode.redBlack = 0
                    self.leftRotation(newNode.parentNode.parentNode)
            else:
                uncleNode = newNode.parentNode.parentNode.right  # Nodo tio

                if uncleNode.redBlack == 0:
                    uncleNode.redBlack = 1
                    newNode.parentNode.redBlack = 1
                    newNode.parentNode.parentNode.redBlack = 0
                    newNode = newNode.parentNode.parentNode
                else:
                    if newNode == newNode.parentNode.right:
                        newNode = newNode.parentNode
                        self.leftRotation(newNode)
                    newNode.parentNode.redBlack = 1
                    newNode.parentNode.parentNode.redBlack = 0
                    self.rightRotation(newNode.parentNode.parentNode)
        self.root.redBlack = 1
# Para el Remove debemos crear funciones para asignarle un nuevo hijo
    def newSon(self, Nodo, newNode):
        if Nodo.parentNode == None:
            self.root = newNode
        elif Nodo == Nodo.parentNode.left:
            Nodo.parentNode.left = newNode
        else:
            Nodo.parentNode.right = newNode
        newNode.parentNode = Nodo.parentNode
# Ahora creamos el Remove
    def Remove(self, valor):
        nodoD = self.Find(valor)
        temp = nodoD
        tempColor = temp.redBlack
        if nodoD.left == self.Null:
            sonNode = nodoD.right
            self.newSon(nodoD, nodoD.right)
        elif nodoD.right == self.Null:
            sonNode = nodoD.left
            self.newSon(nodoD, nodoD.left)
        else:
            temp = self.lowest(nodoD.right)
            tempColor = temp.redBlack
            sonNode = temp.right
            if temp.parentNode == sonNode:
                sonNode.parentNode = temp
            else:
                self.newSon(temp, temp.right)
                temp.right = sonNode.right
                temp.right.parentNode = temp
            self.newSon(nodoD, temp)
            temp.left = nodoD.left
            temp.left.parentNode = temp
            temp.redBlack = sonNode.redBlack
        if tempColor == 1:
            self.removeFixed(sonNode)

    #Ahora balanceamos el arbol luego de remover el nodo
    def removeFixed(self, sonNode):
        while sonNode != self.root and sonNode.redBlack == 0:
            if sonNode == sonNode.parentNode.left:
                temp = sonNode.parentNode.right
                if temp.redBlack == 0:
                    temp.redBlack = 1
                    sonNode.parentNode.redBlack = 0
                    self.leftRotation(sonNode.parentNode)
                    temp = sonNode.parentNode.right
                if temp.left.redBlack == 1 and temp.right.redBlack == 1:
                    temp.redBlack = 0
                    sonNode = sonNode.parentNode
                else:
                    if temp.right.redBlack == 1:
                        temp.left.redBlack = 1
                        temp.redBlack = 0
                        self.rightRotation(temp)
                        temp = sonNode.parentNode.right
                    temp.redBlack = sonNode.parentNode.redBlack
                    sonNode.parentNode.redBlack = 1
                    temp.right.redBlack = 1
                    self.leftRotation(sonNode.parentNode)
                    sonNode = self.root

            else:
                temp = sonNode.parentNode.left
                if temp.redBlack == 0:
                    temp.redBlack = 1
                    sonNode.parentNode.redBlack = 0
                    self.rightRotation(sonNode.parentNode)
                    temp = sonNode.parentNode.left
                if temp.right.redBlack == 1 and temp.right.redBlack == 1:
                    temp.redBlack  = 0
                    sonNode = sonNode.parentNode
                else:
                    if temp.left.redBlack == 1:
                        temp.right.redBlack = 1
                        temp.redBlack = 0
                        self.leftRotation(temp)
                        temp = sonNode.parentNode.left
                    
                    temp.redBlack = sonNode.parentNode.redBlack
                    sonNode.parentNode.redBlack = 1
                    temp.left.redBlack = 1
                    self.rightRotation(sonNode.parentNode)
                    sonNode = self.root
            sonNode.redBlack = 1

    #In onrder Tranversal que imprimira la estructura de nuestro arbol


    def inOrderTransversal(self, Nodo):
        if Nodo.valor != 0:
            self.inOrderTransversal(Nodo.left)
            sys.stdout.write(str(Nodo.valor) + " ")
            self.inOrderTransversal(Nodo.right)

    def inOrdor(self):
        self.inOrderTransversal(self.root)



    

def main():
     tree = RedBlackT()
     tree.Insert(2)
     tree.Insert(1)
     tree.Insert(5)
     tree.Insert(6)
     tree.Insert(3)
     tree.Insert(8)
     tree.Insert(7)
     tree.Insert(4)
     tree.Insert(9)
     tree.Find(2)
     tree.Find(4)
     print(tree.inOrdor())
     #print(tree.inOrderTransversal(5))
     print(tree.Remove(6))
     print(tree.Remove(3))
     tree.rojoNegro(5)
     print(tree.inOrdor())
   
     #print(tree.inOrderTransversal(5))

main()