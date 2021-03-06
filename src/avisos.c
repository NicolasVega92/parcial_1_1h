/*
 * avisos.c
 *
 *  Created on: 1 oct. 2020
 *      Author: Nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avisos.h"
#include "utn.h"
#include "cliente.h"
#include "informes.h"
static int avisos_generarIdNuevo(void);
//static const char TXT_TIPOS[2][LONG_NAME]={"Pausado", "Activo"}; //TXT_TIPOS[pArray[i].estado]
/*
* \brief	Inicializa todas las posiciones del array en empty (TRUE).
* \param 	Avisos* pArray puntero al array recibido
* \param 	int length limite del array
* \return 	int Retorna (-1) si se encuentra un error / (0)  Ok
*/
int avisos_init(Avisos* pArray, int length)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && length > 0)
	{
		for(i=0;i<length ;i++)
		{
			pArray[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Busca dentro de los indices del array Avisos el primer indice donde el valor de isEmpty == TRUE para
 * 			retornar ese valor de (i) como espacio valido para dar un alta
 * \param Avisos* pArray puntero al array
 * \param int limite, es el limite del array
 * \return retorna el valor de ( i ) OK / devuelve (-1) para indicar que no hay espacio a completar
 */
int avisos_findFirstValidPosition(Avisos* pArray, int length)
{
	int i;
	int retorno = -1;
	if(pArray!=NULL && length > 0)
	{
		for(i=0; i < length;i++)
		{
			if(pArray[i].isEmpty == TRUE)
			{
				retorno = i;
				return retorno;
			}
		}
	}
	return retorno;
}
/**
* \brief Agrega en el array de la estructura los valores pasados como parametros dentro del indice devuelto por la funcion searchFirstValidPosition
* \param Avisos* pArray puntero al array recibida
* \param int length limite del array
* \param int id Id recibido
* \param char texto[], array que contiene chars
* \param int idCliente recibido
* \param int numRubro recibido
* \param int auxestado recibido
* \return int Return (-1) Error / (0) Ok
*/
int avisos_add(Avisos* pArray, int length, int id, char texto[], int idCliente, int numRubro, int auxestado)
{
	int retorno = -1;
	int indiceLibre;
	if(pArray!=NULL && length > 0 && id > 0 && texto != NULL && idCliente > 0 &&  numRubro > -1 && numRubro < 10 && (auxestado == 0 || auxestado == 1))
	{
		indiceLibre = avisos_findFirstValidPosition(pArray, length);
		if(indiceLibre == -1)
		{
			printf("Ya no quedan espacios libres.\n");
		}
		else
		{
			pArray[indiceLibre].id = id;
			pArray[indiceLibre].idCliente = idCliente;
			pArray[indiceLibre].numeroRubro = numRubro;
			pArray[indiceLibre].isEmpty = FALSE;
			pArray[indiceLibre].isActive = auxestado;
			strncpy(pArray[indiceLibre].texto, texto, sizeof(pArray[indiceLibre].texto)-1);
		}
		retorno = 0;
	}
	return retorno;
}
/**
* \brief Agrega en el array de la estructura los valores pasados como parametros dentro del indice devuelto por la funcion searchFirstValidPosition
* \param Avisos* pArray puntero al array recibida
* \param int length limite del array
* \param char texto[], array que contiene chars
* \param int idCliente recibido
* \param int numRubro recibido
* \param int activo recibido
* \return int Return (-1) Error / (0) Ok
*/
int avisos_addForzada(Avisos* pArray, int length, char texto[], int idCliente, int numRubro, int activo)
{
	int retorno = -1;
	int indiceLibre;
	if(pArray!=NULL && length > 0 && texto != NULL && idCliente > 0 &&  numRubro < 10 && numRubro > -1 && (activo == TRUE || activo == FALSE))
	{
		indiceLibre = avisos_findFirstValidPosition(pArray, QTY_AVISOS);
		if(indiceLibre == -1)
		{
			printf("Ya no quedan espacios libres.\n");
		}
		else
		{
			pArray[indiceLibre].id = avisos_generarIdNuevo();
			pArray[indiceLibre].idCliente = idCliente;
			pArray[indiceLibre].numeroRubro = numRubro;
			pArray[indiceLibre].isEmpty = FALSE;
			pArray[indiceLibre].isActive = activo;
			strncpy(pArray[indiceLibre].texto, texto, sizeof(pArray[indiceLibre].texto)-1);
		}
		retorno = 0;
	}
	return retorno;
}
/**
* \brief Imprime el array pasado como parametro, si el campo isEmpty == FALSE
* \param Avisos* pArray puntero al array recibida
* \param int length limite del array
* \return int Return (-1) Error / (0) Ok
 */
int avisos_print(Avisos* pArray, int length)
{
	int retorno = -1;
	int i;
	if(pArray!=NULL && length > 0)
	{
		printf("[Avisos Publicados]\n"
				" Id|          Rubro| Id cliente|                     Descripci�n \n");
		for(i=0; i< length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				printf("%3d|%15s|%11d|%64s\n",pArray[i].id, TXT_RUBROS[pArray[i].numeroRubro], pArray[i].idCliente, pArray[i].texto);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/**
* \brief 	Imprime el array pasado como parametro, si el campo isEmpty == FALSE
* 			y el campo isActive == TRUE
* \param Avisos* pArray puntero al array recibida
* \param int length limite del array
* \return int Return (-1) Error / (0) Ok
 */
int avisos_printActivos(Avisos* pArray, int length)
{
	int retorno = -1;
	int i;
	int flagActivos=0;
	if(pArray!=NULL && length > 0)
	{
		printf("[Avisos Publicados Activos]\n"
				" Id|          Rubro| Id cliente|                     Descripci�n \n");
		for(i=0; i< length; i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].isActive == TRUE)
			{
				printf("%3d|%15s|%11d|%64s\n",pArray[i].id, TXT_RUBROS[pArray[i].numeroRubro], pArray[i].idCliente, pArray[i].texto);
				flagActivos=1;
				retorno = 0;
			}
		}
		if(flagActivos == 0)
		{
			printf("\nNo hay ningun aviso activos, vaya a la opcion 6 para Activar alguno o opcion 4 para dar de alta uno nuevo\n\n");
		}
	}
	return retorno;
}
/**
* \brief 	Imprime el array pasado como parametro, si el campo isEmpty == FALSE
* 			y el campo isActive == FALSE
* \param Avisos* pArray puntero al array recibida
* \param int length limite del array
* \return int Return (-1) Error / (0) Ok
 */
int avisos_printPausados(Avisos* pArray, int length)
{
	int retorno = -1;
	int i;
	int flagPausados=0;
	if(pArray!=NULL && length > 0)
	{
		printf("[Avisos Publicados Pausados]\n"
				" Id|          Rubro| Id cliente|                     Descripci�n \n");
		for(i=0; i< length; i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].isActive == FALSE)
			{
				printf("%3d|%15s|%11d|%64s\n",pArray[i].id, TXT_RUBROS[pArray[i].numeroRubro], pArray[i].idCliente, pArray[i].texto);
				flagPausados = 1;
				retorno = 0;
			}
		}
		if(flagPausados == 0)
		{
			printf("\nNo hay ningun aviso pausado, vaya a la opcion 5 para Pausar alguno o opcion 4 para dar de alta uno nuevo\n\n");
		}
	}
	return retorno;
}
/*
* \brief Devuelve como retorno el indice del ID pasado como parametro.
* \param Avisos* pArray puntero al array recibida
* \param int length limite del array
* \param int id, ID recibido a buscar
* \return int Return (-1) Error / (0) Ok
* */
int avisos_findById(Avisos* pArray, int length, int id)
{
	int retorno = -1;
	int i;

	if(pArray!=NULL && length > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				if(pArray[i].id == id)
				{
					retorno = i;
					break;
				}
			}
		}
	}
	return retorno;
}
/*
* \brief 	Devuelve como retorno la cantidad de avisos con estado== TRUE (1)
* 			que coincidan con el id pasado como parametro == idCliente de la struct Avisos
* \param Avisos* pArray puntero al array recibida
* \param int length limite del array
* \param int idValue ID recibido a buscar
* \return int Return (-1) Error / (0) Ok
* */
int avisos_countActiveByIdCliente(Avisos* pArray, int length, int id)
{
	int retorno = -1;
	int i;
	int countActive = 0;
	if(pArray!=NULL && length > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				if(pArray[i].idCliente == id)
				{
					if(pArray[i].isActive == TRUE)
					{
						countActive++;
					}
				}
			}
		}
		retorno = countActive;
	}
	return retorno;
}
/*
* \brief 	Devuelve como retorno la cantidad de avisos con estado==FALSE (0)
* 			que coincidan con el id pasado como parametro == idCliente de la struct Avisos
* \param Avisos* pArray puntero al array recibida
* \param int length limite del array
* \param int id, ID recibido a buscar
* \return int Return (-1) Error / (0) Ok
* */
int avisos_countPauseByIdCliente(Avisos* pArray, int length, int id)
{
	int retorno = -1;
	int i;
	int countPause = 0;
	if(pArray!=NULL && length > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				if(pArray[i].idCliente == id)
				{
					if(pArray[i].isActive == FALSE)
					{
						countPause++;
					}
				}
			}
		}
		retorno = countPause;
	}
	return retorno;
}
/**
* \brief Modifica un campo de un Avisos, dicho empleado es el indicado por el Indice pasado como parametro
* \param Avisos* pArray puntero al array recibida
* \param int length limite del array
* \param int indice Int buscado en el array para modificar alg�n campo
* \return int Return (-1) Error / (0) Ok
 */
