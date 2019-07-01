
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
struct userstruct        /*�û�*/
{
	int bookcount;
	char username[10];
	char scert[10];
	char booklist[10][20];
	struct userstruct *next;
};
struct adminstruct       /*����Ա*/
{
	char adminname[10];
	char scert[10];
	struct adminstruct *next;
};
struct bookstruct
{
	int id;
	char bookname[10];
	char author[10];
	int year;
	int month;
	int day;
	int count;
	struct bookstruct *next;
};
struct userstruct *head = NULL, *end = NULL;
struct adminstruct *adminhead = NULL, *adminend = NULL;
struct bookstruct *bookhead = NULL, *bookend = NULL;
int usercount, admincount, bookcount;

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
void changebook();
void searchuser();
void writefile(int flag);
void changuserbook(char *userbookname,char *bookname);
void deleteuserbook(char *bookname);

int main()
{
	FILE *fp;

	head = (struct userstruct *)malloc(sizeof(struct userstruct));
	adminhead = (struct adminstruct *)malloc(sizeof(struct adminstruct));
	bookhead = (struct bookstruct *)malloc(sizeof(struct bookstruct));

	fp = fopen("user", "a+");
	usercount = fread(head, sizeof(struct userstruct), 1, fp);
	fclose(fp);
	end = head;
	readuserfile();

	fp = fopen("admin", "a+");
	admincount = fread(adminhead, sizeof(struct adminstruct), 1, fp);
	fclose(fp);
	adminend = adminhead;
	readadminfile();

	fp = fopen("book", "a+");
	bookcount = fread(bookhead, sizeof(struct bookstruct), 1, fp);
	fclose(fp);
	bookend = bookhead;
	readbookfile();

	startsys();
	return 0;
}

void startsys()
{
	int cmd;
	int end = 0;

	while (1)
	{
		system("cls");
		printf("\n\n\n\n\n\n\n");
		printf("**************************************************************");
		printf("\nͼ��ݹ���ϵͳ\n");
		printf("1.�û���½\n");
		printf("2.����Ա��½\n");
		printf("3.�û�ע��\n");
		printf("4.����Աע��\n");
		printf("0.�˳�\n");
		printf("**************************************************************");
		printf("\n\n\n\n\n\n\n");
		printf("��������Ҫ���еĲ���: ");
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
			printf("��������!\n");
		}
		if (end == 1)
			break;
	}
}

void userlogin()
{
	struct userstruct *p;
	char username[100];
	char scert[100];
	int exist = 0;
	FILE *fp;

	p = head;
	system("cls");
	printf("\n\n\n\n\n\n\n");
	printf("**************************************************************");
	printf("\n���������û���Ϣ: \n");
	printf("username: ");
	gets(username);
	printf("userscert: ");
	gets(scert);
	printf("**************************************************************");
	printf("\n\n\n\n\n\n\n");

	while (p != NULL)
	{
		if (strcmp(p->username, username) == 0)
		{
			exist = 1;
			while(strcmp(p->scert, scert) != 0)
			{
				printf("�������!����������\n");
				printf("userscert: ");
				gets(scert);
			}
			printf("�û�%s��½�ɹ�!3����Զ���ת���û�����...", p->username);
			Sleep(3000);
			userfunction(p);
		}
		p = p->next;
	}
	if (!exist)
	{
		printf("�����ڴ��û���,����ǰ��ע��...\n");
		printf("3����Զ���ת��������...");
		Sleep(3000);
	}
}

void userfunction(struct userstruct *p)
{
	int cmd;
	int end = 0;

	while (1)
	{
		system("cls");
		printf("\n\n\n\n\n\n\n");
		printf("**************************************************************");
		printf("\nͼ����û�����ϵͳ\n");
		printf("1.�����鼮\n");
		printf("2.�黹�鼮\n");
		printf("3.�ѽ����鼮��Ϣ\n");
		printf("0.�˳�\n");
		printf("**************************************************************");
		printf("\n\n\n\n\n\n\n");
		printf("��������Ҫ���еĲ���: ");
		scanf("%d", &cmd);
		switch (cmd)
		{
		case 1:
			borrowbook(p);
			break;
		case 2:
			returnbook(p);
			break;
		case 3:
			findbook(p);
			break;
		case 0:
			end = 1;
			break;
		default:
			printf("���������!\n");
		}
		if (end == 1)
			break;
	}
}

