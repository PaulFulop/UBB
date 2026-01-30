; a)
; is_in_set(elem, l1..ln) = { False, n == 0 
;                           { True, l1 == elem
;                           { is_in_set(elem, l2..ln)
(defun is_in_set (elem s)
  (cond
    ((null s) nil)
    ((= elem (car s)) T)
    (T (is_in_set elem (cdr s)))
  )
)

; set_diff(l1..ln, s1..sm) = { [], n == 0
;                            { l1 U set_diff(l2..ln, s1..sm), is_in_set(l1, s1..sm) == False
;                            { set_diff(l2..ln, s1..sm), otherwise
(defun set_diff (s1 s2)
  (cond
    ((null s1) nil)
    ((eq nil (is_in_set (car s1) s2)) (cons (car s1) (set_diff (cdr s1) s2)))
    (T (set_diff (cdr s1) s2))
  )
)

(print (set_diff '(1 2 3 4 5 6)  '(9 1 2 8 3 4 7 5)))

; b)
; concat(l1..ln, s1..sm) = { s1..sm, n == 0
;                             { l1 U concat(l2...ln, s1...sm), otherwise
(defun concat (l1 l2)
  (cond
    ((null l1) l2)
    (T (cons (car l1) (concat (cdr l1) l2)))
  )
)

; reverse_list(l1..ln) = { [], n == 0
;                        { concat(reverse_list(l2..ln), l1), is_atom(l1)
;                        { concat(reverse_list(l2..ln), list(reverse_list(l1))), otherwise
(defun reverse_list (l)
  (cond
    ((null l) nil)
    ((atom (car l)) (concat (reverse_list (cdr l)) (list (car l))))
    (T (concat (reverse_list (cdr l)) (list (reverse_list (car l)))))
  )
)

(print (reverse_list '(4 5 6 (1 (2 3)) 7 ((4 3) 2)) ))

; c)
; nr_elem(l1..ln, cnt) = { cnt, n == 0
;                        { nr_elem(l2..ln, cnt + 1), otherwise
(defun nr_elem (l cnt)
  (cond
    ((null l) cnt)
    (T (nr_elem (cdr l) (+ cnt 1)))
  )
)

; first_elements(l1..ln, r1..rm) = { r1..rm, n == 0
;                               { first_elements(l2..ln, l1 U r1..rm), l1 - first element of a list 
;                                                                   and nr_elem(l1..ln) % 2 == 1
;                               { first_elements(l2..ln, concat(r1..rm, first_elements(l1, []))), is_list(l1)
;                               { first_elements(l2...ln, r1..rm), otherwise
(defun first_elements (l found ls)
  (cond
    ((null l) ls)
    ((and (eq nil found) (= 1 (mod (nr_elem l 0) 2))) 
      (first_elements (cdr l) T (cons (car l) ls))
    )
    ((listp (car l)) (first_elements(cdr l) T (concat ls (first_elements (car l) nil nil))))
    (T (first_elements (cdr l) T ls))
  )
)

(print (first_elements '(1 2 (3 (4 5 6) (6 7)) 8 (9 10 11)) nil nil))

; d)
; sum_atoms(l1..ln, sum) = { sum, n == 0
;                         { sum_atoms(l2..ln, sum + l1), is_atom(l1)
;                         { sum_atoms(l2..ln, sum), otherwise
(defun sum_atoms (ls sum)
  (cond
    ((null ls) sum)
    ((atom (car ls)) (sum_atoms (cdr ls) (+ sum (car ls))))
    (T (sum_atoms (cdr ls) sum))
  )
)

(print (sum_atoms '(1 2 (4 2 (3)) 3 (5 6) 4) 0))