( simple assembler/VM test - capitalize [-32] console input )
( requires assembler )

0 const u ( to upper )
1 const c ( char )

  32 u ldc,
 label &start
     c in,
 c u c sub,
     c out,
&start jump,

assemble