int avisos_modifyAvisosByIndex(Avisos* pArray, int length, int indice)
{
	int retorno = -1;
	int opcionModificar;
	Avisos bufferAvisos = pArray[indice];
	if(pArray != NULL && length > 0  && indice >= 0 && indice < length)
	{
		if(utn_getNumberInt("Que desea modificar en la Avisos:\n1- Texto\n2- Rubro\n3- Id Cliente\n", "Error, ingrese una opci�n correcta. (1 - 4)", &opcionModificar, 3, 1, 4)==0)
		{
			switch(opcionModificar)
			{
				case 1:
					if(utn_getText("Ingrese el texto deseado:\n", "Error, reingrese el texto\n", bufferAvisos.texto, 3, TEXT_LONG)==0)
					{
						printf("Nombre del archivo modificado correctamente\n");
					}
					break;
				case 2:
					if(utn_getNumberInt("RUBRO NUEVO\n", "ERRROR\n", &bufferAvisos.numeroRubro, 2, 1, 10)==0)
					{
						printf("rebro del archivo modificado correctamente\n");
					}
					break;
				case 3:
					if(utn_getNumberInt("Ingrese el nuevo numero de id cliente:\n", "ERROR\n", &bufferAvisos.idCliente, 3, 0, 100)==0)
					{
						printf("id cliente modificado\n");
					}
					break;
			}
			bufferAvisos.isEmpty = FALSE;
			bufferAvisos.id = pArray[indice].id;
			bufferAvisos.isActive = TRUE;
			pArray[indice] = bufferAvisos;
			retorno = 0;
		}
	}
	return retorno;
}
/**
* \brief 	Crea los valores para los campos del avisos, que luego se sumaran al array por la funcion addAvisos
* 			Utiliza la funcion cliente_findById para determinar si el id del cliente que quiere crear el aviso existe
* \param Avisos* pArray puntero al array recibida
* \param int length limite del array
* \param Cliente* pArrayCliente puntero al array recibida
* \param int lengthCliente limite del array
* \param int* pId puntero de Id
* \param char aText[]
* \param int* pIdCliente puntero de IdCliente
* \param int* pRubro puntero del rubro
* \param int* pEstado puntero del isActive
* \return int Return (-1) Error / (0) Ok
 */
