#include <stdlib.h>
#include <stdio.h>

typedef struct {
  char *data;
  int key;
} item_t;

//item_t array[] = { 
//                {"bill", 3},
//                {"neil", 4},
//                {"john", 2},
//                {"rick", 5},
//                {"alex", 1},
//};

void sort(item_t * a, int n) {
  int i = 0, j = 0;
  int s = 1;

  for(; i < n && s != 0; i++) {
    s = 0;
    for(j = 0; j < n-1; j++) {
      if(a[j].key > a[j+1].key) {
        item_t t = a[j];
        a[j] = a[j+1];
        a[j+1] = t;

        s++;

      }
    }
    //n--;
  }
}

// Método construtor:
item_t *array_new(int tam) {
	item_t *array = (item_t *) malloc(tam * sizeof(item_t));
	for(int i = 0; i < tam; i++)
	{
		array[i].data = NULL;
		array[i].key = 0;
	}
	return array;
}

// Método destrutor:
void array_destroy(item_t *array) {
	free(array);
}

// Método para adicionar valores ao array:
void array_add(item_t *array, int key, const char *valor) {

  int i;
  int t;
  for(i=0;; i++)
    {
      if(array[i].data == NULL)
        break;
    }
		
	for(t=0;; t++) {
		if(valor[t] == '\0')
			break;
	}
	
	array[i].data = malloc((t + 1) * sizeof(char));
	
	for(int j = 0; j < t + 1; j++) {
		array[i].data[j] = valor[j];
	}
	array[i].key = key;
}

int main(void) {
  item_t *array;
	array = array_new(5);
	array_add(array, 3, "bill");
	array_add(array, 4, "neil");
	array_add(array, 2, "john");
	array_add(array, 5, "rick");
	array_add(array, 1, "alex");

	sort(array,5);
  for(int i = 0; i < 5; i++) {
    printf("array[%d] = {%s, %d}\n", i, array[i].data, array[i].key);
  }
  array_destroy(array);
 }
