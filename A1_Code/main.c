#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>

struct userstruct        /*�û��ṹ��*/
{
	int bookcount;
	char username[10];
	char scert[10];
	char booklist[10][20];
	struct userstruct *next;
};

struct adminstruct       /*����Ա�ṹ��*/
{
	char adminname[10];
	char scert[10];
	struct adminstruct *next;
};

struct bookstruct        /*ͼ��ṹ��*/
{
	int id;
	char bookname[10];
	char author[10];
	int year;
	int month;
	int day;
	int count;
	double price;
	char press[20];
	struct bookstruct *next;
};
struct userstruct *head = NULL, *end = NULL;
struct adminstruct *adminhead = NULL, *adminend = NULL;
struct bookstruct *bookhead = NULL, *bookend = NULL;
int usercount, admincount, bookcount;
char superpwd[20];//��������

/*������ֺ���*/
void startsys();
void readuserfile();
void readadminfile();
void readbookfile();
void userlogin();
void userfunction(struct userstruct *p);
void userregister();
void adminlogin();
void adminregister();
void adminfunction();
void borrowbook(struct userstruct *userp);
void findbook(struct userstruct *userp);
void returnbook(struct userstruct *userp);
void addbook();
void deletebook();
void searchbook();
void searchbookname();
void searchbookauthor();
void changebook();
void searchuser();
void explorebook();
void writefile(int flag);
void changuserbook(char *userbookname,char *bookname);
void deleteuserbook(char *bookname);
int isexist(char *name,int flag);

//������
int main()
{
	FILE *fp;

	head = (struct userstruct *)malloc(sizeof(struct userstruct));
	adminhead = (struct adminstruct *)malloc(sizeof(struct adminstruct));
	bookhead = (struct bookstruct *)malloc(sizeof(struct bookstruct));

	fp = fopen("user.dat", "a+");
	usercount = fread(head, sizeof(struct userstruct), 1, fp);
	fclose(fp);
	end = head;
	readuserfile();

	fp = fopen("admin.dat", "a+");
	admincount = fread(adminhead, sizeof(struct adminstruct), 1, fp);
	fclose(fp);
	adminend = adminhead;
	readadminfile();

	fp = fopen("book.dat", "a+");
	bookcount = fread(bookhead, sizeof(struct bookstruct), 1, fp);
	fclose(fp);
	bookend = bookhead;
	readbookfile();

    system("title ͼ��ݹ���ϵͳ --by ���1804������");
    printf("ϵͳ���ڳ�ʼ�������Ժ�...\n");
    int i;
    for (i=0;i<=30;i++)
    {
        printf(">");
        Sleep(50);
    }
    system("cls");
	startsys();

	return 0;
}

