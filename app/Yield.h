#ifndef Yield_H
#define Yield_H

typedef struct
{
	State state;
}TaskBlock;


#define yield(x) (x)->state = __LINE__; return 1; case __LINE__ : ;
#define startTask(x) switch( (x)->state) { case 0: ;
#define initTaskBlock(x) (x)->state = 0;
#define endTask(x) } ;


#endif // Yield_H
