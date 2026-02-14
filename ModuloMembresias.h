/* ***
   Biblioteca: MenuMembresias.h
   Autor: Jennifer Garcia, Oscar e Isis
   Fecha: 02-Feb-2026
   Objetivo: Crear modulo que logre gestionar membresias junto con el modulo de clientes.
*** */

#ifndef MODULO_MEMBRESIAS_H
#define MODULO_MEMBRESIAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tipos.h"
#include "Interfaz.h"

// Prototipos
int GenerarIDMembresia(pPrimeroM);
void AltaMembresia(pPrimeroM *);
void BajaMembresia(pPrimeroM *, int);
void ModificarMembresia(pPrimeroM, int);
void ListarMembresias(pPrimeroM);
void GuardarArchivoMembresias(pPrimeroM);
void CargarArchivoMembresias(pPrimeroM *);

int ExisteClienteEnArchivo(int idCliente) {
	
    FILE *f = fopen("clientes.dat", "rb");
    TrCliente temp;
    
    if (!f) return 0;
    
    while(fread(&temp, sizeof(TrCliente), 1, f)) {
    	
        if(temp.eId == idCliente) {
		 
			fclose(f); return 1; 
			
		}
		
    }
    
    fclose(f);
    return 0;
    
} //ExisteClienteEnArchivo

int ExisteEntrenadorEnArchivo(char *idEntrenador) {
	
	//Variables
    FILE *f = fopen("Entrenadores.dat", "rb");
    TrEntrenador temp;
    
    if (!f) return 0;
    
    while(fread(&temp, sizeof(TrEntrenador), 1, f)) {
    	
        if(strcmp(temp.sId, idEntrenador) == 0) { 
			
			fclose(f); return 1; 
			
			}
        
    }
    
    fclose(f);
    return 0;
    
} //ExisteEntrenadorEnArchivo


int GenerarIDMembresia(pPrimeroM pLista) {
	
    if (pLista == NULL) return 1;
    
    int contador = 0;
    TrNodo *temp = pLista;
    
    while (temp != NULL) {
        
        contador++;
        temp = temp->pSiguiente;
    }
    
    return contador + 1;
    
} //GenerarIDMembresia

void AltaMembresia(pPrimeroM *pInicio) {
	
    TrNodo *pNuevo = (TrNodo*)malloc(sizeof(TrNodo));
    
    //Variables
    int idC;
    char idE[50];
    
    if (pNuevo == NULL) return;

    system("cls");
    DibujarMarco(2, 1, 117, 28);
    DibujarMarco(30, 8, 90, 22);
    CentrarTexto(10, "ALTA DE MEMBRESIA");

    GoToXY(40, 12); printf("ID Cliente: "); 
	scanf("%d", &idC);
	
    if (!ExisteClienteEnArchivo(idC)) {
    	
        GoToXY(40, 25); 
		printf("ERROR: El Cliente ID %d no existe.", idC);
        system("pause");
        free(pNuevo);
        
        return;
        
    }
    
    pNuevo->datos.eIDCliente = idC;
    
    GoToXY(40, 13); printf("ID Entrenador (Vendedor): "); 
	fflush(stdin); 
	gets(idE);
	
    if (!ExisteEntrenadorEnArchivo(idE)) {
    	
        GoToXY(40, 25); printf("ERROR: El Entrenador ID %s no existe.", idE);
        system("pause");
        free(pNuevo);
        
        return;
        
    }
    
    strcpy(pNuevo->datos.sIDEntrenador, idE);

    GoToXY(40, 15); printf("Tipo (Mensual/Anual): "); 
	fflush(stdin); gets(pNuevo->datos.cTipoMembresia);
    GoToXY(40, 17);
    
	printf("Costo: "); 
	scanf("%f", &pNuevo->datos.fCosto);
    
    GoToXY(40, 19); printf("Inicio (dd mm aaaa): ");
    scanf("%d %d %d", &pNuevo->datos.rFechaInicio.eDia, &pNuevo->datos.rFechaInicio.eMes, &pNuevo->datos.rFechaInicio.eAnio);
    
    GoToXY(40, 21); printf("Vence (dd mm aaaa): ");
    scanf("%d %d %d", &pNuevo->datos.rFechaVencimiento.eDia, &pNuevo->datos.rFechaVencimiento.eMes, &pNuevo->datos.rFechaVencimiento.eAnio);
    
    pNuevo->datos.eIDMembresia = GenerarIDMembresia(*pInicio);
    strcpy(pNuevo->datos.cEstatus, "Activa");
    
    pNuevo->pSiguiente = *pInicio;
    *pInicio = pNuevo;
    
    GoToXY(40, 25); printf("Membresia generada ID: %d", pNuevo->datos.eIDMembresia);
    system("pause");
    
} //AltaMembresia

