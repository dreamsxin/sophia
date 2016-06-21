
/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

#include <libss.h>
#include <libsf.h>
#include <libsr.h>
#include <libsv.h>
#include <libsd.h>

static uint8_t
sd_vifflags(sv *v)
{
	return ((sdv*)v->v)->flags;
}

static char*
sd_vifpointer(sv *v)
{
	sdpage p = {
		.h = (sdpageheader*)v->arg
	};
	return sd_pagepointer(&p, (sdv*)v->v);
}

svif sd_vif =
{
	.flags     = sd_vifflags,
	.pointer   = sd_vifpointer
};

static char*
sd_vrawifpointer(sv *v)
{
	return (char*)v->v + sizeof(sdv);
}

svif sd_vrawif =
{
	.flags     = sd_vifflags,
	.pointer   = sd_vrawifpointer
};
