( assembler for register VM )

var dp ( dictionary pointer )
: here dp @ ;
: , here m! here 1 + dp ! ; ( append )

: ldc,     0 , , , ;        (   v x ldc,  →  x = v            )
: ld,      1 , , , ;        (   a x ld,   →  x = mem[a]       )
: st,      2 , , , ;        (   x a st,   →  mem[a] = x       )
: cp,      3 , , , ;        (   y x cp,   →  x = y            )
: in,      4 , , ;          (     x in,   →  x = getc         )
: out,     5 , , ;          (     x out,  →  putc x           )
: inc,     6 , , , ;        (   y x inc,  →  x = y + 1        )
: dec,     7 , , , ;        (   y x dec,  →  x = y - 1        )
: add,     8 , , , , ;      ( z y x add,  →  x = z + y        )
: sub,     9 , , swap , , ; ( z y x sub,  →  x = z - y        )
: mul,    10 , , , , ;      ( z y x mul,  →  x = z × y        )
: div,    11 , , swap , , ; ( z y x div,  →  x = z ÷ y        )
: mod,    12 , , swap , , ; ( z y x mod,  →  x = z mod y      )
: and,    13 , , , , ;      ( z y x and,  →  x = z and y      )
: or,     14 , , , , ;      ( z y x or,   →  x = z or  y      )
: xor,    15 , , , , ;      ( z y x xor,  →  x = z xor y      )
: not,    16 , , , ;        (   y x not,  →  x = not y        )
: shl,    17 , , swap , , ; ( z y x shl,  →  x = z << y       )
: shr,    18 , , swap , , ; ( z y x shr,  →  x = z >> y       )
: beq,    19 , , , , ;      ( x y a beq,  →  pc = a if x = y  )
: bne,    20 , , , , ;      ( x y a bne,  →  pc = a if x ≠ y  )
: bgt,    21 , , swap , , ; ( x y a bgt,  →  pc = a if x > y  )
: bge,    22 , , swap , , ; ( x y a bge,  →  pc = a if x ≥ y  )
: blt,    23 , , swap , , ; ( x y a blt,  →  pc = a if x < y  )
: ble,    24 , , swap , , ; ( x y a ble,  →  pc = a if x ≤ y  )
: exec,   25 , , ;          (     x exec, →  pc = [x]         )
: jump,   26 , , ;          (     a jump, →  pc = a           )
: call,   27 , , ;          (     a call, →  push[pc], pc = a )
: ret,    28 , ;            (       ret,  →  pc = pop[]       )
: halt,   29 , ;            (       halt, →  halt machine     )
: dump,   30 , ;            (       dump, →  core to boot.bin )

: label here const ;
: ahead, here 1 + 0 jump, ; ( dummy jump, push address )
: then, here swap m! ; ( patch jump )

: assemble here . dump ;