void BajaMembresia(pPrimeroM *pInicio, int id) {
	
    TrNodo *pAct = *pInicio, *pAnt = NULL;
    
    while (pAct != NULL && pAct->datos.eIDMembresia != id) {
    	
        pAnt = pAct; pAct = pAct->pSiguiente;
        
    }
    
    if (pAct == NULL) { 
    
        GoToXY(40, 14); printf("No encontrado.");
        system("pause"); 
		return; 
        
    }
    
    if (pAnt == NULL) *pInicio = pAct->pSiguiente;
    
    else pAnt->pSiguiente = pAct->pSiguiente;
    free(pAct);
    
    GoToXY(40, 14); printf("Membresia dada de baja.");
    
    system("pause");
    
} //BajaMembresia

void ModificarMembresia(pPrimeroM pLista, int id) {
	
    TrNodo *temp = pLista;
    
    while (temp != NULL && temp->datos.eIDMembresia != id) temp = temp->pSiguiente;
    
    if (temp == NULL) { 
    
        GoToXY(40, 14); printf("ID No existe.");
        system("pause"); 
		return; 
        
    }
    
    GoToXY(40, 14); printf("Nuevo Costo: "); scanf("%f", &temp->datos.fCosto);
    GoToXY(40, 16); printf("Costo actualizado.");
    system("pause");
    
} //ModificarMembresia

void ListarMembresias(pPrimeroM pLista) {
	
    int y = 8;
    
    system("cls");
    DibujarMarco(2, 1, 117, 28);
    CentrarTexto(3, "LISTADO DE MEMBRESIAS");
    
    GoToXY(5, 6); printf("%-8s %-8s %-12s %-10s %-8s", "ID MEM", "ID CLI", "ENTRENADOR", "TIPO", "COSTO");
    GoToXY(5, 7); printf("-------------------------------------------------------");

    if (pLista == NULL) { GoToXY(40, 10); printf("No hay registros."); }
    
    while (pLista != NULL) {
    	
        GoToXY(5, y);
        printf("%-8d %-8d %-12s %-10s %.2f", 
               pLista->datos.eIDMembresia, 
               pLista->datos.eIDCliente,
               pLista->datos.sIDEntrenador,
               pLista->datos.cTipoMembresia, 
               pLista->datos.fCosto);
               
        pLista = pLista->pSiguiente;
        y++;
        
        if(y > 25) { 
        
			y=8; system("cls"); 
			
			} 
			
    }
    
    system("pause");
    
} //ListarMembresias

void GuardarArchivoMembresias(pPrimeroM pLista) {
	
    FILE *pFile = fopen("membresias.dat", "wb");
    
    if (pFile == NULL) return;
    
    while (pLista != NULL) {
    	
        fwrite(&pLista->datos, sizeof(rMembresia), 1, pFile);
        pLista = pLista->pSiguiente;
        
    }
    
    fclose(pFile);
    
} //GuardarArchivoMembresias

void CargarArchivoMembresias(pPrimeroM *pLista) {
	
	//Variables
    FILE *pFile = fopen("membresias.dat", "rb");
    rMembresia rTemp;
    TrNodo *pNuevo;
    
    if (pFile == NULL) return;
    
    while (fread(&rTemp, sizeof(rMembresia), 1, pFile)) {
    	
        pNuevo = (TrNodo*)malloc(sizeof(TrNodo));
        
        if (pNuevo != NULL) {
        	
            pNuevo->datos = rTemp;
            pNuevo->pSiguiente = *pLista;
            *pLista = pNuevo;
            
        }
        
    }
    
    fclose(pFile);
    
} //CargarArchivoMembresias

#endif
