(set-logic QF_LIA)
(declare-fun x () Int)
(declare-fun y () Int)
(assert (>= x 0))
(assert (>= y 1))
(assert (>= (+ (* (- 7) x) (* (- 10) y)) (- 10)))
(check-sat)
(exit)