void userregister()
{
	struct userstruct *p;
	char username[1000];
	char scert[1000];
	FILE *fp;

	system("cls");
	if (usercount == 0)            //��һ�����
	{
		printf("username: ");
		while (gets(username))
		{
			if (strlen(username) < 10 && !isexist(username, 0))
				break;
			else if (isexist(username, 0))
			{
				printf("���û����Ѿ�����!\n");
				printf("username: ");
			}
			else
			{
				printf("too long\n");
				printf("username: ");
			}
		}
		strcpy(head->username, username);
		printf("userscert: ");
		while (gets(scert))
		{
			if (strlen(scert) < 10)
				break;
			else
				printf("too long");
		}
		strcpy(head->scert, scert);
		head->bookcount = 0;
		end = head;
		end->next = NULL;

	}
	else
	{
		p = (struct userstruct *)malloc(sizeof(struct userstruct));
		printf("username: ");
		while (gets(username))
		{
			if (strlen(username) < 10 && !isexist(username, 0))
				break;
			else if (isexist(username, 0))
			{
				printf("���û����Ѿ�����!\n");
				printf("username: ");
			}
			else
			{
				printf("too long\n");
				printf("username: ");
			}
		}
		strcpy(p->username, username);
		printf("userscert: ");
		while (gets(scert))
		{
			if (strlen(scert) < 10)
				break;
			else
				printf("too long");
		}
		strcpy(p->scert, scert);
		p->bookcount = 0;
		end->next = p;
		end = p;
		end->next = NULL;
	}
	usercount++;


	fp = fopen("user", "w");
	p = head;
	while (p != NULL)
	{
		fwrite(p, sizeof(struct userstruct), 1, fp);
		p = p->next;
	}
	fclose(fp);

	system("cls");
	printf("�û�%s�����ɹ�\n", end->username);
	printf("3����Զ�����������....\n");
	Sleep(3000);
}

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

void adminlogin()
{
	struct adminstruct *p;
	char adminname[100];
	char adminscert[100];

	p = adminhead;
	system("cls");
	printf("\n\n\n\n\n\n\n");
	printf("**************************************************************");
	printf("\n�������Ĺ���Ա��Ϣ: \n");
	printf("adminname: ");
	gets(adminname);
	printf("adminscert: ");
	gets(adminscert);
	printf("**************************************************************");
	printf("\n\n\n\n\n\n\n");

	while (p != NULL)
	{
		if (strcmp(p->adminname, adminname) == 0)
		{
			while (strcmp(p->scert, adminscert) != 0)
			{
				printf("�������!����������\n");
				printf("adminscert: ");
				gets(adminscert);
			}
			printf("����Ա%s��½�ɹ�!3����Զ���ת���û�����...", p->adminname);
			Sleep(3000);
			adminfunction(p);
		}
		p = p->next;
	}
}

void adminfunction()
{
	int cmd;
	int end = 0;

	while (1)
	{
		system("cls");
		printf("\n\n\n\n\n\n\n");
		printf("**************************************************************");
		printf("\nͼ��ݹ���Ա����ϵͳ\n");
		printf("1.����鼮��Ϣ\n");
		printf("2.ɾ���鼮��Ϣ\n");
		printf("3.�޸��鼮��Ϣ\n");
		printf("4.��ѯ�鼮��Ϣ\n");
		printf("5.��ѯ�û���Ϣ\n");
		printf("0.�˳�\n");
		printf("**************************************************************");
		printf("\n\n\n\n\n\n\n");
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
			searchbook();
			break;
		case 5:
			searchuser();
			break;
		case 0:
			end = 1;
			break;
		default:
			printf("���������!\n");
		}
		if (end == 1)
			break;
	}
}

void adminregister()
{
	struct adminstruct *p;
	char adminname[1000];
	char adminscert[1000];
	FILE *fp;

	system("cls");
	if (admincount == 0)            //��һ�����
	{
		adminhead = (struct adminstruct *)malloc(sizeof(struct adminstruct));
		printf("adminname: ");
		while (gets(adminname))
		{
			if (strlen(adminname) < 10)
				break;
			else
				printf("too long");
		}
		strcpy(adminhead->adminname, adminname);
		printf("adminscert: ");
		while (gets(adminscert))
		{
			if (strlen(adminscert) < 10)
				break;
			else
				printf("too long");
		}
		strcpy(adminhead->scert, adminscert);
		adminend = adminhead;
		adminend->next = NULL;
	}
	else
	{
		p = (struct adminstruct *)malloc(sizeof(struct adminstruct));
		printf("adminname: ");
		while (gets(adminname))
		{
			if (strlen(adminname) < 10)
				break;
			else
				printf("too long");
		}
		strcpy(p->adminname, adminname);
		printf("adminscert: ");
		while (gets(adminscert))
		{
			if (strlen(adminscert) < 10)
				break;
			else
				printf("too long");
		}
		strcpy(p->scert, adminscert);
		adminend->next = p;
		adminend = p;
		adminend->next = NULL;
	}
	admincount++;

	fp = fopen("admin", "w");
	p = adminhead;
	while (p != NULL)
	{
		fwrite(p, sizeof(struct adminstruct), 1, fp);
		p = p->next;
	}
	fclose(fp);

	system("cls");
	printf("����Ա%s�����ɹ�\n", adminend->adminname);
	printf("3����Զ�����������....\n");
	Sleep(3000);
}

