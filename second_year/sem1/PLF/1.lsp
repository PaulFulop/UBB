; max on all levels

(defun my-max (a b)
  (if (> a b) a b))

(defun max-list (lst)
  (cond
    ((null lst) nil)
    ((null (cdr lst)) (car lst))
    (t (my-max (car lst)
               (max-list (cdr lst))))))

(defun max-numeric (tree)
  (cond
    ((numberp tree) tree)
    ((listp tree)
     (max-list
      (remove nil
              (mapcar #'max-numeric tree))))
    (t nil)))

; (print (max-numeric '(1 (2 (3 10) -5) (4 7))))
(print (append '(5 6 7) '(2 3 4)))

;; SAME WOULD BE FOR MIN, OR ANY FUNCTION THAT WOULD RETURN A NUMBER GIVEN A LIST BASICALLY.
;; if the prblem says modify this on all levels its a different story, ive done that already.
;; use mapcan if i need to remove from last result but alwasy return a list even if its an atom, or nil ig. todo look at that too