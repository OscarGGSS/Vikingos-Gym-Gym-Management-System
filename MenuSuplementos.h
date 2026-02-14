/* ***
   Biblioteca: MenuSuplementos.h
   Autor: Jennifer Garcia, Oscar
   Fecha: 02-Feb-2026
   Objetivo: crear menu de suplementos para el manejo del modulo.
*** */
#ifndef MENU_SUPLEMENTOS_H
#define MENU_SUPLEMENTOS_H
#include "ModuloSuplementos.h"

void EjecutarMenuSuplementos() {
	
	//Variables
    int op, idAux;
    CargarArchivoSuplementos(&pListaSup);

    do {
    	
        system("cls"); DibujarMarco(1, 1, 118, 28); DibujarMarco(30, 2, 90, 4);
        CentrarTexto(3, "MODULO DE SUPLEMENTOS");
        GoToXY(45, 8);  printf("1. Alta Suplemento");
        GoToXY(45, 10); printf("2. Vender Suplemento");
        GoToXY(45, 12); printf("3. Ver Inventario");
        GoToXY(45, 14); printf("0. Volver");
        
        GoToXY(45, 18); printf("Opcion: "); scanf("%d", &op);
        
        switch(op) {
        	
            case 1: AltaSuplemento(&pListaSup); 
			
			break;
            
            case 2: VenderSuplemento(pListaSup); 
			
			break;
            
            case 3: Inventario(pListaSup); 
			
			break;
            
            case 0: GoToXY(45, 22); printf("Guardando..."); GuardarArchivoSuplementos(pListaSup); Sleep(500); 
			
			break;
            
        }
        
    } while (op != 0);
    
} //EjecutarMenuSuplementos
#endif