int avisos_altaAvisos(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente, int* pId, char aText[], int* pIdCliente, int* pRubro, int* pEstado)
{
	int retorno = -1;
	int idClienteSearch;
	int idContratar;
	if(pId!= NULL && aText!=NULL && pIdCliente!=NULL &&  pRubro != NULL && length > 0 && pEstado != NULL )
	{

		do
		{
			if(	utn_getNumberInt("Ingrese ID de cliente\n", "ERROR\n", &idClienteSearch, 3, 1, 100)==0)
			{
				idContratar = cliente_findById(pArrayCliente, lengthCliente, idClienteSearch);
				if( idContratar != -1)
				{
					if(	(utn_getText("Ingrese el texto deseado:\n", "Error, reingrese el texto\n", aText, 3, TEXT_LONG)==0) &&
						(utn_getNumberInt("Ingrese el rubro: \n"
								"0-Cerrajer�a, 1-Cochera / 2-Food Trucks / 3-Gimnasio / 4-Locutorio / 5-Sal�n / 6-Hoteles / 7-Educaci�n / 8-Veterinaria / 9-Recreaci�n\n", "Error, ingrese un rubro v�lido (0 - 9)\n", pRubro, 3,0, MAX_RUBROS-1)==0))
					{
						*pIdCliente = idClienteSearch;
						*pId = avisos_generarIdNuevo();
						*pEstado = 1;
						retorno = 0;
					}
				}
				else
				{
					printf("Error, Ingrese una ID v�lido:\n");
				}
			}
		}while(idContratar < 0);

	}
	return retorno;
}
/*
 *	\brief Cada vez que es llamada devuelve un ID nuevo. Que nunca devolvio antes.
 */
