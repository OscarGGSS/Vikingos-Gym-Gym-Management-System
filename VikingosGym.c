/* ***
   Programa: VikingosGym.c
   Autor: Oscar 
   Fecha: 02-Feb-2026
   Objetivo: Programa principal que llama a los menus (modulos)
*** */

#include <stdio.h>
#include <windows.h>
#include "Interfaz.h"
#include "Tipos.h"
#include "MenuClientes.h"
#include "MenuEntrenadores.h"
#include "MenuMembresias.h"   
#include "MenuSuplementos.h"  

int main() {
	int eOpcion;
	
	ConfigurarConsola(120, 30);
	Color(0, 11);

	do {
		system("cls");
		DibujarMarco(1, 1, 118, 28);      
		DibujarMarco(30, 2, 90, 6);       
		CentrarTexto(4, "SISTEMA VIKINGOS GYM");
		
		GoToXY(45, 10); printf("1. Gestion de Clientes");
		GoToXY(45, 12); printf("2. Gestion de Entrenadores");
		GoToXY(45, 14); printf("3. Gestion de Membresias");
		GoToXY(45, 16); printf("4. Gestion de Suplementos");
		GoToXY(45, 20); printf("0. Salir del Sistema");
		
		GoToXY(45, 24); printf("Seleccione un Modulo: ");
		scanf("%d", &eOpcion);
		
		switch(eOpcion) {
			
			case 1:
				EjecutarMenuClientes();
				break;
				
			case 2:
				EjecutarMenuEntrenadores();
				break;
				
			case 3:
				EjecutarMenuMembresias(); 
				break;
				
			case 4:
				EjecutarMenuSuplementos(); 
				break;
				
			case 0:
				GoToXY(45, 26); printf("Cerrando sistema...");
				Sleep(1000);
				break;
				
			default:
				GoToXY(45, 26); printf("Opcion invalida.");
				Sleep(500);
		}
		
	} while(eOpcion != 0);
	
	return 0;
}
