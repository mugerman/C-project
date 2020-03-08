// chen frenkel 205562846	
// alon mugerman 311143366

#include <stdbool.h>

//typedef char list_type;

typedef struct user
{
	char Username[15];
	char Password[15];
	int Level;
	char FullName[20];
}user;


typedef struct node 
{
	int ID;
	char Fullname[20];
	char Position[15];
	char Date[11];
	float Salary;
	bool earnsAboveAvg;
	struct node *next;
	struct node *prev;
}node;


typedef struct list
{
	node *head;
	node *tail;
}list;


bool check_if_users_file_exists();

bool check_if_employees_file_exists();

bool if_Above_Avg(float avg, float Salary);

void update_employee_if_Above_Avg(list* Employees_list, float avg);

void Insert_admin(user* Management_Users, int* Num_Of_Users);

int Start_and_Login(user* Management_Users, char* Current_user);

void Search_by_ID(list* Employees_list);

void Search_by_FullName(list* Employees_list);

void Search_by_Position(list* Employees_list);

void Search_by_FullName_and_Position(list* Employees_list);

void Search_by_Date(list* Employees_list);

void Search_by_if_above_avg_salary(list* Employees_list);

void Search_menu(list* Employees_list);

void Read_Users_from_file();

void print_employee_from_list(list* Employees_list);

void Print_Users_from_struct(user* Management_Users, int* Num_Of_Users);

void Sorted_insertion(list* Employees_list, node* Employee);

void Import_users_from_file(user* Management_Users, int* Num_Of_Users);

void Import_employees_from_file(list* Employees_list);

void Extract_users_to_file(user* Management_Users, int* Num_Of_Users);

void Extract_employees_to_file(list* Employees_list);

void getDateTime(int *day, int *month, int *year, int *hours, int *mins);

bool Delete_users(user* Management_Users, int* Num_Of_Users);

bool Delete_employee(list* Employees_list);

bool Edit_users(user* Management_Users, int* Num_Of_Users);

bool Edit_employee(list* Employees_list);

void Add_users(user* Management_Users, int* Num_Of_Users);

void Add_employee(list* Employees_list);

void LOG_file(char* Current_user, char* info);

float salaries_avg(list* Employees_list);

bool if_ID_Exists(list* Employees_list, int temp);

void Free_list(list* Employees_list);

void initList(list *lst);

int isEmpty(list *lst);

node* allocItem(int ID, char *Fullname, char *Position,char *Date, float Salary , bool earnsAboveAvg);

node* getLinkByIndex(list *lst, int idx);

int insertFirst(list *lst, node *item);

int insertLast(list *lst, node *item);

int deleteFirst(list *lst);

int deleteLast(list *lst);

int deleteLink(list *lst, node *link);

int insertAfter(list *lst, node *item, node *link);

int insertBefore(list *lst, node *item, node *link);
