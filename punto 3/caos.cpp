

#include "iostream"
#include "math.h"
#include "fstream"
using namespace std;

double euler=0.1;double it[4];


double dev(double q1, double q2,double p1, double p2)
{
	

	it[0] = p1;it[1] = p2;it[2] =  -2.0*q1/pow( 4.0*pow(q1,2) + pow(euler,2) ,1.5);double e = pow(euler,2)/4.0;

	it[3] = q1-q2/pow( pow(q1-q2,2)+e, 1.5 ) - (q1+q2)/pow( pow(q1+q2,2)+e, 1.5 );
}


int main()
{
	int k;int i;int j;

	int H =  1 + 3000;double delta = 0.006;int R =  H/delta;double a=1.0/(2.0*sqrt(2.0));

	
	cout << delta << endl << R << endl << euler << endl << a << endl;

	float q1[R];float q2[R];float p1[R];float p2[R];

	q1[0] = 1.0/(2.0*sqrt(2.0));q2[0] = -1.0/(2.0*sqrt(2.0));
	p1[0] = 0.0; p2[0] = 0.0;
	

	double var1[4];double var2[4];double var3[4]; double var4[4];

	double q = 0;
        double ee = 4;

	for (i= q; i < ee; ++i){ 
		it[i] = 0.0;
		var1[i] ,var2[i], var3[i],var4[i] = 0.0;}


	
	fstream caos_data("caos_data.txt");

	for (i = q; i < R-1; ++i){
	
	
		
		dev(q1[i], q2[i], p1[i], p2[i]);
		
		for (j = q; j <ee ; ++j){
			var1[j] = it[j];	}

	float m= q1[i]+0.5*delta*var1[0];float r= q2[i]+0.5*delta*var1[1];float c =p1[i]+0.5*delta*var1[2];float z = p2[i]+0.5*delta*var1[2];

float mm=q1[i]+0.5*delta*var2[0];float rr=q2[i]+0.5*delta*var2[1];float cc=p1[i]+0.5*delta*var2[2];float zz=p2[i]+0.5*delta*var2[3];

float mmm=q1[i]+delta*var3[0];float rrr=q2[i]+delta*var3[1];float ccc=p1[i]+delta*var3[2];float zzz=p2[i]+delta*var3[3];


		
		dev(m, r, c, z);		
		
		for (j = q; j < ee; ++j){
		var2[j] =it[j];	}

		dev(mm, rr, cc, zz);		
		
		for (j = q; j < ee; ++j){
			var3[j] = it[j];}

		dev(mmm, rrr, ccc, zzz);		

		for (j = q; j < ee; ++j){
			var3[j] =it[j];	}

double A=delta/6.0;double B= var1[0] + 2.0*var2[0] + 2.0*var3[0] + var4[0];double C= var1[1] + 2.0*var2[1] + 2.0*var3[1] + var4[1];double D= var1[2] + 2.0*var2[2] + 2.0*var3[2] + var4[2];double E= var1[3] + 2.0*var2[3] + 2.0*var3[3] + var4[3]; 

		
		q1[i+1]	= q1[i] + A*(B);q2[i+1]	= q2[i] + A*(C);p1[i+1]	= p1[i] + A*(D);p2[i+1]	= p2[i] + A*(E);

		
		if (q1[i]>q & q1[i+1]<q){
			caos_data << q2[i] << " " << p2[i] << endl;}
		cout << q1[i] << " " << q2[i] << " " << p1[i] << " " << p2[i] << endl;}

	return 0;
}
