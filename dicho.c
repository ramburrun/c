	 /*   dicho.c							auteur : M.RAMBURRUN   */

#include <stdio.h>
#include <ctype.h>
#define NMAX 50


/*************************************/
/****     attend touche           ****/
/*************************************/
void attend_touche()
{
  printf("\nAppuyer sur Enter pour continuer ...");
  while( getchar( ) != '\n' );  /* ou fgets(vb,80,stdin)  avec  char vb[81];  */
}

/********************************/
/****     affichage          ****/
/********************************/
void aff(int *v,int n)
{
 int i;

 for(i = 0; i < n; i++ ) printf("%7d ",v[i]);
 printf("\n");
}
/********************************/
/****     tri du vecteur     ****/
/********************************/
void tri(int *v,int n)
{
  int i,travail,minimum,reserve;

  for( i = 0; i < n - 1; i++ )
  {
	minimum = i;
    for(travail = i+1; travail < n; travail++ )
     if( v[travail] < v[minimum] ) minimum = travail;
    reserve = v[i];
    v[i] = v[minimum];
    v[minimum] = reserve;
   }
}
/********************************/
/****      saisie            ****/
/********************************/
int saisie(int *v)
{
  int ok;
  int i,n;

  do
  {
	printf("Entrer le nb d'elements (<= %d ) : ",NMAX);
    ok=scanf("%d",&n);
    while( getchar( ) != '\n' );  /* ou fgets(vb,80,stdin)  avec  char vb[81];  */
  }while( !ok || n<0 || n > NMAX );
  for( i = 0; i < n; i++ )
  {
	do
	{
	 printf("v[%2d]=",i);
     ok = scanf("%d",&v[i]);
     while( getchar( ) != '\n' );  /* ou fgets(vb,80,stdin)  avec  char vb[81];  */
    }while( !ok );
  }
  return n;
}
/***********************************/
/****      recherche            ****/
/***********************************/
int recherche(int *v,int n,int val)
{
  int inf,sup,milieu;

  if( val < v[0] )   return 0;
  if( val > v[n-1] ) return n;
  inf = 0;
  sup = n - 1;
  milieu = ( sup + inf ) / 2;
  while( v[milieu] !=val && ( sup - inf ) > 1 )
  { if( val < v[milieu] )
    {
	   sup = milieu;
	   milieu =(sup+inf)/2;
    }
    else
    {
	   inf = milieu;
	   milieu = (sup + inf ) / 2;
    }
  }
  milieu++;
  while( milieu >0  && v[milieu-1] == val )
  {
	milieu--;
  }
  return milieu;
}
/*************************************/
/****        insertion            ****/
/*************************************/
int insert(int *v,int n,int val,int milieu)
{
  int i;

  for(i = n; i > milieu;i-- ) v[i] = v[i-1];
  v[milieu] = val;
  n++;
  printf("\n\"%d\" a ete insere en position %d\n",val,milieu+1);
  printf("Apres insertion on a :\n");
  aff(v,n);
  attend_touche();
  return n;
}
/************************************/
/****          suppression       ****/
/************************************/
int supp(int *v,int n,int val,int milieu)
{
 int i;

 if( milieu >=0 && v[milieu]==val )
  { for( i = milieu;i < n-1;i++) v[i] = v[i+1];
    n--;
    printf("\n\"%d\" a ete supprime en position %d\n",val,milieu+1);
    printf("Apres suppression on a :\n");
    aff(v,n);
  }
  else
   printf("\nSuppression impossible...");
  attend_touche();
  return n;
}
/*************************************/
/****           menu              ****/
/*************************************/
void menu()
{
  printf("            T O U T   S U R   L A   D I C H O T O M I E\n\n");
  printf("\n\n\n        r) initialisation ou reitialisation du vecteur\n");
  printf("\n        i) insertion par dichotomie\n");
  printf("\n        s) suppression par dichotomie\n");
  printf("\n        f) fin\n\n\n");
  printf("\n                 Votre choix : ");
}
/*************************************/
/****        fonction principale  ****/
/*************************************/
int main()
{
  char c,rep;int ok;
  int n;
  int v[NMAX];
  int milieu;
  int val;
  n = 0;  /* important a initialiser */

  do
  {
	do
    {
	  menu();
      c = toupper(getchar());
      while( getchar( ) != '\n' );  /* ou fgets(vb,80,stdin)  avec  char vb[81];  */
    } while(c!='F' && c!='I' && c!='R' && c!='S');
  if(c == 'R')
    {
      n=saisie(v);
      tri(v,n);
    }
  if(c == 'I' && n >= 0 && n < NMAX )
    {
      printf("Avant insertion on a :\n");
      aff(v,n);
      do
      {
       printf("\nQuel nbr voulez vous inserer : ");
       do
	   {
	    ok = scanf("%d",&val);
	    while( getchar( ) != '\n' );  /* ou fgets(vb,80,stdin)  avec  char vb[81];  */
	   }while(!ok);
       milieu=recherche(v,n,val);
       n=insert(v,n,val,milieu);
       printf("Autre insertion (o/n) ? ");
       rep = tolower(getchar());
	   while( getchar( ) != '\n' );  /* ou fgets(vb,80,stdin)  avec  char vb[81];  */
      }while ( n < NMAX && rep != 'n' );
    }
  if( c == 'S' && n > 0 )
    {
      printf("Avant suppression on a :\n");
      aff(v,n);
      do
      {
       printf("\nQuel nbre voulez vous supprimer : ");
       do
	   {
	    ok = scanf("%d",&val);
	    while( getchar( ) != '\n' );  /* ou fgets(vb,80,stdin)  avec  char vb[81];  */
	   }while(!ok );
       milieu = recherche(v,n,val);
       n = supp(v,n,val,milieu);
       printf("Autre suppression (o/n) ? ");
       rep = tolower(getchar());
	   while( getchar( ) != '\n' );  /* ou fgets(vb,80,stdin)  avec  char vb[81];  */
      }while ( n > 0 && rep != 'n' );
    }
  if(c == 'S' && n == 0 )
    {
	  printf("\nIl n'y a pas d'element dans le vecteur\n");
      printf("Vous ne pouvez donc pas en supprimer.");
      attend_touche();
    }
  if(c == 'I' && n > NMAX )
    {
	  printf("\nLe vecteur est plein...");
      attend_touche();
    }
  }while( c != 'F' );
 return 0;
}
