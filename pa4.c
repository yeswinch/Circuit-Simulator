#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>

typedef struct Node
{
   char* var;
   int value;

   struct Node* next;



}Node;



int search(char* r, Node* h)
{
  Node* current;
  for(current = h; current!= NULL; current= current->next)
    {
      if(strcmp(current->var,r) == 0)

	{
	  return current->value;

        }

    }

  return -1;

}





void change(int b,char* v, Node* h)
{
    Node* holder;
   for(holder = h; holder != NULL; holder = holder->next)
    {
      if(strcmp(holder->var,v) == 0)
	{
	  holder->value = b;
          break;


        }

    }
}




void insert(char* add, Node* ptr)
{
  Node* holder;
  Node* plus = (Node*)malloc(sizeof(Node));


  plus->var = malloc(20*sizeof(char));
  strcpy(plus->var,add);
  plus->next = NULL;

  for(holder = ptr; holder != NULL; holder = holder->next)
    {

      if(holder->next == NULL)
	{

	  holder->next = plus;
          break;

        }


    }



}


void setarray(int** array, int numRows,int numColumns)
{
  int r;
  int c;
   for(r = 0; r < numRows; r++)
      {

	for(c = 0; c < numColumns; c++)
	  {
	    array[r][c]=0;

	  }

      }

}
void printarray(int** array, int numRows,int numColumns)
{
  int r;
  int c;
   for(r = 0; r < numRows; r++)
      {

	for(c = 0; c < numColumns; c++)
	  {
	    printf("%d ",array[r][c]);

	  }
	printf("\n");
      }

}



