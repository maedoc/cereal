/* copyright 2016 Apache 2 cereal authors */

#include "cereal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data
{
	FILE *fd;
	struct Cereal c;
};

static bool _bool(struct Cereal *c, bool *value)
{
	char buf[10];
	fscanf(((struct data*)c->ptr)->fd, "%s ", buf);
	if (!strcmp("True", buf))
		*value = true;
	else
		*value = false;
	return true;
}

static bool _uint32(struct Cereal *c, uint32_t *value)
{
	fscanf(((struct data*)c->ptr)->fd, "%u ", value);
	return true;
}

static bool _double(struct Cereal *c, double *value)
{
	fscanf(((struct data*)c->ptr)->fd, "%lf ", value);
	return true;
}

static void _free(struct Cereal *c)
{
	fclose(((struct data*)c->ptr)->fd);
	free(c->ptr);
}

struct Cereal *Cereal_ascii_reader(char *filename)
{
	struct data *d;
	if ((d = malloc(sizeof(struct data))) == NULL
	 || (d->fd = fopen(filename, "r")) == NULL)
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
