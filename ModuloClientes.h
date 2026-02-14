/* ***
   Biblioteca: ModuloClientes.h
   Autor: Islas Isis, oscar
   Fecha: 01-Feb-2026
   Objetivo: Crear modulo que logre gestionar a los clientes para utilizar junto a membresias.
*** */

#ifndef MODULO_CLIENTES_H
#define MODULO_CLIENTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tipos.h"
#include "Interfaz.h"

// Prototipos
int ListaVacia(TpCliente);
int ListaLlena(TpCliente *);
void GenerarIdCliente(TpCliente, int *);
void PrepararNodo(TpCliente, int, TsCadena, TsCadena);
void AgregarEnListaVacia(TpCliente *, TpCliente *, TpCliente);
void AgregarDespuesDeUltimo (TpCliente *, TpCliente);
void AgregarCliente(TpCliente *, TpCliente *);
void DarBajaCliente(TpCliente *, TpCliente *);
void ModificarCliente(TpCliente);
void ConsultarCliente(TpCliente);
void GuardarArchivo(TpCliente);
void CargarArchivo(TpCliente *, TpCliente *);

// Implementacion

int ListaVacia(TpCliente pPrimero){
	
	return (pPrimero == NULL);
	
} //ListaVacia

int ListaLlena(TpCliente *pNuevo){
	
	*pNuevo = (TpCliente)malloc(sizeof(TrCliente));
	return (*pNuevo == NULL);	
	
} //ListaLlena

void GenerarIdCliente(TpCliente pPrimero, int *pIdClienteNuevo) {
	
	//Variables
	int eMaxId;
	TpCliente pAuxiliar;
	eMaxId = 0;
	pAuxiliar = pPrimero;
	
	while (pAuxiliar != NULL) {
		
		if (pAuxiliar->eId > eMaxId) {
			
			eMaxId = pAuxiliar->eId;
			
		}
		
		pAuxiliar = pAuxiliar->pSiguiente;
		
	}
	
	*pIdClienteNuevo = eMaxId + 1;
	
} //GenerarIdCliente

void PrepararNodo(TpCliente pNuevo, int eIdNuevo, TsCadena sNom, TsCadena sTel) {
	
	pNuevo->eId = eIdNuevo;
	strcpy(pNuevo->sNombre, sNom);
	strcpy(pNuevo->sTelefono, sTel);
	pNuevo->pSiguiente = NULL;
	
} //PrepararNodo 

void AgregarEnListaVacia(TpCliente *pPrimero, TpCliente *pUltimo, TpCliente pNuevo){
	
	*pPrimero = pNuevo;
	*pUltimo = pNuevo;
	
} //AgregarEnListaVacia

void AgregarDespuesDeUltimo (TpCliente *pUltimo , TpCliente pNuevo){
	
	(*pUltimo)->pSiguiente = pNuevo;
	*pUltimo = pNuevo;
	
} //AgregarDespuesDeUltimo

void AgregarCliente(TpCliente *pPrimero, TpCliente *pUltimo) {
	
	//Variables
	TpCliente pNuevo;
	int eIdNuevo;
	TsCadena sNom, sTel;

	system("cls");
	DibujarMarco(2, 1, 117, 28);
	DibujarMarco(30, 8, 90, 20);
	CentrarTexto(10, "REGISTRO DE CLIENTE");

	if (ListaLlena(&pNuevo)) {
		
		GoToXY(40, 25); printf("Error: No se pueden agregar mas clientes");
		system("pause");
		
		return;
		
	}

	GenerarIdCliente(*pPrimero, &eIdNuevo);

	GoToXY(40, 12); printf("ID Asignado: %d", eIdNuevo);
	GoToXY(40, 14); printf("Nombre: ");
	fflush(stdin);
	gets(sNom);
	
	GoToXY(40, 16); printf("Telefono: ");
	fflush(stdin);
	gets(sTel);

	PrepararNodo(pNuevo, eIdNuevo, sNom, sTel);

	if (ListaVacia(*pPrimero)) {
		
		AgregarEnListaVacia(pPrimero, pUltimo, pNuevo);
		
	} else {
		
		AgregarDespuesDeUltimo(pUltimo, pNuevo);
		
	}

	GoToXY(40, 25); printf("El registro se realizo con exito");
	system("pause");
	
} //AgregarCliente 

