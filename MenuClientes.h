/* ***
   Biblioteca: MenuClientes.h
   Autor: Islas Isis
   Fecha: 02-Feb-2026
   Objetivo: Crear menu para el modulo clientes
*** */

//Bibliotecas
#ifndef MENU_CLIENTES_H
#define MENU_CLIENTES_H
#include "ModuloClientes.h"

void EjecutarMenuClientes() {

	//Variables
	TpCliente pPrimero = NULL, pUltimo = NULL;
	int eOpcion;
	
	CargarArchivo(&pPrimero, &pUltimo);

	do {
		
		system("cls");
		DibujarMarco(1, 1, 118, 28);
		DibujarMarco(30, 2, 90, 4);
		CentrarTexto(3, "MODULO DE CLIENTES");

		GoToXY(45, 8); printf("1. Agregar Cliente");
		GoToXY(45, 10); printf("2. Consultar Cliente (por ID)");
		GoToXY(45, 12); printf("3. Modificar Cliente");
		GoToXY(45, 14); printf("4. Dar de Baja Cliente");
		GoToXY(45, 16); printf("0. Volver al Menu Principal");

		GoToXY(45, 20); printf("Seleccione una opci%cn: ", 162);
		scanf("%d", &eOpcion);

		switch (eOpcion) {
			
			case 1: 
			
				AgregarCliente(&pPrimero, &pUltimo); 
			
				break;
				
			case 2: 
			
				ConsultarCliente(pPrimero); 
				
				break;
				
			case 3: 
			
				ModificarCliente(pPrimero); 
				break;
				
			case 4: 
			
				DarBajaCliente(&pPrimero, &pUltimo); 
				break;
				
			case 0:
				
				GoToXY(45, 24); printf("Guardando datos...");
				GuardarArchivo(pPrimero);
				Sleep(500);
				
				break;
			
			default:
				
				GoToXY(45, 24); printf("Opcion inv%clida", 160);
				Sleep(500);
				
				break;
				
		}
		
	} while (eOpcion != 0);
	
} //EjecutarMenuClientes

#endif