//����ϵͳ���������˵�
void startsys()
{
	int cmd;
	int end = 0;

    system("cls");
    printf("\n              ��ӭʹ��ͼ�����ϵͳ\n\n");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("����δ��¼�����ȵ�¼��\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("***********************************************\n");
    printf("|         1 -------------- �����ߵ�¼         |\n");
    printf("|         2 -------------- ����Ա��¼         |\n");
    printf("|         3 -------------- ������ע��         |\n");
    printf("|         4 -------------- ����Աע��         |\n");
    printf("|         0 -------------- �˳�ϵͳ           |\n");
    printf("***********************************************\n");
    printf("���������֣�");
    scanf("%d", &cmd);
    getchar();
    switch (cmd)
    {
    case 1:
        userlogin();
        break;
    case 2:
        adminlogin();
        break;
    case 3:
        userregister();
        break;
    case 4:
        adminregister();
        break;
    case 0:
        end = 1;
        break;
    default:
        {
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
            printf("��������������1~4��0��");
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            Sleep(1500);
        }
    }
    if (end == 1)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        printf("�����˳�ϵͳ�����Ժ�...\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        printf("����Co~ ");
        Sleep(900);
        printf("Co~ ");
        Sleep(900);
        printf("Da~ ");
        Sleep(900);
        printf("Yo~ ");
        Sleep(900);
        printf("Docter~  \n�����㲻Ҫ������������\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("�˳��ɹ���");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        system("pause");
        exit(0);
    }
}

//�û���¼�˵�
void userlogin()
{
    struct userstruct *p;
	char username[100];
	char userscert[100];
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	p = head;
	system("cls");
    printf("***********************************************\n\n");
    printf("                  �����ߵ�¼>>\n\n");
    printf("***********************************************\n");
    printf("�����������û���Ϣ��\n");
	printf("�û�����");
	gets(username);
	printf("���룺");
	gets(userscert);

	while (p != NULL)
	{
		if (strcmp(p->username, username) == 0)
		{
			while (strcmp(p->scert, userscert) != 0)
			{
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("���������������������\n");
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("���룺");
				gets(userscert);
			}
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			printf("�û�%s��½�ɹ���\n",p->username);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("3����Զ���ת���������...");
			Sleep(3000);
			userfunction(p);
		}
		p = p->next;
	}
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("��¼ʧ�ܣ������û��������룡����������һ�㡣");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Sleep(3000);
	startsys();
}

//�û����˵�
void userfunction(struct userstruct *p)
{
	int cmd;
	int end = 0;

	while (1)
	{
		system("cls");
		printf("\n              ��ӭʹ��ͼ�����ϵͳ\n\n");
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("��ǰ��¼��ݣ�%s\n",p->username);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        printf("***********************************************\n");
        printf("|        1 -------------- ����ͼ��            |\n");
        printf("|        2 -------------- ͼ����Ϣ���        |\n");
        printf("|        3 -------------- ͼ����Ϣ����        |\n");
        printf("|        4 -------------- �黹ͼ��            |\n");
        printf("|        5 -------------- �ѽ���ͼ��          |\n");
        printf("|        0 -------------- �˳���¼            |\n");
        printf("***********************************************\n");
		printf("���������֣�");
		scanf("%d", &cmd);
		switch (cmd)
		{
		case 1:
			borrowbook(p);
			break;
        case 2:
			explorebook();
			break;
		case 3:
			searchbook();
			break;
		case 4:
			returnbook(p);
			break;
		case 5:
			findbook(p);
			break;
		case 0:
			end = 1;
			break;
		default:
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
            printf("��������������1~3��0��");
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            Sleep(1500);
		}
		if (end == 1)
			startsys();
	}
}

//�û�ע��
void userregister()
{
	struct userstruct *p;
	char username[1000];
	char scert[1000];
	FILE *fp;

	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	printf("***********************************************\n\n");
    printf("                  ������ע��>>\n\n");
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    printf("��ʾ���û���������ĳ��Ȳ��ö���10���ַ���\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("�����������û���Ϣ: \n");
	if (usercount == 0)            //��һ�����
	{
		printf("�û���: ");
		while (gets(username))
		{
			if (strlen(username) < 10 && (!isexist(username, 0)))
				break;
			else if (isexist(username, 0))
			{
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("���󣺸��û����Ѿ����ڣ��뻻һ���û���ע����¼��\n");
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("�û���: ");
			}
			else
			{
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("�����ַ����ȳ�������\n");
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("�û���: ");
			}
		}
		strcpy(head->username, username);
		printf("����: ");
		while (gets(scert))
		{
			if (strlen(scert) < 10)
				break;
			else
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("�����ַ����ȳ�������\n");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
		}
		strcpy(head->scert, scert);
		head->bookcount = 0;
		end = head;
		end->next = NULL;

	}
	else
	{
		p = (struct userstruct *)malloc(sizeof(struct userstruct));
		printf("�û�����");
		while (gets(username))
		{
			if (strlen(username) < 10 && !isexist(username, 0))
				break;
			else if (isexist(username, 0))
			{
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("���󣺸��û����Ѿ����ڣ��뻻һ���û���ע����¼��\n");
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("�û�����");
			}
			else
			{
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("�����ַ����ȳ�������\n");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("�û�����");
			}
		}
		strcpy(p->username, username);
		printf("���룺");
		while (gets(scert))
		{
			if (strlen(scert) < 10)
				break;
			else
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("�����ַ����ȳ�������\n");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
            }
		}
		strcpy(p->scert, scert);
		p->bookcount = 0;
		end->next = p;
		end = p;
		end->next = NULL;
	}
	usercount++;

    printf("���һ���������Ա���볬�����룬�����ע�᣺");
    scanf("%s",superpwd);
    if (strcmp(superpwd,"superpassword")==0)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("����������ȷ���������ע��...\n");
        Sleep(500);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
    else
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("�����������ע��ʧ�ܣ�����������һ����");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        Sleep(3000);
        return;
    }

	fp = fopen("user.dat", "w");
	p = head;
	while (p != NULL)
	{
		fwrite(p, sizeof(struct userstruct), 1, fp);
		p = p->next;
	}
	fclose(fp);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	printf("�û�%s�����ɹ���\n", end->username);

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("3����Զ�����������....\n");
	Sleep(3000);
}

//�ж��Ƿ���ڵĺ���
int isexist(char *name,int flag)
{
	if (flag == 0)
	{
		struct userstruct *p;
		p = head;
		while (p != NULL && usercount != 0)
		{
			if (strcmp(name, p->username) == 0)
				return 1;
			p = p->next;
		}
	}
	else if (flag == 1)
	{
		struct adminstruct *p;
		p = adminhead;
		while (p != NULL)
		{
			if (strcmp(name, p->adminname) == 0)
				return 1;
			p = p->next;
		}
	}
	else if (flag == 2)
	{
		struct bookstruct *p;
		p = bookhead;
		while (p != NULL)
		{
			if (strcmp(name, p->bookname) == 0)
				return 1;
			p = p->next;
		}
	}
	return 0;
}

//����Ա��¼
void adminlogin()
{
	struct adminstruct *p;
	char adminname[100];
	char adminscert[100];
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	p = adminhead;
	system("cls");
    printf("***********************************************\n\n");
    printf("                  ����Ա��¼>>\n\n");
    printf("***********************************************\n");
    printf("�����������û���Ϣ��\n");
	printf("�û�����");
	gets(adminname);
	printf("���룺");
	gets(adminscert);

	while (p != NULL)
	{
		if (strcmp(p->adminname, adminname) == 0)
		{
			while (strcmp(p->scert, adminscert) != 0)
			{
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("���������������������\n");
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("���룺");
				gets(adminscert);
			}
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			printf("����Ա%s��½�ɹ���\n",p->adminname);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("3����Զ���ת���������...");
			Sleep(3000);
			adminfunction(p);
		}
		p = p->next;
	}
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("��¼ʧ�ܣ������û��������룡����������һ�㡣");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Sleep(3000);
	startsys();
}

//����Ա���˵�
void adminfunction(struct adminstruct *p)
{
	int cmd;
	int end = 0;

	while (1)
	{
		system("cls");
		printf("\n              ��ӭʹ��ͼ�����ϵͳ\n\n");
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("��ǰ��¼��ݣ�%s\n",p->adminname);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        printf("***********************************************\n");
        printf("|        1 -------------- ͼ����Ϣ¼��        |\n");
        printf("|        2 -------------- ͼ����Ϣɾ��        |\n");
        printf("|        3 -------------- ͼ����Ϣ�޸�        |\n");
        printf("|        4 -------------- ͼ����Ϣ���        |\n");
        printf("|        5 -------------- ͼ����Ϣ����        |\n");
        printf("|        6 -------------- �û���Ϣ��ѯ        |\n");
        printf("|        0 -------------- �˳���¼            |\n");
        printf("***********************************************\n");
		printf("��������Ҫ���еĲ���: ");
		scanf("%d", &cmd);
		getchar();
		switch (cmd)
		{
		case 1:
			addbook();
			break;
		case 2:
			deletebook();
			break;
		case 3:
			changebook();
			break;
        case 4:
			explorebook();
			break;
		case 5:
			searchbook();
			break;
		case 6:
			searchuser();
			break;
		case 0:
			end = 1;
			break;
		default:
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
            printf("��������������1~5��0��");
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            Sleep(1500);
		}
		if (end == 1)
			startsys();
	}
}

//����Աע��
void adminregister()
{
	struct adminstruct *p;
	char adminname[1000];
	char adminscert[1000];
	FILE *fp;
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("***********************************************\n\n");
    printf("                  ����Աע��>>\n\n");
    printf("***********************************************\n");
    printf("�������볬�����룺");
    scanf("%s",superpwd);
    if (strcmp(superpwd,"superpassword")==0)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("����������ȷ�������ע�����~\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
    else
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("����������󣡼���������һ����");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        Sleep(3000);
        return;
    }
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    printf("��ʾ���û���������ĳ��Ȳ��ö���10���ַ���\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("�����������û���Ϣ��\n");
    getchar();
	if (admincount == 0)            //��һ�����
	{
		adminhead = (struct adminstruct *)malloc(sizeof(struct adminstruct));
		printf("�û�����");
		while (gets(adminname))
		{
			if (strlen(adminname) < 10)
				break;
			else
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("�����ַ����ȳ�������");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
		}
		strcpy(adminhead->adminname, adminname);
		printf("���룺");
		while (gets(adminscert))
		{
			if (strlen(adminscert) < 10)
				break;
			else
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("�����ַ����ȳ�������");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
		}
		strcpy(adminhead->scert, adminscert);
		adminend = adminhead;
		adminend->next = NULL;
	}
	else
	{
		p = (struct adminstruct *)malloc(sizeof(struct adminstruct));
		printf("�û�����");
		while (gets(adminname))
		{
			if (strlen(adminname) < 10)
				break;
			else
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("�����ַ����ȳ�������");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
		}
		strcpy(p->adminname, adminname);
		printf("���룺");
		while (gets(adminscert))
		{
			if (strlen(adminscert) < 10)
				break;
			else
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("�����ַ����ȳ�������");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
		}
		strcpy(p->scert, adminscert);
		adminend->next = p;
		adminend = p;
		adminend->next = NULL;
	}
	admincount++;

	fp = fopen("admin.dat", "w");
	p = adminhead;
	while (p != NULL)
	{
		fwrite(p, sizeof(struct adminstruct), 1, fp);
		p = p->next;
	}
	fclose(fp);

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	printf("����Ա%s�����ɹ�\n", adminend->adminname);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("3����Զ�����������....\n");
	Sleep(3000);
}

//����ģ��
void borrowbook(struct userstruct *userp)
{
	struct bookstruct *p;
	char bookname[100];
	int exist = 0;
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("***********************************************\n\n");
    printf("                 ͼ�����ϵͳ>>\n\n");
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    printf("��ʾ���·���ʾ�˵�����������е��飬���������\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	p = bookhead;
	printf("���\t����\t������\t������\t����ʱ��\t�۸�\tͼ������\n");
    printf("----------------------------------------------------------------\n");
	while (p != NULL)
	{
            printf("%d\t", p->id);
            printf("%s\t",p->bookname);
			printf("%s\t", p->author);
			printf("%s\t", p->press);
			printf("%d/%d/%d\t", p->year, p->month, p->day);
			printf("%.2lf\t", p->price);
			printf("%d\n", p->count);
            p = p->next;
	}
	printf("��������Ҫ���ĵ��鼮����: ");
	getchar();
	gets(bookname);

	p = bookhead;
	while (p != NULL)
	{
		if (strcmp(bookname, p->bookname) == 0)
		{
			if (p->count == 0)
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("���󣺴�������������ʱ���ܽ���...");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            }
			else
			{
				p->count -= 1;
				userp->bookcount++;
				strcpy(userp->booklist[userp->bookcount - 1], p->bookname);
				writefile(0);
				writefile(2);
				exist = 1;
				break;
			}
		}
		p = p->next;
	}

	if (exist == 0)
	{
	    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
		printf("���󣺲����ڴ��飡\n");
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	}
	else
	{
	    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	    printf("%s���ĳɹ���\n", p->bookname);
	    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	}

	printf("3��󷵻��û�����...");
	Sleep(3000);
}

//����ģ��
void returnbook(struct userstruct *userp)
{
	struct bookstruct *p;
	char bookname[100];
	int count = userp->bookcount;
	int exist;
	int flag;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	printf("***********************************************\n\n");
    printf("                 ͼ��黹ϵͳ>>\n\n");
    printf("***********************************************\n");
	p = bookhead;
	printf("�鼮���ƣ�\n");
	while (count--)
	{
		printf("%s\n", userp->booklist[count]);
	}
	printf("����������Ҫ�黹���鼮����: ");

	getchar();
	while (gets(bookname))
	{
		exist = 0;
		int i;
		for (i = 0; i < userp->bookcount; i++)
		{
			if (strcmp(bookname, userp->booklist[i]) == 0)
			{
				flag = i;
				exist = 1;
				break;
			}
		}
		if (!exist)
		{
		    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			printf("��������ĵ��鼮�в����ڴ��鼮...\n");
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("��������������Ҫ�黹���鼮����: ");
		}
		else
			break;
	}
	while (p != NULL)
	{
		if (strcmp(p->bookname, bookname) == 0)
		{
			p->count++;
			break;
		}
		p = p->next;
	}
    int i;
	for (i = flag; i < userp->bookcount - 1; i++)
	{
		strcpy(userp->booklist[i], userp->booklist[i + 1]);
	}
	userp->bookcount--;
	writefile(0);
	writefile(2);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	printf("\n%s�黹�ɹ���\n", bookname);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("3����Զ���ת���û�����...");
	Sleep(3000);
}

/*�ѽ���ͼ����Ϣ*/
void findbook(struct userstruct *userp)
{
	int count = userp->bookcount;
	int n;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
    printf("***********************************************\n\n");
    printf("                 �ѽ���ͼ��>>\n\n");
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    printf("��ʾ���·����б����г��������������ͼ�������\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	while (count--)
	{
		printf("%s\n", userp->booklist[count]);
	}
	printf("\n����0�����û����棺");
    scanf("%d", &n);
    if (n == 0)
        return;
    else
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("��Ч�����룬���������룡");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        Sleep(1500);
        findbook(userp);
    }
}

//����ͼ��ģ��
void addbook()
{
	struct bookstruct *p;
	char bookname[100];
	FILE *fp;

	system("cls");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("***********************************************\n\n");
    printf("                 ͼ��¼��ϵͳ>>\n\n");
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    printf("��ʾ���������������Լ����������ֵĳ��Ȳ��ö���10���ַ�������0������һ����\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	if (bookcount == 0)
	{
		printf("���������鼮��ͼ������: ");
		while (gets(bookname))
		{
		    if (strcmp(bookname,"0")==0) return;
			if (strlen(bookname) > 10)
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("�����ַ����ȳ�������\n");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("���������鼮��ͼ������: ");
            }
			else
				break;
		}
		strcpy(bookhead->bookname, bookname);
		printf("ͼ���ţ�");
		scanf("%d", &bookhead->id);
		printf("���ߣ�");
		scanf("%s", bookhead->author);
		printf("�����磺");
		scanf("%s", bookhead->press);
		printf("������ݣ�");
		scanf("%d", &bookhead->year);
		printf("�����·ݣ�");
		scanf("%d", &bookhead->month);
		printf("�������ڣ�");
		scanf("%d", &bookhead->day);
		printf("ͼ��۸�");
		scanf("%lf", &bookhead->price);
		printf("ͼ��������");
		scanf("%d", &bookhead->count);

		bookend = bookhead;
		bookend->next = NULL;
	}
	else
	{
	    printf("���������鼮��ͼ������: ");
		while (gets(bookname))
		{
		    if (strcmp(bookname,"0")==0) return;
			if (strlen(bookname) > 10)
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("�����ַ����ȳ�������\n");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("���������鼮��ͼ������: ");
            }
			else
				break;
		}
		int isexist = 0;
		p = bookhead;
		while (p != NULL)
		{
			if (strcmp(bookname, p->bookname) == 0)
			{
				isexist = 1;
				break;
			}
			p = p->next;
		}
		if (isexist == 1)
		{
			int count;

			printf("���������鼮������: ");
			scanf("%d", &count);
			p->count += count;
		}
		else
		{
			p = (struct bookstruct *)malloc(sizeof(struct bookstruct));

			strcpy(p->bookname, bookname);
			printf("ͼ���ţ�");
			scanf("%d", &p->id);
			printf("���ߣ�");
			scanf("%s", p->author);
			printf("�����磺");
            scanf("%s", p->press);
			printf("������ݣ�");
			scanf("%d", &p->year);
			printf("�����·ݣ�");
			scanf("%d", &p->month);
			printf("�������ڣ�");
			scanf("%d", &p->day);
			printf("ͼ��۸�");
            scanf("%lf", &p->price);
			printf("ͼ��������");
			scanf("%d", &p->count);

			bookend->next = p;
			bookend = p;
			bookend->next = NULL;
		}
	}
	bookcount++;

	p = bookhead;
	fp = fopen("book.dat", "w");
	while (p != NULL)
	{
		fwrite(p, sizeof(struct bookstruct), 1, fp);
		p = p->next;
	}
	fclose(fp);

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	printf("�鼮��ӳɹ�\n");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("3����Զ����ع���Ա����....\n");
	Sleep(3000);
}

//ɾ��ͼ��ģ��
void deletebook()
{
	struct bookstruct *bookp;
	char bookname[100];
	int exist = 0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    printf("***********************************************\n\n");
    printf("                 ͼ����Ϣɾ��>>\n\n");
    printf("***********************************************\n");
	bookp = bookhead;
	printf("��������Ҫɾ�����鼮���ƣ�����0������һ��: ");
	while (gets(bookname))
	{
	    if (strcmp(bookname,"0")==0) return;
		while (bookp != NULL)
		{
			if (strcmp(bookname, bookp->bookname) == 0)
			{
				exist = 1;
				break;
			}
			bookp = bookp->next;
		}
		if (!exist)
		{
		    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			printf("�����ڴ��鼮���Ƶ��鼮...\n");
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("����������: ");
		}
		else
			break;
	}
	deleteuserbook(bookname);
	bookp = bookhead;
	if (strcmp(bookhead->bookname,bookname) == 0)
		bookhead = bookhead->next;
	while (bookp->next != NULL)
	{
		if (strcmp(bookp->next->bookname, bookname) == 0)
		{
			bookp->next = bookp->next->next;
			break;
		}
		bookp = bookp->next;
	}
	bookp = NULL;
	writefile(2);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	printf("ɾ��ͼ��ɹ����������������˵�...");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Sleep(1500);
}

void explorebook()
{
    struct bookstruct *p;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
    printf("\n                  ͼ����Ϣ���\n\n");
    printf("****************************************************************\n");
	p = bookhead;
	if (p == NULL)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("��ǰ���Ϊ�գ������Ա��¼��ͼ�����ݣ�\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
    else
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
        printf("��ʾ�������ȫ��ͼ����Ϣ���£�\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        printf("���\t����\t������\t������\t����ʱ��\t�۸�\tͼ������\n");
        printf("----------------------------------------------------------------\n");
        while (p != NULL)
        {
            printf("%d\t", p->id);
            printf("%s\t",p->bookname);
			printf("%s\t", p->author);
			printf("%s\t", p->press);
			printf("%d/%d/%d\t", p->year, p->month, p->day);
			printf("%.2lf\t", p->price);
			printf("%d\n", p->count);
            p = p->next;
        }
    }
	printf("\n����0������һ��˵���");
	int n;
	scanf("%d",&n);
	if (n!=0)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("�����������ִ������������룡");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        Sleep(1500);
        explorebook();
    }
	else return;
}

void searchbookname()
{
    struct bookstruct *p;
	char bookname[100];
	int exist = 0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
    printf("\n                ͼ����Ϣ����\n\n");
    printf("                                                --Search by name\n");
    printf("****************************************************************\n");
	printf("����������Ҫ�������鼮����: ");
	gets(bookname);

	p = bookhead;
	while (p != NULL)
	{
		if (strcmp(p->bookname, bookname) == 0)
		{
		    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		    printf("��ʾ������������£�\n");
		    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		    printf("���\t����\t������\t������\t����ʱ��\t�۸�\tͼ������\n");
            printf("----------------------------------------------------------------\n");
            printf("%d\t", p->id);
            printf("%s\t",p->bookname);
			printf("%s\t", p->author);
			printf("%s\t", p->press);
			printf("%d/%d/%d\t", p->year, p->month, p->day);
			printf("%.2lf\t", p->price);
			printf("%d\n", p->count);
			exist = 1;
			break;
		}
		p = p->next;
	}
	if (exist == 0)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("����δ�ҵ�����鼮...\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
	printf("\n����0������һ��˵���");
	int n;

	while (1)
	{
		scanf("%d", &n);
		if (n == 0)
			break;
        else
        {
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
            printf("�����������ִ������������룡");
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            Sleep(1500);
        }
	}
	return;
}

void searchbookauthor()
{
    struct bookstruct *p;
	char bookauthor[100];
	int exist = 0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
    printf("\n               ͼ����Ϣ����\n\n");
    printf("                                              --Search by author\n");
    printf("****************************************************************\n");
	printf("����������Ҫ�������鼮����: ");
	gets(bookauthor);

	p = bookhead;
	while (p != NULL)
	{
		if (strcmp(p->author, bookauthor) == 0)
		{
		    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		    printf("��ʾ������������£�\n");
		    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		    printf("���\t����\t������\t������\t����ʱ��\tͼ������\n");
            printf("----------------------------------------------------------------\n");
            printf("%d\t", p->id);
            printf("%s\t",p->bookname);
			printf("%s\t", p->author);
			printf("%d/%d/%d\t", p->year, p->month, p->day);
			printf("%d\n", p->count);
			exist = 1;
			break;
		}
		p = p->next;
	}
	if (exist == 0)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("����δ�ҵ�����鼮...\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
	printf("\n����0������һ��˵���");
	int n;

	while (1)
	{
		scanf("%d", &n);
		if (n == 0)
			break;
        else
        {
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
            printf("�����������ִ������������룡");
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            Sleep(1500);
        }
	}
	return;
}

//����ͼ��ģ�顪����ͼ������
void searchbook()
{
    int cmd;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
    printf("\n               ͼ����Ϣ����\n\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("��ʾ�������ṩ���ּ���ͼ��ķ������밴��ѡ��\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("***********************************************\n");
    printf("|      1 -------------- Search by name        |\n");
    printf("|      2 -------------- Search by author      |\n");
    printf("|      0 -------------- ������һ��            |\n");
    printf("***********************************************\n");
    printf("��������Ҫ���еĲ���: ");
    scanf("%d", &cmd);
	getchar();
	switch (cmd)
	{
	case 1:
		searchbookname();
		break;
	case 2:
		searchbookauthor();
		break;
	case 0:
		return;
		break;
	default:
	    {
	        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
            printf("��������������1~5��0��");
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            Sleep(1500);
            searchbook();
	    }
	}
}

//�޸�ͼ����Ϣ
void changebook()
{
	struct bookstruct *bookp;
	char bookname[100];
	int exist = 0;
	int end = 0;
	double bookprice;
	int bookyear, bookmonth, bookday, bookid, count;
	char bookauthor[100],bookpress[100];
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	bookp = bookhead;
	system("cls");
	printf("***********************************************\n\n");
    printf("                 ͼ����Ϣ�޸�>>\n\n");
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	printf("��ʾ���·���ʾ�˵�����������е��飬�밴���޸ģ�\n");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	while (bookp != NULL)
	{
		printf("ͼ�����ƣ�%10s\n", bookp->bookname);
		bookp = bookp->next;
	}

	bookp = bookhead;
	printf("��������Ҫ�޸ĵ��鼮���ƣ�����0������һ��: ");
	while (gets(bookname))
	{
		if (strcmp(bookname, "0") == 0)
			break;
		while (bookp != NULL)
		{
			if (strcmp(bookp->bookname, bookname) == 0)
			{
				exist = 1;
				break;
			}
			bookp = bookp->next;
		}
		if (!exist)
        {
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
            printf("���󣺲����ڸ��鼮���ƣ�����������: ");
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        }
		else
			break;
	}

	if (!exist)
		return;
	else
	{
		int cmd;
		printf("***********************************************\n");
		printf("|        1 -------------- �޸��鼮����        |\n");
		printf("|        2 -------------- �޸��鼮���        |\n");
		printf("|        3 -------------- �޸��鼮����        |\n");
		printf("|        4 -------------- �޸��鼮����        |\n");
		printf("|        5 -------------- �޸��鼮����        |\n");
		printf("|        6 -------------- �޸��鼮������      |\n");
		printf("|        7 -------------- �޸��鼮�۸�        |\n");
		printf("|        0 -------------- ������һ��          |\n");
		printf("***********************************************\n");
		while (1)
		{
			printf("��������Ҫ���еĲ���,����0������һ��: ");
			scanf("%d", &cmd);
			switch (cmd)
			{
                case 1:
                {
                    printf("�������޸ĺ���鼮����: ");
                    scanf("%s", bookname);
                    changuserbook(bookp->bookname,bookname);
                    strcpy(bookp->bookname, bookname);
                    break;
                }
                case 2:
                {
                    printf("�������޸ĺ���鼮���: ");
                    scanf("%d", &bookid);
                    bookp->id = bookid;
                    break;
                }
                case 3:
                {
                    printf("�������޸ĺ���鼮����: ");
                    scanf("%d%d%d", &bookyear, &bookmonth, &bookday);
                    bookp->year = bookyear;
                    bookp->month = bookmonth;
                    bookp->day = bookday;
                    break;
                }
                case 4:
                {
                    printf("�������޸ĺ���鼮����: ");
                    scanf("%d", &count);
                    bookp->count = count;
                    break;
                }
                case 5:
                {
                    printf("�������޸ĺ���鼮����: ");
                    scanf("%s", bookauthor);
                    strcpy(bookp->author, bookauthor);
                    break;
                }
                case 6:
                {
                    printf("�������޸ĺ���鼮������: ");
                    scanf("%s", bookpress);
                    strcpy(bookp->press, bookpress);
                    break;
                }
                case 7:
                {
                    printf("�������޸ĺ���鼮�۸�: ");
                    scanf("%lf", &bookprice);
                    bookp->price = bookprice;
                    break;
                }
                case 0:
                {
                    end = 1;
                    break;
                }
			}
			if (end == 1)
				break;
		}
	}
	writefile(2);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	printf("�޸�ͼ����Ϣ�ɹ����������������˵�...");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Sleep(1500);
}

//�����û�
void searchuser()
{
	struct userstruct *p;
	char username[100];
	int flag = 0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	p = head;
	system("cls");
	printf("***********************************************\n\n");
    printf("                 �û���Ϣ��ѯ>>\n\n");
    printf("***********************************************\n");
	printf("����������Ҫ��ѯ���û�����");
	gets(username);
	while (p != NULL)
	{
		if (strcmp(p->username, username) == 0)
		{
			flag = 1;
			break;
		}
		p = p->next;
	}
	if (flag == 0)
	{
	    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
		printf("���󣺲����ڸ��û���Ϣ\n");
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		printf("3����Զ���ת������Աҳ��...\n");
		Sleep(3000);
		return;
	}
	else
	{
		int n;
		while (1)
		{
			printf("***********************************************\n");
			printf("�û�%s�ĸ�����Ϣ��\n", p->username);
			printf("�û�����");
			puts(p->username);
			printf("���룺");
			puts(p->scert);

			printf("��ǰ����������%d\n", p->bookcount);
			if (p->bookcount != 0)
			{
				printf("��ǰ������Ŀ��\n");
				int i;
				for (i = 0; i < p->bookcount; i++)
					puts(p->booklist[i]);
			}
			printf("***********************************************");
			printf("\n����0���ع���Աҳ��!\n");
			scanf("%d", &n);
			if (n == 0) return;
			else
			{
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			    printf("�����������");
			    Sleep(1500);
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			    system("cls");
			}
		}
	}
}

//��ȡ�ļ�
void readuserfile()
{
	struct userstruct *p;
	FILE *fp;

	p = head;
	fp = fopen("user.dat", "ab+");
	while (fread(p,sizeof(struct userstruct),1,fp))
	{
		if (p->next != NULL)
		{
			p = (struct userstruct *)malloc(sizeof(struct userstruct));

			end->next = p;
			end = p;
			end->next = NULL;
		}
	}
}

void readadminfile()
{
	struct adminstruct *p;
	FILE *fp;

	p = adminhead;
	fp = fopen("admin.dat", "ab+");
	while (fread(p, sizeof(struct adminstruct), 1, fp))
	{
		if (p->next != NULL)
		{
			p = (struct adminstruct *)malloc(sizeof(struct adminstruct));

			adminend->next = p;
			adminend = p;
			adminend->next = NULL;
		}
	}
}

void readbookfile()
{
	struct bookstruct *p;
	FILE *fp;

	p = bookhead;
	fp = fopen("book.dat", "ab+");
	while (fread(p, sizeof(struct bookstruct), 1, fp))
	{
		if (p->next != NULL)
		{
			p = (struct bookstruct *)malloc(sizeof(struct bookstruct));

			bookend->next = p;
			bookend = p;
			bookend->next = NULL;
		}
	}
}

void writefile(int flag)
{
	FILE *fp;
	struct userstruct *userp;
	struct adminstruct *adminp;
	struct bookstruct *bookp;

	userp = head;
	adminp = adminhead;
	bookp = bookhead;

	if (flag == 0)
	{
		fp = fopen("user.dat", "w");
		while (userp != NULL)
		{
			fwrite(userp, sizeof(struct userstruct), 1, fp);
			userp = userp->next;
		}
	}
	else if (flag == 1)
	{
		fp = fopen("admin.dat", "w");
		while (adminp != NULL)
		{
			fwrite(adminp, sizeof(struct adminstruct), 1, fp);
			adminp = adminp->next;
		}
	}
	else
	{
		fp = fopen("book.dat", "w");
		while (bookp != NULL )
		{
			fwrite(bookp, sizeof(struct bookstruct), 1, fp);
			bookp = bookp->next;
		}
	}
	fclose(fp);
}

void changuserbook(char *userbookname,char *bookname)
{
	struct userstruct *userp;

	userp = head;
	while (userp != NULL)
	{
	    int i;
		for (i = 0; i < userp->bookcount; i++)
		{
			if (strcmp(userp->booklist[i], userbookname) == 0)
			{
				strcpy(userp->booklist[i], bookname);
			}
		}
		userp = userp->next;
	}
	writefile(0);
}

void deleteuserbook(char *bookname)
{
	struct userstruct *userp;
	int flag = -1;

	userp = head;
	while (userp != NULL)
	{
		flag = -1;
		int i;
		for (i = 0; i < userp->bookcount; i++)
		{
			if (strcmp(userp->booklist[i], bookname) == 0)
			{
				flag = i;
				break;
			}
		}
		if (flag != -1)
		{
		    int i;
			for (i = flag; i < userp->bookcount - 1; i++)
			{
				strcpy(userp->booklist[i], userp->booklist[i + 1]);
			}
			userp->bookcount--;
		}
		userp = userp->next;
	}
	writefile(0);
}
