#ifndef SDB_H
#define SDB_H

#define SetBit(Reg,BitNum) Reg|=(1<<BitNum)
#define ClrBit(Reg,BitNum) Reg&=(~(1<<BitNum))
#define TogBit(Reg,BitNum) Reg^=(1<<BitNum)
#define GetBit(Reg,BitNum) ((Reg>>BitNum)&1)

#endif
