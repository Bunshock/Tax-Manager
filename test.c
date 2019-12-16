#include <stdlib.h>

#include "info.h"
#include "tax.h"
#include "types.h"

int main() {

	tax_list_t tax_list = tax_list_empty();
	tax_list = tax_add(tax_list, 1u);

	tax_dump(tax_list, stdout);

	tax_list = tax_add(tax_list, 56u);

	printf("FIRST TAX: \n %u\n", tax_list->list->data);
	printf("SECOND TAX: \n %u\n\n", tax_list->list->next->data);

	tax_dump(tax_list, stdout);

	tax_list = destroy_tax_list(tax_list);
	return 0;
}