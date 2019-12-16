#include <stdlib.h>

#include "info.h"
#include "tax.h"
#include "types.h"

int main() {

	printf("Setting up new information structure...\n");
	info_t information = info_empty();
	information->cost = 300u;
	information->month = 10u;
	information->year = 2015u;
	information->bill = "Gas";
	information->unit = "m3";
	information->currency = "ARS";
	information->paid = true;
	information->consumption = 800u;
	printf("Information for structure set:\n");
	info_dump(information, stdout);
	
	printf("\nAllocating new tax list...\n");
	tax_list_t tax_list = tax_list_empty();
	printf("Adding first tax to the list\n");
	tax_list = tax_add(tax_list, information);

	printf("The tax list is:\n");
	tax_dump(tax_list, stdout);


	printf("\nSetting up new information structure...\n");
	info_t information2 = info_empty();
	information2->cost = 45u;
	information2->month = 11u;
	information2->year = 2017u;
	information2->bill = "Luz";
	information2->unit = "kwh";
	information2->currency = "USD";
	information2->paid = true;
	information2->consumption = 20u;
	printf("Information for structure set:\n");
	info_dump(information2, stdout);
	
	printf("Adding second tax to the list\n");
	tax_list = tax_add(tax_list, information2);

	printf("The tax list is:\n");
	tax_dump(tax_list, stdout);

	/*
	tax_list = tax_add(tax_list, 56u);

	printf("FIRST TAX: \n %u\n", tax_list->list->data);
	printf("SECOND TAX: \n %u\n\n", tax_list->list->next->data);

	tax_dump(tax_list, stdout);
*/
	printf("Destroying tax list...\n");
	tax_list = destroy_tax_list(tax_list);

	printf("\n---- TESTING INFO STRUCT ----\n");
	printf("\nAllocating info struct\n");
	info_t info = info_empty();
	
	printf("Destroying allocated info\n");
	info = destroy_info(info);

	return 0;
}