/* ***
   Biblioteca: ModuloEntrenadores.h
   Autor: Oscar Gonzalez, Isis
   Fecha: 01-Feb-2026
   Objetivo: Crear modulo que logre gestionar a los entrenadores.
*** */

#ifndef MODULO_ENTRENADORES_H
#define MODULO_ENTRENADORES_H

//Bibliotecas

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tipos.h"
#include "Interfaz.h"

// Prototipos
int ListaVaciaEntrenador(TpNodoEntrenador);
int ListaLlenaEntrenador(TpNodoEntrenador *);
TpNodoEntrenador BuscarEntrenador(TpNodoEntrenador, TsCadenaEntrenador);
void LiberarListaEntrenador(TpNodoEntrenador);
TrEntrenador LeerDatosEntrenador();
void AltaEntrenador(TpNodoEntrenador *, TrEntrenador);
void BajaEntrenador(TpNodoEntrenador *, TsCadenaEntrenador);
void ModificarEntrenador(TpNodoEntrenador *);
void ConsultarEntrenador(TpNodoEntrenador, TsCadenaEntrenador);
void ConsultarVentasEntrenador(TpNodoEntrenador, TsCadenaEntrenador);
void ListarEntrenadores(TpNodoEntrenador);
void GuardarArchivoEntrenador(TpNodoEntrenador);
void CargarArchivoEntrenador(TpNodoEntrenador *);
void PlantillaBaseEntrenador(char *);


void PlantillaBaseEntrenador(char *titulo) {
	
	system("cls");
	DibujarMarco(2, 1, 117, 28);
	DibujarMarco(30, 2, 90, 4);
	CentrarTexto(3, titulo);
	
} //PlantillaBaseEntrenador

int ListaVaciaEntrenador(TpNodoEntrenador pPrimero){
	
	return (pPrimero == NULL);
	
} //ListaVaciaEntrenador

int ListaLlenaEntrenador(TpNodoEntrenador *pNuevo){
	
	*pNuevo = (TpNodoEntrenador) malloc(sizeof(TrNodoEntrenador));
	return (*pNuevo == NULL); 
	
} //ListaLlenaEntrenador

TpNodoEntrenador BuscarEntrenador(TpNodoEntrenador pPrimero, TsCadenaEntrenador sIdBuscado){
	
	//Variables
	TpNodoEntrenador pActual = pPrimero;
	
	while(pActual != NULL){
		
		if(strcmp(pActual->rDato.sId, sIdBuscado) == 0) return pActual;
		
		pActual = pActual->pSiguiente;
		
	}
	
	return NULL;
	
} //BuscarEntrenador

void LiberarListaEntrenador(TpNodoEntrenador pPrimero){
	
	//Variables
	TpNodoEntrenador pTemp;
	
	while(pPrimero != NULL){
		
		pTemp = pPrimero;
		pPrimero = pPrimero->pSiguiente;
		free(pTemp);
		
	}
	
} //LiberarListaEntrenador

void AltaEntrenador(TpNodoEntrenador *pPrimero, TrEntrenador rEnt){
	
	//Variables
	TpNodoEntrenador pNuevo;
	TpNodoEntrenador pAux = *pPrimero;
	int maxID = 0;
	int idActual;

	while (pAux != NULL) {
		
		idActual = atoi(pAux->rDato.sId); 
		if (idActual > maxID) maxID = idActual;
		pAux = pAux->pSiguiente;
		
	}
	sprintf(rEnt.sId, "%d", maxID + 1);

	if(ListaLlenaEntrenador(&pNuevo)){
		
		GoToXY(40, 26); printf("Memoria Llena (RAM agotada).");
		return;
		
	}

	pNuevo->rDato = rEnt;
	pNuevo->pSiguiente = *pPrimero;
	*pPrimero = pNuevo;
	
	GoToXY(40, 26); printf("Entrenador %s (ID: %s) registrado.", rEnt.sNombre, rEnt.sId);
	
} //AltaEntrenador

void BajaEntrenador(TpNodoEntrenador *pPrimero, TsCadenaEntrenador sIdBorrar){
	
	//Variables
	TpNodoEntrenador pActual = *pPrimero;
	TpNodoEntrenador pAnterior = NULL;

	if(ListaVaciaEntrenador(*pPrimero)){
		
		GoToXY(40, 12); printf("Lista vacia.");
		return;
		
	}

	while(pActual != NULL && strcmp(pActual->rDato.sId, sIdBorrar) != 0){
		
		pAnterior = pActual;
		pActual = pActual->pSiguiente;
		
	}

	if(pActual == NULL){
		
		GoToXY(40, 12); printf("No se encontro el ID: %s.", sIdBorrar);
		
	} else {
		
		if(pAnterior == NULL) *pPrimero = pActual->pSiguiente;
		
		else pAnterior->pSiguiente = pActual->pSiguiente;
		
		free(pActual);
		GoToXY(40, 12); printf("Entrenador eliminado.");
		
	}
	
} //BajaEntrenador

