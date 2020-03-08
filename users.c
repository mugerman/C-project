// chen frenkel 205562846	
// alon mugerman 311143366

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "header_file.h"

#define USERS_PATH "C:\\temp\\Users_file.txt"


void Read_Users_from_file() //get's the path of the users file, and print all users information.
{
	FILE *fp;
	int level;
	char c, temp[200], username[16], password[16], fullname[21];
	fp = fopen(USERS_PATH, "r");
	if (!fp)
	{
		printf("File not found!\n");
		return;
	}

	fgets(temp, 200, fp);
	puts(temp);
	fgets(temp, 200, fp);
	puts(temp);

	while (fscanf_s(fp, "%s %s %1d %s", username, 16, password, 16, &level, fullname, 21) != EOF)
	{
		printf_s("%-15s %-15s %-1d %-20s\n", username, password, level, fullname);
		c = fgetc(fp);
		c = fgetc(fp);
	}

	fclose(fp);
	return;
}


void Insert_admin(user* Management_Users, int* Num_Of_Users)
{
	strcpy(Management_Users[0].Username, "admin");
	strcpy(Management_Users[0].Password, "admin");
	strcpy(Management_Users[0].FullName, "System_Manager");
	Management_Users[0].Level = 3;
	(*Num_Of_Users)++;
}


bool check_if_users_file_exists()
{
	FILE *fp = fopen(USERS_PATH, "r");
	if (fp != NULL)
	{
		fclose(fp);
		return true;
	}
	return false;
}


void Print_Users_from_struct(user* Management_Users, int* Num_Of_Users)
{
	int i;
	printf("Username        Password        L Fullname\n\n");
	for (i = 0; i < *Num_Of_Users; i++)
		printf("%-15s %-15s %-1d %-20s\n", Management_Users[i].Username, Management_Users[i].Password, Management_Users[i].Level, Management_Users[i].FullName);
}


void Import_users_from_file(user* Management_Users, int* Num_Of_Users)  // version 2 by fscanf
{
	FILE* fp;
	char temp[200], c;
	int index = 0;
	fp = fopen(USERS_PATH, "r");
	if (fp != NULL)
	{
		fgets(temp, 200, fp);
		//puts(temp);
		fgets(temp, 200, fp);
		//puts(temp);

		while (fscanf_s(fp, "%s %s %d %19s", Management_Users[index].Username, 16, Management_Users[index].Password, 16, &Management_Users[index].Level, Management_Users[index].FullName, 21) != EOF)
		{
			//printf("%-15s %-15s %-1d %-20s\n", Management_Users[index].Username, Management_Users[index].Password, Management_Users[index].Level, Management_Users[index].FullName);
			c = fgetc(fp);
			c = fgetc(fp);
			index++;
			(*Num_Of_Users)++;
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


void Extract_users_to_file(user* Management_Users, int* Num_Of_Users)
{
	FILE *fp;
	int i = 0;
	remove(USERS_PATH);
	fp = fopen(USERS_PATH, "w+");
	fprintf(fp, "Username        Password        L Fullname\n\n");
	for (i = 0; i < *Num_Of_Users; i++)
		fprintf(fp, "%-15s %-15s %-1d %-20s\n", Management_Users[i].Username, Management_Users[i].Password, Management_Users[i].Level, Management_Users[i].FullName);
	fclose(fp);
}


bool Delete_users(user* Management_Users, int* Num_Of_Users) // if success delete return true else false
{
	Print_Users_from_struct(Management_Users, Num_Of_Users);
	int i, j;
	char username[15];
	printf("\nPlease enter the username you would like to delete: ");
	scanf("%s", &username);
	system("cls");
	for (i = 0; i < *Num_Of_Users; i++)
	{
		if (!strcmp(username, Management_Users[i].Username))
		{
			if (!strcmp(Management_Users[i].Username, "admin"))
				return printf("Cannot delete admin!!!\n");
			for (j = i; j < *Num_Of_Users; j++)
			{
				strcpy(Management_Users[j].Username, Management_Users[j + 1].Username);
				strcpy(Management_Users[j].Password, Management_Users[j + 1].Password);
				Management_Users[j].Level = Management_Users[j + 1].Level;
				strcpy(Management_Users[j].FullName, Management_Users[j + 1].FullName);
			}
			(*Num_Of_Users)--;
			return true;
		}
	}
	return false;
}


bool Edit_users(user* Management_Users, int* Num_Of_Users) // if success edit return true else false
{
	int i;
	char temp[15];
	system("cls");
	Print_Users_from_struct(Management_Users, Num_Of_Users);
	printf("\nPlease enter the username you would like to edit: ");
	scanf("%s", &temp);
	system("cls");
	for (i = 0; i < *Num_Of_Users; i++)
	{
		if (!strcmp(Management_Users[i].Username, temp))
		{
			int num1 = 0;
			while (num1 != 9)
			{
				printf("1 - Edit Username \n");
				printf("2 - Edit Password \n");
				printf("3 - Edit Permission Level \n");
				printf("4 - Edit Fullname \n");
				printf("9 - Back\n\n");
				printf("Choose from the menu:  ");
				scanf_s("%d", &num1);
				system("cls");
				switch (num1)
				{
				case 1: //Edit Username
				{
					printf("\n Please enter a new Username:  ");
					scanf("%s", Management_Users[i].Username);
					break;
				}
				case 2:  //Edit Password
				{
					printf("\n Please enter a new Password:  ");
					scanf("%s", Management_Users[i].Password);
					break;
				}
				case 3:  //Edit Permission Level
				{
					printf("\n Please enter a new Permission Level:  ");
					scanf("%d", &Management_Users[i].Level);
					break;
				}
				case 4:  //Edit Fullname
				{
					printf("\n Please enter a new Fullname:  ");
					scanf("%s", Management_Users[i].FullName);
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
	}
	return false;
}


void Add_users(user* Management_Users, int* Num_Of_Users)
{
	printf("\n Please enter a Username:  ");
	scanf("%s", Management_Users[*Num_Of_Users].Username); system("cls");
	printf("\n Please enter a Password:  ");
	scanf("%s", Management_Users[*Num_Of_Users].Password); system("cls");
	printf("\n Please enter a Permission Level:  ");
	scanf("%d", &Management_Users[*Num_Of_Users].Level); system("cls");
	printf("\n Please enter a Fullname:  ");
	scanf("%s", Management_Users[*Num_Of_Users].FullName); system("cls");
	(*Num_Of_Users)++;
}