; increment(l1...ln, carry) =
;   1, if n = 0 and carry = 1
;   null, if n = 0 and carry = 0
;   ((l1 + carry) % 10) U increment(l2...ln, carry)

(defun increment (digits carry)
  (cond
    ((null digits)
     (if (= carry 1) '(1) nil))

    (t
     (cons
      (mod (+ (car digits) carry) 10)
      (increment
       (cdr digits)
       (if (>= (+ (car digits) carry) 10) 1 0))))))

; reverse_list(l1...ln) =
;   nil, n = 0
;      reverse_list(l2...ln) U l1
(defun reverse_list (l)
  (cond 
    ((null l) nil)
    (t (append (reverse_list (cdr l)) (list (car l))))))

; increment_number (l1...ln)
;   reverse_list(increment(reverse_list(l1..ln), 1))
(defun increment_number (digits)
  (reverse_list
   (increment (reverse_list digits) 1))   
)

(print (increment_number '(1 9 3 5 9 9)))
(print (increment_number '(1 2 3)))
(print (increment_number '(9 9)))
(print (increment_number '(2 1 9)))