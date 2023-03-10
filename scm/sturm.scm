
(define-record-type <quadric>
  (make-quadric name a00 a01 a02 a03 a11 a12 a13 a22 a23 a33)
  quadric?
  (name    quadric-name)
  (a00     quadric-a00   set-quadric-a00!)
  (a01     quadric-a01   set-quadric-a01!)
  (a02     quadric-a02   set-quadric-a02!)

  (a03     quadric-a03   set-quadric-a03!)
  (a11     quadric-a11   set-quadric-a11!)
  (a12     quadric-a12   set-quadric-a12!)

  (a13     quadric-a13   set-quadric-a13!)
  (a22     quadric-a22   set-quadric-a22!)
  (a23     quadric-a23   set-quadric-a23!)
  (a33     quadric-a33   set-quadric-a33!)
)


; (rationalize (inexact->exact .3) 1/10)
(define (sturm polyA polyB)
  (define a1  (quadric-a00 polyA))
  (define a2  (quadric-a01 polyA))
  (define a3  (quadric-a02 polyA))
  (define a4  (quadric-a03 polyA))
  (define a5  (quadric-a11 polyA))
  (define a6  (quadric-a12 polyA))
  (define a7  (quadric-a13 polyA))
  (define a8  (quadric-a22 polyA))
  (define a9  (quadric-a23 polyA))
  (define a10 (quadric-a33 polyA))
  (define b1  (quadric-a00 polyB))
  (define b2  (quadric-a01 polyB))
  (define b3  (quadric-a02 polyB))
  (define b4  (quadric-a03 polyB))
  (define b5  (quadric-a11 polyB))
  (define b6  (quadric-a12 polyB))
  (define b7  (quadric-a13 polyB))
  (define b8  (quadric-a22 polyB))
  (define b9  (quadric-a23 polyB))
  (define b10 (quadric-a33 polyB))
  (define C 
  (+
    (+ (* a3 a3 a7 a7) (- (* a1 a7 a7 a8)) (* a4 a4 (+ (* a6 a6) (- (* a5 a8)))))
    (- (* a10 (+ (* a3 a3 a5) (- (* 2/1 a2 a3 a6)) (* a1 a6 a6) (* a2 a2 a8)) (- (* a1 a5 a8))))
    (- (* 2/1 a2 a3 a7 a9))
    (* 2/1 a1 a6 a7 a9)
    (* a2 a2 a9 a9)
    (- (* a1 a5 a9 a9)) 
    (- (* 2/1 a4 (+ (* a3 a6 a7) (- (* a2 a7 a8)) (- (* a3 a5 a9)) (* a2 a6 a9))))
    )
  )
    (define D 
    (+
(- (* a5 a9 a9 b1))
(- (* a3 a3 a5 b10))
(* 2/1 a2 a3 a6 b10)
(- (* a1 a6 a6 b10))
(- (* a2 a2 a8 b10))
(* a1 a5 a8 b10)
(- (* 2/1 a4 a6 a9 b2))
(* 2/1 a2 a9 a9 b2)
(* 2/1 a4 a5 a9 b3)
(* 2/1 a4 a6 a6 b4)
(- (* 2/1 a4 a5 a8 b4))
(* 2/1 a3 a5 a9 b4)
(- (* 2/1 a2 a6 a9 b4))
(- (* a4 a4 a8 b5))
(* 2/1 a3 a4 a9 b5)
(- (* a1 a9 a9 b5))
(- (* 2/1 a4 a4 a6 b6))
(- (* 2/1 a2 a4 a9 b6))
(- (* 2 a3 a4 a6 b7))
(* 2/1 a2 a4 a8 b7)
(- (* 2/1 a2 a3 a9 b7))
(* 2/1 a1 a6 a9 b7)
(- (* a4 a4 a5 b8))
(- (* a7 a7 (+ (* a8 b1) (- (* 2/1 a3 b3)) (* a1 b8))))
(* a10 (+ (- (* a6 a6 b1)) (* a5 a8 b1) (- (* 2/1 a2 a8 b2)) (- (* 2/1 a3 a5 b3)) (- (* a3 a3 b5)) (* a1 a8 b5) (* 2/1 a2 a3 b6) (* 2/1 a6 (+ (* a3 b2) (* a2 b3) (- (* a1 b6))) (- (* a2 a2 b8))) (* a1 a5 b8)))
(* 2/1 a3 a4 a5 b9)
(- (* 2/1 a2 a4 a6 b9))
(* 2/1 a2 a2 a9 b9)
(- (* 2/1 a1 a5 a9 b9))
(* 2/1 a7 (+ (* a4 a8 b2) (- (* a3 a9 b2) (- (* a2 a9 b3)) (* a2 a8 b4) (- (* a3 a4 b6)) (* a1 a9 b6) (* a3 a3 b7) (- (* a1 a8 b7)) (* a2 a4 b8) (- (* a2 a3 b9)) (* a6 (+ (* a9 b1) (- (* a4 b3)) (- (* a3 b4)) (* a1 b9))))))
    )
  )
  (define E
  
  (+
(- (* 2/1 a2 a8 b10 b2)) (- (* a10 a8 b2 b2)) (* a9 a9 b2 b2)
(- (* 2/1 a7 a9 b2 b3)) (* a7 a7 b3 b3) (* 2/1 a7 a8 b2 b4)

(* a6 a6 (+ (- (* b1 b10)) (* b4 b4))) (* a10 a8 b1 b5)(- (* a9 a9 b1 b5))

(- (* a3 a3 b10 b5)) (* a1 a8 b10 b5) (- (* 2/1 a10 a3 b3 b5))
(* 2/1 a4 a9 b3 b5) (- 2/1 a4 a8 b4 b5) (* 2/1 a3 a9 b4 b5)
(* 2/1 a7 a9 b1 b6) (* 2/1 a2 a3 b10 b6) (* 2/1 a10 a3 b2 b6)
(- (* 2/1 a4 a9 b2 b6)) (* 2/1 a10 a2 b3 b6) (- (* 2/1 a4 a7 b3 b6))
(- (* 2/1 a3 a7 b4 b6)) (- (* 2/1 a2 a9 b4 b6)) (- (* a1 a10 b6 b6))
(* a4 a4 b6 b6) (- (* 2/1 a7 a8 b1 b7)) (* 2/1 a4 a8 b2 b7)
(- (* 2/1 a3 a9 b2 b7)) (* 4/1 a3 a7 b3 b7) (- (* 2/1 a2 a9 b3 b7))
(* 2/1 a2 a8 b4 b7) (- (* 2/1  a3 a4 b6 b7)) (* 2/1 a1 a9 b6 b7)
(* a3 a3 b7 b7) (- (* a1 a8 b7 b7)) (- (* a7 a7 b1 b8)) (- (* a2 a2 b10 b8)) (- (* 2/1 a10 a2 b2 b8))
(* 2/1 a4 a7 b2 b8) (* 2/1 a2 a7 b4 b8) (* a1 a10 b5 b8)
(- (* a4 a4 b5 b8)) (* 2/1 a2 a4 b7 b8) (- (* 2/1 a1 a7 b7 b8))

(- (* 2/1 a3 a7 b2 b9)) (* 4/1 a2 a9 b2 b9) (- (* 2/1 a2 a7 b3 b9))
(* 2/1 a3 a4 b5 b9) (- (* 2/1 a1 a9 b5 b9))(- (* 2/1 a2 a4 b6 b9))
(+ 2/1 a1 a7 b6 b9) (- (* 2/1 a2 a3 b7 b9)) (* a2 a2 b9 b9)
(+ (* 2/1 a6 (+ (* a3 b10 b2) (* a2 b10 b3) (* a10 b2 b3) (- (* a9 b2 b4))

 (- (* a7 b3 b4)) (- (* a10 b1 b6)) (- (* a1 b10 b6)) (* 2/1 (* a4 b4 b6)) (* a9 b1 b7)
 (- (* a4 b3 b7)) (- (* a3 b4 b7)) (* a7 b1 b9) (- (* a4 b2 b9)) (- (* a2 b4 b9))
 (* a1 b7 b9))) (* a5 (+ (* a8 b1 b10) (- (* 2/1 a3 b10 b3)) (- (* a10 b3 b3))
 (* 2/1 a9 b3 b4) (- (* a8 b4 b4)) (* a10 b1 b8) (* a1 b10 b8)
 (- (* 2/1 a4 b4 b8)) (- (* 2/1 a9 b1 b9)) (* 2/1 a4 b3 b9) (* 2/1 a3 b4 b9) (- (* a1 b9 b9)))))
)
  )
  (define F
(+ 
(- (* a5 b10 b3 b3)) (- (* 2 a3 b10 b3 b5)) (- (* a10 b3 b3 b5))
(* 2 a9 b3 b4 b5) (* 2 a3 b10 b2 b6) (* 2 a2 b10 b3 b6)
(* 2 a10 b2 b3 b6) (- (* 2 a9 b2 b4 b6)) (- (* 2 a7 b3 b4 b6))
(- (* a10 b1 b6 b6)) (- (* a1 b10 b6 b6)) (* 2 a4 b4 b6 b6) (- (* 2 a9 b2 b3 b7))
(* 2 a7 b3 b3 b7) (* 2 a9 b1 b6 b7) (- (* 2 a4 b3 b6 b7))
(- (* 2 a3 b4 b6 b7)) (* 2 a3 b3 b7 b7) (- (* a8 (+ (* b4 b4 b5) (* b10 (+ (* b2 b2) (- (* b1 b5)))
(- (* 2 b2 b4 b7)) (* b1 b7 b7))))) (* a5 b1 b10 b8) (- (* 2 a2 b10 b2 b8)) (- (* a10 b2 b2 b8))
(* 2 a7 b2 b4 b8) (- (* a5 b4 b4 b8)) (* a10 b1 b5 b8) (* a1 b10 b5 b8) (- (* 2 a4 b4 b5 b8))
(- (* 2 a7 b1 b7 b8)) (* 2 a4 b2 b7 b8) (* 2 a2 b4 b7 b8) (- (* a1 b7 b7 b8))
(* 2 a9 b2 b2 b9) (- (* 2 a7 b2 b3 b9)) (* 2 a5 b3 b4 b9) (- (* 2 a9 b1 b5 b9))
(* 2/1 a4 b3 b5 b9) (* 2/1 a3 b4 b5 b9) (* 2/1 a7 b1 b6 b9) (- (* 2/1 a4 b2 b6 b9))
(- (* 2/1 a2 b4 b6 b9)) (- (* 2/1 a3 b2 b7 b9)) (- (* 2/1 a2 b3 b7 b9)) (* 2/1 a1 b6 b7 b9)
(- (* a5 b1 b9 b9)) (* 2/1 a2 b2 b9 b9) (- (* a1 b5 b9 b9)) (* 2/1 a6 (+ (* b10 b2 b3) (- (* b1 b10 b6)) (* b4 b4 b6) (- (* b3 b4 b7)) (- (* b2 b4 b9)) (* b1 b7 b9)))
)
  )
  
  (define G
  
  (+ 
(* b3 b3 b7 b7) (- (* b1 b7 b7 b8)) (* b4 b4 (+ (* b6 b6) (- (* b5 b8)))) (- (* b10 (+ (* b3 b3 b5) (- (* 2 b2 b3 b6)) (* b1 b6 b6) (* b2 b2 b8) (- (* b1 b5 b8)))))
(- (* 2 b2 b3 b7 b9)) (* 2 b1 b6 b7 b9) (* b2 b2 b9 b9) (- (* b1 b5 b9 b9)) (- (* 2 b4 (+ (* b3 b6 b7) (- (* b2 b7 b8)) (- (* b3 b5 b9)) (* b2 b6 b9))))
)
  
  )
  
  (cons C (cons D (cons E (cons F (cons G '())))))
)


(define (sturm2 polyA polyB)
(let* (
  (a1  (quadric-a00 polyA))
  (a2  (quadric-a01 polyA))
  (a3  (quadric-a02 polyA))
  (a4  (quadric-a03 polyA))
  (a5  (quadric-a11 polyA))
  (a6  (quadric-a12 polyA))
  (a7  (quadric-a13 polyA))
  (a8  (quadric-a22 polyA))
  (a9  (quadric-a23 polyA))
  (a10 (quadric-a33 polyA))
  (b1  (quadric-a00 polyB))
  (b2  (quadric-a01 polyB))
  (b3  (quadric-a02 polyB))
  (b4  (quadric-a03 polyB))
  (b5  (quadric-a11 polyB))
  (b6  (quadric-a12 polyB))
  (b7  (quadric-a13 polyB))
  (b8  (quadric-a22 polyB))
  (b9  (quadric-a23 polyB))
  (b10 (quadric-a33 polyB))
  (C 
  (+
    (+ (* a3 a3 a7 a7) (- (* a1 a7 a7 a8)) (* a4 a4 (+ (* a6 a6) (- (* a5 a8)))))
    (- (* a10 (+ (* a3 a3 a5) (- (* 2 a2 a3 a6)) (* a1 a6 a6) (* a2 a2 a8) (- (* a1 a5 a8)))))
    (- (* 2 a2 a3 a7 a9))
    (* 2 a1 a6 a7 a9)
    (* a2 a2 a9 a9)
    (- (* a1 a5 a9 a9)) 
    (- (* 2 a4 (+ (* a3 a6 a7) (- (* a2 a7 a8)) (- (* a3 a5 a9)) (* a2 a6 a9))))
    )
  )
  (D 
    (+
(- (* a5 a9 a9 b1))
(- (* a3 a3 a5 b10))
(* 2 a2 a3 a6 b10)
(- (* a1 a6 a6 b10))
(- (* a2 a2 a8 b10))
(* a1 a5 a8 b10)
(- (* 2 a4 a6 a9 b2))
(* 2 a2 a9 a9 b2)
(* 2 a4 a5 a9 b3)
(* 2 a4 a6 a6 b4)
(- (* 2 a4 a5 a8 b4))
(* 2 a3 a5 a9 b4)
(- (* 2 a2 a6 a9 b4))
(- (* a4 a4 a8 b5))
(* 2 a3 a4 a9 b5)
(- (* a1 a9 a9 b5))
(+ (* 2 a4 a4 a6 b6))
(- (* 2 a2 a4 a9 b6))
(- (* 2 a3 a4 a6 b7))
(* 2 a2 a4 a8 b7)
(- (* 2 a2 a3 a9 b7))
(* 2 a1 a6 a9 b7)
(- (* a4 a4 a5 b8))
(- (* a7 a7 (+ (* a8 b1) (- (* 2 a3 b3)) (* a1 b8))))
(* a10 (+ (- (* a6 a6 b1)) (* a5 a8 b1) (- (* 2 a2 a8 b2)) (- (* 2 a3 a5 b3)) (- (* a3 a3 b5)) (* a1 a8 b5) (* 2 a2 a3 b6) (* 2 a6 (+ (* a3 b2) (* a2 b3) (- (* a1 b6)))) (- (* a2 a2 b8)) (* a1 a5 b8)))
(* 2 a3 a4 a5 b9)
(- (* 2 a2 a4 a6 b9))
(* 2 a2 a2 a9 b9)
(- (* 2 a1 a5 a9 b9))
(* 2 a7 (+ (* a4 a8 b2) (- (* a3 a9 b2)) (- (* a2 a9 b3)) (* a2 a8 b4) (- (* a3 a4 b6)) (* a1 a9 b6) (* a3 a3 b7) (- (* a1 a8 b7)) (* a2 a4 b8) (- (* a2 a3 b9)) (* a6 (+ (* a9 b1) (- (* a4 b3)) (- (* a3 b4)) (* a1 b9)))))
    )
  )
  (E 
  (+
(- (* 2/1 a2 a8 b10 b2)) (- (* a10 a8 b2 b2)) (* a9 a9 b2 b2)
(- (* 2/1 a7 a9 b2 b3)) (* a7 a7 b3 b3) (* 2/1 a7 a8 b2 b4)
(* a6 a6 (+ (- (* b1 b10)) (* b4 b4))) (* a10 a8 b1 b5) (- (* a9 a9 b1 b5))

(- (* a3 a3 b10 b5)) (* a1 a8 b10 b5) (- (* 2 a10 a3 b3 b5))
(* 2 a4 a9 b3 b5) (- (* 2 a4 a8 b4 b5)) (* 2 a3 a9 b4 b5)
(* 2 a7 a9 b1 b6) (* 2 a2 a3 b10 b6) (* 2 a10 a3 b2 b6)
(- (* 2/1 a4 a9 b2 b6)) (* 2/1 a10 a2 b3 b6) (- (* 2/1 a4 a7 b3 b6))
(- (* 2/1 a3 a7 b4 b6)) (- (* 2/1 a2 a9 b4 b6)) (- (* a1 a10 b6 b6))
(* a4 a4 b6 b6) (- (* 2/1 a7 a8 b1 b7)) (* 2/1 a4 a8 b2 b7)
(- (* 2/1 a3 a9 b2 b7)) (* 4/1 a3 a7 b3 b7) (- (* 2/1 a2 a9 b3 b7))
(* 2/1 a2 a8 b4 b7) (- (* 2/1  a3 a4 b6 b7)) (* 2/1 a1 a9 b6 b7)
(* a3 a3 b7 b7) (- (* a1 a8 b7 b7)) (- (* a7 a7 b1 b8)) (- (* a2 a2 b10 b8)) (- (* 2/1 a10 a2 b2 b8))
(* 2/1 a4 a7 b2 b8) (* 2/1 a2 a7 b4 b8) (* a1 a10 b5 b8)
(- (* a4 a4 b5 b8)) (* 2/1 a2 a4 b7 b8) (- (* 2/1 a1 a7 b7 b8))

(- (* 2 a3 a7 b2 b9)) (* 4 a2 a9 b2 b9) (- (* 2 a2 a7 b3 b9))
(* 2 a3 a4 b5 b9) (- (* 2 a1 a9 b5 b9))(- (* 2/1 a2 a4 b6 b9))
(* 2 a1 a7 b6 b9) (- (* 2 a2 a3 b7 b9)) (* a2 a2 b9 b9)

(+ (* 2 a6 (+ (* a3 b10 b2) (* a2 b10 b3) (* a10 b2 b3) (- (* a9 b2 b4))

(- (* a7 b3 b4)) (- (* a10 b1 b6)) (- (* a1 b10 b6)) (* 2 (* a4 b4 b6)) (* a9 b1 b7)
(- (* a4 b3 b7)) (- (* a3 b4 b7)) (* a7 b1 b9) (- (* a4 b2 b9)) (- (* a2 b4 b9))
(* a1 b7 b9))) (* a5 (+ (* a8 b1 b10) (- (* 2/1 a3 b10 b3)) (- (* a10 b3 b3))
(* 2/1 a9 b3 b4) (- (* a8 b4 b4)) (* a10 b1 b8) (* a1 b10 b8)
(- (* 2/1 a4 b4 b8)) (- (* 2/1 a9 b1 b9)) (* 2/1 a4 b3 b9) (* 2/1 a3 b4 b9) (- (* a1 b9 b9)))))
)
  )
  (F
(+ 
(- (* a5 b10 b3 b3)) (- (* 2 a3 b10 b3 b5)) (- (* a10 b3 b3 b5))
(* 2 a9 b3 b4 b5) (* 2 a3 b10 b2 b6) (* 2 a2 b10 b3 b6)
(* 2 a10 b2 b3 b6) (- (* 2 a9 b2 b4 b6)) (- (* 2 a7 b3 b4 b6))
(- (* a10 b1 b6 b6)) (- (* a1 b10 b6 b6)) (* 2 a4 b4 b6 b6) (- (* 2 a9 b2 b3 b7))
(* 2 a7 b3 b3 b7) (* 2 a9 b1 b6 b7) (- (* 2 a4 b3 b6 b7))
(- (* 2 a3 b4 b6 b7)) (* 2 a3 b3 b7 b7) (- (* a8 (+ (* b4 b4 b5) (* b10 (+ (* b2 b2) (- (* b1 b5))))
(- (* 2 b2 b4 b7)) (* b1 b7 b7)))) (* a5 b1 b10 b8) (- (* 2 a2 b10 b2 b8)) (- (* a10 b2 b2 b8))
(* 2 a7 b2 b4 b8) (- (* a5 b4 b4 b8)) (* a10 b1 b5 b8) (* a1 b10 b5 b8) (- (* 2 a4 b4 b5 b8))
(- (* 2 a7 b1 b7 b8)) (* 2 a4 b2 b7 b8) (* 2 a2 b4 b7 b8) (- (* a1 b7 b7 b8))
(* 2 a9 b2 b2 b9) (- (* 2 a7 b2 b3 b9)) (* 2 a5 b3 b4 b9) (- (* 2 a9 b1 b5 b9))
(* 2/1 a4 b3 b5 b9) (* 2/1 a3 b4 b5 b9) (* 2/1 a7 b1 b6 b9) (- (* 2/1 a4 b2 b6 b9))
(- (* 2/1 a2 b4 b6 b9)) (- (* 2/1 a3 b2 b7 b9)) (- (* 2/1 a2 b3 b7 b9)) (* 2/1 a1 b6 b7 b9)
(- (* a5 b1 b9 b9)) (* 2/1 a2 b2 b9 b9) (- (* a1 b5 b9 b9)) (* 2/1 a6 (+ (* b10 b2 b3) (- (* b1 b10 b6)) (* b4 b4 b6) (- (* b3 b4 b7)) (- (* b2 b4 b9)) (* b1 b7 b9)))
)
  )
  (G
  (+ 
(* b3 b3 b7 b7) (- (* b1 b7 b7 b8)) (* b4 b4 (+ (* b6 b6) (- (* b5 b8)))) (- (* b10 (+ (* b3 b3 b5) (- (* 2 b2 b3 b6)) (* b1 b6 b6) (* b2 b2 b8) (- (* b1 b5 b8)))))
(- (* 2 b2 b3 b7 b9)) (* 2 b1 b6 b7 b9) (* b2 b2 b9 b9) (- (* b1 b5 b9 b9)) (- (* 2 b4 (+ (* b3 b6 b7) (- (* b2 b7 b8)) (- (* b3 b5 b9)) (* b2 b6 b9))))
)
  )
)
  
  (cons C (cons D (cons E (cons F (cons G '())))))
)
)


(define polyA 
          (make-quadric "PolyA" 1 2 3 4 5 6 7 8 9 10))

(define polyB          
          (make-quadric "PolyB" 11 12 13 14 15 16 17 18 19 110)
          )

(sturm polyA polyB)

(sturm2 polyA polyB)





(define (add-three number)
  (+ number 3))

(define (add-gghree number)
  (define a1 (+ number 3))
  (+ 4 a1)
)


; a3*a3*a7*a7-a1*a7*a7*a8+a4*a4*(a6*a6-a5*a8)
-a10*(a3*a3*a5-Rat(2)*a2*a3*a6+a1*a6*a6+a2*a2*a8-a1*a5*a8)
-Rat(2)*a2*a3*a7*a9
+Rat(2)*a1*a6*a7*a9
+a2*a2*a9*a9
-a1*a5*a9*a9
-Rat(2)*a4*(a3*a6*a7-a2*a7*a8-a3*a5*a9+a2*a6*a9)

(+
(+ (* a3 a3 a7 a7) (- (* a1 a7 a7 a8)) (* a4 a4 (+ (* a6 a6) (- (* a5 a8)))))
(- (* a10 (+ (* a3 a3 a5) (- (* 2/1 a2 a3 a6)) (* a1 a6 a6) +(* a2 a2 a8)) (- (* a1 a5 a8))))
(- (* 2/1 a2 a3 a7 a9))
(* 2/1 a1 a6 a7 a9)
(* a2 a2 a9 a9)
(- (* a1 a5 a9 a9)) 
(- (* 2/1 a4 (+ (* a3 a6 a7) (- (* a2 a7 a8)) (- (* a3 a5 a9)) (* a2 a6 a9)))))





-a5*a9*a9*b1
-a3*a3*a5*b10
+Rat(2)*a2*a3*a6*b10
-a1*a6*a6*b10
-a2*a2*a8*b10
+a1*a5*a8*b10
-Rat(2)*a4*a6*a9*b2
+Rat(2)*a2*a9*a9*b2
+Rat(2)*a4*a5*a9*b3
+Rat(2)*a4*a6*a6*b4
-Rat(2)*a4*a5*a8*b4
+Rat(2)*a3*a5*a9*b4
-Rat(2)*a2*a6*a9*b4
-a4*a4*a8*b5
+Rat(2)*a3*a4*a9*b5
-a1*a9*a9*b5
+Rat(2)*a4*a4*a6*b6
-Rat(2)*a2*a4*a9*b6
-Rat(2)*a3*a4*a6*b7
+Rat(2)*a2*a4*a8*b7
-Rat(2)*a2*a3*a9*b7
+Rat(2)*a1*a6*a9*b7
-a4*a4*a5*b8
-a7*a7*(a8*b1-Rat(2)*a3*b3+a1*b8)
+a10*(-a6*a6*b1+a5*a8*b1-Rat(2)*a2*a8*b2-Rat(2)*a3*a5*b3-a3*a3*b5+a1*a8*b5+Rat(2)*a2*a3*b6+Rat(2)*a6*(a3*b2+a2*b3-a1*b6)-a2*a2*b8+a1*a5*b8)
+Rat(2)*a3*a4*a5*b9
-Rat(2)*a2*a4*a6*b9
+Rat(2)*a2*a2*a9*b9
-Rat(2)*a1*a5*a9*b9
+Rat(2)*a7*(a4*a8*b2-a3*a9*b2-a2*a9*b3+a2*a8*b4-a3*a4*b6+a1*a9*b6+a3*a3*b7-a1*a8*b7+a2*a4*b8-a2*a3*b9+a6*(a9*b1-a4*b3-a3*b4+a1*b9))

(+
(- (* a5 a9 a9 b1))
(- (* a3 a3 a5 b10))
(* 2/1 a2 a3 a6 b10)
(- (* a1 a6 a6 b10))
(- (* a2 a2 a8 b10))
(* a1 a5 a8 b10)
(- (* 2/1 a4 a6 a9 b2))
(* 2/1 a2 a9 a9 b2)
(* 2/1 a4 a5 a9 b3)
(* 2/1 a4 a6 a6 b4)
(- (* 2/1 a4 a5 a8 b4))
(* 2/1 a3 a5 a9 b4)
(- (* 2/1 a2 a6 a9 b4))
(- (* a4 a4 a8 b5))
(* 2/1 a3 a4 a9 b5)
(- (* a1 a9 a9 b5))
(- (* 2/1 a4 a4 a6 b6))
(- (* 2/1 a2 a4 a9 b6))
(- (* 2 a3 a4 a6 b7))
(* 2/1 a2 a4 a8 b7)
(- (* 2/1 a2 a3 a9 b7))
(* 2/1 a1 a6 a9 b7)
(- (* a4 a4 a5 b8))
(- (* a7 a7 (+ (* a8 b1) (- (* 2/1 a3 b3)) (* a1 b8))))
(* a10 (+ (- (* a6 a6 b1)) (* a5 a8 b1) (- (* 2/1 a2 a8 b2)) (- (* 2/1 a3 a5 b3)) (- (* a3 a3 b5)) (* a1 a8 b5) (* 2/1 a2 a3 b6) (* 2/1 a6 (+ (* a3 b2) (* a2 *b3) (- (* a1 b6))) (- (* a2 a2 b8))) (* a1 a5 b8)))
(* 2/1 a3 a4 a5 b9)
(- (* 2/1 a2 a4 a6 b9))
(* 2/1 a2 a2 a9 b9)
(- (* 2/1 a1 a5 a9 b9))
(* 2/1 a7 (+(* a4 a8 b2) (- (* a3 a9 b2) (- (* a2 a9 b3)) (* a2 a8 b4) (- (* a3 a4 b6)) (* a1 a9 b6) (* a3 a3 b7) (- (* a1 a8 b7)) (* a2 a4 b8) (-(* a2 a3 b9)) (* a6 (+(* a9 b1) (- (* a4 b3)) (-(* a3 b4)) (* a1 b9))))))
)






-Rat(2)*a2*a8*b10*b2-a10*a8*b2*b2+a9*a9*b2*b2
-Rat(2)*a7*a9*b2*b3+a7*a7*b3*b3+Rat(2)*a7*a8*b2*b4
+a6*a6*(-b1*b10+b4*b4)+a10*a8*b1*b5-a9*a9*b1*b5
-a3*a3*b10*b5+a1*a8*b10*b5-Rat(2)*a10*a3*b3*b5
+Rat(2)*a4*a9*b3*b5-Rat(2)*a4*a8*b4*b5+Rat(2)*a3*a9*b4*b5
+Rat(2)*a7*a9*b1*b6+Rat(2)*a2*a3*b10*b6+Rat(2)*a10*a3*b2*b6
-Rat(2)*a4*a9*b2*b6+Rat(2)*a10*a2*b3*b6-Rat(2)*a4*a7*b3*b6
-Rat(2)*a3*a7*b4*b6-Rat(2)*a2*a9*b4*b6-a1*a10*b6*b6
+a4*a4*b6*b6-Rat(2)*a7*a8*b1*b7+Rat(2)*a4*a8*b2*b7
-Rat(2)*a3*a9*b2*b7+Rat(4)*a3*a7*b3*b7-Rat(2)*a2*a9*b3*b7
+Rat(2)*a2*a8*b4*b7-Rat(2)*a3*a4*b6*b7+Rat(2)*a1*a9*b6*b7
+a3*a3*b7*b7-a1*a8*b7*b7-a7*a7*b1*b8-a2*a2*b10*b8-Rat(2)*a10*a2*b2*b8
+Rat(2)*a4*a7*b2*b8+Rat(2)*a2*a7*b4*b8+a1*a10*b5*b8
-a4*a4*b5*b8+Rat(2)*a2*a4*b7*b8-Rat(2)*a1*a7*b7*b8

-Rat(2)*a3*a7*b2*b9+Rat(4)*a2*a9*b2*b9-Rat(2)*a2*a7*b3*b9
+Rat(2)*a3*a4*b5*b9-Rat(2)*a1*a9*b5*b9-Rat(2)*a2*a4*b6*b9
+Rat(2)*a1*a7*b6*b9-Rat(2)*a2*a3*b7*b9+a2*a2*b9*b9
+Rat(2)*a6*(a3*b10*b2+a2*b10*b3+a10*b2*b3-a9*b2*b4

-a7*b3*b4-a10*b1*b6-a1*b10*b6+Rat(2)*a4*b4*b6+a9*b1*b7
-a4*b3*b7-a3*b4*b7+a7*b1*b9-a4*b2*b9-a2*b4*b9
+a1*b7*b9)+a5*(a8*b1*b10-Rat(2)*a3*b10*b3-a10*b3*b3
+Rat(2)*a9*b3*b4-a8*b4*b4+a10*b1*b8+a1*b10*b8
-Rat(2)*a4*b4*b8-Rat(2)*a9*b1*b9+Rat(2)*a4*b3*b9+Rat(2)*a3*b4*b9-a1*b9*b9)




(+
(- (* 2/1 a2 a8 b10 b2)) (- (* a10 a8 b2 b2)) (* a9 a9 b2 b2)
(- (* 2/1 a7 a9 b2 b3)) (* a7 a7 b3 b3) (* 2/1 a7 a8 b2 b4)
(* a6 a6 (+ (- (* b1 b10)) (* b4 b4))) (* a10 a8 b1 b5)(- (* a9 a9 b1 b5))
(- (* a3 a3 b10 b5))+(* a1 a8 b10 b5)+(- (* 2/1 a10 a3 b3 b5))
(* 2/1 a4 a9 b3 b5)+(- 2/1 a4 a8 b4 b5)+(* 2/1 a3 a9 b4 b5)
(* 2/1 a7 a9 b1 b6)+(* 2/1 a2 a3 b10 b6)+(* 2/1 a10 a3 b2 b6)
(- (* 2/1 a4 a9 b2 b6))+(* 2/1 a10 a2 b3 b6)+(- (* 2/1 a4 a7 b3 b6))
(- (* 2/1 a3 a7 b4 b6))+(- (* 2/1 a2 a9 b4 b6))+(- (* a1 a10 b6 b6))
(* a4 a4 b6 b6)+(- (* 2/1 a7 a8 b1 b7))+(* 2/1 a4 a8 b2 b7)
(- (* 2/1 a3 a9 b2 b7))+(* 4/1 a3 a7 b3 b7)+(- (* 2/1 a2 a9 b3 b7))
(* 2/1 a2 a8 b4 b7)+(- (* 2/1  a3 a4 b6 b7))+(* 2/1 a1 a9 b6 b7)
(* a3 a3 b7 b7)+(- (* a1 a8 b7 b7))+(- (* a7 a7 b1 b8))+(- (* a2 a2 b10 b8))+(- (* 2/1 a10 a2 b2 b8))
(* 2/1 a4 a7 b2 b8)+(* 2/1 a2 a7 b4 b8)+(* a1 a10 b5 b8)
(- (* a4 a4 b5 b8))+(* 2/1 a2 a4 b7 b8)+(- (* 2/1 a1 a7 b7 b8))

(- (* 2/1 a3 a7 b2 b9))+(* 4/1 a2 a9 b2 b9)+(- (* 2/1 a2 a7 b3 b9))
(* 2/1 a3 a4 b5 b9)+(- (* 2/1 a1 a9 b5 b9))+(- (* 2/1 a2 a4 b6 b9))
(+ 2/1 a1 a7 b6 b9)+(- (* 2/1 a2 a3 b7 b9))+(* a2 a2*b9*b9)
(+ (* 2/1 a6 (+ ( * a3 b10 b2) (* a2 b10 b3) (* a10 b2 b3) (- (* a9 b2 b4))

 (- (* a7 b3 b4)) (- (* a10 b1 b6)) (- (* a1 b10 b6)) (* 2/1 (* a4 b4 b6)) (* a9 b1 b7)
 (- (* a4 b3 b7)) (- (* a3 b4 b7)) (* a7 b1 b9) (- (* a4 b2 b9)) (- (* a2 b4 b9))
 (* a1 b7 b9))) (* a5 ((* a8 b1 b10) (- (* 2/1 a3 b10 b3)) (- (* a10 b3 b3))
 (* 2/1 a9 b3 b4) (- (* a8 b4 b4)) (* a10 b1 b8) (* a1 b10 b8)
 (- (* 2/1 a4 b4 b8)) (- (* 2/1 a9 b1 b9)) (* 2/1 a4 b3 b9) (* 2/1 a3 b4 b9) (-(* a1 b9 b9)))))
)

-a5*b10*b3*b3-Rat(2)*a3*b10*b3*b5-a10*b3*b3*b5
+Rat(2)*a9*b3*b4*b5+Rat(2)*a3*b10*b2*b6+Rat(2)*a2*b10*b3*b6
+Rat(2)*a10*b2*b3*b6-Rat(2)*a9*b2*b4*b6-Rat(2)*a7*b3*b4*b6
-a10*b1*b6*b6-a1*b10*b6*b6+Rat(2)*a4*b4*b6*b6-Rat(2)*a9*b2*b3*b7
+Rat(2)*a7*b3*b3*b7+Rat(2)*a9*b1*b6*b7-Rat(2)*a4*b3*b6*b7
-Rat(2)*a3*b4*b6*b7+Rat(2)*a3*b3*b7*b7-a8*(b4*b4*b5+b10*(b2*b2-b1*b5)
-Rat(2)*b2*b4*b7+b1*b7*b7)+a5*b1*b10*b8-Rat(2)*a2*b10*b2*b8-a10*b2*b2*b8
+Rat(2)*a7*b2*b4*b8-a5*b4*b4*b8+a10*b1*b5*b8+a1*b10*b5*b8-Rat(2)*a4*b4*b5*b8
-Rat(2)*a7*b1*b7*b8+Rat(2)*a4*b2*b7*b8+Rat(2)*a2*b4*b7*b8-a1*b7*b7*b8
+Rat(2)*a9*b2*b2*b9-Rat(2)*a7*b2*b3*b9+Rat(2)*a5*b3*b4*b9-Rat(2)*a9*b1*b5*b9
+Rat(2)*a4*b3*b5*b9+Rat(2)*a3*b4*b5*b9+Rat(2)*a7*b1*b6*b9-Rat(2)*a4*b2*b6*b9
-Rat(2)*a2*b4*b6*b9-Rat(2)*a3*b2*b7*b9-Rat(2)*a2*b3*b7*b9+Rat(2)*a1*b6*b7*b9
-a5*b1*b9*b9+Rat(2)*a2*b2*b9*b9-a1*b5*b9*b9+Rat(2)*a6*(b10*b2*b3-b1*b10*b6+b4*b4*b6-b3*b4*b7-b2*b4*b9+b1*b7*b9)


(+
(- (* a5 b10 b3 b3)) (- (* 2 a3 b10 b3 b5)) (- (* a10 b3 b3 b5))
(* 2 a9 b3 b4 b5) (* 2 a3 b10 b2 b6) (* 2 a2 b10 b3 b6)
(* 2 a10 b2 b3 b6) (- (* 2 a9 b2 b4 b6)) (- (* 2 a7 b3 b4 b6))
(- (* a10 b1 b6 b6)) (- (* a1 b10 b6 b6)) (* 2 a4 b4 b6 b6) (- (* 2 a9 b2 b3 b7))
(* 2 a7 b3 b3 b7) (* 2 a9 b1 b6 b7) (- (* 2 a4 b3 b6 b7))
(- (* 2 a3 b4 b6 b7)) (* 2 a3 b3 b7 b7) (- (* a8 (+ (* b4 b4 b5) (* b10 (+ (* b2 b2) (- (* b1 b5)))
(- (* 2 b2 b4 b7)) (* b1 b7 b7))))) (* a5 b1 b10 b8) (- (* 2 a2 b10 b2 b8)) (- (* a10 b2 b2 b8))
(* 2 a7 b2 b4 b8) (- (* a5 b4 b4 b8)) (* a10 b1 b5 b8) (* a1 b10 b5 b8) (- (* 2 a4 b4 b5 b8))
(- (* 2 a7 b1 b7 b8)) (* 2 a4 b2 b7 b8) (* 2 a2 b4 b7 b8) (- (* a1 b7 b7 b8))
(* 2 a9 b2 b2 b9) (- (* 2 a7 b2 b3 b9)) (* 2 a5 b3 b4 b9) (- (* 2 a9 b1 b5 b9))
(* 2/1 a4 b3 b5 b9) (* 2/1 a3 b4 b5 b9) (* 2/1 a7 b1 b6 b9) (- (* 2/1 a4 b2 b6 b9))
(- (* 2/1 a2 b4 b6 b9)) (- (* 2/1 a3 b2 b7 b9)) (- (* 2/1 a2 b3 b7 b9)) (* 2/1 a1 b6 b7 b9)
(- (* a5 b1 b9 b9)) (* 2/1 a2 b2 b9 b9) (- (* a1 b5 b9 b9)) (* 2/1 a6 (+ (* b10 b2 b3) (- (* b1 b10 b6)) (* b4 b4 b6) (- (* b3 b4 b7)) (- (* b2 b4 b9))+(* b1 b7 b9)))
)


G = b3*b3*b7*b7-b1*b7*b7*b8+b4*b4*(b6*b6-b5*b8)-b10*(b3*b3*b5-Rat(2)*b2*b3*b6+b1*b6*b6+b2*b2*b8-b1*b5*b8)
-Rat(2)*b2*b3*b7*b9+Rat(2)*b1*b6*b7*b9+b2*b2*b9*b9-b1*b5*b9*b9-Rat(2)*b4*(b3*b6*b7-b2*b7*b8-b3*b5*b9+b2*b6*b9);



G = 
(+ 
(* b3 b3 b7 b7) (- (* b1*b7*b7*b8)) (* b4 b4 (+ (* b6 b6) (- (* b5 b8)))) (- (* b10 (+ (* b3 b3 b5) (- (* 2 b2 b3 b6)) (* b1 b6 b6) (* b2 b2 b8) (- (* b1 b5 b8)))))
(- (* 2 b2 b3 b7 b9)) (* 2 b1 b6 b7 b9) (* b2 b2 b9 b9) (- (* b1 b5 b9 b9)) (- (* 2 b4* ((* b3 b6 b7) (- (* b2 b7 b8)) (- (* b3 b5 b9)) (* b2 b6 b9))))
)