static int avisos_generarIdNuevo(void)
{
	static int id=0;
	id = id + 1;
	return id;
}
/*
* \brief 	Remueve un avisos del array poniendo a isEmpty == TRUE con el parametro del indice recibido
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	int indice indice recibido a buscar en el array
* \return	int Return (-1) Error / (0) Ok
*/
int avisos_remove(Avisos* pArray, int length, int indice)
{
	int retorno = -1;
	if(pArray != NULL && length > 0 && indice >= 0)
	{
		pArray[indice].isEmpty = TRUE;
		retorno = 0;
	}
	return retorno;
}
/*
* \brief 	recibe un id y recorriendo el array struct Avisos pondra en TRUE el isEmpty
* 			que coincidan el id recibido con el idCliente de avisos
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	int idClienteARemover indice recibido a buscar en el array
* \return 	int Return (-1) Error / (0) Ok
*/
int avisos_removeByIdCliente(Avisos* pArray, int length, int idClienteARemover)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && length > 0 && idClienteARemover > 0)
	{
		for(i=0; i< length;i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				if(pArray[i].idCliente == idClienteARemover)
				{
					pArray[i].isEmpty = TRUE;
				}
			}

		}
		retorno = 0;
	}
	return retorno;
}
/**
* \brief Utilizando las funciones "alta" y "add", crea un avisos valido en el array de la structura.
* \param Avisos* pArray, array recibida para crear el avisos
* \param int length limite del array
* \param Cliente* pArrayCliente, array recibida para crear el avisos
* \param int lengthCliente limite del array
* \return int Return (-1) Error / (0) Ok
 */
int avisos_create(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente)
{
	int retorno = -1;
	int id;
	char texto[TEXT_LONG];
	int idCliente;
	int rubro;
	int auxEstado;
	if(pArray != NULL && length > 0)
	{
		if(avisos_altaAvisos(pArray, length, pArrayCliente, lengthCliente, &id, texto, &idCliente, &rubro, &auxEstado)==0)
		{
			if(avisos_add(pArray, length,  id, texto, idCliente, rubro, auxEstado)==0)
			{
				printf("Carga de la avisos exitosa!\n\n");
				retorno = 0;
			}
			else
			{
				printf("No se pudo cargar la avisos\n\n");
			}
		}
		else
		{
			printf("No se pudieron obterner los datos de la avisos manera correcta\n");
		}
	}
	return retorno;
}
/*
* \brief 	recibe un indice y convierte el campo de ese indice en isActive = FALSE (0).
* 			Si el aviso ya estaba en isActive = 0, devuelve un mensaje de error
* \param 	Avisos* pArray, array recibida para crear el avisos
* \param 	int length limite del array
* \param 	int indice, numero de indice recibido a revisar
* \return	int Return (-1) Error / (0) Ok
 */
