#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#define TYPET int

using namespace std;
template <class type>
void Swap(type *a, type *b)
{
    type tmp=*a;
    *a=*b;
    *b=tmp;
}
template <class type>
bool spr(type T[],int str,int size)
{
    int i=str;
    while(i<size-1)
    {
        if(T[i]>T[i+1])
        {
            return false;
        }
        i++;
    }
    return true;
}
template <class type>
int part(type T[],int str, int end)
{
    type x=T[(str+end)/2];
    int i=str,j=end;
    while(1>0)
    {
        while(T[j]>x)
        {
            j--;
        }
        while(T[i]<x)
        {
            i++;
        }
        if(i<j)
        {
            Swap(&T[i],&T[j]);
            i++;
            j--;
        }
        else
        {
            return j;
        }
        
    }
}
template <class type>
void qs(type T[], int str, int end)
{
    int eq=0;

    if(str<end)
    {
        eq=part(T,str,end);
        qs(T,str,eq);
        qs(T,eq+1,end);
    }
}
template <class type>
void Heapm(type T[],int str,int end)
{
    type tmp=T[str];
    while(str<=end/2)
    {
        int k=2*str;
        while(k<end&&T[k]<T[k+1])
        {
            k++;
        }
        if(tmp>=T[k])
        {
            break;
        }
        T[str]=T[k];
        str=k;
    }
    T[str]=tmp;
}
template <class type>
void Heaps(type T[],int str,int end)
{
    for(int i=(end-1)/2;i>=str;i--)
    {
        Heapm(T,i,end-1);
    }
    for(int i=end-1;i>=str;i--)
    {
        Swap(&T[i],&T[str]);
        Heapm(T,str,i-1);
    }
}
template <class type>
void Insert(type T[],int str, int end)
{
    TYPET CV;
    int j;
    for(int i=str+1;i<=end;i++)
    {
        j=i-1;
        CV=T[i];
        while(j>=str && CV<T[j])
        {
            T[j+1]=T[j];
            j--;
        }
        T[j+1]=CV;
    }
}
template <class type>
void intro(type T[],int str,int end,int dept)
{
        if(dept=0)
        {
            Heaps(T,str,end);
        }
        if(end-str<16)
        { 
            Insert(T,str,end);
        }
        else
        {
            int eq;
            eq=part(T,str,end);
            intro(T,str,eq,dept-1);
            intro(T,eq+1,end,dept-1);
        }

}
template <class type>
void intros(type T[],int size)
{
    intro(T,0,size-1,2*log2(size));
}
template <class type>
void Merge(type T[],int str,int eq,int end)
{
    type *TMP = new type[(end-str)+1];
    int i=str,j=eq+1,k=0;
    while(i<=eq && j<=end)
    {
        if(T[j]<T[i])
        {
            TMP[k]=T[j];
            j++;
        }
        else
        {
            TMP[k]=T[i];
            i++;
        }
        k++;
    }
    if(i<=eq)
    {
        while(i<=eq)
        {
            TMP[k]=T[i];
            i++;
            k++;
        }
    }
    else
    {
        while(j<=end)
        {
            TMP[k]=T[j];
            j++;
            k++;
        }
    }
    for(i=0;i<=(end-str);i++)
    {
        T[str+i]=TMP[i];
    }
    delete [] TMP;
}
template <class type>
void MS(type T[],int str, int end)
{
    int eq;
    if(str!=end)
    {
        eq=(str+end)/2;
        MS(T,str,eq);
        MS(T,eq+1,end);
        Merge(T,str,eq,end);
    }

}
template <class type>
type *Create (int size)
{
    return new type[size];
}
template <class type>
void Fill(type T[],int size,float co)
{
    for(int i=0;i<size*co;i++)
 {
     T[i]=i;
 }
  for(int i=size*co+1;i<size;i++)
 {
     T[i]=(rand()%size+size*co+1);
 }
}

