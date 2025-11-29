class Nod:
    def __init__(self, e):
        self.e = e
        self.urm = None
    
class Lista:
    def __init__(self):
        self.prim = None
        

'''
crearea unei liste din valori citite pana la 0
'''
def creareLista():
    lista = Lista()
    lista.prim = creareLista_rec()
    return lista

def creareLista_rec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        nod = Nod(x)
        nod.urm = creareLista_rec()
        return nod
    
'''
tiparirea elementelor unei liste
'''
def tipar(lista):
    tipar_rec(lista.prim)
    
def tipar_rec(nod):
    if nod != None:
        print (nod.e)
        tipar_rec(nod.urm)
        

'''
program pentru test

7. a. Test the equality of two lists.
b. Determine the intersection of two sets represented as lists.

a -> f(l1 l2...ln, j1 j2...jm):
           false, (n == 0 and m != 0) or (m == 0 and n != 0)
           true, n = 0
           false, is_member(l1, j1 j2...jm) = false
           f(l2 l3...ln, remove_member(l1, j1 j2...jm)), otherwise


b -> g(l1 l2...ln, j1 j2...jm):
    [], n = 0
    l1 U g(l2...ln, j1 j2...jm), is_member(l1, j1 j2...jm) = true
    g(l2, l3...ln, j1 j2...jm), otherwise

    
helper -> is_member(x, j1 j2...jm):
        false, m = 0
        true, x = j1
        is_member(x, j2 j3...jm), otherwise

helper -> remove_member(x, j1 j2...jm):
        [], m = 0
        [j2 j3...jm], x = j1
        j1 U remove_member(x, j2 j3...jm), otherwise
'''

def f(h1:Nod, h2:Nod):
    if (h1 == None and h2 != None) or (h1 != None and h2 == None):
        return False
    
    if (h1 == None): return True
    if not is_member(h1.e, h2): return False

    x = h1.e
    return f(h1.urm, remove_member(x, h2))


def g(h1, h2):
    if h1 is None:
        return None

    if is_member(h1.e, h2):
        nod = Nod(h1.e)
        nod.urm = g(h1.urm, h2)
        return nod
    else:
        return g(h1.urm, h2)
    

def is_member(x, h:Nod):
    if h == None: return False
    if x == h.e: return True
    return is_member(x, h.urm)

def remove_member(x, h: Nod):
    if h is None:
        return None
    
    if h.e == x:
        return h.urm

    h.urm = remove_member(x, h.urm)
    return h

        
def main():
    list1 = creareLista()
    print("Reading the second list...\n")

    list2 = creareLista()
    # print(f(list1.prim, list2.prim))

    gnod = g(list1.prim, list2.prim)

    while gnod != None:
        print(gnod.e)
        gnod = gnod.urm
    
main() 