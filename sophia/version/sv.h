#ifndef SV_H_
#define SV_H_

/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

#define SVNONE       0
#define SVDELETE     1
#define SVUPSERT     2
#define SVGET        4
#define SVDUP        8

#define SVBEGIN     16
#define SVCONFLICT  32

typedef struct svif svif;
typedef struct sv sv;

struct svif {
	uint8_t (*flags)(sv*);
	char *(*pointer)(sv*);
};

struct sv {
	svif *i;
	void *v, *arg;
} sspacked;

static inline void
sv_init(sv *v, svif *i, void *vptr, void *arg) {
	v->i   = i;
	v->v   = vptr;
	v->arg = arg;
}

static inline uint8_t
sv_flags(sv *v) {
	return v->i->flags(v);
}

static inline int
sv_isflags(int flags, int value) {
	return (flags & value) > 0;
}

static inline int
sv_is(sv *v, int flags) {
	return sv_isflags(sv_flags(v), flags) > 0;
}

static inline char*
sv_pointer(sv *v) {
	return v->i->pointer(v);
}

static inline uint32_t
sv_size(sv *v, sr *r) {
	return sf_size(r->scheme, v->i->pointer(v));
}

static inline uint64_t
sv_lsn(sv *v, sr *r) {
	return sf_lsn(r->scheme, v->i->pointer(v));
}

static inline void
sv_lsnset(sv *v, sr *r, uint64_t lsn) {
	sf_lsnset(r->scheme, v->i->pointer(v), lsn);
}

static inline char*
sv_field(sv *v, sr *r, int pos, uint32_t *size) {
	return sf_fieldof(r->scheme, pos, v->i->pointer(v), size);
}

static inline uint64_t
sv_hash(sv *v, sr *r) {
	return sf_hash(r->scheme, sv_pointer(v));
}

#endif
