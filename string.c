#include <stdio.h>
#include <stdlib.h>
#include "string.h"

//string iteration section
//new
struct _stringIter *newStringIter(char *rawString, int start, int step, int size){
	struct _stringIter *_new = malloc(sizeof(struct _stringIter));
	_new->size = size;
	_new->step = step;
	_new->start = start;
	_new->rawString = rawString;
	

}

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
	printf("S:_%s_;size: %d", this->getRaw(this), this->getSize(this));
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
	int x = 0;
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
int *_findString(struct _string *this, struct _string *token){
	int *results = malloc(sizeof(int));
	*result = 0;
	int t = 1;
	if(token->getSize(token) > this->getSize(this))
		return result;
	for(int i = 0; i <this->getSize(this), i++){
		if(this->index(this, i) == token->index(token, 0)){
			t = 1;
			for(int j = 0; j <token->getSize(token), j++){
				if(this->index(this, i+j) != token->index(token, j))
					t = 0;
			}
			if (t==1){
				(*result)++;
				result = realloc(result, (*result)+1);
				*(result+(*result)) = i;
			}
		}
	}
	return result;

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
	test->concat(test, test2);
	printf("%s\n", test->rawString);
	string *sub = test->substr(test, 4);
	sub->print(sub);

	sub->delete(sub);
	test->delete(test);
	test2->delete(test2);
}


