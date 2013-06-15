#ifndef JSON_CHECKER_H_
#define JSON_CHECKER_H_

/* JSON_checker.h */
typedef struct JSON_checker_struct {
    int state;
    int depth;
    int top;
    int* stack;
} * JSON_checker;

extern JSON_checker new_JSON_checker(int depth);
extern int  JSON_checker_char(JSON_checker jc, int next_char);
extern int  JSON_checker_done(JSON_checker jc);

#endif /* JSON_CHECKER_H_ */
