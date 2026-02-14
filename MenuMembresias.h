/* ***
   Biblioteca: MenuMembresias.h
   Autor: Jennifer Garcia, Oscar
   Fecha: 02-Feb-2026
   Objetivo: crear menu para el modulo membresias.
   
*** */

#ifndef MENU_MEMBRESIAS_H
#define MENU_MEMBRESIAS_H
#include "ModuloMembresias.h"

void EjecutarMenuMembresias() {
    
    //Variables
    pPrimeroM pListaMem = NULL; 
    int op, idAux;
    
    CargarArchivoMembresias(&pListaMem);

    do {
    	
        system("cls");
        DibujarMarco(1, 1, 118, 28);
        DibujarMarco(30, 2, 90, 4);
        CentrarTexto(3, "MODULO DE MEMBRESIAS");

        GoToXY(45, 8);  printf("1. Alta Membresia");
        GoToXY(45, 10); printf("2. Baja Membresia");
        GoToXY(45, 12); printf("3. Modificar Costo");
        GoToXY(45, 14); printf("4. Listado General");
        GoToXY(45, 16); printf("0. Volver");
        
        GoToXY(45, 20); printf("Opcion: "); scanf("%d", &op);
        
        switch (op) {
        	
            case 1: 
            
                AltaMembresia(&pListaMem); 
                break;
                
            case 2: 
            
                system("cls"); DibujarMarco(2, 1, 117, 28);
                GoToXY(40, 10); printf("ID a eliminar: "); scanf("%d", &idAux); 
                BajaMembresia(&pListaMem, idAux); 
                
                break;
                
            case 3: 
            
                system("cls"); DibujarMarco(2, 1, 117, 28);
                GoToXY(40, 10); printf("ID a modificar: "); scanf("%d", &idAux); 
                ModificarMembresia(pListaMem, idAux); 
                
                break;
                
            case 4: 
            
                ListarMembresias(pListaMem); 
                
                break;
                
            case 0: 
            
                GoToXY(45, 24); printf("Guardando..."); 
                GuardarArchivoMembresias(pListaMem);
                Sleep(500); 
                
                break;
                
            default:
            	
                GoToXY(45, 24); printf("Opcion inv%clida", 160);
                Sleep(500);
                
        }
        
    } while (op != 0);
    
}

#endif
