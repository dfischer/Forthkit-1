#include <stdio.h>

int main(void)
{
    unsigned short mem[0x8000];
    short pc = 0;
    short reg[32] = {};

    short rstack[256] = {};
    short* r = rstack;

    FILE *file = fopen("boot.bin", "r");
    if (!file || !fread(&mem, sizeof(mem), 1, file))
    {
        printf("Could not open boot image.");
        return 1;
    }
    fclose(file);

    short x, y, z;

    #define NEXT mem[pc++]
    #define X x = NEXT;
    #define XY X; y = NEXT;
    #define XYZ XY; z = NEXT;
    #define Rx reg[x]
    #define Ry reg[y]
    #define Rz reg[z]

    while (1)
    {
        switch(NEXT)
        {
            case  0: XY;  Rx = y;                  break; // ldc (x = v)
            case  1: XY;  Rx = mem[y];             break; // ld (x = m[y])
            case  2: XY;  mem[x] = y;              break; // st (m[x] = y)
            case  3: XY;  Rx = Ry;                 break; // cp (x = y)
            case  4: X;   Rx = getc(stdin);        break; // in (x = getc())
            case  5: X;   putc(Rx, stdout);        break; // out (putc(x))
            case  6: XY;  Rx = Ry + 1;             break; // inc (x = ++y)
            case  7: XY;  Rx = Ry - 1;             break; // dec (x = --y)
            case  8: XYZ; Rx = Ry + Rz;            break; // add (x = y + z)
            case  9: XYZ; Rx = Ry - Rz;            break; // sub (x = y - z)
            case 10: XYZ; Rx = Ry * Rz;            break; // mul (x = y * z)
            case 11: XYZ; Rx = Ry / Rz;            break; // div (x = y / z)
            case 12: XYZ; Rx = Ry % Rz;            break; // mod (x = y % z)
            case 13: XYZ; Rx = Ry & Rz;            break; // and (x = y & z)
            case 14: XYZ; Rx = Ry | Rz;            break; // or (x = y | z)
            case 15: XYZ; Rx = Ry ^ Rz;            break; // xor (x = y ^ z)
            case 16: XY;  Rx = ~Ry;                break; // not (x = ~y)
            case 17: XYZ; Rx = Ry << Rz;           break; // lsh (x = y << z)
            case 18: XYZ; Rx = Ry >> Rz;           break; // rsh (x = y >> z)
            case 19: XYZ; if (Ry == Rz) pc = x;    break; // beq (branch if x == y)
            case 20: XYZ; if (Ry != Rz) pc = x;    break; // bne (branch if x != y)
            case 21: XYZ; if (Ry >  Rz) pc = x;    break; // bgt (branch if x > y)
            case 22: XYZ; if (Ry >= Rz) pc = x;    break; // bge (branch if x >= y)
            case 23: XYZ; if (Ry <  Rz) pc = x;    break; // blt (branch if x < y)
            case 24: XYZ; if (Ry <= Rz) pc = x;    break; // ble (branch if x <= y)
            case 25: X;   pc = Rx;                 break; // exec (pc = x)
            case 26: X;   pc = x;                  break; // jump (pc = v)
            case 27: X;   *(r++) = pc + 1; pc = x; break; // call (jsr(v))
            case 28:      pc = *(--r);             break; // return (ret)
            case 29:      return 0; // halt
            case 30: // dump
                file = fopen("boot.bin", "w");
                if (!file || !fwrite(&mem, sizeof(mem), 1, file))
                {
                    printf("Could not write boot image.");
                    return 1;
                }
                fclose(file);
                return 0;
            default:
                printf("Invalid instruction!");
                return 1;
        }
    }

    return 0;
}