void ModificarEntrenador(TpNodoEntrenador *pPrimero){
	
	//Variables
	TsCadenaEntrenador sIdTemporal;
	TrEntrenador rEntrenadorTemporal;
	TpNodoEntrenador pEncontrado;
	
	PlantillaBaseEntrenador("MODIFICAR ENTRENADOR");
	GoToXY(40, 10); printf("ID a modificar: "); fflush(stdin); gets(sIdTemporal);
	
	pEncontrado = BuscarEntrenador(*pPrimero, sIdTemporal);
	
	if(pEncontrado == NULL){
		
		GoToXY(40, 12); printf("El ID no existe.");
		
	} else {
		
		GoToXY(40, 12); printf("Ingrese NUEVOS datos:");
		Sleep(1000); 
		rEntrenadorTemporal = LeerDatosEntrenador();
		
		strcpy(rEntrenadorTemporal.sId, sIdTemporal);
		
		pEncontrado->rDato = rEntrenadorTemporal;
		
		GoToXY(40, 26); printf("Datos actualizados correctamente.");
	}
	
} //ModificarEntrenador

TrEntrenador LeerDatosEntrenador(){
	
	//Variable
	TrEntrenador rE;
	
	PlantillaBaseEntrenador("DATOS DEL ENTRENADOR");
	
	GoToXY(20, 8);  printf("Nombre: "); 
	GoToXY(20, 10); printf("Ap. Paterno: "); 
	GoToXY(60, 10); printf("Ap. Materno: "); 
	GoToXY(20, 12); printf("Fecha Nac (dd mm aa): "); 
	GoToXY(60, 12); printf("Contrato (dd mm aa): "); 
	GoToXY(20, 14); printf("Sueldo: "); 
	GoToXY(60, 14); printf("Tel: "); 
	GoToXY(20, 16); printf("--- DIRECCION ---");
	GoToXY(20, 18); printf("Calle: "); 
	GoToXY(60, 18); printf("CP: "); 
	GoToXY(20, 20); printf("Colonia: "); 
	GoToXY(20, 22); printf("Municipio: "); 
	GoToXY(60, 22); printf("Estado: "); 

	fflush(stdin);

	GoToXY(28, 8);  gets(rE.sNombre);
	GoToXY(33, 10); gets(rE.sApPaterno);
	GoToXY(73, 10); gets(rE.sApMaterno);
	
	GoToXY(40, 12); scanf("%d %d %d", &rE.rFechaNac.eDia, &rE.rFechaNac.eMes, &rE.rFechaNac.eAnio);
	GoToXY(78, 12); scanf("%d %d %d", &rE.rFechaContrato.eDia, &rE.rFechaContrato.eMes, &rE.rFechaContrato.eAnio);
	
	GoToXY(28, 14); scanf("%f", &rE.fSueldoFijo);
	fflush(stdin);
	GoToXY(65, 14); gets(rE.sTelefono);
	
	GoToXY(27, 18); gets(rE.rDireccion.sCalle);
	GoToXY(64, 18); scanf("%d", &rE.rDireccion.eCP);
	fflush(stdin);
	GoToXY(29, 20); gets(rE.rDireccion.sColonia);
	GoToXY(31, 22); gets(rE.rDireccion.sMunicipio);
	GoToXY(68, 22); gets(rE.rDireccion.sEstado);
	
	return rE;
	
} //ModificarEntrenaador

void ConsultarEntrenador(TpNodoEntrenador pPrimero, TsCadenaEntrenador sId){
	
	//Variables
	TpNodoEntrenador p = BuscarEntrenador(pPrimero, sId);
	
	PlantillaBaseEntrenador("INFORMACION COMPLETA");
	
	if(p){
		
		GoToXY(30, 8);  printf("ID: %s", p->rDato.sId);
		GoToXY(30, 10); printf("Nombre: %s %s %s", p->rDato.sNombre, p->rDato.sApPaterno, p->rDato.sApMaterno);
		GoToXY(30, 12); printf("Fecha Nac: %02d/%02d/%d", p->rDato.rFechaNac.eDia, p->rDato.rFechaNac.eMes, p->rDato.rFechaNac.eAnio);
		GoToXY(70, 12); printf("Fecha Contrato: %02d/%02d/%d", p->rDato.rFechaContrato.eDia, p->rDato.rFechaContrato.eMes, p->rDato.rFechaContrato.eAnio);
		GoToXY(30, 14); printf("Sueldo: %.2f", p->rDato.fSueldoFijo);
		GoToXY(70, 14); printf("Telefono: %s", p->rDato.sTelefono);
		
		GoToXY(30, 16); printf("Direccion:");
		GoToXY(30, 17); printf("%s, Col. %s", p->rDato.rDireccion.sCalle, p->rDato.rDireccion.sColonia);
		GoToXY(30, 18); printf("CP %d, %s, %s", p->rDato.rDireccion.eCP, p->rDato.rDireccion.sMunicipio, p->rDato.rDireccion.sEstado);
		
	} else {
		
		GoToXY(40, 12); printf("No encontrado.");
		
	}
	
	GoToXY(40, 25); 
	
} //ConsultarEntrenador

