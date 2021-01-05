#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node{

	int coeff;
	int exp[3];
	struct node *link;
};

typedef struct node* Nodeptr;

void read(Nodeptr new)
{
	printf("Enter the coefficient: ");
	scanf("%d", &new->coeff);
	printf("Enter the coeffients of x, y, z: ");
	scanf("%d%d%d", &new->exp[0], &new->exp[1], &new->exp[2]);
}

Nodeptr createN()
{
	Nodeptr newnode;
	newnode = (Nodeptr)malloc(sizeof(struct node));
	newnode->link=newnode;
	return newnode;
}

//struct node *A, *B, *C;
//struct node *A=NULL, *B=NULL, *C=NULL;




Nodeptr insertE(Nodeptr head)
{
	Nodeptr temp, ptr;
	ptr=head;
	temp = createN();
	while(ptr->link!=head)
		ptr=ptr->link;
	ptr->link=temp;
	temp->link=head;
	return temp;
}

int compare(Nodeptr h1, Nodeptr h2)
{
	if(h1->exp[0]==h2->exp[0])
	{
		if(h1->exp[1]==h2->exp[1])
		{
			if(h1->exp[2]==h2->exp[2])
				return 0;
			else if(h1->exp[2]>h2->exp[2])
				return 1;
			else
				return 0;
		}
	}
	else if(h1->exp[0]>h2->exp[0])
		return 1;
	else
		return -1;
}

void attach(Nodeptr h3, int c, int e[3])
{
	Nodeptr temp, ptr;
	temp = createN();
	temp->coeff=c;
	for(int i=0; i<3; i++)
		temp->exp[i]=e[i];

	ptr=h3;
	while(ptr->link!=h3)
		ptr=ptr->link;
	ptr->link=temp;
	temp->link=h3;
}



void add(Nodeptr h1, Nodeptr h2, Nodeptr h3)
{
	Nodeptr a, b;
	int sum=0;
	a=h1->link;//not sure about this part. Actually only a=h1 and b=h2
	b=h2->link;//not sure about this part
	while(a!=h1 && b!=h2)
	{
		switch(compare(a,b))
		{
			case 0: sum = a->coeff + b->coeff;
				attach(h3, sum, a->exp);
				a=a->link;
				b=b->link;
				break;
			case 1: attach(h3, a->coeff, a->exp);
				a=a->link;
				break;
			case -1:attach(h3, b->coeff, b->exp);
				b=b->link;
				break;
		}
	}
	if(a!=h1)
		while(a!=h1)
		{
			attach(h3, a->coeff, a->exp);
			a=a->link;
		}
	if(b!=h2)
		while(b!=h2)
		{
			attach(h3, b->coeff, b->exp);
			b=b->link;
		}
}



void displayP(Nodeptr head)
{
	Nodeptr ptr = head->link;
    while(ptr!=head)
	{
		if(ptr->coeff!=0)
		{
			printf("%d", ptr->coeff);
			if(ptr->exp[0]!=0)
				printf("x^%d", ptr->exp[0]);
			if(ptr->exp[1]!=0)
				printf("y^%d", ptr->exp[1]);
			if(ptr->exp[2]!=0)
				printf("z^%d", ptr->exp[2]);
		}
		if(ptr->link!=head)
            printf(" + ");
		ptr=ptr->link;
	}
	printf("\n");
}

void PEval(Nodeptr head)
{
    Nodeptr ptr=head->link;
    int x, y, z, value=0;
    printf("Enter the values of x, y, z: ");
    scanf("%d%d%d", &x, &y, &z);
    while(ptr!=head)
    {
        value += (ptr->coeff * pow(x, ptr->exp[0]) * pow(y, ptr->exp[1]) * pow(z, ptr->exp[2]));
        ptr=ptr->link;
    }
    printf("Value = %d\n\n", value);
}

void main()
{
	int choice, n[2], eval;
	Nodeptr A, B, C;
    A=createN();
    B=createN();
    C=createN();
	Nodeptr T;
	printf("1. Add 2 polynomials\n2. Evaluate polynomials\n3. Exit\n");
	while(1)
{
	printf("Enter your choice: ");
	scanf("%d", &choice);
	switch(choice)
	{
		case 1: for(int i=1; i<=2; i++)
			    {
                    printf("Enter the number of terms in polynomial %d: ", i);
                    scanf("%d", &n[i-1]);
                    if(i==1)
                        T=A;
                    else
                        T=B;
                    for(int j=1; j<=n[i-1]; j++)
                    {
                        printf("Enter the data for term %d:\n", j);
                        read(insertE(T));
                        printf("\n");
                    }
                    printf("\n");
                }
                printf("The polynomials are: \n");
                printf("A = ");
                displayP(A);
                printf("B = ");
                displayP(B);
                add(A,B,C);
                printf("\nSum = ");
                displayP(C);
                break;
		case 2: printf("Enter the number of terms in polynomial: ");
                scanf("%d", &eval);
                for(int j=1; j<=eval; j++)
                {
                    printf("Enter the data for term %d:\n", j);
                    read(insertE(A));
                    printf("\n");
                }
                printf("\n");
                displayP(A);
                PEval(A);

                break;
		case 3: exit(0);
		default: printf("Invalid choice. \n");
	}
}
}

