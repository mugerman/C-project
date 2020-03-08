// chen frenkel 205562846	
// alon mugerman 311143366

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "header_file.h"

#define ITEMS_PATH "C:\\temp\\Items_file.txt"


void Import_employees_from_file(list* Employees_list)
{
	FILE* fp;
	int ID;
	float Salary;
	bool earnsAboveAvgbool;
	char temp[200], Fullname[20], Position[15], Date[11], earnsAboveAvg[6], c;
	initList(Employees_list);
	fp = fopen(ITEMS_PATH, "r");
	if (fp != NULL)
	{
		//printf("\n\n");
		fgets(temp, 200, fp);
		//puts(temp);
		fgets(temp, 200, fp);
		//puts(temp);

		while (fscanf(fp, "%10d %20s %15s %11s %f %5s", &ID, Fullname, Position, Date, &Salary, earnsAboveAvg) != EOF)
		{
			if (!strcmp(earnsAboveAvg, "true")) earnsAboveAvgbool = true;
			else earnsAboveAvgbool = false;
			node* Employee = allocItem(ID, Fullname, Position, Date, Salary, earnsAboveAvgbool);
			Sorted_insertion(Employees_list, Employee);
			//printf("%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
			c = fgetc(fp);
			c = fgetc(fp);
		}
	}
	else
	{
		printf("File not exisits!\n");
		return;
	}
	fclose(fp);
	return;
}


void update_employee_if_Above_Avg(list* Employees_list, float avg)
{
	node* Employee = Employees_list->head;
	while ((Employee) != NULL)
	{
		Employee->earnsAboveAvg = if_Above_Avg(avg, Employee->Salary);
		Employee = Employee->next;
	}
}


void Extract_employees_to_file(list* Employees_list)
{
	node* Employee = Employees_list->head;
	FILE *fp;
	int i = 0;
	remove(ITEMS_PATH);
	fp = fopen(ITEMS_PATH, "w+");
	fprintf(fp, "ID         Fullname             Position        Start_date   Salary[k]  EarnsAboveAvg\n\n");
	while ((Employee) != NULL)
	{
		fprintf(fp, "%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
		Employee = Employee->next;
	}
	fclose(fp);
}


void print_employee_from_list(list* Employees_list)
{
	node* Employee = Employees_list->head;
	system("cls");
	printf("ID         Fullname             Position        Start_date   Salary[k]  EarnsAboveAvg\n\n");
	while ((Employee) != NULL)
	{
		printf("%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
		Employee = Employee->next;
	}
}


void Sorted_insertion(list* Employees_list, node* Employee)
{
	node* ptr = Employees_list->head;
	if ((ptr == NULL) || (Employee->ID < Employees_list->head->ID))
		insertFirst(Employees_list, Employee);
	if (Employee->ID > Employees_list->tail->ID)
		insertLast(Employees_list, Employee);
	while (ptr != NULL)
	{
		if ((Employee->ID > ptr->ID) && (Employee->ID < ptr->next->ID))
		{
			insertAfter(Employees_list, Employee, ptr);
			return;
		}
		ptr = ptr->next;
	}
}


void Add_employee(list* Employees_list)
{
	node* Employee = (node*)malloc(sizeof(node));
	int temp;
	printf("\n Please enter a ID:  ");
	scanf("%d", &temp); system("cls");
	while (if_ID_Exists(Employees_list, temp))
	{
		printf("\nThis employee already exists, please enter a new ID:  ");
		scanf("%d", &temp); system("cls");
	}
	Employee->ID = temp;
	printf("\n Please enter a Fullname:  ");
	scanf("%s", Employee->Fullname); system("cls");
	printf("\n Please enter a Position:  ");
	scanf("%s", Employee->Position); system("cls");;
	printf("\n Please enter a date (dd.mm.yyyy):  ");
	scanf("%s", Employee->Date); system("cls");
	printf("\n Please enter a Salary:  ");
	scanf("%f", &(Employee->Salary)); system("cls");
	Sorted_insertion(Employees_list, Employee);
	Employee->earnsAboveAvg = if_Above_Avg(salaries_avg(Employees_list), Employee->Salary);
	update_employee_if_Above_Avg(Employees_list, salaries_avg(Employees_list));
}


bool Edit_employee(list* Employees_list) // if success edit return true else false
{
	system("cls");
	int num1 = 0, id;
	node* ptr = Employees_list->head;
	print_employee_from_list(Employees_list);
	printf("\n\nPlease enter the ID of employee you would like to edit: ");
	scanf("%d", &id);
	system("cls");
	while ((ptr) != NULL)
	{
		if (id == ptr->ID)
		{
			while (num1 != 9)
			{
				printf("1 - Edit Fullname \n");
				printf("2 - Edit Position \n");
				printf("3 - Edit Start date \n");
				printf("4 - Edit Salary \n");
				printf("9 - Back\n\n");
				printf("Choose from the menu:  ");
				scanf_s("%d", &num1);
				system("cls");
				switch (num1)
				{
				case 1: //Edit Fullname
				{
					printf("\n Please enter a new Fullname:  ");
					scanf("%s", ptr->Fullname);
					break;
				}
				case 2:  //Edit Position
				{
					printf("\n Please enter a new Position:  ");
					scanf("%s", ptr->Position);
					break;
				}
				case 3:  //Edit Start date
				{
					printf("\n Please enter a new start date:  ");
					scanf("%s", ptr->Date);
					break;
				}
				case 4:  //Edit Salary
				{
					printf("\n Please enter a new salary:  ");
					scanf("%f", &(ptr->Salary));
					update_employee_if_Above_Avg(Employees_list, salaries_avg(Employees_list));
					break;
				}
				case 9:
					break;
				default:
				{
					printf("Wrong number selection");
					break;
				}
				}
				system("cls");
			}
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}


bool Delete_employee(list* Employees_list)
{
	node* employee = Employees_list->head;
	system("cls");
	print_employee_from_list(Employees_list);
	int ID;
	printf("\nPlease enter the ID of employee you would like to delete: ");
	scanf("%d", &ID);
	system("cls");
	while (employee != NULL)
	{
		if (ID == employee->ID)
		{
			deleteLink(Employees_list, employee);
			update_employee_if_Above_Avg(Employees_list, salaries_avg(Employees_list));
			return true;
		}
		employee = employee->next;
	}
	return false;
}


float salaries_avg(list* Employees_list)
{
	node* Employee = Employees_list->head;
	int i = 0;
	float avg = 0;
	if (Employee == NULL) return 0;
	while ((Employee) != NULL)
	{
		avg = avg + (Employee->Salary);
		Employee = Employee->next;
		i++;
	}
	avg = avg / i;

	return avg;
}


bool if_ID_Exists(list* Employees_list, int temp)
{
	node* ptr = Employees_list->head;
	while ((ptr) != NULL)
	{
		if (temp == ptr->ID) return true;
		ptr = ptr->next;
	}
	return false;
}


void Free_list(list* Employees_list)
{
	while (!isEmpty(Employees_list))
		deleteFirst(Employees_list);
}


bool check_if_employees_file_exists()
{
	FILE *fp = fopen(ITEMS_PATH, "r");
	if (fp != NULL)
	{
		fclose(fp);
		return true;
	}
	return false;
}


bool if_Above_Avg(float avg, float Salary)
{
	if (Salary >= avg) return true;
	else return false;
}
