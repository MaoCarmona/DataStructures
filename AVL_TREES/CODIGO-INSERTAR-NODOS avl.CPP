/* EN ESTE PROGRAMA SE MUESTRAN LAS RUTINAS QUE
   INSERTAN NODOS EN UN ARBOL AVL MANTENIENDO LAS PROPIEDADES
   DE UN ARBOL AVL */

#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
//#include "alloc.h"
#define nodo_arbol (struct nodo *) malloc (sizeof (struct nodo))
struct nodo {
	int info;
	int bal;
	struct nodo *izq;
	struct nodo *der;
};

int lea();

int main()
{
	int n;
	void inorden (struct nodo *raiz);
	struct nodo *raiz=NULL;
	int ins_avl(struct nodo **,int);
	printf ("lea n \n"); 
	n = lea();
	while (n != 9999) {
		ins_avl (&raiz,n);
		printf ("lea n \n"); 
		n = lea();
	}
	inorden(raiz);
	getch();
	return 0;
}
void inorden (struct nodo *raiz)
{
	if (raiz != NULL) {
		inorden (raiz->izq);
		printf ("%d %d   ",raiz->info,raiz->bal);
		inorden (raiz->der);
	}
}

void r_derecha (struct nodo *p,struct nodo *q)
{
	p->bal = 0;
	q->bal = 0;
	p->izq = q->der;
	q->der = p;
}
void r_izquierda (struct nodo *p,struct nodo *q)
{
	p->bal = 0;
	q->bal = 0;
	p->der = q->izq;
	q->izq = p;
}

void dr_derecha (struct nodo *p,struct nodo **q)
{
	struct nodo *r;

	r = (*q)->der;
	(*q)->der = r->izq;
	r->izq = *q;
	p->izq = r->der;
	r->der = p;
	switch (r->bal) {
		case -1 : (*q)->bal = 1;
				p->bal = 0;
				break;
		case  0 : (*q)->bal = p->bal = 0;
				break;
		case  1 : (*q)->bal = 0;
				p->bal = -1;
				break;
	}
	r->bal = 0;
	*q = r;
}
void dr_izquierda (struct nodo *p,struct nodo **q)
{
	struct nodo *r;

	r = (*q)->izq;
	(*q)->izq = r->der;
	r->der = *q;
	p->der = r->izq;
	r->izq = p;
	switch (r->bal) {
		case -1 : (*q)->bal = 0;
				p->bal = 1;
				break;
		case  1 : (*q)->bal = -1;
				p->bal =  0;
				break;
		case  0 : (*q)->bal = p->bal = 0;
				break;

	}
	r->bal = 0;
	*q = r;
}

struct nodo *crear_nodo (int n)
{
	struct nodo *nuevo;

	nuevo = nodo_arbol;
	nuevo->info = n;
	nuevo->bal = 0;
	nuevo->izq = NULL;
	nuevo->der = NULL;
	return (nuevo);
}

int ins_avl (struct nodo **raiz,int n)
{
	struct nodo *nuevo,*p,*q,*s,*pivote,*pp;
	int llave,altura;

	nuevo = crear_nodo(n);
	if (*raiz == NULL) {
		*raiz = nuevo;
		return (1);  /* el arbol tiene un solo nodo */
	}
	pp = q = NULL;
	pivote = p = *raiz;
	llave = nuevo->info;
	while (p != NULL) {
		if (p->bal) {
			pp = q;
			pivote = p;
		}
		if (llave == p->info) {
			free (nuevo);
			return (2); /* ya existe */
		}
		else {
				q = p;
				if (llave < p->info)
					p = p->izq;
				else p = p->der;
			}
	}
	if (llave < q->info)
		q->izq = nuevo;
	else q->der = nuevo;
	if (llave < pivote->info) {
		s = pivote->izq;
		altura  = 1;
	}
	else {
			s = pivote->der;
			altura = -1;
		}
	p = s;
	while (p != nuevo)
		if (llave < p->info) {
			p->bal = 1;
			p = p->izq;
		}
		else {
				p->bal = -1;
				p = p->der;
			}
	if (pivote->bal == 0)
		pivote->bal = altura;
	else if (pivote->bal + altura == 0)
			pivote->bal = 0;
		else {
				if (altura == 1)
					if (s->bal == 1)
						r_derecha (pivote,s);
					else dr_derecha (pivote,&s);
				else if (s->bal == -1)
						r_izquierda (pivote,s);
					else dr_izquierda (pivote,&s);
				if (pp == NULL)
					*raiz = s;
				else if (pp->izq == pivote)
						pp->izq = s;
					else pp->der = s;
			}
}



int lea()
{
	int l;

	scanf("%d",&l);
	return l;
}
