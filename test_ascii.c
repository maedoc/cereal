/* copyright 2016 Apache 2 cereal authors */

#include "cereal.h"
#include <stdio.h>

struct data {
	bool b1, b2;
	uint32_t u1, u2, u3;
	double d1, d2;
};

void process(struct Cereal *c, struct data *d)
{
	c->UInt32(c, &d->u1);
	c->Bool(c, &d->b2);
	c->Bool(c, &d->b1);
	c->Double(c, &d->d1);
	c->UInt32(c, &d->u3);
	c->Double(c, &d->d2);
	c->UInt32(c, &d->u2);
	c->free(c);
}

int main()
{
	struct data foo, bar = {.b1=true, .b2=false, 
		.u1=42, .u2=4242, .u3=424242,
		.d1=0.2349, .d2=42e42};

	process(Cereal_ascii_writer("ascii_test.txt"), &bar);
	printf("written.\n");
	process(Cereal_ascii_reader("ascii_test.txt"), &foo);

	bool pass = true;

	if (foo.u1 != bar.u1) { pass = false; printf("attr u1 not eq\n"); }
	if (foo.b2 != bar.b2) { pass = false; printf("attr b2 not eq\n"); }
	if (foo.b1 != bar.b1) { pass = false; printf("attr b1 not eq\n"); }
	if (foo.d1 != bar.d1) { pass = false; printf("attr d1 not eq\n"); }
	if (foo.u3 != bar.u3) { pass = false; printf("attr u3 not eq\n"); }
	if (foo.d2 != bar.d2) { pass = false; printf("attr d2 not eq\n"); }
	if (foo.u2 != bar.u2) { pass = false; printf("attr u2 not eq\n"); }

	return pass ? 0 : 1;
}
