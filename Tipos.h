/* ***
   Biblioteca: Tipos.h
   Autor: Isis
   Fecha: 02-Feb-2026
   objetivo: Unir los tipos de todo el sistema en la misma biblioteca.
*** */

//Bibliotecas

#ifndef TIPOS_H
#define TIPOS_H

typedef char TsCadena[30];

typedef char TsCadenaEntrenador[50]; 

typedef struct {
	
    int eDia; int eMes; int eAnio; 
    
} TrRegistroFecha; 


// 1. CLIENTES
typedef struct rCliente {
	
    TsCadena sNombre;
    TsCadena sTelefono;
    int eId;
    struct rCliente *pSiguiente;
    
} TrCliente; //Registro de TrCliente

typedef TrCliente *TpCliente; //Apuntador a TrCliente

// 2. ENTRENADORES
typedef struct {
	
    TsCadenaEntrenador sCalle; int eCP;
    TsCadenaEntrenador sColonia, sMunicipio, sEstado;
    
} TrDireccionEntrenador; //Registro de Domicilio

typedef struct {
	
    TsCadenaEntrenador sId; 
    TsCadenaEntrenador sNombre, sApPaterno, sApMaterno;
    TrRegistroFecha rFechaNac, rFechaContrato;
    float fSueldoFijo;
    TsCadenaEntrenador sTelefono;
    TrDireccionEntrenador rDireccion;
    
} TrEntrenador; //Registro de TrEntrenador

typedef struct rNodoEntrenador {
	
    TrEntrenador rDato;
    struct rNodoEntrenador *pSiguiente;
    
} TrNodoEntrenador; //Registro de TrNodoEntrenador

typedef TrNodoEntrenador *TpNodoEntrenador; //Apuntador a TrNodoEntrenador

// 3. MEMBRESIAS
typedef struct TrMembresia {
	
    int eIDMembresia;            
    char cTipoMembresia[21];     
    float fCosto;                
    TrRegistroFecha rFechaInicio, rFechaVencimiento; 
    int eIDCliente;
    char sIDEntrenador[50]; 
    char cEstatus[15]; 
    
} rMembresia; //Registro de TrMembresia

typedef struct rNodo {
	
    rMembresia datos;
    struct rNodo *pSiguiente;
    
} TrNodo; //Registro de TrNodo

typedef TrNodo *pPrimeroM; //Apuntador a TrNodo

// 4. SUPLEMENTOS 
typedef struct rSuplemento {
	
    int eIdProducto;
    char sNombre[50];     
    float fPrecio;          
    TrRegistroFecha eFechaCaducidad;    
    int eDisponibilidad;  
    
} TrSuplemento; //Registro de TrSuplemento

typedef struct rVentaSuplemento {
	
    int eIdVenta;
    int eIdProducto;
    int eCantidad;
    float fTotalPagado;
    char sIDEntrenador[50];
    TrRegistroFecha fechaVenta;
    
} TrVentaSuplemento; //Registro de TrVentaSuplemento

typedef struct rNodoSuplemento {
	
    TrSuplemento datos;  
    struct rNodoSuplemento *pSiguiente; 
    
} TrNodoSuplemento; //Registro de TrNodoSuplemento
 
typedef TrNodoSuplemento *pInicioInv; //Apuntador a TrNodoSuplemento

#endif
