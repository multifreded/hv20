(set-logic QF_UF)
(declare-sort U 0)
(declare-fun f () U)
(declare-fun g () U)
(declare-fun h () U)
(assert (and (= f g) (not (= f h))))
(check-sat)
(get-value (f g h true false))
