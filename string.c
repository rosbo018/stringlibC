#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../Ctuple/tuple.h"

//string iteration section
//new
struct _stringIter *newStringIter(char *rawString, int start, int step, int size){
	struct _stringIter *_new = malloc(sizeof(struct _stringIter));
	_new->size = size;
	_new->step = step;
	_new->start = start;
	_new->rawString = rawString;
    return _new;
};

//application
char _stringIterNext(struct _stringIter *this){
	char s;
	if(this->step>0 && ((this->start + this->step) < this->size)){
		this->start += this->step;
		 s = *(this->rawString + this->start);
	}
	else 
	if(this->step<0 && ((this->start + this->step) > 0)){
		this->start += this->step;
		 s = *(this->rawString + this->start);
	}
	else
		 s = *(this->rawString + this->start);
	return s;
}



// main string section
//new
struct _string * newStringc(char *_set){
	string *_new = malloc(sizeof(string));
	_new->set = &_setString;
	_new->concat = &_concatString;
	_new->delete = &_deleteString;
	_new->getRaw = &_getCharString;
	_new->getSize = &_getSizeString;
	_new->substr = &_substr;
	_new->subnstr = &_subnstr;
	_new->print = &_printString;
	_new->equals = &_equalsString;
    _new->index = &_indexAt;

	_new->set(_new, _set);
	return _new;
}

struct _string * newString(){
	string *_new = malloc(sizeof(string));
	_new->set = &_setString;
	_new->concat = &_concatString;
	_new->delete = &_deleteString;
	_new->getRaw = &_getCharString;
	_new->getSize = &_getSizeString;
	_new->substr = &_substr;
	_new->subnstr = &_subnstr;
	_new->print = &_printString;
	_new->equals = &_equalsString;
	return _new;
}
//get
char *_getCharString(struct _string *this){
	return this->rawString;
}
int _getSizeString(struct _string *this){
	return this->size;
}
//print
void _printString(struct _string *this){
	printf("\nS:_%s_;size: %d\n", this->getRaw(this), this->getSize(this));
}
//set
void _setString(struct _string *this, char *_info){
	int _size = 0;
	char c;
	while((c = *(_info+_size)) != '\0')
		_size++;
	if(_info != NULL ){
		this->rawString = malloc(_size);
		for(int i = 0; i <_size; i++) //so that everything has a nice pointer
			*(this->rawString+i) = *(_info+i);
		this->size = _size;
	}
}
//iterator
stringIter *_getStringIter(string *this){
	return newStringIter(this->rawString, 0, 1, this->getSize(this));
}
//applications
void _concatString(struct _string *this, struct _string *other){//appends
	printf("this %d, that %d\n", this->size, other->size);
    this->rawString = realloc(this->rawString,  this->size + other->size + 1);
	int i = this->size;
	for(int j = 0; j < other->size; j++, i++)
		*(this->rawString+i) = *(other->rawString+j);
	this->size = this->size + other->size;
}
struct _string *_substr(struct _string *this, int end){ //substr starting at 0
	if(end < this->getSize(this)){
		struct _string *_new = newString();
		_new->rawString = malloc(end+1);
		charCopy(_new->rawString, this->rawString, end);
		return _new;
	}
	else{
		printf("substr out of bounds\n");
		return NULL;
	}
}

	//substr starting at start
struct _string *_subnstr(struct _string *this, int start, int end){ 
    printf("substr= start: %d, end: %d", start, end);
    fflush(stdout);
	if(end > start && start >= 0 && end < this->getSize(this)){
		struct _string *_new = newString();
		_new->rawString = malloc((end - start)+1);
		charnCopy(_new->rawString, this->rawString, start, end);
		return _new;
	}
	else{
		printf("substr out of bounds\n");
		return NULL;
	}
}
char _indexAt(struct _string *this, int index){
	if(this->getSize(this)>=index)
		return NULL;
	return *(this->getRaw(this) + index);


}

int _equalsString(struct _string *this, struct _string *other){
	if(this->getSize(this) != other->getSize(other))
		return 0;
	for(int i = 0; i < this->getSize(this); i++)
		if(this->index(this, i) != other->index(other, i))
			return 0;
	return 1;
			       
}
int
_findString(struct _string *this, struct _string *other)
{
    char *thisTemp = this->getRaw(this);
    char *otherTemp = other->getRaw(other);
    if (other->size > this->size)
        return 0;

    for (int index = 0; index < (this->size); index++){
        if (*(thisTemp+index) == *(otherTemp+index)){
            return 1;
        }
    }
    return 0;



}

struct Tuple*
findCharLocations(struct _string *this, char c)
{
    int *locations = malloc(sizeof(*locations));
    char *raw = this->rawString;
    int numLocCount = 0;
    int index = 0;
    for (char temp; index < this->size; index++){
        temp = *(raw+index);
        if(c == temp){
            *(locations+numLocCount) = index;
            locations = addItemSpace(locations, numLocCount++);
        }
    }
    printf("num locations :%d\n", (numLocCount));
    return newTuple(locations, &numLocCount);
}
struct Tuple*
split(struct _string *this, char c)
{
    struct Tuple *tuple = findCharLocations(this, c);
    int numLocations;
    numLocations = *((int *) tuple->B );
    struct _string **splitStrings;
    splitStrings= malloc(sizeof(*splitStrings) * (numLocations+1));
    int *locations;
    int start = 0;
    int end;
    locations = tuple->A;
    if (numLocations == 0){
        *splitStrings = this;
        return newTuple(splitStrings, &start);
    }
    printf("n:%d\n", (numLocations));
    printf("L:%d\n", *(locations));
    for (int i = 0; i < numLocations; i++){
        printf("iteration %d", i);
        end = *(locations + i);
        printf("end : %d\n", end);
        *(splitStrings + i) = _subnstr(this, start, end);
        _printString(*(splitStrings + i));
    }

    //return newTuple((void *)splitStrings,(void *) num);
    return newTuple(NULL, NULL);


}
void*
addItemSpace(void *lst, int numElems)
{
    lst = realloc(lst, sizeof(*lst)*(numElems+1));
    return lst;
}

//deallocate
void _deleteString(struct _string *this){
	free(this->rawString);
	free(this);
}




//other
void charCopy(char *dest, char *src, int n){
	//printf("charcopy\n");
	for (int i = 0; i < n; i++)
		 *(dest+i) = *(src+i);
	*(dest+n) = '\0';
}
void charnCopy(char *dest, char *src, int start, int n){
	//printf("charncopy\n");
	int iter = start;
	for (int i = 0; i < n; i++, iter++)
		 *(dest+i) = *(src+iter);
	*(dest+n) = '\0';
}

int main(){
	string *test = newStringc("this");
	string *test2 = newStringc("that");
    int *i;
    struct Tuple *Tup;
    struct _string **list;
    Tup = split(test,'h');

    fflush(stdin);

	test->delete(test);
	test2->delete(test2);
}