int main ()
{
ofstream write("resoults.txt");
write<<"TYPE \t SIZE \t sorted \t time"<<endl;
clock_t beg,fin;
int size;
long double co,timeo;
int S[]={10000,50000,100000,500000,1000000};
float CO[]={0,0.25,0.5,0.75,0.95,0.99,0.997};
int sorted;
 srand( time(NULL));
 for(int c=0;c<7;c++)
 {
     co=CO[c];
     for(int s=0;s<5;s++)
{ 
    size=S[s]; 
    sorted=0;
    beg=clock();
    for(int j=0;j<100;j++)
 {
TYPET *T=Create<TYPET>(size);
Fill(T,size,co);

 qs(T,0,size-1);

if(spr(T,0,size)==true)
{
    sorted++;
}

delete [] T;
}
fin=clock();
timeo=(long double)(fin-beg)/CLOCKS_PER_SEC;
std::cout<<"posrotowano prawidolowo "<<sorted<<" tablic o wielkosci "<<size<<" o pierwszych "<<co*100<<"% posortowanych elementach uzywajac quick sorta w "<<timeo<<" s"<<std::endl;
write<<"Quicksort :"<<size<<"\t"<<co*100<<"\t"<<timeo<<std::endl;
sorted=0;
beg=clock();
for(int j=0;j<100;j++)
 {
TYPET *T=Create<TYPET>(size);
Fill(T,size,co);

 MS(T,0,size-1);
 

if(spr(T,0,size)==true)
{
    sorted++;
}

delete [] T;
}
fin=clock();
timeo=(long double)(fin-beg)/CLOCKS_PER_SEC;
std::cout<<"posrotowano prawidolowo "<<sorted<<" tablic o wielkosci "<<size<<" o pierwszych "<<co*100<<"% posortowanych elementch uzywajac merge sorta w "<<timeo<<" s"<<std::endl;
write<<"Mergesort :"<<size<<"\t"<<co*100<<"\t"<<timeo<<std::endl;
sorted=0;
beg=clock();
for(int j=0;j<100;j++)
 {
TYPET *T=Create<TYPET>(size);
Fill(T,size,co);

 intros(T,size);


if(spr(T,0,size)==true)
{
    sorted++;
}

delete [] T;
}
fin=clock();
timeo=(long double)(fin-beg)/CLOCKS_PER_SEC;
std::cout<<"posrotowano prawidolowo "<<sorted<<" tablic o wielkosci "<<size<<" o pierwszych "<<co*100<<"% posortowanych elementach uzywajac introsorta w "<<timeo<<" s"<<std::endl;
write<<"Introsort :"<<size<<"\t"<<co*100<<"\t"<<timeo<<std::endl;
}
}
 for(int s=0;s<5;s++)
{ 
    size=S[s]; 
    sorted=0;
    beg=clock();
    for(int j=0;j<100;j++)
 {

TYPET *T=Create<TYPET>(size);
 for(int i=0;i<size;i++)
 {
     T[i]=size-i;
 }

 qs(T,0,size-1);

if(spr(T,0,size)==true)
{
    sorted++;
}

delete [] T;
}
fin=clock();
timeo=(long double)(fin-beg)/CLOCKS_PER_SEC;
std::cout<<"posrotowano prawidolowo "<<sorted<<" tablic o wielkosci "<<size<<" o odwrotnie posortowanych elementach uzywajac quick sorta w "<<timeo<<" s"<<std::endl;
write<<"Quicksort :"<<size<<"\t rev \t"<<timeo<<std::endl;
sorted=0;
beg=clock();
for(int j=0;j<100;j++)
 {
TYPET *T=Create<TYPET>(size);
 for(int i=0;i<size;i++)
 {
     T[i]=size-i;
 }

 MS(T,0,size-1);

if(spr(T,0,size)==true)
{
    sorted++;
}

delete [] T;
}
fin=clock();
timeo=(long double)(fin-beg)/CLOCKS_PER_SEC;
std::cout<<"posrotowano prawidolowo "<<sorted<<" tablic o wielkosci "<<size<<" o odwrotnie posortowanych elementch uzywajac merge sorta w "<<timeo<<" s"<<std::endl;
write<<"Mergesort :"<<size<<"\t rev \t"<<timeo<<std::endl;
sorted=0;
beg=clock();
for(int j=0;j<100;j++)
 {
TYPET *T=Create<TYPET>(size);
 for(int i=0;i<size;i++)
 {
     T[i]=size-i;
 }

 intros(T,size);

if(spr(T,0,size)==true)
{
    sorted++;
}

delete [] T;
}
fin=clock();
timeo=(long double)(fin-beg)/CLOCKS_PER_SEC;
std::cout<<"posrotowano prawidolowo "<<sorted<<" tablic o wielkosci "<<size<<" o odwrotnie posortowanych elementach uzywajac introsorta w "<<timeo<<" s"<<std::endl;
write<<"Introsort :"<<size<<"\t rev \t"<<timeo<<std::endl;
}
 return 0;
}