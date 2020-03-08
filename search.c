// chen frenkel 205562846	
// alon mugerman 311143366

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "header_file.h"



void Search_menu(list* Employees_list)
{
	int num1 = 0;
	system("cls");
	while (num1 != 9)
	{
		printf("Search menu: \n");
		printf("1 - Search by ID \n");
		printf("2 - Search by FullName \n");
		printf("3 - Search by Position \n");
		printf("4 - Search by FullName and Job \n");
		printf("5 - Search by Date \n");
		printf("6 - Search by Average salary \n");
		printf("9 - Back\n\n");
		printf("Choose from the menu:  ");
		scanf_s("%d", &num1);
		switch (num1)
		{
		case 1: //Search by ID
		{
			Search_by_ID(Employees_list);
			return;
		}
		case 2:  //Search by FullName
		{
			Search_by_FullName(Employees_list);
			return;
		}
		case 3:  //Search by Position
		{
			Search_by_Position(Employees_list);
			return;
		}
		case 4:  //Search by FullName and Job
		{
			Search_by_FullName_and_Position(Employees_list);
			return;
		}
		case 5:  //Search by Date
		{
			Search_by_Date(Employees_list);
			return;
		}
		case 6:  //Search by if above avg salary
		{
			Search_by_if_above_avg_salary(Employees_list);
			return;
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
}


void Search_by_ID(list* Employees_list)
{
	system("cls");
	int ID;
	printf("Please enter ID:  ");
	scanf("%d", &ID); 	system("cls");
	node* Employee = Employees_list->head;
	while ((Employee) != NULL)
	{
		if (ID == Employee->ID)
		{
			printf("ID         Fullname             Position        Start_date   Salary[k]  EarnsAboveAvg\n\n");
			printf("\n%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n\n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
			return;
		}
		Employee = Employee->next;
	}
	printf("Nothing found\n\n");
}


void Search_by_FullName(list* Employees_list)
{
	system("cls");
	char Fullname[20];
	printf("Please enter FullName:  ");
	scanf("%s", Fullname); 	system("cls");
	node* Employee = Employees_list->head;
	printf("ID         Fullname             Position        Start_date   Salary[k]  EarnsAboveAvg\n\n");
	while ((Employee) != NULL)
	{
		if (!strcmp(Fullname, Employee->Fullname))
			printf("\n%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
		Employee = Employee->next;
	}
	printf("\n\n");
}


void Search_by_Position(list* Employees_list)
{
	system("cls");
	char Position[15];
	printf("Please enter a Position:  ");
	scanf("%s", Position); 	system("cls");
	node* Employee = Employees_list->head;
	printf("ID         Fullname             Position        Start_date   Salary[k]  EarnsAboveAvg\n\n");
	while ((Employee) != NULL)
	{
		if (!strcmp(Position, Employee->Position))
			printf("%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
		Employee = Employee->next;
	}
	printf("\n\n");
}


void Search_by_FullName_and_Position(list* Employees_list)
{
	system("cls");
	char Fullname[20], Position[15];
	printf("Please enter FullName:  ");
	scanf("%s", Fullname);
	printf("\nPlease enter a Position:  ");
	scanf("%s", Position); 	system("cls");
	node* Employee = Employees_list->head;
	printf("ID         Fullname             Position        Start_date   Salary[k]  EarnsAboveAvg\n\n");
	while ((Employee) != NULL)
	{
		if (!(strcmp(Fullname, Employee->Fullname) || strcmp(Position, Employee->Position)))
			printf("\n%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
		Employee = Employee->next;
	}
	printf("\n\n");
}


void Search_by_Date(list* Employees_list)
{
	system("cls");
	int num = 0, ins_day, ins_month, ins_year, emp_day, emp_month, emp_year;
	char Date[11];
	printf("1 - After the date\n");
	printf("2 - Before the date\n");
	printf("9 - back\n");
	scanf("%d", &num); 	system("cls");
	while (!(num == 1 || num == 2 || num == 9))
	{
		printf("Wrong number of selection, please enter a new one:  ");
		scanf("%d", &num); 	system("cls");
	}
	if (num == 9)  return;
	node* Employee = Employees_list->head;
	printf("Please enter a date: ");
	scanf("%s", Date); 	system("cls");
	sscanf(strtok(Date, "."), "%d", &ins_day);
	sscanf(strtok(NULL, "."), "%d", &ins_month);
	sscanf(strtok(NULL, "."), "%d", &ins_year);
	printf("ID         Fullname             Position        Start_date   Salary[k]  EarnsAboveAvg\n\n");
	while (Employee != NULL)
	{
		strcpy(Date, Employee->Date);
		sscanf(strtok(Date, "."), "%d", &emp_day);
		sscanf(strtok(NULL, "."), "%d", &emp_month);
		sscanf(strtok(NULL, "."), "%d", &emp_year);
		if (num == 1) // after
		{
			if (emp_year > ins_year) printf("%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
			if (emp_year == ins_year)
			{
				if (emp_month > ins_month) printf("%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
				if (emp_month == ins_month)
					if (emp_day >= ins_day) printf("%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
			}
		}
		if (num == 2) //before
		{
			if (emp_year < ins_year) printf("%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
			if (emp_year == ins_year)
			{
				if (emp_month < ins_month) printf("%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
				if (emp_month == ins_month)
					if (emp_day < ins_day) printf("%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
			}
		}
		Employee = Employee->next;
	}
	printf("\n\n");
}


void Search_by_if_above_avg_salary(list* Employees_list)
{
	system("cls");
	int num;
	printf("1 - Above average\n");
	printf("2 - Below average\n");
	printf("9 - back\n");
	scanf("%d", &num); 	system("cls");
	node* Employee = Employees_list->head;
	while (!(num == 1 || num == 2 || num == 9))
	{
		printf("Wrong number of selection, please enter a new one:  ");
		scanf("%d", &num); 	system("cls");
	}
	if (num == 9)  return;
	printf("ID         Fullname             Position        Start_date   Salary[k]  EarnsAboveAvg\n\n");
	while (Employee != NULL)
	{
		if ((num == 1) && (Employee->earnsAboveAvg == true))
			printf("%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
		if ((num == 2) && (Employee->earnsAboveAvg == false))
			printf("%-10d %-20s %-15s %-11s  %-.2lf      %-5s \n", Employee->ID, Employee->Fullname, Employee->Position, Employee->Date, Employee->Salary, (Employee->earnsAboveAvg ? "true" : "false"));
		Employee = Employee->next;
	}
	printf("\n\n");
}