int avisos_estadoPause(Avisos* pArray, int length, int indice)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && length >0 && indice >= 0)
	{
		for(i=0; i < length;i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				if(i == indice)
				{
					if(pArray[indice].isActive == TRUE)
					{
						pArray[indice].isActive = FALSE;
						retorno = 0;
					}
					else
					{
						printf("El aviso ya estaba pausado\n");
						retorno = -2;
					}
				}
			}
		}
	}
	return retorno;
}
/*
* \brief 	recibe un indice y convierte el campo de ese indice en isActive = TRUE (1).
* 			Si el indice se encontraba en isActive = TRUE, devuelve un mensaje de error.
* \param 	Avisos* pArray, array recibida para crear el avisos
* \param 	int length limite del array
* \param 	int indice, numero de indice recibido a revisar
* \return 	int Return (-1) Error / (0) Ok
 */
int avisos_estadoActive(Avisos* pArray, int length, int indice)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && length >0 && indice >= 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				if(i == indice)
				{
					if(pArray[indice].isActive == FALSE)
					{
						pArray[indice].isActive = TRUE;
						retorno = 0;
					}
					else
					{
						printf("El aviso ya estaba activo\n");
						retorno = -2;
					}
				}
			}
		}
	}
	return retorno;
}
/*
* \brief 	recibe un id y recorriendo la struct Avisos imprime el campo rubro y su estado
* 			que coincida el id recibido con el .idCliente de avisos
* \param 	Avisos* pArray, array recibida para crear el avisos
* \param 	int length limite del array
* \return 	int Return (-1) Error / (0) Ok
 */
int avisos_printByIdCliente(Avisos* pArray, int length, int idBuscar)
{
	int retorno = -1;
	int i;
	int flagAviso = 0;
	if(pArray!=NULL && length > 0 && idBuscar > 0)
	{
		printf("Avisos que posee el cliente a dar de baja:\n");
		for(i=0;i<length;i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				if(pArray[i].idCliente == idBuscar)
				{
					printf("%15s --> %10s\n", TXT_RUBROS[pArray[i].numeroRubro], TXT_TIPOS[pArray[i].isActive]);
					flagAviso = 1;
				}
			}
		}
		if(flagAviso == 0)
		{
			printf("0\n");
		}
	}
	return retorno;
}
/*
* \brief 	Devuelve como retorno la cantidad de avisos pausados recorriendo el struct de Avisos
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \return int Return (-1) Error / numero de avisos pausados Ok
 */
int avisos_calcularAvisosPausados(Avisos* pArray, int length)
{
	int retorno = -1;
	int cantAvisosPausados = 0;
	int i;
	if(pArray!= NULL && length > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE && pArray[i].isActive == FALSE)
			{
				cantAvisosPausados++;
			}
		}
		retorno = cantAvisosPausados;
	}
	return retorno;
}
/*
* \brief Recibe un ID para comparar con los id de los avisos para retornar el idCliente de ese aviso
* \param Avisos* pArray puntero al array recibida
* \param int length limite del array
* \param int idAvisoBuscar sector recibido
* \return int Return (-1) Error / numero de ID cliente en caso de Ok
 */
int avisos_searchIdClienteByIdAviso(Avisos* pArray, int length, int idAvisoBuscar)
{
	int retorno = -1;
	int i;
	int auxIdCliente;
	if(pArray != NULL && length > 0 && idAvisoBuscar > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				if(pArray[i].id == idAvisoBuscar)
				{
					auxIdCliente = pArray[i].idCliente;
					retorno = auxIdCliente;
					break;
				}
			}
		}
	}
	return retorno;
}