int main(int argc, char* argv[])
{

  FILE* fp = fopen(argv[1],"r");
  if(fp == NULL) return 0;

  int iVars;
  int oVars;

  fscanf(fp,"%*s %d", &iVars);

   Node* iVar = NULL;
   Node* oVar = NULL;

   int i;

   for(i=0 ; i < iVars; i++)
    {

	char* holder =(char*) malloc(20*sizeof(char));
         fscanf(fp,"%s", holder);

         if(iVar == NULL)
	   {
	     Node* make = (Node*)malloc(sizeof(Node));
             make->next = NULL;
             make->var = holder;
             iVar = make;

	   }
	 else
	   {
             insert(holder,iVar);
           }


      }

    fscanf(fp,"%*s %d\n",&oVars);
    int k;
    for(k=0 ; k < oVars; k++)
    {

	char* holder =(char*) malloc(20*sizeof(char));
         fscanf(fp,"%s", holder);
         if(oVar == NULL)
	   {
	     Node* make = (Node*)malloc(sizeof(Node));
             make->next = NULL;
             make->var = holder;
             oVar = make;

	   }
	 else
	   {
             insert(holder,oVar);
           }


      }





    int** gird = (int**)malloc((int)pow(2,iVars)*sizeof(int*));
    int c;
    for(c = 0; c <(int) pow(2,iVars);c++)
      {
	gird[c]= (int*)malloc((iVars + oVars)*sizeof(int));


      }
    setarray(gird,(int)pow(2,iVars),iVars +oVars);


    int r;
    int col;
    int freq=1;
    int swVar= 0;
    int ctr = 0;
    int gridRow = (int)pow(2,iVars);
    int gridCol = iVars + oVars;


    for( col = iVars -1; col >= 0; col--)
      {

	ctr = 0;
    swVar= 0;
	for(r = 0; r < (int)pow(2,iVars); r++)
	  {
	    if(ctr == freq)
	      {
		if(swVar ==0){ swVar =1;}
                else { swVar = 0; }
                ctr = 0;

	      }
	    gird[r][col]= swVar;
	      ctr++;

	  }
	freq = freq *2;


      }


    int r1;
    int c1;
    for(r1 = 0; r1 < gridRow  ;r1++)
      {

        Node* add = iVar;
	for(c1 = 0; c1 < gridCol -oVars; c1++)
	  {

	    int adding = gird[r1][c1];

            add->value = adding;

            add = add->next;

          }


         char* oper = malloc(5*sizeof(char));
          fclose(fp);
          fp= fopen(argv[1],"r");
          fscanf(fp,"%*[^\n]");
          fscanf(fp,"\n");
          fscanf(fp,"%*[^\n]");
          fscanf(fp,"\n");
	 while(fscanf(fp,"%s",oper)!= EOF) {

	    char* fVar = malloc(20*sizeof(char));

            fscanf(fp,"%s",fVar);

            char* secVar = malloc(20*sizeof(char));
             fscanf(fp,"%s",secVar);

            if(strcmp("NOT",oper)==0 )
	     {

               if(secVar[0] >= 'a' && secVar[0] <= 'z')
		 {
		   if(search(secVar,iVar) == -1)
		     {
		       insert(secVar,iVar);

                     }

                 }
	       if(search(fVar,iVar)!= -1)
		 {

		   int negate = !search(fVar,iVar);

		   if(search(secVar,iVar) != -1)
                     {

                       change(negate,secVar,iVar);
                     }
                   else if(search(secVar,oVar) != -1)
                     {
                       change(negate,secVar,oVar);

                     }

                 }
	       else
		 {
		   int negate = !search(fVar,oVar);
                     if(search(secVar,iVar) != -1)
                     {

                       change(negate,secVar,iVar);

                     }
                   else if(search(secVar,oVar) != -1)
                     {

                       change(negate,secVar,oVar);

                     }


                 }




             }
             if(strcmp("AND",oper)==0 )
	       {
		 int temp1;
                 int temp2;
                 int f;
                 if(search(fVar,iVar)!= -1){ temp1 = search(fVar,iVar);}
                 else temp1 = search(fVar,oVar);
                 if(search(secVar,iVar)!= -1){ temp2 = search(secVar,iVar);}
                 else temp2 = search(secVar,oVar);

		 f = temp1 && temp2;

                 char* thirdV = malloc(20*sizeof(char));
                 fscanf(fp,"%s",thirdV);
                 if(thirdV[0] >= 'a' && thirdV[0] <= 'z')
		   {
		     if(search(thirdV,iVar) == -1) insert(thirdV,iVar);


                   }

                 if(search(thirdV,iVar) != -1) change(f,thirdV,iVar);

                 else change(f,thirdV,oVar);


               }




                 if(strcmp("OR",oper)==0 )
	       {
		 int temp1;
                 int temp2;
                 int f;
                 if(search(fVar,iVar)!= -1){ temp1 = search(fVar,iVar);}
                 else temp1 = search(fVar,oVar);
                 if(search(secVar,iVar)!= -1){ temp2 = search(secVar,iVar);}
                 else temp2 = search(secVar,oVar);

		 f = temp1 || temp2;

                 char* thirdV = malloc(20*sizeof(char));
                 fscanf(fp,"%s",thirdV);
                 if(thirdV[0] >= 'a' && thirdV[0] <= 'z')
		   {
		     if(search(thirdV,iVar) == -1) insert(thirdV,iVar);


                   }

                 if(search(thirdV,iVar) != -1) change(f,thirdV,iVar);

                 else change(f,thirdV,oVar);


               }
                 if(strcmp("NOR",oper)==0 )
	       {
		 int temp1;
                 int temp2;
                 int f;
                 if(search(fVar,iVar)!= -1){ temp1 = search(fVar,iVar);}
                 else temp1 = search(fVar,oVar);
                 if(search(secVar,iVar)!= -1){ temp2 = search(secVar,iVar);}
                 else temp2 = search(secVar,oVar);

		 f = !(temp1 || temp2);

                 char* thirdV = malloc(20*sizeof(char));
                 fscanf(fp,"%s",thirdV);
                 if(thirdV[0] >= 'a' && thirdV[0] <= 'z')
		   {
		     if(search(thirdV,iVar) == -1) insert(thirdV,iVar);


                   }

                 if(search(thirdV,iVar) != -1) change(f,thirdV,iVar);

                 else change(f,thirdV,oVar);


               }
                 if(strcmp("NAND",oper)==0 )
	       {
		 int temp1;
                 int temp2;
                 int f;
                 if(search(fVar,iVar)!= -1){ temp1 = search(fVar,iVar);}
                 else temp1 = search(fVar,oVar);
                 if(search(secVar,iVar)!= -1){ temp2 = search(secVar,iVar);}
                 else temp2 = search(secVar,oVar);

		 f = !(temp1 && temp2);

                 char* thirdV = malloc(20*sizeof(char));
                 fscanf(fp,"%s",thirdV);
                 if(thirdV[0] >= 'a' && thirdV[0] <= 'z')
		   {
		     if(search(thirdV,iVar) == -1) insert(thirdV,iVar);


                   }

                 if(search(thirdV,iVar) != -1) change(f,thirdV,iVar);

                 else change(f,thirdV,oVar);


               }
                if(strcmp("XOR",oper)==0 )
	       {
		 int temp1;
                 int temp2;
                 int f;
                 if(search(fVar,iVar)!= -1){ temp1 = search(fVar,iVar);}
                 else temp1 = search(fVar,oVar);
                 if(search(secVar,iVar)!= -1){ temp2 = search(secVar,iVar);}
                 else temp2 = search(secVar,oVar);

		 f = temp1 ^ temp2;

                 char* thirdV = malloc(20*sizeof(char));
                 fscanf(fp,"%s",thirdV);
                 if(thirdV[0] >= 'a' && thirdV[0] <= 'z')
		   {
		     if(search(thirdV,iVar) == -1) insert(thirdV,iVar);


                   }

                 if(search(thirdV,iVar) != -1) change(f,thirdV,iVar);

                 else change(f,thirdV,oVar);


               }

	 }
        Node* temp = oVar;
        for(c1 = gridCol - oVars; c1 < gridCol ; c1++)
	  {

	    gird[r1][c1] = temp->value;
            temp = temp->next;


          }

      }
    printarray(gird,gridRow,gridCol);

  return 0;
}
