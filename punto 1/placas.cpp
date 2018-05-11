#include "iostream"
#include "fstream"
using namespace std;

int main()
{
	int iteraciones;
	int m = 512;

	// Encontrar indices en donde ubicar las placas
	int placa_jx0 = int(1.5/5.0*float(m));
	int placa_jxf = int(3.5/5.0*float(m));
	int placa_iy0 = int(2.0/5.0*float(m));
	int placa_iyf = int(3.0/5.0*float(m));


	int i;
	int j;

	// Crear matrices de Potencial y ubicar el Potencial de las placas
	float Pot[m][m];
	float Pot1[m][m];
	float Pot2[m][m];

	// Crear arreglos para campo electrico
	float cElectrico_x[m][m];
	float cElectrico_y[m][m];

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			Pot[i][j] = 0.0; // Inicializar todo en cero
			Pot1[i][j] = 0.0; 
			Pot2[i][j] = 0.0; 
			cElectrico_x[i][j] = 0.0; 
			cElectrico_y[i][j] = 0.0; 
		}
	}

	// En las posiciones de las placas ubicar V0/2 y -V0/2
	for (j = placa_jx0; j < placa_jxf+1; j++)
	{
		Pot[placa_iy0][j] = 50.0;
		Pot[placa_iyf][j] = -50.0;

		Pot1[placa_iy0][j] = 50.0;
		Pot1[placa_iyf][j] = -50.0;

		Pot2[placa_iy0][j] = 50.0;
		Pot2[placa_iyf][j] = -50.0;
	}


	//cout << placa_iy0 << "\n" << placa_iyf << "\n" << placa_jx0 << "\n" << placa_jxf << "\n";

	int count = 2*m*m/1000;
	// Relajar sistema
	for (iteraciones = 0; iteraciones < count; iteraciones++)
	{
		//cout << "\n" << iteraciones << "\n";
		for (i = 1; i < m-1; i++)
		{
			for (j = 1; j < m-1; j++)
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
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < m; j++)
			{
				Pot1[i][j] = Pot2[i][j];
			}
		}

		// reasignar valores
//		for (i = 0; i < m; i++)
//		{
//			for (j = 0; j < m; j++)
//			{
//				Pot1[i][j] = Pot[i][j];
//			}
//		}


		// En la ultima iteracion, calcular el campo electrico
		if (iteraciones==count-1)
		{ // ultima iteracion
			for (i = 1; i < m-1; i++)
			{
				for (j = 1; j < m-1; j++)
				{ // nodos centrales
					cElectrico_x[i][j] = ( Pot2[i][j+1]-Pot2[i][j-1] )/(10.0/float(m-1.0));
					cElectrico_y[i][j] = ( Pot2[i+1][j]-Pot2[i-1][j] )/(10.0/float(m-1.0));
				}

				// calcular campo en los bordes
				cElectrico_x[0][i] = 0.0; // no hay cambios horizontales en el borde superior
				cElectrico_x[m-1][i] = 0.0; // no hay cambios horizontales en el borde inferior

				cElectrico_x[i][0] = (Pot2[i][1]-Pot2[i][0])/(5.0/float(m-1.0)); // derivada horizontal en borde izquierdo
				cElectrico_x[i][m-1] = (Pot2[i][m-1]-Pot2[i][m-2])/(5.0/float(m-1.0)); // derivada horizontal en borde derecho

				// calcular campo en los bordes
				cElectrico_y[0][i] = (Pot2[1][i]-Pot2[0][i])/(5.0/float(m-1.0)); // cambios vertical en el borde superior
				cElectrico_y[m-1][i] = (Pot2[m-1][i]-Pot2[m-2][i])/(5.0/float(m-1.0)); // cambios vertical en el borde inferior

				cElectrico_y[i][0] = 0.0; // derivada vertical en borde izquierdo
				cElectrico_y[i][m-1] = 0.0; // derivada vertical en borde derecho
			}

			// Esquinas
			cElectrico_x[0][0] = cElectrico_x[1][1];
			cElectrico_x[0][m-1] = cElectrico_x[1][m-2];

			cElectrico_x[m-1][m-1] = cElectrico_x[m-2][m-2];
			cElectrico_x[m-1][0] = cElectrico_x[m-2][1];

			cElectrico_y[0][0] = cElectrico_y[1][1];
			cElectrico_y[0][m-1] = cElectrico_y[1][m-2];

			cElectrico_y[m-1][m-1] = cElectrico_y[m-2][m-2];
			cElectrico_y[m-1][0] = cElectrico_y[m-2][1];
		}

	}


	// Exportar datos en consola
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			cout << Pot2[i][j] << " "; // Imprimir datos
		}
		cout << "\n"; // impirmir nueva linea
	}	

	
	// Escribir archivo con los datos del campo electrico
	ofstream cElectrico("cElectrico.txt");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			cElectrico << cElectrico_x[i][j] << " "; // Imprimir datos
		}

		for (j = 0; j < m; j++)
		{
			cElectrico << cElectrico_y[i][j] << " "; // Imprimir datos
		}
		cElectrico << "\n"; // impirmir nueva linea
	}	



	return 0;
}
