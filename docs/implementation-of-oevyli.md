# The Project

## Add followings
* Basic data types
  - int
  - float (f32)
  - double (f64)
  - string
* Tiles (Tensors)
  - standard data types is f16
  - vector
  - matrix
  - for higher dimensions
* Operator fusion
* A way to measure time spent on your GPU computing FLOPS, time spent transferring
tensors within a GPU.

## An Example Code
```python
# dot_product.ovli

# Perform C = A * B.T
A = uniform((1024, 1024))
B = uniform((1024, 1024))
T = uniform((1024, 1))

C = A * dot(B, T)
print C
```

# The Implementation
The projects aim is to compile AI program into efficient CPU/GPU code. On the other
it can output LLVM-IR too (use `gen-llvm` when compiling the code).

At the end you should be able to compile and run above program in matter of seconds
```sh
$ oevyli dot_product.ovli
```