void DarBajaCliente(TpCliente *pPrimero, TpCliente *pUltimo) {
	
	//Variables
	int eIdBuscar;
	char cOpcion; 
	TpCliente pActual, pAnterior = NULL;

	system("cls");
	DibujarMarco(2, 1, 117, 28);
	CentrarTexto(3, "BAJA DE CLIENTE");

	if (ListaVacia(*pPrimero)) {
		
		GoToXY(40, 12); printf("No hay clientes para dar de baja");
		system("pause");
		
		return;
		
	}

	GoToXY(40, 10); printf("Ingrese el ID del cliente: ");
	scanf("%d", &eIdBuscar);
	fflush(stdin);

	pActual = *pPrimero;

	while (pActual != NULL && pActual->eId != eIdBuscar) {
		
		pAnterior = pActual;
		pActual = pActual->pSiguiente;
		
	}

	if (pActual == NULL) {
		
		GoToXY(40, 14); printf("Error: El ID (%d) no existe", eIdBuscar);
		
	} else {
		
		DibujarMarco(35, 12, 85, 20);
		GoToXY(40, 14); printf("ID: %d", pActual->eId);
		GoToXY(40, 16); printf("Nombre: %s", pActual->sNombre);
		GoToXY(40, 18); printf("Telefono: %s", pActual->sTelefono);

		GoToXY(40, 22); printf("Desea borrar este cliente? (S/N): ");
		scanf(" %c", &cOpcion); 
		fflush(stdin);

		if (cOpcion == 'S' || cOpcion == 's') {
			
			if (pActual == *pPrimero) {
				
				*pPrimero = (*pPrimero)->pSiguiente;
				
				if (*pPrimero == NULL) *pUltimo = NULL;
				
			} else {
				
				pAnterior->pSiguiente = pActual->pSiguiente;
				
				if (pActual == *pUltimo) {
					
					*pUltimo = pAnterior;
					
				}
				
			}
			
			free(pActual);
			
			GoToXY(40, 25); printf("El registro del cliente se borro correctamente");
			
		} else {
			
			GoToXY(40, 25); printf("No se realizara la funcion");
			
		}
		
	}
	
	system("pause");
	
} //DarBajaCliente

void ModificarCliente(TpCliente pPrimero) {
	
	//Variables
	int eIdBuscar;
	char cOpcion;
	TpCliente pAuxiliar;

	system("cls");
	DibujarMarco(2, 1, 117, 28);
	CentrarTexto(3, "MODIFICAR CLIENTE");

	if (ListaVacia(pPrimero)) {
		
		GoToXY(40, 12); printf("No hay clientes para modificar");
		system("pause");
		
		return;
		
	}

	GoToXY(40, 10); printf("Ingrese el ID del cliente: ");
	scanf("%d", &eIdBuscar);
	fflush(stdin);

	pAuxiliar = pPrimero;

	while (pAuxiliar != NULL && pAuxiliar->eId != eIdBuscar) {
		
		pAuxiliar = pAuxiliar->pSiguiente;
		
	}

	if (pAuxiliar == NULL) {
		
		GoToXY(40, 12); printf("Error: El ID (%d) no existe", eIdBuscar);
		
	} else {
		
		DibujarMarco(35, 12, 85, 20);
		
		GoToXY(40, 14); printf("ID: %d", pAuxiliar->eId);
		GoToXY(40, 16); printf("Nombre: %s", pAuxiliar->sNombre);
		GoToXY(40, 18); printf("Telefono: %s", pAuxiliar->sTelefono);

		GoToXY(40, 22); printf("Desea modificar a este cliente? (S/N): ");
		scanf(" %c", &cOpcion);
		fflush(stdin);

		if (cOpcion == 'S' || cOpcion == 's') {
			
			system("cls");
			DibujarMarco(2, 1, 117, 28);
			DibujarMarco(30, 8, 90, 18);
			CentrarTexto(10, "NUEVOS DATOS");
			
			GoToXY(40, 12); printf("Ingrese el nuevo nombre: ");
			gets(pAuxiliar->sNombre);
			
			GoToXY(40, 14); printf("Ingrese nuevo telefono: ");
			gets(pAuxiliar->sTelefono);

			if (strlen(pAuxiliar->sNombre) > 0) {
				
				GoToXY(40, 24); printf("El registro se modifico de manera correcta");
				
			} else {
				
				GoToXY(40, 24); printf("Error al guardar los datos.");
				
			}
			
		} else if (cOpcion == 'N' || cOpcion == 'n') {
			
			GoToXY(40, 24); printf("No se realizara la funci%cn", 162);
			
		} else {
			
			GoToXY(40, 24); printf("No se realizara la funci%cn", 160);
			
		}
		
	}
	
	system("pause");
	
} //DarBajaCliente

