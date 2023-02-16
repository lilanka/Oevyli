# OevyliLang
## Syntax
* Commenting:
  - For single line: `#` for single line
  - For nestable: `#- ... -#`
* Regexp: `[_a-zA-Z][_a_zA-Z0-9]*`
* Breaking lines: `\`
* Variable assignment: `=`
* Declaration: `v`
* Equality / Inequalit: `==`, `!=`, `is`, `is not`
* Comparison: `<`, `>`, `<=`, `>=`
* Runtime evaluation: `exec`
* Function call:
  - With parameters:`f(a, b, ...)`
  - With no parameters: `f()`
* Function definition: `fn f(para1, para2, ...): ...`
* Control flow
  - Sequence: `,`
  - if: `if c: ...`
  - Loop
    - while: `while c: ...`
  - Breaking control flow: `return(<value>)`
* Tensors:
  - General: `[]`, `[[], []]`, ...
  - Using tile command: `tensor((dim1, dim2, ...))`
* Types:
  - Statically typed
  - Strings: `string`
  - Integers: `i8`, `i16`, `i32`, `i64`
  - Floating point: `f32`, `f64`
* No sytatic suger yet.

## Creation Ops
***zeros(shape, dtype)***<br>
Returns a tensor filled with value 0<br>
Parameters:
* shape: A tuple of ints that represent the shape of the tensor
* dtype(optional): Data type of the tensor. Default `f16`

## Tensors
***tensor(shape, dtype)***<br>
Returns a block of zeros<br>
Parameters:
* shape: A tuple of ints that represent the shape of the tensor
* dtype(optional): Data type of the tensor. Default `f16`

## Random Number Generation
***randn(seed, shape)***<br>
Returns a block of random `f32` in `N(0, 1)`.<br>
Parameters:
* seed: The seed for generating random numbers
* shape: A tuple of the size of the tensor