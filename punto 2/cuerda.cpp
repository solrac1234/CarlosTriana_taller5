#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

double x[20]; double cp[20]; double cpr[20]; double cf[20];

FILE *close;
const int n = 20;
const double L = 100; const double deltax = L/19; const double c = 2; const double Timeframe=(L*6); const double deltat=sqrt(0.9*pow(deltax,2)/(pow(c,2))); const int nt = Timeframe/sqrt(0.9*pow(deltax,2)/(pow(c,2)));



// asginar valores a la variable global x

int variable()
{
int B; x[0] = 0.0;
	for (B = 1; B < n; ++B){
		int aa = x[B-1] + deltax;
		x[B] = aa;}

	return 0;}


// avanzar en el tiempo, es decir que el futuro se convierte en el presente y el presente se convierte en el pasado


int renew()
{
int i;
	for (i = 1; i < n-1; ++i){
		cpr[i] = cf[i]; cp[i] = cpr[i];}

	return 0;}


// Calcular la perturbacion de la cuerda en el futuro a  partir de la discretizacion de diferencias finitas

int step()
{
int i;
	for (i = 1; i < n-1; ++i){
	cf[i] = -1*cp[i] + 2*cpr[i] + (1.2/2)*( cpr[i-1] - 2*cpr[i] + cpr[i+1] );}

	return 0;}

// Inicializar el presente igual que el pasado

int primeC()
{

	int j;
	int comp = (4/5)*L;
	int res = (5/4)*x[j]/L;
	for (j = 0; j < n; ++j){
		if ( x[j] < comp){
			cp[j] = res;}
		if (x[j]>comp){
			cp[j] = 5-5*x[j]/L;}}

	for (j = 0; j < n; ++j){
		cpr[j] = cp[j]; cf[j] = 0.0 ;}	
 
	return 0;}

// Imprimir tiempo futuro en archivo de salida

int print(double arg){

	int k;
	
	for (k = 1; k < n-1; ++k){
		fprintf(close, "%f ", cpr[k]);}
		fprintf(close, "\n");

	cout << "printing " << arg << endl;

	return 0;}


int main(int argc, char const *argv[])
{

	int k;
	k = variable();
	if (k==0){
		cout << "generated vector" << endl;}

	k = primeC();
	if (k==0){
		cout << "prime c" << endl;}



	

int a;
	close = fopen("cuerda.txt", "w");

	for (k = 0; k < nt+2; ++k){
		a = step();a = renew();a = print(double(k*sqrt(0.9*pow(deltax,2)/(pow(c,2)))));}
	
	fclose(close);
	
	return 0;
}

