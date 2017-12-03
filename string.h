#ifndef STRING_H
#define STRING_H

typedef struct _stringIter{
	char *rawString;
	int start, step, size;
	char (*next)(struct _stringIter*);
}stringIter;
typedef struct _string{
	char *rawString;
	int size;
	void (*concat)(struct _string *,struct _string *);
	void (*set)(struct _string *, char *);
	void (*delete)(struct _string *);
	stringIter (*begin)(struct _string *);
	int (*getSize)(struct _string *);
	char *(*getRaw)(struct _string *);
	void (*print)(struct _string *);
	struct _string * (*substr)(struct _string *, int );
	struct _string * (*subnstr)(struct _string *,int , int );
} string;


void _concatString(struct _string *,struct _string *);
void _setString(struct _string *, char *);
void _deleteString(struct _string *);
char *_getCharString(struct _string *);
int _getSizeString(struct _string *);

struct _string *_substr(struct _string *this, int end);
struct _string *_subnstr(struct _string *this,int start, int end);

struct _string * newString();
struct _string * newStringc(char *);
void _printString(struct _string *this);

struct _stringIter *newStringIter(char *, int, int, int);
char _stringIterNext(struct _stringIter *);
void charCopy(char *src, char *dest, int n);
void charnCopy(char *src, char *dest, int start, int n);
#endif
