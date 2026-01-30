; Write a function to determine the depth of a list.

; my_max(a, b) = 
;     = a, if a > b
;     = b, otherwise
(defun my_max (a b)
    (cond
        ((< b a) a)
        (T b)
    )
)

;(print (my_max 2 3))


; depth(max_depth, l1...ln) = 
;     = max_depth + 1, if n = 0
;     = depth(max(max_depth, depth(0, l1)), l2...ln), if l1 is a list
;     = depth(max_depth, l2...ln), otherwise
(defun depth (max_depth l)
    (cond
        ((null l) (+ max_depth 1))
        ((listp (car l)) (depth (my_max max_depth (depth 0 (car l))) (cdr l)))
        (T (depth max_depth (cdr l)))    
    )
)

(print (depth 0 '(5 (1 2 (8 3 (4))) 20)))