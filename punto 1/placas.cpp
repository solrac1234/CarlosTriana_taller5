#include "iostream"
#include "fstream"
using namespace std;


int main()
{
	int iteraciones;
	int n = 512;
	float l = 2.0;
	

	// Encontrar indices en donde ubicar las placas
	int placa_jx0 = int( (5/2.0-l/2.0)/5*float(512) );
	int placa_jxf = int( (5/2.0+l/2.0)/5*float(512) );
	int placa_iy0 = int( (5/2.0-(1.0/2.0))/5*float(512) );
	int placa_iyf = int( (5/2.0+(1.0/2.0))/5*float(512) );


	int i;
	int j;

	// Crear matrices de Potencial y ubicar el Potencial de las placas
	float Pot[n][n];
	float Pot1[n][n];
	float Pot2[n][n];

	// Crear arreglos para campo electrico
	float cElectrico_x[n][n];
	float cElectrico_y[n][n];

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			Pot[i][j] = 0.0; // Inicializar todo en cero
			Pot1[i][j] = 0.0; 
			Pot2[i][j] = 0.0; 
			cElectrico_x[i][j] = 0.0; 
			cElectrico_y[i][j] = 0.0; 
		}
	}

	for (j = placa_jx0; j < placa_jxf+1; j++)
	{
		Pot[placa_iy0][j] = 50;
		Pot[placa_iyf][j] = -50;

		Pot1[placa_iy0][j] = 50;
		Pot1[placa_iyf][j] = -50;

		Pot2[placa_iy0][j] = 50;
		Pot2[placa_iyf][j] = -50;
	}


	//cout << placa_iy0 << "\n" << placa_iyf << "\n" << placa_jx0 << "\n" << placa_jxf << "\n";

	int count = 2*n*n/1000;
	// Relajar sistema
	for (iteraciones = 0; iteraciones < count; iteraciones++)
	{
		//cout << "\n" << iteraciones << "\n";
		for (i = 1; i < n-1; i++)
		{
			for (j = 1; j < n-1; j++)
			{
				//cout << (placa_jxf<j) << " ";
				//if ( (i!=placa_iy0 || i!=placa_iyf)  &&  (j<placa_jx0 || j>placa_jxf))
				if ( (i!=placa_iy0 & i!=placa_iyf))
				{// no este en y 
					Pot2[i][j] = (1.0/4.0)*(Pot1[i][j+1] + Pot1[i][j-1] + Pot1[i+1][j] + Pot1[i-1][j]);
				}else if ( j<placa_jx0 || j>placa_jxf )
				{
					Pot2[i][j] = (1.0/4.0)*(Pot1[i][j+1] + Pot1[i][j-1] + Pot1[i+1][j] + Pot1[i-1][j]);
				}
			}
		}

		// reasignar valores
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				Pot1[i][j] = Pot2[i][j];
			}
		}

		// reasignar valores
//		for (i = 0; i < n; i++)
//		{
//			for (j = 0; j < n; j++)
//			{
//				Pot1[i][j] = Pot[i][j];
//			}
//		}


		// En la ultima iteracion, calcular el campo electrico
		if (iteraciones==count-1)
		{ // ultima iteracion
			for (i = 1; i < n-1; i++)
			{
				for (j = 1; j < n-1; j++)
				{ // nodos centrales
					cElectrico_x[i][j] = ( Pot2[i][j+1]-Pot2[i][j-1] )/(2.0*5.0/float(n-1.0));
					cElectrico_y[i][j] = ( Pot2[i+1][j]-Pot2[i-1][j] )/(2.0*5.0/float(n-1.0));
				}

				// calcular campo en los bordes
				cElectrico_x[0][i] = 0.0; // no hay cambios horizontales en el borde superior
				cElectrico_x[n-1][i] = 0.0; // no hay cambios horizontales en el borde inferior
				cElectrico_x[i][0] = (Pot2[i][1]-Pot2[i][0])/(5.0/float(n-1.0)); // derivada horizontal en borde izquierdo
				cElectrico_x[i][n-1] = (Pot2[i][n-1]-Pot2[i][n-2])/(5.0/float(n-1.0)); // derivada horizontal en borde derecho

				// calcular campo en los bordes
				cElectrico_y[0][i] = (Pot2[1][i]-Pot2[0][i])/(5.0/float(n-1.0)); // cambios vertical en el borde superior
				cElectrico_y[n-1][i] = (Pot2[n-1][i]-Pot2[n-2][i])/(5.0/float(n-1.0)); // cambios vertical en el borde inferior
				cElectrico_y[i][0] = 0.0; // derivada vertical en borde izquierdo
				cElectrico_y[i][n-1] = 0.0; // derivada vertical en borde derecho
			}

			// Esquinas
			cElectrico_x[0][0] = cElectrico_x[1][1];
			cElectrico_x[0][n-1] = cElectrico_x[1][n-2];
			cElectrico_x[n-1][n-1] = cElectrico_x[n-2][n-2];
			cElectrico_x[n-1][0] = cElectrico_x[n-2][1];

			cElectrico_y[0][0] = cElectrico_y[1][1];
			cElectrico_y[0][n-1] = cElectrico_y[1][n-2];
			cElectrico_y[n-1][n-1] = cElectrico_y[n-2][n-2];
			cElectrico_y[n-1][0] = cElectrico_y[n-2][1];
		}

	}


	// Exportar datos en consola
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << Pot2[i][j] << " "; // Imprimir datos
		}
		cout << "\n"; // impirmir nueva linea
	}	

	
	// Escribir archivo con los datos del campo electrico
	ofstream cElectrico("cElectrico.txt");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cElectrico << cElectrico_x[i][j] << " "; // Imprimir datos
		}

		for (j = 0; j < n; j++)
		{
			cElectrico << cElectrico_y[i][j] << " "; // Imprimir datos
		}
		cElectrico << "\n"; // impirmir nueva linea
	}	



	return 0;
}
