#ifndef STYLE_H_
#define STYLE_H_

typedef enum 
{
    style_default,    /* white*/
    style_fancy,      /* cyan */
    style_error,      /* red */
    style_success,    /* green */
} style_t;

void style_set (style_t style);
void style_reset (void);

#endif/* STYLE_H_ */
