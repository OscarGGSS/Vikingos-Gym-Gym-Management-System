/* ***
   Biblioteca: ModuloSuplementos.h
   Autor: Jennifer Garcia, Oscar e Isis
   Fecha: 02-Feb-2026
   Objetivo: Crear modulo que permita el manejo de suplementos junto con el de ventas de entrenadores.
*** */
#ifndef MODULO_SUPLEMENTOS_H
#define MODULO_SUPLEMENTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tipos.h"
#include "Interfaz.h"

pInicioInv pListaSup = NULL;

void GuardarArchivoSuplementos(pInicioInv pLista) {
	
    FILE *pFile = fopen("suplementos.dat", "wb");
    
    if (pFile == NULL) return;
    
    while (pLista != NULL) {
    	
        fwrite(&pLista->datos, sizeof(TrSuplemento), 1, pFile);
        pLista = pLista->pSiguiente;
        
    }
    
    fclose(pFile);
    
} //GuardarArchivoSuplementos

void CargarArchivoSuplementos(pInicioInv *pLista) {
	
	//Variables
    FILE *pFile = fopen("suplementos.dat", "rb");
    TrSuplemento rTemp;
    TrNodoSuplemento *pNuevo;
    *pLista = NULL;
    
    if (pFile == NULL) return;
    
    while (fread(&rTemp, sizeof(TrSuplemento), 1, pFile)) {
    	
        pNuevo = (TrNodoSuplemento*)malloc(sizeof(TrNodoSuplemento));
        
        if (pNuevo != NULL) {
        	
            pNuevo->datos = rTemp;
            pNuevo->pSiguiente = *pLista;
            *pLista = pNuevo;
            
        }
        
    }
    
    fclose(pFile);
    
} //CargarArchivoSuplementos

int ExisteEntrenadorS(char *id) {
	
	//Variables
    FILE *f = fopen("Entrenadores.dat", "rb");
    TrEntrenador t;
    
    if(!f) return 0;
    
    while(fread(&t, sizeof(TrEntrenador), 1, f)) {
    	
        if(strcmp(t.sId, id)==0) { fclose(f); return 1; }
        
    }
    
    fclose(f); return 0;
    
} //ExisteEntrenadorS


void AltaSuplemento(pInicioInv *pLista) {
	
	//Variables
	int contador = 1;
    TrNodoSuplemento *pNuevo = (TrNodoSuplemento *)malloc(sizeof(TrNodoSuplemento));
    system("cls"); 
	DibujarMarco(2, 1, 117, 28); 
	CentrarTexto(10, "ALTA SUPLEMENTO");

    TrNodoSuplemento *pAux = *pLista;
    
    while (pAux != NULL) {
    	
        contador++;
        
        pAux = pAux->pSiguiente;
        
    }
    
    pNuevo->datos.eIdProducto = contador;
    
    GoToXY(40, 12); 
	printf("Nombre: "); 
	fflush(stdin); 
	gets(pNuevo->datos.sNombre);
    
    GoToXY(40, 14); 
	printf("Precio: "); 
	scanf("%f", &pNuevo->datos.fPrecio);
	
    GoToXY(40, 16); 
	printf("Stock: "); 
	scanf("%d", &pNuevo->datos.eDisponibilidad);
    
    pNuevo->datos.eFechaCaducidad.eDia = 1; 
	pNuevo->datos.eFechaCaducidad.eMes = 1; 
	pNuevo->datos.eFechaCaducidad.eAnio = 2026;

    pNuevo->pSiguiente = *pLista;
    *pLista = pNuevo;
    
    GoToXY(40, 24); printf("Registrado ID: %d", pNuevo->datos.eIdProducto); 
    
	system("pause");
    
} // AltaSuplemento

void VenderSuplemento(pInicioInv pLista) {
	
	//Variables
    int id, cant; 
	char idEnt[50]; 
	TrVentaSuplemento venta;
	
    system("cls"); DibujarMarco(2, 1, 117, 28); 
	CentrarTexto(3, "VENTA SUPLEMENTO");
    
    GoToXY(40, 8); printf("ID Producto: "); 
	scanf("%d", &id);
    while(pLista && pLista->datos.eIdProducto != id) pLista = pLista->pSiguiente;

    if(!pLista) { 
		GoToXY(40, 12); 
		
		printf("No existe."); 
		system("pause"); 
		
		return; 
	
	}

    GoToXY(40, 12); printf("Prod: %s ($%.2f)", pLista->datos.sNombre, pLista->datos.fPrecio);
    GoToXY(40, 13); printf("Stock: %d", pLista->datos.eDisponibilidad);
    
    GoToXY(40, 15); printf("Cantidad: "); 
	scanf("%d", &cant);
	
    if(cant > pLista->datos.eDisponibilidad) { 
    
		GoToXY(40, 17); 
		printf("Sin Stock."); 
		system("pause"); 
		return; 
	
	}

    GoToXY(40, 17); printf("ID Vendedor: "); 
	fflush(stdin); 
	gets(idEnt);
    
    if(!ExisteEntrenadorS(idEnt)) { 
	
		GoToXY(40,19); 
		printf("Entrenador invalido"); 
		system("pause"); 
		return; 
		
		}

    pLista->datos.eDisponibilidad -= cant;
    
    venta.eIdProducto = id; 
	venta.eCantidad = cant; 
    venta.fTotalPagado = cant * pLista->datos.fPrecio;
    strcpy(venta.sIDEntrenador, idEnt);
    
    FILE *f = fopen("ventas_suplementos.dat", "ab");
    
    if(f) { 
    
		fwrite(&venta, sizeof(TrVentaSuplemento), 1, f); 
		fclose(f); 
	
	}

    GoToXY(40, 22); printf("Venta OK. Total: $%.2f", venta.fTotalPagado); 
	system("pause");
    
} //VenderSuplemento

void Inventario(pInicioInv pLista) {
	
	//Variable
    int y=8;
    system("cls"); 
	DibujarMarco(2, 1, 117, 28); 
	CentrarTexto(3, "INVENTARIO");
    GoToXY(5, 6); 
	printf("ID   NOMBRE               PRECIO    STOCK");
    
    while(pLista) {
    	
        GoToXY(5, y++); 
        printf("%d  %-20s $%-8.2f %d", pLista->datos.eIdProducto, pLista->datos.sNombre, pLista->datos.fPrecio, pLista->datos.eDisponibilidad);
        pLista = pLista->pSiguiente;
        
    }
    
    system("pause");
    
} //Inventario

#endif