void borrowbook(struct userstruct *userp)
{
	struct bookstruct *p;
	char bookname[100];
	int exist = 0;

	system("cls");
	p = bookhead;
	while (p != NULL)
	{
		printf("bookname: %10s\tbookcount: %3d\n", p->bookname, p->count);
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
				printf("����������...");
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
		printf("�����ڴ���!\n");
	else
		printf("%s���ĳɹ�", p->bookname);
	printf("3��󷵻��û�����...");
	Sleep(3000);
}

void returnbook(struct userstruct *userp)
{
	struct bookstruct *p;
	char bookname[100];
	int count = userp->bookcount;
	int exist;
	int flag;

	system("cls");
	p = bookhead;
	while (count--)
	{
		printf("booklist:\n");
		printf("%s\n", userp->booklist[count]);
	}
	printf("\n\n\n\n\n");
	printf("**************************************************************");
	printf("\n��������Ҫ�黹���鼮����: ");

	getchar();
	while (gets(bookname))
	{
		exist = 0;
		for (int i = 0; i < userp->bookcount; i++)
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
			printf("����ĵ��鼮�в����ڴ��鼮...\n");
			printf("��������������Ҫ�黹���鼮����: ");
		}
		else
			break;
	}
	printf("**************************************************************");
	while (p != NULL)
	{
		if (strcmp(p->bookname, bookname) == 0)
		{
			p->count++;
			break;
		}
		p = p->next;
	}

	for (int i = flag; i < userp->bookcount - 1; i++)
	{
		strcpy(userp->booklist[i], userp->booklist[i + 1]);
	}
	userp->bookcount--;
	writefile(0);
	writefile(2);
	printf("\n%s�黹�ɹ�...", bookname);
	printf("3����Զ���ת���û�����...");
	Sleep(3000);
}

void findbook(struct userstruct *userp)
{
	int count = userp->bookcount;
	int n;

	system("cls");
	printf("\n\n\n\n\n");
	printf("**************************************************************");
	printf("\nbooklist:\n");
	while (count--)
	{
		printf("%s\n", userp->booklist[count]);
	}
	printf("**************************************************************");
	printf("\n����0�����û�����: ");
	while (1)
	{
		scanf("%d", &n);
		if (n == 0)
			break;
		else
			printf("��Ч�����룬����������: ");
	}
}

void addbook()
{
	struct bookstruct *p;
	char bookname[100];
	FILE *fp;

	system("cls");
	if (bookcount == 0)
	{
		printf("���������鼮������: ");
		while (gets(bookname))
		{
			if (strlen(bookname) > 10)
				printf("too long\n");
			else
				break;
		}
		strcpy(bookhead->bookname, bookname);
		printf("id: ");
		scanf("%d", &bookhead->id);
		printf("author: ");
		scanf("%s", bookhead->author);
		printf("bookyear: ");
		scanf("%d", &bookhead->year);
		printf("bookmonth: ");
		scanf("%d", &bookhead->month);
		printf("bookday: ");
		scanf("%d", &bookhead->day);
		printf("bookcount: ");
		scanf("%d", &bookhead->count);

		bookend = bookhead;
		bookend->next = NULL;
	}
	else
	{
		printf("���������鼮������: ");
		while (gets(bookname))
		{
			if (strlen(bookname) > 10)
				printf("too long\n");
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
			printf("id: ");
			scanf("%d", &p->id);
			printf("author: ");
			scanf("%s", p->author);
			printf("bookyear: ");
			scanf("%d", &p->year);
			printf("bookmonth: ");
			scanf("%d", &p->month);
			printf("bookday: ");
			scanf("%d", &p->day);
			printf("bookcount: ");
			scanf("%d", &p->count);

			bookend->next = p;
			bookend = p;
			bookend->next = NULL;
		}
	}
	bookcount++;

	p = bookhead;
	fp = fopen("book", "w");
	while (p != NULL)
	{
		fwrite(p, sizeof(struct bookstruct), 1, fp);
		p = p->next;
	}
	fclose(fp);

	system("cls");
	printf("�鼮��ӳɹ�\n");
	printf("3����Զ����ع���Ա����....\n");
	Sleep(3000);
}

