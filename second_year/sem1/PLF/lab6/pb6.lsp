; inorder traversal of a type 1 tree, using a collector
; in_order(l1..ln, c1..ck) = 
;  = [], n == 0
;  = l1 U in_order(l3..ln, c1..ck), k == 0 and l2 == 0
;  = l1 U in_order(c1 U 0 U l3..ln, c3..ck), c2 == 1 and l2 == 0
;  = l1 U c1 U in_order(l3..ln, c3..ck), c2 == 2 and l2 == 0
;  = in_order(l3..ln, l1 U l2 U c1..ck), otherwise

(defun in_order_traversal (l c)
    (cond
        ((null l) nil)
        ((= (cadr l) 0)
            (cons (car l)
                (cond
                    ((null c) (in_order_traversal(cddr l) c))
                    ((= (cadr c) 1) (in_order_traversal (cons (car c) (cons 0 (cddr l))) (cddr c)))
                    (T (cons (car c) (in_order_traversal (cddr l) (cddr c))))
                )
            )
        )
        (T (in_order_traversal (cddr l) (cons (car l) (cons (cadr l) c))))
    )
)

(print (in_order_traversal '(A 2 B 0 C 2 D 0 E 0) nil)) ;B A D C E
(print (in_order_traversal '(A 2 B 1 C 0 D 0) nil)) ;C B A D