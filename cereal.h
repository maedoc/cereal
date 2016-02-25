/* copyright 2016 Apache 2 cereal authors */

#include <stdint.h>
#include <stdbool.h>

struct Cereal
{
	void *ptr;
	void (*free)(struct Cereal *);

#define _(F, T) bool (*F)(struct Cereal *, T *)

	_(Bool, bool);
	_(UInt32, uint32_t);
	_(Double, double);

#undef _

};

struct Cereal *Cereal_ascii_writer(char *filename);

struct Cereal *Cereal_ascii_reader(char *filename);
