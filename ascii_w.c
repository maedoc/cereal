/* copyright 2016 Apache 2 cereal authors */

#include "cereal.h"
#include <stdio.h>
#include <stdlib.h>

struct data
{
	FILE *fd;
	struct Cereal c;
};

static bool _bool(struct Cereal *c, bool *value)
{
	if (*value)
		fprintf(((struct data*)c->ptr)->fd, "True\n");
	else
		fprintf(((struct data*)c->ptr)->fd, "False\n");
	return true;
}

static bool _uint32(struct Cereal *c, uint32_t *value)
{
	fprintf(((struct data*)c->ptr)->fd, "%u\n", *value);
	return true;
}

static bool _double(struct Cereal *c, double *value)
{
	fprintf(((struct data*)c->ptr)->fd, "%lf\n", *value);
	return true;
}

static void _free(struct Cereal *c)
{
	fclose(((struct data*)c->ptr)->fd);
	free(c->ptr);
}

struct Cereal *Cereal_ascii_writer(char *filename)
{
	struct data *d;
	if ((d = malloc(sizeof(struct data))) == NULL
	 || (d->fd = fopen(filename, "w")) == NULL)
	{
		if (d != NULL)
			free(d);
		return NULL;
	}
	d->c.Bool = &_bool;
	d->c.UInt32 = &_uint32;
	d->c.Double = &_double;
	d->c.free = &_free;
	d->c.ptr = d;
	return &(d->c);
}
