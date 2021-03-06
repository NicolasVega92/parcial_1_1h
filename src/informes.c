/*
 * informes.c
 *
 *  Created on: 11 oct. 2020
 *      Author: Nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "avisos.h"
#include "utn.h"
#include "informes.h"
static int aux_init(Auxiliar* pArray, int length);
static int aux_printMaxAvisosWithCuit(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length, int indicesRecorrer);
static int aux_calcularCantDeAvisosByIdCliente(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length);
static int aux_printMaxRubro(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length,int indiceARecorrer);
static int aux_calcularCantRubros(Auxiliar* arrayAux, int length, Avisos* pArray, int indiceARecorrer);
static int aux_calcularCantDeAvisosActivosByIdCliente(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length);
static int aux_printMaxAvisosActivosWithCuit(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length, int indicesRecorrer);
static int aux_calcularCantDeAvisosPausadosByIdCliente(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length);
static int aux_printMaxAvisosPausadosWithCuit(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length, int indicesRecorrer);
static int aux_crearCampos(Auxiliar* arrayAux, int lengthCliente, Cliente* pArrayCliente, int* pIndiceCuitLibre);



/*
* \brief 	Imprime los valores del Cliente y le agrega al print la cantidad de avisos buscados por la funcion
* 			avisos_countActiveByIdCliente() Y avisos_countPauseByIdCliente()
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	Cliente* pArrayCliente puntero al array recibida
* \param 	int lengthCliente limite del array
* \return int Return (-1) Error / (0) Ok
*/
int info_printClienteWithAvisos(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente)
{
	int retorno = -1;
	int i;
	int contadorActivos;
	int contadorPausados;
	if(pArray != NULL && pArrayCliente != NULL && length > 0 && lengthCliente > 0)
	{
		printf(" ID|         Nombre|       Apellido|           CUIT|  Avisos activos| Avisos Pausados|\n");
		for(i=0; i < lengthCliente; i++)
		{
			if(pArrayCliente[i].isEmpty == FALSE)
			{
				contadorActivos = avisos_countActiveByIdCliente(pArray, QTY_AVISOS, pArrayCliente[i].id);
				contadorPausados = avisos_countPauseByIdCliente(pArray, QTY_AVISOS, pArrayCliente[i].id);
				printf("%3d|%15s|%15s|%15s|%16d|%16d|\n", pArrayCliente[i].id, pArrayCliente[i].nameCliente, pArrayCliente[i].lastName, pArrayCliente[i].cuit, contadorActivos, contadorPausados);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
* \brief	Inicializa todas las posiciones del array en el campo isEmpty== (TRUE).
* 			Inicializa todas las posiciones del array en el campo cantidad = 0
* \param 	Auxiliar* pArray puntero al array recibido
* \param 	int length limite del array
* \return 	(-1) si se encuentra un error / (0)  Ok
*/
static int aux_init(Auxiliar* pArray, int length)
{
	int retorno = -1;
	int i;
	if(pArray != NULL && length > 0)
	{
		for(i=0;i<length ;i++)
		{
			pArray[i].isEmpty = TRUE;
			pArray[i].cantidad = 0;
		}
		retorno = 0;
	}
	return retorno;
}
/*
* \brief 	Crea una estructura auxiliar para generar campos a utilizar, luego llama a otras funciones para los prints
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	Cliente* pArrayCliente puntero al array recibida
* \param 	int lengthCliente limite del array
* \return 	int Return (-1) Error / (0) Ok
 */
int info_calcularMaxAvisosByCuit(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente)
{
	int retorno = -1;
	Auxiliar arrayAux[lengthCliente];
	int indiceCuitLibre;
	if(pArray != NULL && pArrayCliente != NULL && length > 0 && lengthCliente > 0)
	{
		if(aux_init(arrayAux, lengthCliente)==0)
		{
			if(aux_crearCampos(arrayAux, lengthCliente, pArrayCliente, &indiceCuitLibre)==0)
			{
				printf("funca\n\n");
			}
			if(aux_printMaxAvisosWithCuit(arrayAux, lengthCliente, pArray, length, indiceCuitLibre)==0)
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}
/*
* \brief 	Agrega en los campos de la estructura nuevos clientes verificando que no haya repetidos por medio del CUIT
* 			Agrega los campos CUIT, idCliente e isEmpty
* \param 	Auxiliar* pArray puntero al array recibida
* \param 	int lengthCliente limite del array
* \param 	Cliente* pArrayCliente puntero al array recibida
* \param 	int* pIndiceCuitLibre puntero al indice que luego se utilizara como l�mite
* \return 	int Return (-1) Error / (0) Ok
 */
static int aux_crearCampos(Auxiliar* arrayAux, int lengthCliente, Cliente* pArrayCliente, int* pIndiceCuitLibre)
{
	int retorno = -1;
	int indiceCuitLibre=0;
	int flagExiste;
	int i;
	int j;
	//Luego de inicializar el Auxiliar recorre el arrayClientes y en los cargados verifica si el CUIT existe en el array Auxiliar
	//en caso de que si el flagExiste = 1 y no hace nada.
	//Si no coincide se agrega el CUIT, idCliente y isEmpty al Auxiliar
	//el indiceCuitLibre aumenta
	if(arrayAux != NULL && pArrayCliente != NULL && lengthCliente > 0)
	{
		for(i=0; i < lengthCliente; i++)
		{
			if(pArrayCliente[i].isEmpty == FALSE)
			{
				flagExiste = 0;
				for(j=0; j < indiceCuitLibre; j++)
				{
					if(arrayAux[j].isEmpty == FALSE && strncmp(arrayAux[j].cuit, pArrayCliente[i].cuit, LONG_NAME)==0)
					{
						flagExiste = 1;
						break;
					}
				}
				if(flagExiste == 0)
				{
					strncpy(arrayAux[indiceCuitLibre].cuit, pArrayCliente[i].cuit, LONG_NAME);
					arrayAux[indiceCuitLibre].idCliente = pArrayCliente[i].id;
					arrayAux[indiceCuitLibre].isEmpty = FALSE;
					indiceCuitLibre++;
				}
			}
		}
		*pIndiceCuitLibre = indiceCuitLibre;
	}
	return retorno;
}
/*
* \brief 	Imprime el id del cliente con la cantidad de avisos que posee
* 			Imprime el cliente con su cuit y el que tiene mas Avisos
* \param 	Auxiliar* arrayAux puntero al array recibida
* \param 	int length lengthAux del array
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param	int indicesRecorrer limite del array
* \return int Return (-1) Error / (0) Ok
 */
static int aux_printMaxAvisosWithCuit(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length, int indicesRecorrer)
{
	int retorno = -1;
	int i;
	int maxAvisos;
	if(arrayAux!= NULL && lengthAux >0 && pArray != NULL && length > 0 && indicesRecorrer >= 0)
	{
		if(aux_calcularCantDeAvisosByIdCliente(arrayAux, lengthAux, pArray, length)==0)
		{
			for(i=0; i< indicesRecorrer;i++)
			{
				//Print de todos los id clientes con su cantidad de avisos activos y pausados
				printf("cliente con ID: %d tiene %d avisos\n", arrayAux[i].idCliente, arrayAux[i].cantidad);
				if(arrayAux[i].cantidad > maxAvisos || i==0)
				{
					maxAvisos = arrayAux[i].cantidad;
				}
			}
			for(i=0; i < indicesRecorrer; i++)
			{
				if(maxAvisos == arrayAux[i].cantidad)
				{
					//print del maximo cliente con avisos act y pausados
					printf("\nEl cliente con mas Avisos es el del ID %d con CUIT: %s con %d avisos\n", arrayAux[i].idCliente, arrayAux[i].cuit,maxAvisos);
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}
/*
* \brief 	Calcula en la estructura Auxiliar la cantidad de avisos que coinciden con el idCliente del array de Avisos
* \param 	Auxiliar* arrayAux puntero al array recibida
* \param 	int length lengthAux del array
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \return 	int Return (-1) Error / (0) Ok
 */
static int aux_calcularCantDeAvisosByIdCliente(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length)
{
	int retorno=-1;
	int i;
	int j;
	if(arrayAux!= NULL && lengthAux >0 && pArray != NULL && length > 0)
	{
		for(i = 0; i < lengthAux;i++)
		{
			if(arrayAux[i].isEmpty == FALSE)
			{
				for(j=0; j < length;j++)
				{
					if(pArray[j].isEmpty == FALSE && arrayAux[i].idCliente == pArray[j].idCliente)
					{
						arrayAux[i].cantidad++;
					}
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
* \brief 	Crea una estructura auxiliar para generar campos a utilizar, luego llama a otras funciones para los prints
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	Cliente* pArrayCliente puntero al array recibida
* \param 	int lengthCliente limite del array
* \return 	int Return (-1) Error / (0) Ok
 */
int info_calcularMaxAvisosActivosByCuit(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente)
{
	int retorno = -1;
	Auxiliar arrayAux[lengthCliente];
	int indiceCuitLibre;
	if(pArray != NULL && pArrayCliente != NULL && length > 0 && lengthCliente > 0)
	{
		if(aux_init(arrayAux, lengthCliente)==0)
		{
			//Luego de inicializar el Auxiliar recorre el arrayClientes y en los cargados verifica si el CUIT existe en el array Auxiliar
			//en caso de que si el flagExiste = 1 y no hace nada.
			//Si no coincide se agrega el CUIT, idCliente y isEmpty al Auxiliar
			//el indiceCuitLibre aumenta
			if(aux_crearCampos(arrayAux, lengthCliente, pArrayCliente, &indiceCuitLibre)==0)
			{
				printf("funca\n\n");
			}
			if(aux_printMaxAvisosActivosWithCuit(arrayAux, lengthCliente, pArray, length, indiceCuitLibre)==0)
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}
/*
 *
 */
static int aux_printMaxAvisosActivosWithCuit(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length, int indicesRecorrer)
{
	int retorno = -1;
	int i;
	int maxAvisos;
	if(arrayAux!= NULL && lengthAux >0 && pArray != NULL && length > 0 && indicesRecorrer >= 0)
	{
		if(aux_calcularCantDeAvisosActivosByIdCliente(arrayAux, lengthAux, pArray, length)==0)
		{
			for(i=0; i< indicesRecorrer;i++)
			{
				//Print de todos los id clientes con su cantidad de avisos activos y pausados
				printf("cliente con ID: %d tiene %d avisos\n", arrayAux[i].idCliente, arrayAux[i].cantidad);
				if(arrayAux[i].cantidad > maxAvisos || i==0)
				{
					maxAvisos = arrayAux[i].cantidad;
				}
			}
			for(i=0; i < indicesRecorrer; i++)
			{
				if(maxAvisos == arrayAux[i].cantidad)
				{
					//print del maximo cliente con avisos act y pausados
					printf("\nEl cliente con mas Avisos Activos es el del ID %d con CUIT: %s con %d avisos\n", arrayAux[i].idCliente, arrayAux[i].cuit,maxAvisos);
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}
/*
 *
 */
static int aux_calcularCantDeAvisosActivosByIdCliente(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length)
{
	int retorno=-1;
	int i;
	int j;
	if(arrayAux!= NULL && lengthAux >0 && pArray != NULL && length > 0)
	{
		for(i = 0; i < lengthAux;i++)
		{
			if(arrayAux[i].isEmpty == FALSE)
			{
				for(j=0; j < length;j++)
				{
					if(pArray[j].isEmpty == FALSE && arrayAux[i].idCliente == pArray[j].idCliente && pArray[j].isActive == TRUE)
					{
						arrayAux[i].cantidad++;
					}
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
* \brief 	Crea una estructura auxiliar para generar campos a utilizar, luego llama a otras funciones para los prints
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	Cliente* pArrayCliente puntero al array recibida
* \param 	int lengthCliente limite del array
* \return 	int Return (-1) Error / (0) Ok
 */
int info_calcularMaxRubro(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente)
{
	int retorno = -1;
	Auxiliar arrayAux[lengthCliente];
	int i;
	int j;
	int flagExiste;
	int indiceCuitLibre = 0;
	if(pArray != NULL && pArrayCliente != NULL && length > 0 && lengthCliente > 0)
	{
		if(aux_init(arrayAux, lengthCliente)==0)
		{
			for(i=0; i < lengthCliente; i++)
			{
				if(pArray[i].isEmpty == FALSE)
				{
					flagExiste = 0;
					for(j=0; j < indiceCuitLibre; j++)
					{
						if(arrayAux[j].isEmpty == FALSE && pArray[i].numeroRubro == arrayAux[j].rubros)
						{
							flagExiste = 1;
							break;
						}
					}
					if(flagExiste == 0)
					{
						arrayAux[indiceCuitLibre].rubros = pArray[i].numeroRubro;
						arrayAux[indiceCuitLibre].isEmpty = FALSE;
						indiceCuitLibre++;
					}
				}
			}
			if(aux_printMaxRubro(arrayAux, lengthCliente, pArray, length, indiceCuitLibre)==0)
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}
/*
* \brief 	Imprime el rubro con sus avisos
* 			Imprime el rubro con mas cantidad y su cantidad
* \param 	Auxiliar* arrayAux puntero al array recibida
* \param 	int lengthAux limite del array
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	int indiceARecorrer numero de indices cargados
* \return 	int Return (-1) Error / (0) Ok
 */
static int aux_printMaxRubro(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length, int indiceARecorrer)
{
	int retorno = -1;
	int i;
	int avisosMax;
	if(arrayAux!= NULL && lengthAux > 0 && pArray !=NULL && length > 0 && indiceARecorrer > 0)
	{
		if(aux_calcularCantRubros(arrayAux, lengthAux, pArray, indiceARecorrer)==0)
		{
			for(i=0; i< indiceARecorrer;i++)
			{
				printf("El rubro: %s tiene %d avisos\n", TXT_RUBROS[arrayAux[i].rubros], arrayAux[i].cantidad);
				if(arrayAux[i].cantidad > avisosMax || i==0)
				{
					avisosMax = arrayAux[i].cantidad;
				}
			}
			for(i=0; i< indiceARecorrer;i++)
			{
				if(avisosMax == arrayAux[i].cantidad)
				{
					printf("\nEl rubro con mas Avisos es el de %s con %d avisos\n", TXT_RUBROS[arrayAux[i].rubros], avisosMax);
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}
/*
* \brief	Calcula la cantidad de rubros que coinciden con el rubro del array de Avisos
* \param 	Auxiliar* arrayAux puntero al array recibida
* \param 	int length limite del array
* \param 	Avisos* pArray puntero al array recibida
* \param 	int indiceARecorrer numero de indices cargados
* \return 	int Return (-1) Error / (0) Ok
 */
static int aux_calcularCantRubros(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int indiceARecorrer)
{
	int retorno = -1;
	int j;
	int i;
	if(arrayAux!=NULL && lengthAux > 0 && pArray != NULL && indiceARecorrer > 0)
	{
		for(i = 0; i < indiceARecorrer;i++)
		{
			if(arrayAux[i].isEmpty == FALSE)
			{
				for(j=0; j < lengthAux;j++)
				{
					if(pArray[j].isEmpty == FALSE && arrayAux[i].rubros == pArray[j].numeroRubro)
					{
						arrayAux[i].cantidad++;
					}
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
* NO USAR
*/
int info_printClienteWithCantidadAvisos(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente, char cuit[])
{
	int retorno = -1;
	int i;
	int indiceArrayCliente;
	int contadorAvisos=0;
	if(pArray != NULL && pArrayCliente != NULL && cuit != NULL && length > 0 && lengthCliente > 0)
	{
		for(i=0; i < length; i++)
		{
			if(pArray[i].isEmpty == FALSE)
			{
				indiceArrayCliente = cliente_findById(pArrayCliente, QTY_CLIENTE, pArray[i].idCliente);
				if(indiceArrayCliente != -1)
				{
					contadorAvisos++;
				}
				printf("Id:%d  - Nombre: %s  -  Apellido: %s  -   Cuit: %s  - Cantidad de avisos contratados: %d \n",
																												pArrayCliente[i].id,
																												pArrayCliente[i].nameCliente,
																												pArrayCliente[i].lastName,
																												pArrayCliente[i].cuit,
																												contadorAvisos);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
 * NO USAR
 */
int info_countActiveByIdCliente(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente)
{
	int retorno = -1;
	int i;
	int j;
	int countActive = 0;
	int maxClienteAvisos;
	int idMaxCliente;
	if(pArray!=NULL && length > 0)
	{
		for(i=0; i < lengthCliente; i++)
		{
			if(pArrayCliente[i].isEmpty == FALSE)
			{
				for(j=0; j<length;j++)
				{
					if(pArrayCliente[i].id == pArray[j].idCliente)
					{
						if(pArray[j].isActive == TRUE)
						{
							countActive++;
						}
					}
				}
				if(i==0 || countActive > maxClienteAvisos)
				{
					maxClienteAvisos = countActive;
					idMaxCliente = i;
				}

			}
		}
		printf("El cliente con mas avisos activos es %s con %d\n\n", pArrayCliente[idMaxCliente].nameCliente, countActive);
		retorno = 0;
	}
	return retorno;
}
/*
* \brief 	Crea una estructura auxiliar para generar campos a utilizar, luego llama a otras funciones para los prints
* \param 	Avisos* pArray puntero al array recibida
* \param 	int length limite del array
* \param 	Cliente* pArrayCliente puntero al array recibida
* \param 	int lengthCliente limite del array
* \return 	int Return (-1) Error / (0) Ok
 */
int info_calcularMaxAvisosPausadosByCuit(Avisos* pArray, int length, Cliente* pArrayCliente, int lengthCliente)
{
	int retorno = -1;
	Auxiliar arrayAux[lengthCliente];
	int indiceCuitLibre;
	if(pArray != NULL && pArrayCliente != NULL && length > 0 && lengthCliente > 0)
	{
		if(aux_init(arrayAux, lengthCliente)==0)
		{
			//Luego de inicializar el Auxiliar recorre el arrayClientes y en los cargados verifica si el CUIT existe en el array Auxiliar
			//en caso de que si el flagExiste = 1 y no hace nada.
			//Si no coincide se agrega el CUIT, idCliente y isEmpty al Auxiliar
			//el indiceCuitLibre aumenta
			if(aux_crearCampos(arrayAux, lengthCliente, pArrayCliente, &indiceCuitLibre)==0)
			{
				printf("funca\n\n");
			}
			if(aux_printMaxAvisosPausadosWithCuit(arrayAux, lengthCliente, pArray, length, indiceCuitLibre)==0)
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}
/*
 *
 */
static int aux_printMaxAvisosPausadosWithCuit(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length, int indicesRecorrer)
{
	int retorno = -1;
	int i;
	int maxAvisos;
	if(arrayAux!= NULL && lengthAux >0 && pArray != NULL && length > 0 && indicesRecorrer >= 0)
	{
		if(aux_calcularCantDeAvisosPausadosByIdCliente(arrayAux, lengthAux, pArray, length)==0)
		{
			for(i=0; i< indicesRecorrer;i++)
			{
				//Print de todos los id clientes con su cantidad de avisos activos y pausados
				printf("cliente con ID: %d tiene %d avisos\n", arrayAux[i].idCliente, arrayAux[i].cantidad);
				if(arrayAux[i].cantidad > maxAvisos || i==0)
				{
					maxAvisos = arrayAux[i].cantidad;
				}
			}
			for(i=0; i < indicesRecorrer; i++)
			{
				if(maxAvisos == arrayAux[i].cantidad)
				{
					//print del maximo cliente con avisos act y pausados
					printf("\nEl cliente con mas Avisos Pausados es el del ID %d con CUIT: %s con %d avisos\n", arrayAux[i].idCliente, arrayAux[i].cuit,maxAvisos);
				}
			}
			retorno = 0;
		}
	}
	return retorno;
}
/*
 *
 */
static int aux_calcularCantDeAvisosPausadosByIdCliente(Auxiliar* arrayAux, int lengthAux, Avisos* pArray, int length)
{
	int retorno=-1;
	int i;
	int j;
	if(arrayAux!= NULL && lengthAux >0 && pArray != NULL && length > 0)
	{
		for(i = 0; i < lengthAux;i++)
		{
			if(arrayAux[i].isEmpty == FALSE)
			{
				for(j=0; j < length;j++)
				{
					if(pArray[j].isEmpty == FALSE && arrayAux[i].idCliente == pArray[j].idCliente && pArray[j].isActive == FALSE)
					{
						arrayAux[i].cantidad++;
					}
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}