void deletebook()
{
	struct bookstruct *bookp;
	char bookname[100];
	int exist = 0;

	bookp = bookhead;
	printf("��������Ҫɾ�����鼮����: ");
	while (gets(bookname))
	{
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
			printf("�����ڴ��鼮���Ƶ��鼮...\n");
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
}

void searchbook()
{
	struct bookstruct *p;
	char bookname[100];
	int exist = 0;

	system("cls");
	printf("\n\n\n\n\n\n\n");
	printf("\n����������Ҫ��ѯ���鼮���ƻ��鼮���: ");
	gets(bookname);
	printf("\n\n\n\n\n\n\n");

	p = bookhead;
	while (p != NULL)
	{
		if (strcmp(p->bookname, bookname) == 0)
		{
			printf("**************************************************************");
			printf("\nbookname: ");
			puts(p->bookname);
			printf("bookid: %d\n", p->id);
			printf("author: %s\n", p->author);
			printf("year/month/day: %d/%d/%d\n", p->year, p->month, p->day);
			printf("bookcount: %d\n", p->count);
			printf("**************************************************************\n");
			exist = 1;
			break;
		}
		p = p->next;
	}
	if (exist == 0)
		printf("δ�ҵ�����鼮...\n");
	printf("����0���ع���Ա����: ");
	int n;

	while (1)
	{
		scanf("%d", &n);
		if (n == 0)
			break;
	}
}

void changebook()
{
	struct bookstruct *bookp;
	char bookname[100];
	int exist = 0;
	int end = 0;
	int bookyear, bookmonth, bookday, bookid, count;
	char bookauthor[100];

	bookp = bookhead;
	system("cls");
	printf("booklist:\n");
	while (bookp != NULL)
	{
		printf("bookname: %10s\n", bookp->bookname);
		bookp = bookp->next;
	}

	bookp = bookhead;
	printf("��������Ҫ�޸ĵ��鼮����(��@�˳�): ");
	while (gets(bookname))
	{
		if (strcmp(bookname, "@") == 0)
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
			printf("�����ڸ��鼮���ƣ�����������: ");
		else
			break;
	}

	if (!exist)
		return;
	else
	{
		int cmd;

		system("cls");
		printf("\n\n\n\n\n\n\n");
		printf("**************************************************************\n");
		printf("1.�޸��鼮����\n");
		printf("2.�޸��鼮id��\n");
		printf("3.�޸��鼮����\n");
		printf("4.�޸��鼮����\n");
		printf("5.�޸��鼮����\n");
		printf("0.�˳�\n");
		printf("**************************************************************");
		printf("\n\n\n\n\n\n\n");
		while (1)
		{
			printf("��������Ҫ���еĲ���: ");
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
				printf("�������޸ĺ���鼮ID: ");
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
}

void searchuser()
{
	struct userstruct *p;
	char username[100];
	int flag = 0;

	p = head;
	system("cls");
	printf("\n\n\n\n\n\n\n");
	printf("**************************************************************");
	printf("\n��������Ҫ��ѯ���û���!\n");
	printf("username: ");
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
		system("cls");
		printf("�����ڸ��û���Ϣ\n");
		printf("3����Զ���ת������Աҳ��...\n");
		Sleep(3000);
		return;
	}
	else
	{
		int n;

		while (1)
		{
			system("cls");
			printf("\n\n\n\n\n\n\n");
			printf("**************************************************************");
			printf("\n\t�û�%s�ĸ�����Ϣ\n", p->username);
			printf("**************************************************************");
			printf("\nusername: ");
			puts(p->username);
			printf("userscert: ");
			puts(p->scert);
			printf("bookcount: %d\n", p->bookcount);
			if (p->bookcount != 0)
			{
				printf("booklist: ");
				for (int i = 0; i < p->bookcount; i++)
					puts(p->booklist[i]);
			}
			printf("����0���ع���Աҳ��!\n");
			scanf("%d", &n);
			if (n == 0)
				break;
		}
	}
}

void readuserfile()
{
	struct userstruct *p;
	FILE *fp;

	p = head;
	fp = fopen("user", "ab+");
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
	fp = fopen("admin", "ab+");
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
	fp = fopen("book", "ab+");
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
		fp = fopen("user", "w");
		while (userp != NULL)
		{
			fwrite(userp, sizeof(struct userstruct), 1, fp);
			userp = userp->next;
		}
	}
	else if (flag == 1)
	{
		fp = fopen("admin", "w");
		while (adminp != NULL)
		{
			fwrite(adminp, sizeof(struct adminstruct), 1, fp);
			adminp = adminp->next;
		}
	}
	else
	{
		fp = fopen("book", "w");
		while (bookp != NULL)
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
		for (int i = 0; i < userp->bookcount; i++)
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
		for (int i = 0; i < userp->bookcount; i++)
		{
			if (strcmp(userp->booklist[i], bookname) == 0)
			{
				flag = i;
				break;
			}
		}
		if (flag != -1)
		{
			for (int i = flag; i < userp->bookcount - 1; i++)
			{
				strcpy(userp->booklist[i], userp->booklist[i + 1]);
			}
			userp->bookcount--;
		}
		userp = userp->next;
	}
	writefile(0);
}

