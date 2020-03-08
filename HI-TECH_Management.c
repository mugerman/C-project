// chen frenkel 205562846	
// alon mugerman 311143366

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header_file.h"

#define USERS_PATH "C:\\temp\\Users_file.txt"
#define ITEMS_PATH "C:\\temp\\Items_file.txt"
#define LOG_PATH "C:\\temp\\LOG_file.txt"

#define Max_Num_Of_Management_Users 10


void main()
{
	list Employees_list;
	user Management_Users[Max_Num_Of_Management_Users];
	int num = 0, Num_Of_Users = 0;
	char Current_user[20];
	if (!check_if_users_file_exists())
		Insert_admin(Management_Users, &Num_Of_Users);
	else Import_users_from_file(Management_Users, &Num_Of_Users);

	if (check_if_employees_file_exists())
		Import_employees_from_file(&Employees_list);

	int Permission_Level = Start_and_Login(Management_Users, Current_user);
	system("cls");
	switch (Permission_Level)
	{
	case 0: // wrong ID or password
	{
		printf("You were wrong three times\n\n");
		system("pause");
		break;
	}

	case 1: // Human Resources
	{
		while (num != 9)
		{
			printf("1 - Search \n");
			printf("2 - Add employees \n");
			printf("9 - Exit\n\n");
			printf("Choose from the menu:  ");
			scanf_s("%d", &num);
			system("cls");
			switch (num)
			{
			case 1: //Search
			{
				Search_menu(&Employees_list);
				LOG_file(Current_user, "Searched");
				break;
			}
			case 2:  //Add employees
			{
				Add_employee(&Employees_list);
				LOG_file(Current_user, "Added employee");
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
		}
		break;
	}

	case 2: // Team Managers
	{
		while (num != 9)
		{
			printf("1 - Search \n");
			printf("2 - Add employees \n");
			printf("3 - Update employees \n");
			printf("4 - Delete employees \n");
			printf("9 - Exit\n\n");
			printf("Choose from the menu:  ");
			scanf_s("%d", &num);
			system("cls");
			switch (num)
			{
			case 1: //Search
			{
				Search_menu(&Employees_list);
				LOG_file(Current_user, "Searched");
				break;
			}
			case 2:  //Add employees
			{
				Add_employee(&Employees_list);
				LOG_file(Current_user, "Added employee");
				break;
			}
			case 3:  //Edit employees
			{
				if (Edit_employee(&Employees_list))
				{
					LOG_file(Current_user, "Edited Employee");
					printf("\nEmployee edited\n\n");
				}
				else printf("\nNot edited - employee not found\n\n");
				break;
			}
			case 4:  //Delete employees
			{
				if (Delete_employee(&Employees_list))
				{
					LOG_file(Current_user, "Deleted employee");
					printf("\nEmployee deleted\n\n");
				}
				else printf("\nNot deleted - employee not found\n\n");
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
		}
		break;
	}

	case 3: // CEO
	{
		while (num != 9)
		{
			printf("1 - Search \n");
			printf("2 - Add employees \n");
			printf("3 - Edit employees \n");
			printf("4 - Delete employees \n");
			printf("5 - Add users \n");
			printf("6 - Edit users \n");
			printf("7 - Delete users \n");
			printf("9 - Exit\n\n");
			printf("Choose from the menu:  ");
			scanf_s("%d", &num);
			system("cls");
			switch (num)
			{
			case 1: //Search
			{
				Search_menu(&Employees_list);
				LOG_file(Current_user, "Searched");
				break;
			}
			case 2:  //Add employees
			{
				Add_employee(&Employees_list);
				LOG_file(Current_user, "Added employee");
				break;
			}
			case 3:  //Edit employees
			{
				if (Edit_employee(&Employees_list))
				{
					LOG_file(Current_user, "Edited Employee");
					printf("\nEmployee edited\n\n");
				}
				else printf("\nNot edited - employee not found\n\n");
				break;
			}
			case 4:  //Delete employees
			{
				if (Delete_employee(&Employees_list))
				{
					LOG_file(Current_user, "Deleted employee");
					printf("\nEmployee deleted\n\n");
				}
				else printf("\nNot deleted - employee not found\n\n");
				break;
			}
			case 5:  //Add users
			{
				Add_users(Management_Users, &Num_Of_Users);
				LOG_file(Current_user, "Added user");
				break;
			}
			case 6:  //Edit users
			{
				if (Edit_users(Management_Users, &Num_Of_Users))
				{
					LOG_file(Current_user, "Edited user");
					printf("\nUser edited\n\n");
				}
				else printf("\nNot edited - user not found\n\n");
				break;
			}
			case 7:  //Delete users
			{
				if (Delete_users(Management_Users, &Num_Of_Users))
				{
					LOG_file(Current_user, "Deleted user");
					printf("\nUser deleted\n\n");
				}
				else printf("\nNot deleted - user not found\n\n");
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
		}
		break;
	}

	}
	printf("\n\n");


	Extract_employees_to_file(&Employees_list);
	Extract_users_to_file(Management_Users, &Num_Of_Users);


	//print_employee_from_list(&Employees_list);
	//printf("\n");
	//Read_Users_from_file();

	Free_list(&Employees_list);

	printf("\n");
	system("pause");

}



int Start_and_Login(user* Management_Users,char* Current_user)    //if success login return Permission_Level else return 0
{
	int i = 0, Error_Quantity = 0;
	char temp_Username[15],temp_Password[15];
	printf("\n----- HI-TECH-Management -----\n\n");
	printf("Enter Username: ");
	gets(temp_Username, sizeof(temp_Username));
	while (strcmp(temp_Username, Management_Users[i].Username))
	{
		i++;
		if (i == Max_Num_Of_Management_Users)
		{
			Error_Quantity++;
			if (Error_Quantity == 3) return 0;
			printf("Please enter new Username: ");
			gets(temp_Username, sizeof(temp_Username));
			i = 0;
		}
	}
	
	printf("Enter Password: ");
	gets(temp_Password, sizeof(temp_Password)); //scanf_s("%s", &temp_Password);
	while (strcmp(temp_Password, Management_Users[i].Password))
	{
		Error_Quantity++;
		if (Error_Quantity == 3) return 0;
		printf("Wrong Password, Please enter a new one: ");
		gets(temp_Password, sizeof(temp_Password));
	}
	strcpy(Current_user,Management_Users[i].FullName);
	LOG_file(Current_user, "Login");
	return Management_Users[i].Level;
}  


void getDateTime(int *day, int *month, int *year, int *hours, int *mins) //Returns by referfance the current date and time
{
	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	*day = timeinfo.tm_mday;
	*month = timeinfo.tm_mon + 1;
	*year = timeinfo.tm_year + 1900;
	*hours = timeinfo.tm_hour;
	*mins = timeinfo.tm_min;
}


void LOG_file(char* Current_user,char* info)
{
	FILE* fp;
	fp = fopen(LOG_PATH, "a+");
	if (fp != NULL)
	{
		int day, month, year, hours, mins;
		fprintf(fp,"%-20s%-25s", Current_user,info);
		getDateTime(&day, &month, &year, &hours, &mins);
		fprintf(fp,"%02d:%02d , %02d/%02d/%-d\n", hours, mins, day, month, year);
	}
	else
	{
		printf("File not exisits!\n");
		return;
	}
	fclose(fp);
	return;
}

