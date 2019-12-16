#include <stdlib.h>

#include "info.h"
#include "tax.h"
#include "types.h"

int main() {

	printf("Setting up new information structure...\n");
	info_t information = info_empty();
	information->cost = 300u;
	information->period->month = 10u;
	information->period->year = 2015u;
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
	information2->period->month = 11u;
	information2->period->year = 2017u;
	information2->bill = "Luz";
	information2->unit = "kwh";
	information2->currency = "USD";
	information2->paid = false;
	information2->consumption = 20u;
	printf("Information for structure set:\n");
	info_dump(information2, stdout);
	
	printf("Adding second tax to the list\n");
	tax_list = tax_add(tax_list, information2);

	printf("The tax list is:\n");
	tax_dump(tax_list, stdout);

	printf("Setting up period structure for comparing...\n");
	period_t period = period_empty();
	period->year = 2015;
	period->month = 10;

	printf("Exists function test:\n");
	printf("Does the tax %d/%d exists? %s\n", period->month, period->year, tax_exists(tax_list, period) ? "true" : "false");
	printf("Is the tax %d/%d paid? %s\n", period->month, period->year, tax_is_paid(tax_list, period) ? "true" : "false");

	printf("\nTesting date structure\n");
	printf("Setting up date structure...\n");
	date_t date = date_empty();
	date->day = 25;
	date->month = 4;
	date->year = 2016;

	printf("Setting up pay date for tax");
	tax_list = set_payment_date(tax_list, period, date);

	printf("The tax list is:\n");
	tax_dump(tax_list, stdout);

	printf("\nTesting tax remove\n");
	printf("Removing tax of period %d/%d...\n", period->month, period->year);
	tax_list = tax_remove(tax_list, period);

	printf("The tax list is:\n");
	tax_dump(tax_list, stdout);

	

	printf("\nDESTROYING...\n");
	printf("Destroying tax list...\n");
	tax_list = destroy_tax_list(tax_list);

	printf("\n---- TESTING INFO STRUCT ----\n");
	printf("\nAllocating info struct\n");
	info_t info = info_empty();
	
	printf("Destroying allocated info\n");
	info = destroy_info(info);

	printf("Destroying allocated period\n");
	free(period);

	printf("Destroying allocated date\n");
	destroy_date(date);

	return 0;
}