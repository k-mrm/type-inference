An implementaion of Hindley-Milner type inference in C.

## Example

```
200 : int
choko : unknown identifer `choko`
+ : int -> int -> int
true : bool
pair : a -> b -> (a * b)
let x = 10 in x : int
let y = false in y : bool
let z = 200 in + z 210 : int
λa -> λb -> > a b : int -> int -> bool
let add = λa -> λb -> + a b in add 100 200 : int
λx -> x : c -> c
let f = λx -> x in pair f 200 f true : (int * bool)
```

## Reference
- https://github.com/semahawk/type-inference
- https://qiita.com/reki2000/items/b7f26e65930519295355
- http://lucacardelli.name/Papers/BasicTypechecking.pdf
- http://dysphoria.net/2009/06/28/hindley-milner-type-inference-in-scala/
