/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
 // 德摩根定律
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x&y) & (~(~x&~y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x) return !y;
    if(!y) return 0;
    return !((x >> 31) ^ (y >> 31));
}
/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int a, b, c, d;
    a=(v>>16)>0;
    v>>=a<<4;
    b=(v>>8)>0;
    v>>=b<<3;
    c=(v>>4)>0;
    v>>=c<<2;
    d=(v>>2)>0;
    v>>=d<<1;
    return (a<<4)|(b<<3)|(c<<2)|(d<<1)|(v>>1);
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int ns=n<<3;
    int ms=m<<3;
    int a=(x>>ns)&0xff;
    int b=(x>>ms)&0xff;
    int diff=a^b;
    return x^(diff<<ns)^(diff<<ms);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned re=0;
    unsigned c=32;
    while (c) {
        re=(re<<1)|(v&1);
        v>>=1;
        c=c-1;
    }return re;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int k=n+!n+~0;
    int m=(0x7fffffff>>k)|((~0x7fffffff)&(~(!n) +1));
    return (x>>n)&m;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int y=~x;
    int n=0;
    n=n+(!(y>>16)<<4);
    n=n+(!(y>>(24+~n+1))<<3);
    n=n+(!(y>>(28+~n+1))<<2);
    n=n+(!(y>>(30+~n+1))<<1);
    n=n+!(y>>(31+~n+1));
    return n+ !y;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned s=0;
    unsigned m;
    unsigned f;
    unsigned e;
    unsigned dr;
    unsigned h;
    int b=31;
    int sh;
    if(x==0) return 0;
    if(x<0) {
        s=1u<<31;
        m=-(x+1);
        m=m+1;}
    else{m=x;}
    while(!(m>>b))b=b-1;
    e=b+127;
    if(b<=23){
        f=(m<<(23-b))&0x7fffff;}
    else{
        sh=b-23;
        f=(m>>sh)&0x7fffff;
        dr=m&((1u<<sh)-1u);
        h=1u<<(sh-1);
        if(dr>h)f=f+1;
        else if(dr==h)f=f+(f&1);}
    return s|((e<<23)+f);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned s=uf&0x80000000u;
    unsigned e=(uf>>23)&0xff;
    unsigned f=uf&0x7fffff;
    if(e==255)return uf;
    if(e==0)return s|(f<<1);
    if(e==254)return s|0x7f800000u;
    return s|((e+1)<<23)|f;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1,unsigned uf2){
    int ex=(uf2>>20)&0x7ff;
    int b=ex-1023;
    unsigned h=(uf2&0xfffff)|0x100000;
    unsigned v;
    int res;
    if(b<0)return 0;
    if(b>=31)return ~0x7fffffff;
    if(b<=20){
        v=h>>(20-b);
    }else{
        v=(h<<(b-20))|(uf1>>(52-b));
    }
    res=v;
    if(uf2>>31)return -res;
    return res;
}


/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x){
    if(x<-149)return 0;
    if(x<-126)return 1u<<(x+149);
    if(x>127)return 0x7f800000u;
    return (x+127)<<23;
}

