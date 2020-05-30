#include <stdlib.h>

#include "info.h"
#include "tax.h"
#include "types.h"
#include "avlt.h"

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

	printf("\nAllocating new tax tree...\n");
	tax_tree_t tax_tree = tax_tree_empty();
	printf("Adding first tax to the tree\n");
	tax_tree = tax_add(tax_tree, information);

	printf("The tax tree is:\n");
	tax_dump(tax_tree, stdout);


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
	
	printf("\nAdding second tax to the tree\n");
	tax_tree = tax_add(tax_tree, information2);

	printf("The tax tree is:\n");
	tax_dump(tax_tree, stdout);

	printf("\nSetting up period structure for comparing... period: 10/2015\n");
	period_t period = period_empty();
	period->year = 2015;
	period->month = 10;

	printf("Exists function test:\n");
	printf("Does the tax %d/%d exists? %s\n", period->month, period->year, tax_exists(tax_tree, period) ? "true" : "false");
	printf("Is the tax %d/%d paid? %s\n", period->month, period->year, tax_is_paid(tax_tree, period) ? "true" : "false");

	printf("\nTesting date structure\n");
	printf("Setting up date structure... date: 25/4/2016\n");
	date_t date = date_empty();
	date->day = 25;
	date->month = 4;
	date->year = 2016;

	printf("Setting up pay date for tax: period: 10/2015, date: 25/4/2016");
	tax_tree = set_payment_date(tax_tree, period, date);

	printf("\nThe tax tree is:\n");
	tax_dump(tax_tree, stdout);

	printf("\nTesting tax remove\n");
	printf("Removing tax of period %d/%d...\n", period->month, period->year);
	tax_tree = tax_remove(tax_tree, period);

	printf("The tax tree is:\n");
	tax_dump(tax_tree, stdout);



	printf("\nDESTROYING...\n");
	printf("Destroying tax tree...\n");
	tax_tree = destroy_tax_tree(tax_tree);

	/*
	printf("\n---- TESTING AVL TREE STRUCT ----\n");
	avlt_t tree = avlt_empty();
	tree = avlt_add(tree, information);
	printf("\nDumping tree\n\n");
	avlt_dump(tree, stdout);
	printf("\nTesting avlt_info: test_info = avlt_info(tree, period)\n");
	info_t test_info = avlt_info(tree, period);
	printf("Printing resulting info:\n");
	info_dump(test_info, stdout);

	printf("\nRemoving one node: tree = avlt_remove(tree, period)");
	tree = avlt_remove(tree, period);
	printf("\nDumping tree\n\n");
	avlt_dump(tree, stdout);
	*/

	printf("Destroying allocated period for comparing\n");
	free(period);
	period = NULL;

	return 0;
}