typedef struct term{
    int coeff;
    int exp;
}term;

typedef struct poly{
	term* t;
    int size; //holds the number of terms that have been added
	int n;
}poly;

void init_poly(poly* p, int size);
void append(poly* p, int coeff, int exp);
void display(poly p);
void add_poly(poly* p1, poly* p2, poly* res);
void sub_poly(poly* p1, poly* p2, poly* res);