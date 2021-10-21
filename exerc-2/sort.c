#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <string.h>

typedef struct {
  char *data;
  int key;
} item_t;

/* item_t array[] = { */
/*                   {"bill", 3}, */
/*                   {"neil", 4}, */
/*                   {"john", 2}, */
/*                   {"rick", 5}, */
/*                   {"alex", 1}, */
/* }; */

gint compare_item(gconstpointer a, gconstpointer b) {
  if (((item_t *)a)->key < ((item_t *)b)->key) {
    return -1;
  }
  else if (((item_t *)a)->key > ((item_t *)b)->key) {
    return 1;
  }
  else {
    return 0;
  }
}

void print_item(gpointer data, gpointer user_data) {
  int *i = (int *) user_data;
  printf("Nº %d -> key=%d: %s\n", *i + 1, ((item_t *)data)->key, ((item_t *)data)->data);
  (*i)++;
}

GList *insert_element(GList *list, int key, char *data) {
  item_t *info = (item_t *)malloc(sizeof(item_t));
	info->key = key;
	info->data = data;
	GList *newlist = g_list_append(list, &info);
	return list;
}

item_t *item_init(char *data, int key) {
  item_t *self = malloc(sizeof(item_t));
  self->key = key;
  self->data = strdup(data); // duplica a string no heap
  return self;
}

void item_destroy(gpointer _self, gpointer unused_data) {
  item_t *self = (item_t *) _self;
  free(self->data);
  free(self);
}

int main(void) {
  //item_t a = {"bill", 3};
  GList *list = g_list_append(NULL, item_init("bill", 3));
  //item_t b = {"neil", 4};
  list = g_list_insert_sorted(list, item_init("neil", 4), compare_item);
  //item_t c = {"john", 2};
  list = g_list_insert_sorted(list, item_init("john", 2), compare_item);
  list = g_list_insert_sorted(list, item_init("sara", 7), compare_item);
  list = g_list_insert_sorted(list, item_init("rick", 5), compare_item);
  list = g_list_insert_sorted(list, item_init("alex", 1), compare_item);

  //g_list_append(list, "Second");
  //printf("The first item is '%s'\n", ((item_t *)g_list_first(list)->data)->data);
  //list = g_list_next(list);
  //printf("The second item is '%s'\n ", ((item_t *)list->data)->data;

  list = g_list_first(list);
  int i = 0;
  g_list_foreach(list, print_item, &i);

  list = g_list_first(list);
  g_list_foreach(list, item_destroy, NULL);
  g_list_free(list);
  return 0;
}

