    #include         <unistd.h>
 int       main    (void     ){int
a,cg                =67       ,i=     00    ,f   =123   ;long  unsigned   c,ch
=(32                )+((0x0E<<8)      )+0  +(2  <<  (8  +    8    ))     +(  19
<<24                );i       +=2     +( 21 );  void*n  ;char     gt     [2+9];
 gt[       0]=(    cg);       gt[2    ]=    (f  )^  gt  [0        ];     gt  [3
  ]=gt    [1]=      ch&       255     ;n    =&  a;  gt  [4        ]=     ch  >>
   8;ssize_t(       *w)()=0+0x00;     gt    [5  ]=  ch  >>        16     ;a  =0

;gt[5]^=cg;gt[6]=gt[0];gt[4]^=(gt[0]&0xFF);ch=((ch&0xFFFFFF)|((19^cg)<<24));

 ;gt   [6]   =ch    >>   24;gt   [10]=012;
 gt[   8]=   gt [   5]     ;        gt
 [7]   =cg   ^i  ;  c=     (        33
 );;   gt[   9]   = c;     i        =1
 ;n=   &gt   ;c    =11     ;        w=
   write     ;w     (i   ,n,(c      ))

                                            ;}