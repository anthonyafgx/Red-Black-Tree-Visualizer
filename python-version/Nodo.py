
class Nodo(): #Clase que representa cada nodo en el arbol
    def __init__(self, valor): # metodo especial iniciador por eso recibe __xxxx__
        self.redBlack = 0 # 0) Rojo. 1) Negro
        self.parentNode = None # Nodo padre
        self.valor = valor # Valor del nodo
        self.left = None # Hijo izquierdo
        self.right = None # Hijo derecho

        