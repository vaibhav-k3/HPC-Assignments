#include<iostream>
#include<omp.h>
#include<stdlib.h>
using namespace std;
void disp1d( int a[], int n)
{
	for( int i = 0 ;i < n ; i++)
	{
		cout<<a[i]<<" ";
	}		
}
void disp2d( int a[][100] , int n , int m)
{
	for(int i = 0; i< n; i++)
	{
		for(int j = 0 ; j< m ; j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
}
void matmul(int a[][100] , int b[][100] , int n1 , int m1 , int n2 , int m2)
{
	int c[100][100];
	if(m1 == n2)
	{
		for(int i = 0 ; i < n1 ; i++)
		{
			for(int j = 0 ; j<m2 ; j++)
			{	
				c[i][j] = 0 ;
				#pragma omp parallel for
				for(int k = 0 ; k<n2  ; k++)
				{
					c[i][j] = c[i][j] + a[i][k]*b[k][j];
				}
			}
		}
		disp2d(c , n1 , m2);
	}
	else
	{
		cout<<"cannot multiply matrix \n";
	}
}
void vecmatmul(int a[][100] , int b[][1] , int n1 , int m1 , int n2 , int m2)
{
	int c[100][100];
	if(m1 == n2)
	{
		for(int i = 0 ; i < n1 ; i++)
		{
			for(int j = 0 ; j<m2 ; j++)
			{	
				c[i][j] = 0 ;
				#pragma omp parallel for
				for(int k = 0 ; k<n2  ; k++)
				{
					c[i][j] = c[i][j] + a[i][k]*b[k][j];
				}
			}
		}
		disp2d(c , n1 , m2);
	}
	else
	{
		cout<<"cannot multiply matrix \n";
	}
}
void add(int a[] , int b[] , int n)
{
	int c[n];
	#pragma omp parallel for
	for(int i = 0 ;i < n ;i++)
	{
		c[i] = a[i] + b[i];
	}
	disp1d(c , n);
}
int main()
{
	int a_2d[100][100] , b_2d[100][100] , i_2d[100][100] = {
	{1 ,0 , 0},
	{0 ,1 ,0},
	{0 , 0 ,1}};
	int a_1d[50] , b_1d[50];
	int vector[100][1];
	//initialize randomnly ; 
	for(int i = 0 ; i <10; i++)
	{
		for(int j = 0 ; j < 10 ; j++)
		{
			a_2d[i][j] = rand()%10;
			b_2d[i][j] = rand()%10;
		}
	}
	for(int i = 0 ; i<10 ;i++)
	{
		a_1d[i] = rand()%10;
		b_1d[i] = rand()%10;
		vector[i][1] = rand()%10;
	}
	cout<<"\n1st input matrix"<<endl ; 
		disp2d(a_2d ,10,10);
		cout<<"\n2nd input matrix"<<endl ; 
		disp2d(b_2d ,10 ,10);
		cout<<"\n1st input vector"<<endl ; 
		disp1d(a_1d , 10 );
		cout<<endl;
		cout<<"\n2nd input vector"<<endl ; 
		disp1d(b_1d , 10 );
		cout<<endl;
	int choice = 0 ; 
	do{
		
		
		cout<<"\n1 . parralel vector addition "<<endl;
		cout<<"2 . parralel matrix X matrix multiplication"<<endl;
		cout<<"3 . parralel matrix Vector multiplication"<<endl;
		cout<<" enter -1 to exit "<<endl;
		cin>>choice ; 
		switch(choice)
		{
			case 1 :
					add(a_1d , b_1d , 10);
					break ; 
			case 2 :
					matmul(a_2d ,b_2d , 10,10,10,10);
					break ; 
			case 3 :
					vecmatmul(a_2d , vector , 10 , 10 ,10 ,1);
					break ; 
			case -1:
					cout<<"exiting"<<endl ;
					break ;
			default:
					cout<<" invalid Selection"<<endl;
					
		}
	
	}while(choice!= -1 );
	
	/*
	disp2d(a_2d ,100,100);
	cout<<endl;
	disp2d(b_2d ,100 ,100);
	cout<<endl;
	matmul(a_2d ,b_2d , 100,100,100,100);
	
	disp1d(a_1d , 50 );
	cout<<endl;
	disp1d(b_1d , 50 );
	cout<<endl;
	cout<<" Vector addition " <<endl;
	add(a_1d , b_1d , 50);
	
	cout<<endl;
	cout<<"vector matrix multiplication"<<endl;
	vecmatmul(a_2d , vector , 100 , 100 ,100 ,1);*/
	return 0 ; 
}
