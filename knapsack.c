#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "knapsack.h"
#include "item.h"
#include "helpers.h"
#include "string.h"

//Debido a las distintas notaciones entre el pseudocódigo y el lenguaje C, cada vez que se trabaje con el largo del arreglo se tomará el tamaño del arreglo - 1, de esta manera compensando esta diferencia de notación

value_t knapsack_backtracking(item_t* items, unsigned int array_length, weight_t max_weight){
	//Creo un pseudocódigo basado en la notación matemática: mochila(i,j) ={0 [j=0],0 [j>0 && i=0], mochila(i-1,j) [wi]>j>0 && i>0, max(mochila(i-1,j),vi+mochila(i-1,j-wi) [j>wi>0 && i>0]
	//En el pseudocódigo: j = max_weight, i = array_length, wi = item_weight(items[i]) (peso del elemento i), vi = item_value(items[i]) (valor del elemento i)
	//Defino la variable de retorno 
	value_t r;
	//Adapto la estructura del pseudocódigo, reemplazando los valores i, j, vi, wi por sus correspondientes equivalencias
	if (max_weight == 0){
		r = 0;	
	}
	else if(max_weight > 0 && array_length==0){
		r = 0;
	}
	else if (item_weight(items[array_length-1]) > max_weight){
		r=knapsack_backtracking(items,array_length-1,max_weight);
	}
	else if (max_weight>= item_weight(items[array_length-1]) && array_length>0) {
		r = fmax(knapsack_backtracking(items,array_length-1,max_weight),item_value(items[array_length-1])+knapsack_backtracking(items,array_length-1,max_weight-item_weight(items[array_length-1])));
	}
	return r;

}


value_t knapsack_dynamic(item_t* items, unsigned array_length, weight_t max_weight){
	//Siguiendo el pseudocódigo provisto por el teórico
	//Cro una tabla de valores
	value_t** moch;
	//Reservo memoria para la tabla de valores
	moch = calloc(array_length+1, sizeof(value_t*));
	//Defino la variable de retorno
	value_t r;
	//Reservo memoria para los elementos de la tabla de valores
	for (unsigned int i=0; i<=array_length; i++){ 
		moch[i] = calloc(max_weight+1,(sizeof(value_t))); 
	}
	
	for (unsigned int i=0; i<=array_length; i++){ 
		moch[i][0] = 0; 
	}
	for (unsigned int j=1; j<=max_weight; j++){
		moch[0][j] = 0;
	}
	for (unsigned int i=1; i <= array_length; i++){ 
		for (unsigned int j=1; j<=max_weight; j++) 
			if (item_weight(items[i-1]) > j){ 
				moch[i][j] = moch[i-1][j];
			}
			else{
				moch[i][j] = fmax(moch[i-1][j],item_value(items[i-1])+moch[i-1][j-item_weight(items[i-1])]);
			}
	}
	r = moch[array_length][max_weight];
	//Libero la memoria reservada para cada uno de los elementos del arreglo
	for (unsigned int i=0; i<=array_length; i++){ 
		free(moch[i]);
		moch[i] = NULL;
	}
	//Libero la memoria reservada para el arreglo
	free(moch);
	return r;
}
value_t knapsack_dynamic_selection(item_t* items, bool* selected, unsigned int array_length, weight_t max_weight){
	//Siguiendo la estructura del pseudocódigo provisto por el material teórico
	//La función es muy similar a la anterior, salvo por las variables r y s
	//Creo una tabla de valores de la forma puntero a puntero pues es una matriz
	value_t** moch;
	//Reservo memoria para la tabla
	moch = calloc(array_length+1, sizeof(value_t*));
	//Defino una variable de retorno
	value_t t;
	int r,s;
	//Reservo memoria para los elementos de la tabla
	for (unsigned int i=0; i<=array_length; i++){ 
		moch[i] = calloc(max_weight+1,(sizeof(value_t))); 
	}
	
	for (unsigned int i=0; i<=array_length; i++){ 
		moch[i][0] = 0; 
	}
	for (unsigned int j=1; j<=max_weight; j++){
		moch[0][j] = 0;
	}
	for (unsigned int i=1; i <= array_length; i++){ 
		for (unsigned int j=1; j<=max_weight; j++) 
			if (item_weight(items[i-1]) > j){ 
				moch[i][j] = moch[i-1][j];
			}
			else{
				moch[i][j] = fmax(moch[i-1][j],item_value(items[i-1])+moch[i-1][j-item_weight(items[i-1])]);
			}
	}
	//Asigno el largo del arreglo y el peso máximo a sus respectivas variables según el pseudocódigo
	r = array_length;
	s = max_weight;
	while (moch[r][s]>0){
		if (moch[r][s]==moch[r-1][s]){
			selected[r] = 0;	
		}
		else{
			selected[r] = 1;
			s = s-item_weight(items[r-1]);
		}
		r = r-1;
	}
	t = moch[array_length][max_weight];
	//Libero la memoria reservada para los elementos del arreglo
	for (unsigned int i=0; i<=array_length; i++){ 
		free(moch[i]);
		moch[i] = NULL;
	}
	//Libero la memoria reservada para el arreglo
	free(moch);
	return t;
}
	