void ListarEntrenadores(TpNodoEntrenador pPrimero){
	
	//Variables
	int y = 8; 
	
	PlantillaBaseEntrenador("LISTADO DE ENTRENADORES");
	
	GoToXY(10, 6); printf("%-10s %-20s %-20s", "ID", "NOMBRE", "AP. PATERNO");
	GoToXY(10, 7); printf("--------------------------------------------------");
	
	while(pPrimero != NULL){
		
		GoToXY(10, y); 
		printf("%-10s %-20s %-20s", pPrimero->rDato.sId, pPrimero->rDato.sNombre, pPrimero->rDato.sApPaterno);
		pPrimero = pPrimero->pSiguiente;
		y++;
		
		if(y > 25) { 
		
			GoToXY(80, 26); printf("Siguiente pagina...");
			getch();
			PlantillaBaseEntrenador("LISTADO DE ENTRENADORES (Cont.)");
			y = 8;
			
		}
		
	}
	
	GoToXY(40, 26);
	
} //ListarEntrenadores


void ConsultarVentasEntrenador(TpNodoEntrenador pPrimero, TsCadenaEntrenador sId){
	
	//Variables
    FILE *fMem, *fSup;
    rMembresia mem;
    TrVentaSuplemento ventaSup;
    float total = 0.0;
    int y = 10;
    int foundMem = 0, foundSup = 0;

	PlantillaBaseEntrenador("CONSULTAR VENTAS");
	
	if(!BuscarEntrenador(pPrimero, sId)){
		
		GoToXY(40, 12); printf("El Entrenador no existe.");
		system("pause"); return;
		
	}

    GoToXY(5, 8); printf("VENTAS DEL ENTRENADOR: %s", sId);

    fMem = fopen("membresias.dat", "rb");
    
    if(fMem) {
    	
        while(fread(&mem, sizeof(rMembresia), 1, fMem)) {
        	
            if(strcmp(mem.sIDEntrenador, sId) == 0) {
            	
                if(foundMem == 0) {
                	
                    GoToXY(5, y++); printf("--- MEMBRESIAS ---");
                    
                    foundMem = 1;
                }
                
                GoToXY(5, y++); printf("Mem: %s - $%.2f", mem.cTipoMembresia, mem.fCosto);
                total += mem.fCosto;
                
            }
            
        }
        
        fclose(fMem);
        
    }

    y = 10; 
    
    fSup = fopen("ventas_suplementos.dat", "rb");
    
    if(fSup) {
    	
        while(fread(&ventaSup, sizeof(TrVentaSuplemento), 1, fSup)) {
        	
            if(strcmp(ventaSup.sIDEntrenador, sId) == 0) {
            	
                if(foundSup == 0) {
                	
                    GoToXY(60, y++); printf("--- SUPLEMENTOS ---");
                    
                    foundSup = 1;
                    
                }
                
                GoToXY(60, y++); printf("Sup ID:%d (x%d) - $%.2f", ventaSup.eIdProducto, ventaSup.eCantidad, ventaSup.fTotalPagado);
                total += ventaSup.fTotalPagado;
                
            }
            
        }
        
        fclose(fSup);
        
    }

    GoToXY(40, 25); printf("TOTAL GENERADO: $%.2f", total);
	system("pause");
	
} //ConsultarVentasEntrenador

void GuardarArchivoEntrenador(TpNodoEntrenador pPrimero){
	
	//Variables
	FILE *pArchivo;
	pArchivo = fopen("Entrenadores.dat", "wb");
	
	if(pArchivo == NULL){
		
		printf("Error al abrir archivo.");
		return;
		
	}
	
	while(pPrimero != NULL){
		
		fwrite(&(pPrimero->rDato), sizeof(TrEntrenador), 1, pArchivo);
		pPrimero = pPrimero->pSiguiente;
		
	}
	
	fclose(pArchivo);
	
} //GuardarArchivoEntrenador

void CargarArchivoEntrenador(TpNodoEntrenador *pPrimero){
	
	//Variables
	FILE *pArchivo;
	TrEntrenador rEnt;
	TpNodoEntrenador pNuevo;
	
	pArchivo = fopen("Entrenadores.dat", "rb");
	
	if(pArchivo == NULL) return; 
	
	while(fread(&rEnt, sizeof(TrEntrenador), 1, pArchivo)){
		
		if(ListaLlenaEntrenador(&pNuevo)) break;
		
		pNuevo->rDato = rEnt;
		pNuevo->pSiguiente = *pPrimero;
		*pPrimero = pNuevo;
		
	}
	
	fclose(pArchivo);
	
} //CargarArchivoEntrenador

#endif
