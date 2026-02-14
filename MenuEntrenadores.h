/* ***
   Biblioteca: MenuEntrenadores.h
   Autor: Oscar
   Fecha: 02-Feb-2026
   Objetivo: Crear menu para el modulo entrenadores
*** */

#ifndef MENU_ENTRENADORES_H
#define MENU_ENTRENADORES_H
#include "ModuloEntrenadores.h"

void EjecutarMenuEntrenadores() {
	
	//Variables
	TpNodoEntrenador pListaEntrenadores = NULL;
	int eOpcion;
	TsCadenaEntrenador sIdTemporal;
	TrEntrenador rEntrenadorTemporal;
	
	CargarArchivoEntrenador(&pListaEntrenadores);

	do {
		
		PlantillaBaseEntrenador("MODULO DE ENTRENADORES");
		
		GoToXY(45, 8);  printf("1. Alta de Entrenador");
		GoToXY(45, 10); printf("2. Baja de Entrenador");
		GoToXY(45, 12); printf("3. Modificar Entrenador");
		GoToXY(45, 14); printf("4. Consultar Informacion");
		GoToXY(45, 16); printf("5. Consultar Ventas");
		GoToXY(45, 18); printf("6. Listar Entrenadores");
		GoToXY(45, 20); printf("0. Volver al Menu Principal");
		
		GoToXY(45, 24); printf("Selecciona: ");
		scanf("%d", &eOpcion);

		switch(eOpcion){
			
			case 1:
				
				rEntrenadorTemporal = LeerDatosEntrenador();
				AltaEntrenador(&pListaEntrenadores, rEntrenadorTemporal);
				system("pause"); 
				
				break;
				
			case 2:
				
				PlantillaBaseEntrenador("BAJA DE ENTRENADOR");
				GoToXY(40, 10); printf("ID a eliminar: "); fflush(stdin); gets(sIdTemporal);
				BajaEntrenador(&pListaEntrenadores, sIdTemporal);
				system("pause"); 
				
				break;
				
				
			case 3:
				
				ModificarEntrenador(&pListaEntrenadores);
				system("pause"); 
				
				break;
				
			case 4:
				
				PlantillaBaseEntrenador("CONSULTAR INFORMACION");
				GoToXY(40, 10); printf("ID a consultar: "); fflush(stdin); gets(sIdTemporal);
				ConsultarEntrenador(pListaEntrenadores, sIdTemporal);
				system("pause"); 
				
				break;
				
			case 5:
				
				PlantillaBaseEntrenador("CONSULTAR VENTAS");
				GoToXY(40, 10); printf("ID para ventas: "); fflush(stdin); gets(sIdTemporal);
				ConsultarVentasEntrenador(pListaEntrenadores, sIdTemporal);
				system("pause"); 
				
				break;
				
			case 6:
				
				ListarEntrenadores(pListaEntrenadores);
				system("pause"); 
				
				break;
				
			case 0: 
			
				GoToXY(40, 26); printf("Guardando cambios...");
				GuardarArchivoEntrenador(pListaEntrenadores);
				Sleep(500);
				
				break;
				
			default: GoToXY(40, 26); printf("Opcion inv%clida", 160);
			system("pause");
		}
	} while(eOpcion != 0);

	LiberarListaEntrenador(pListaEntrenadores);
}

#endif