void ConsultarCliente(TpCliente pPrimero) {
	
	//Variables
	int eIdBuscar;
	TpCliente pAuxiliar;
	int lEncontrado = 0; 

	system("cls");
	DibujarMarco(2, 1, 117, 28);
	CentrarTexto(3, "CONSULTA DE CLIENTE");

	if (ListaVacia(pPrimero)) {
		
		GoToXY(40, 12); printf("No hay clientes que consultar");
		system("pause");
		return;
		
	}

	GoToXY(40, 10); printf("Ingrese el ID del cliente: ");
	scanf("%d", &eIdBuscar);
	fflush(stdin);

	pAuxiliar = pPrimero;

	while (pAuxiliar != NULL) {
		
		if (pAuxiliar->eId == eIdBuscar) {
			
			DibujarMarco(35, 12, 85, 20);
			CentrarTexto(13, "DATOS ENCONTRADOS");
			GoToXY(40, 15); printf("ID: %d", pAuxiliar->eId);
			GoToXY(40, 17); printf("Nombre: %s", pAuxiliar->sNombre);
			GoToXY(40, 19); printf("Telefono: %s", pAuxiliar->sTelefono);
			lEncontrado = 1;
			break;
			
		}
		
		pAuxiliar = pAuxiliar->pSiguiente;
		
	}

	if (lEncontrado == 0) {
		
		GoToXY(40, 14); printf("El cliente con ID %d no existe", eIdBuscar);
		
	}
	
	system("pause");
	
} //ConsultarCliente

void GuardarArchivo(TpCliente pPrimero) {
	
	//Variables
	FILE *pFile;
	TpCliente pAuxiliar = pPrimero;
	pFile = fopen("clientes.dat", "wb"); 
	
	if (pFile == NULL) {
		
		printf("\nError al abrir el archivo para guardar");
		return;
		
	}

	while (pAuxiliar != NULL) {
		
		fwrite(pAuxiliar, sizeof(TrCliente), 1, pFile);
		pAuxiliar = pAuxiliar->pSiguiente;
		
	}
	
	fclose(pFile);
	
} //GuardarArchivo

void CargarArchivo(TpCliente *pPrimero, TpCliente *pUltimo) {
	
	//Variables
	FILE *pFile;
	TrCliente rTemp;
	TpCliente pNuevo;

	pFile = fopen("clientes.dat", "rb");
	
	if (pFile == NULL) return;
	
	while (fread(&rTemp, sizeof(TrCliente), 1, pFile)) {
		
		if (!ListaLlena(&pNuevo)) {
			
			pNuevo->eId = rTemp.eId;
			strcpy(pNuevo->sNombre, rTemp.sNombre);
			strcpy(pNuevo->sTelefono, rTemp.sTelefono);
			pNuevo->pSiguiente = NULL;

			if (ListaVacia(*pPrimero)) {
				
				AgregarEnListaVacia(pPrimero, pUltimo, pNuevo);
				
			} else {
				
				AgregarDespuesDeUltimo(pUltimo, pNuevo);
				
			}
			
		}
		
	}
	
	fclose(pFile);
	
} //CargarArchivo

#endif
