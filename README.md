An implementation of Hindley-Milner type inference in C.

## Example

```
200 : int
choko : unknown identifer `choko`
+ : int -> int -> int
true : bool
pair : a -> b -> (a * b)
fst : (c * d) -> c
snd : (e * f) -> f
let x = 10 in x : int
let y = false in y : bool
let z = 200 in ((+ z) 210) : int
λa -> λb -> ((> a) b) : int -> int -> bool
let add = λa -> λb -> ((+ a) b) in ((add 100) 200) : int
λx -> x : g -> g
λn -> λm -> 300 : h -> i -> int
let f = λx -> x in ((pair (f 200)) (f true)) : (int * bool)
(fst ((pair false) 100000)) : bool
(snd ((pair false) 100000)) : int
let rec fibo = λn -> (((if ((< n) 2)) n) ((+ (fibo ((- n) 2))) (fibo ((- n) 1)))) in (fibo 30) : int
```

## Reference
- https://github.com/semahawk/type-inference
- https://qiita.com/reki2000/items/b7f26e65930519295355
- http://lucacardelli.name/Papers/BasicTypechecking.pdf
- http://dysphoria.net/2009/06/28/hindley-milner-type-inference-in-scala/
