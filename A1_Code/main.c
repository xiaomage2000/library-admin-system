#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>

struct userstruct        /*用户结构体*/
{
	int bookcount;
	char username[10];
	char scert[10];
	char booklist[10][20];
	struct userstruct *next;
};

struct adminstruct       /*管理员结构体*/
{
	char adminname[10];
	char scert[10];
	struct adminstruct *next;
};

struct bookstruct        /*图书结构体*/
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
char superpwd[20];//超级密码

/*定义各种函数*/
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

//主函数
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

    system("title 图书馆管理系统 --by 软件1804马云龙");
    printf("系统正在初始化，请稍后...\n");
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

//启动系统，进入主菜单
void startsys()
{
	int cmd;
	int end = 0;

    system("cls");
    printf("\n              欢迎使用图书管理系统\n\n");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("您还未登录，请先登录！\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("***********************************************\n");
    printf("|         1 -------------- 借阅者登录         |\n");
    printf("|         2 -------------- 管理员登录         |\n");
    printf("|         3 -------------- 借阅者注册         |\n");
    printf("|         4 -------------- 管理员注册         |\n");
    printf("|         0 -------------- 退出系统           |\n");
    printf("***********************************************\n");
    printf("请输入数字：");
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
            printf("错误：请输入数字1~4或0！");
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            Sleep(1500);
        }
    }
    if (end == 1)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        printf("正在退出系统，请稍后...\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        printf("——Co~ ");
        Sleep(900);
        printf("Co~ ");
        Sleep(900);
        printf("Da~ ");
        Sleep(900);
        printf("Yo~ ");
        Sleep(900);
        printf("Docter~  \n——你不要过来啊！！！\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("退出成功！");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        system("pause");
        exit(0);
    }
}

//用户登录菜单
void userlogin()
{
    struct userstruct *p;
	char username[100];
	char userscert[100];
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	p = head;
	system("cls");
    printf("***********************************************\n\n");
    printf("                  借阅者登录>>\n\n");
    printf("***********************************************\n");
    printf("请输入您的用户信息：\n");
	printf("用户名：");
	gets(username);
	printf("密码：");
	gets(userscert);

	while (p != NULL)
	{
		if (strcmp(p->username, username) == 0)
		{
			while (strcmp(p->scert, userscert) != 0)
			{
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：密码错误！请重新输入\n");
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("密码：");
				gets(userscert);
			}
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			printf("用户%s登陆成功！\n",p->username);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("3秒后自动跳转至管理界面...");
			Sleep(3000);
			userfunction(p);
		}
		p = p->next;
	}
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("登录失败！请检查用户名和密码！即将返回上一层。");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Sleep(3000);
	startsys();
}

//用户主菜单
void userfunction(struct userstruct *p)
{
	int cmd;
	int end = 0;

	while (1)
	{
		system("cls");
		printf("\n              欢迎使用图书借阅系统\n\n");
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("当前登录身份：%s\n",p->username);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        printf("***********************************************\n");
        printf("|        1 -------------- 借阅图书            |\n");
        printf("|        2 -------------- 图书信息浏览        |\n");
        printf("|        3 -------------- 图书信息检索        |\n");
        printf("|        4 -------------- 归还图书            |\n");
        printf("|        5 -------------- 已借阅图书          |\n");
        printf("|        0 -------------- 退出登录            |\n");
        printf("***********************************************\n");
		printf("请输入数字：");
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
            printf("错误：请输入数字1~3或0！");
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            Sleep(1500);
		}
		if (end == 1)
			startsys();
	}
}

//用户注册
void userregister()
{
	struct userstruct *p;
	char username[1000];
	char scert[1000];
	FILE *fp;

	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	printf("***********************************************\n\n");
    printf("                  借阅者注册>>\n\n");
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    printf("提示：用户名和密码的长度不得多于10个字符。\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("请输入您的用户信息: \n");
	if (usercount == 0)            //第一次添加
	{
		printf("用户名: ");
		while (gets(username))
		{
			if (strlen(username) < 10 && (!isexist(username, 0)))
				break;
			else if (isexist(username, 0))
			{
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：该用户名已经存在！请换一个用户名注册或登录！\n");
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("用户名: ");
			}
			else
			{
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：字符长度超过限制\n");
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("用户名: ");
			}
		}
		strcpy(head->username, username);
		printf("密码: ");
		while (gets(scert))
		{
			if (strlen(scert) < 10)
				break;
			else
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：字符长度超过限制\n");
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
		printf("用户名：");
		while (gets(username))
		{
			if (strlen(username) < 10 && !isexist(username, 0))
				break;
			else if (isexist(username, 0))
			{
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：该用户名已经存在！请换一个用户名注册或登录！\n");
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("用户名：");
			}
			else
			{
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：字符长度超过限制\n");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("用户名：");
			}
		}
		strcpy(p->username, username);
		printf("密码：");
		while (gets(scert))
		{
			if (strlen(scert) < 10)
				break;
			else
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：字符长度超过限制\n");
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

    printf("最后一步：请管理员输入超级密码，以审核注册：");
    scanf("%s",superpwd);
    if (strcmp(superpwd,"superpassword")==0)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("超级密码正确！正在完成注册...\n");
        Sleep(500);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
    else
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("超级密码错误！注册失败！即将返回上一级！");
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
	printf("用户%s创建成功！\n", end->username);

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("3秒后自动返回主界面....\n");
	Sleep(3000);
}

//判断是否存在的函数
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

//管理员登录
void adminlogin()
{
	struct adminstruct *p;
	char adminname[100];
	char adminscert[100];
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	p = adminhead;
	system("cls");
    printf("***********************************************\n\n");
    printf("                  管理员登录>>\n\n");
    printf("***********************************************\n");
    printf("请输入您的用户信息：\n");
	printf("用户名：");
	gets(adminname);
	printf("密码：");
	gets(adminscert);

	while (p != NULL)
	{
		if (strcmp(p->adminname, adminname) == 0)
		{
			while (strcmp(p->scert, adminscert) != 0)
			{
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：密码错误！请重新输入\n");
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("密码：");
				gets(adminscert);
			}
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			printf("管理员%s登陆成功！\n",p->adminname);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("3秒后自动跳转至管理界面...");
			Sleep(3000);
			adminfunction(p);
		}
		p = p->next;
	}
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("登录失败！请检查用户名和密码！即将返回上一层。");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Sleep(3000);
	startsys();
}

//管理员主菜单
void adminfunction(struct adminstruct *p)
{
	int cmd;
	int end = 0;

	while (1)
	{
		system("cls");
		printf("\n              欢迎使用图书管理系统\n\n");
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("当前登录身份：%s\n",p->adminname);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        printf("***********************************************\n");
        printf("|        1 -------------- 图书信息录入        |\n");
        printf("|        2 -------------- 图书信息删除        |\n");
        printf("|        3 -------------- 图书信息修改        |\n");
        printf("|        4 -------------- 图书信息浏览        |\n");
        printf("|        5 -------------- 图书信息检索        |\n");
        printf("|        6 -------------- 用户信息查询        |\n");
        printf("|        0 -------------- 退出登录            |\n");
        printf("***********************************************\n");
		printf("输入您需要进行的操作: ");
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
            printf("错误：请输入数字1~5或0！");
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            Sleep(1500);
		}
		if (end == 1)
			startsys();
	}
}

//管理员注册
void adminregister()
{
	struct adminstruct *p;
	char adminname[1000];
	char adminscert[1000];
	FILE *fp;
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("***********************************************\n\n");
    printf("                  管理员注册>>\n\n");
    printf("***********************************************\n");
    printf("请先输入超级密码：");
    scanf("%s",superpwd);
    if (strcmp(superpwd,"superpassword")==0)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("超级密码正确！请继续注册过程~\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
    else
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("超级密码错误！即将返回上一级！");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        Sleep(3000);
        return;
    }
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    printf("提示：用户名和密码的长度不得多于10个字符。\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("请输入您的用户信息：\n");
    getchar();
	if (admincount == 0)            //第一次添加
	{
		adminhead = (struct adminstruct *)malloc(sizeof(struct adminstruct));
		printf("用户名：");
		while (gets(adminname))
		{
			if (strlen(adminname) < 10)
				break;
			else
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：字符长度超过限制");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
		}
		strcpy(adminhead->adminname, adminname);
		printf("密码：");
		while (gets(adminscert))
		{
			if (strlen(adminscert) < 10)
				break;
			else
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：字符长度超过限制");
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
		printf("用户名：");
		while (gets(adminname))
		{
			if (strlen(adminname) < 10)
				break;
			else
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：字符长度超过限制");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
		}
		strcpy(p->adminname, adminname);
		printf("密码：");
		while (gets(adminscert))
		{
			if (strlen(adminscert) < 10)
				break;
			else
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：字符长度超过限制");
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
	printf("管理员%s创建成功\n", adminend->adminname);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("3秒后自动返回主界面....\n");
	Sleep(3000);
}

//借书模块
void borrowbook(struct userstruct *userp)
{
	struct bookstruct *p;
	char bookname[100];
	int exist = 0;
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("***********************************************\n\n");
    printf("                 图书借阅系统>>\n\n");
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    printf("提示：下方显示了当先书库中所有的书，请酌情借阅\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	p = bookhead;
	printf("书号\t书名\t作者名\t出版社\t出版时间\t价格\t图书余量\n");
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
	printf("输入您需要借阅的书籍名称: ");
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
				printf("错误：此书无余量，暂时不能借阅...");
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
		printf("错误：不存在此书！\n");
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	}
	else
	{
	    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	    printf("%s借阅成功！\n", p->bookname);
	    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	}

	printf("3秒后返回用户界面...");
	Sleep(3000);
}

//还书模块
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
    printf("                 图书归还系统>>\n\n");
    printf("***********************************************\n");
	p = bookhead;
	printf("书籍名称：\n");
	while (count--)
	{
		printf("%s\n", userp->booklist[count]);
	}
	printf("请输入你需要归还的书籍名称: ");

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
			printf("错误：你借阅的书籍中不存在此书籍...\n");
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("请重新输入你需要归还的书籍名称: ");
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
	printf("\n%s归还成功！\n", bookname);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("3秒后自动跳转回用户界面...");
	Sleep(3000);
}

/*已借阅图书信息*/
void findbook(struct userstruct *userp)
{
	int count = userp->bookcount;
	int n;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
    printf("***********************************************\n\n");
    printf("                 已借阅图书>>\n\n");
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    printf("提示：下方的列表中列出了你所借的所有图书的名称\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	while (count--)
	{
		printf("%s\n", userp->booklist[count]);
	}
	printf("\n输入0返回用户界面：");
    scanf("%d", &n);
    if (n == 0)
        return;
    else
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("无效的输入，请重新输入！");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        Sleep(1500);
        findbook(userp);
    }
}

//增加图书模块
void addbook()
{
	struct bookstruct *p;
	char bookname[100];
	FILE *fp;

	system("cls");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("***********************************************\n\n");
    printf("                 图书录入系统>>\n\n");
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    printf("提示：书名，作者名以及出版社名字的长度不得多于10个字符。输入0返回上一级。\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	if (bookcount == 0)
	{
		printf("输入新增书籍的图书名称: ");
		while (gets(bookname))
		{
		    if (strcmp(bookname,"0")==0) return;
			if (strlen(bookname) > 10)
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：字符长度超过限制\n");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("输入新增书籍的图书名称: ");
            }
			else
				break;
		}
		strcpy(bookhead->bookname, bookname);
		printf("图书编号：");
		scanf("%d", &bookhead->id);
		printf("作者：");
		scanf("%s", bookhead->author);
		printf("出版社：");
		scanf("%s", bookhead->press);
		printf("出版年份：");
		scanf("%d", &bookhead->year);
		printf("出版月份：");
		scanf("%d", &bookhead->month);
		printf("出版日期：");
		scanf("%d", &bookhead->day);
		printf("图书价格：");
		scanf("%lf", &bookhead->price);
		printf("图书余量：");
		scanf("%d", &bookhead->count);

		bookend = bookhead;
		bookend->next = NULL;
	}
	else
	{
	    printf("输入新增书籍的图书名称: ");
		while (gets(bookname))
		{
		    if (strcmp(bookname,"0")==0) return;
			if (strlen(bookname) > 10)
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("错误：字符长度超过限制\n");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				Sleep(1500);
				printf("输入新增书籍的图书名称: ");
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

			printf("输入新添书籍的数量: ");
			scanf("%d", &count);
			p->count += count;
		}
		else
		{
			p = (struct bookstruct *)malloc(sizeof(struct bookstruct));

			strcpy(p->bookname, bookname);
			printf("图书编号：");
			scanf("%d", &p->id);
			printf("作者：");
			scanf("%s", p->author);
			printf("出版社：");
            scanf("%s", p->press);
			printf("出版年份：");
			scanf("%d", &p->year);
			printf("出版月份：");
			scanf("%d", &p->month);
			printf("出版日期：");
			scanf("%d", &p->day);
			printf("图书价格：");
            scanf("%lf", &p->price);
			printf("图书余量：");
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
	printf("书籍添加成功\n");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("3秒后自动返回管理员界面....\n");
	Sleep(3000);
}

//删除图书模块
void deletebook()
{
	struct bookstruct *bookp;
	char bookname[100];
	int exist = 0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    printf("***********************************************\n\n");
    printf("                 图书信息删除>>\n\n");
    printf("***********************************************\n");
	bookp = bookhead;
	printf("输入你需要删除的书籍名称，输入0返回上一层: ");
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
			printf("不存在此书籍名称的书籍...\n");
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("请重新输入: ");
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
	printf("删除图书成功！即将返回至主菜单...");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Sleep(1500);
}

void explorebook()
{
    struct bookstruct *p;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
    printf("\n                  图书信息浏览\n\n");
    printf("****************************************************************\n");
	p = bookhead;
	if (p == NULL)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("当前书库为空，请管理员先录入图书数据！\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
    else
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
        printf("提示：书库内全部图书信息如下：\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        printf("书号\t书名\t作者名\t出版社\t出版时间\t价格\t图书余量\n");
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
	printf("\n输入0返回上一层菜单：");
	int n;
	scanf("%d",&n);
	if (n!=0)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("错误：输入数字错误！请重新输入！");
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
    printf("\n                图书信息检索\n\n");
    printf("                                                --Search by name\n");
    printf("****************************************************************\n");
	printf("请输入您需要检索的书籍名称: ");
	gets(bookname);

	p = bookhead;
	while (p != NULL)
	{
		if (strcmp(p->bookname, bookname) == 0)
		{
		    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		    printf("提示：检索结果如下：\n");
		    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		    printf("书号\t书名\t作者名\t出版社\t出版时间\t价格\t图书余量\n");
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
        printf("错误：未找到相关书籍...\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
	printf("\n输入0返回上一层菜单：");
	int n;

	while (1)
	{
		scanf("%d", &n);
		if (n == 0)
			break;
        else
        {
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
            printf("错误：输入数字错误！请重新输入！");
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
    printf("\n               图书信息检索\n\n");
    printf("                                              --Search by author\n");
    printf("****************************************************************\n");
	printf("请输入您需要检索的书籍作者: ");
	gets(bookauthor);

	p = bookhead;
	while (p != NULL)
	{
		if (strcmp(p->author, bookauthor) == 0)
		{
		    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		    printf("提示：检索结果如下：\n");
		    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		    printf("书号\t书名\t作者名\t出版社\t出版时间\t图书余量\n");
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
        printf("错误：未找到相关书籍...\n");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
	printf("\n输入0返回上一层菜单：");
	int n;

	while (1)
	{
		scanf("%d", &n);
		if (n == 0)
			break;
        else
        {
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
            printf("错误：输入数字错误！请重新输入！");
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            Sleep(1500);
        }
	}
	return;
}

//查找图书模块——按图书名称
void searchbook()
{
    int cmd;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
    printf("\n               图书信息检索\n\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("提示：我们提供两种检索图书的方法，请按需选择。\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("***********************************************\n");
    printf("|      1 -------------- Search by name        |\n");
    printf("|      2 -------------- Search by author      |\n");
    printf("|      0 -------------- 返回上一层            |\n");
    printf("***********************************************\n");
    printf("输入您需要进行的操作: ");
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
            printf("错误：请输入数字1~5或0！");
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            Sleep(1500);
            searchbook();
	    }
	}
}

//修改图书信息
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
    printf("                 图书信息修改>>\n\n");
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	printf("提示：下方显示了当先书库中所有的书，请按需修改：\n");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	while (bookp != NULL)
	{
		printf("图书名称：%10s\n", bookp->bookname);
		bookp = bookp->next;
	}

	bookp = bookhead;
	printf("输入你需要修改的书籍名称，输入0返回上一级: ");
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
            printf("错误：不存在该书籍名称，请重新输入: ");
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
		printf("|        1 -------------- 修改书籍名称        |\n");
		printf("|        2 -------------- 修改书籍编号        |\n");
		printf("|        3 -------------- 修改书籍日期        |\n");
		printf("|        4 -------------- 修改书籍余量        |\n");
		printf("|        5 -------------- 修改书籍作者        |\n");
		printf("|        6 -------------- 修改书籍出版社      |\n");
		printf("|        7 -------------- 修改书籍价格        |\n");
		printf("|        0 -------------- 返回上一层          |\n");
		printf("***********************************************\n");
		while (1)
		{
			printf("输入您需要进行的操作,输入0返回上一层: ");
			scanf("%d", &cmd);
			switch (cmd)
			{
                case 1:
                {
                    printf("输入你修改后的书籍名称: ");
                    scanf("%s", bookname);
                    changuserbook(bookp->bookname,bookname);
                    strcpy(bookp->bookname, bookname);
                    break;
                }
                case 2:
                {
                    printf("输入你修改后的书籍编号: ");
                    scanf("%d", &bookid);
                    bookp->id = bookid;
                    break;
                }
                case 3:
                {
                    printf("输入你修改后的书籍日期: ");
                    scanf("%d%d%d", &bookyear, &bookmonth, &bookday);
                    bookp->year = bookyear;
                    bookp->month = bookmonth;
                    bookp->day = bookday;
                    break;
                }
                case 4:
                {
                    printf("输入你修改后的书籍数量: ");
                    scanf("%d", &count);
                    bookp->count = count;
                    break;
                }
                case 5:
                {
                    printf("输入你修改后的书籍作者: ");
                    scanf("%s", bookauthor);
                    strcpy(bookp->author, bookauthor);
                    break;
                }
                case 6:
                {
                    printf("输入你修改后的书籍出版社: ");
                    scanf("%s", bookpress);
                    strcpy(bookp->press, bookpress);
                    break;
                }
                case 7:
                {
                    printf("输入你修改后的书籍价格: ");
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
	printf("修改图书信息成功！即将返回至主菜单...");
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Sleep(1500);
}

//查找用户
void searchuser()
{
	struct userstruct *p;
	char username[100];
	int flag = 0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	p = head;
	system("cls");
	printf("***********************************************\n\n");
    printf("                 用户信息查询>>\n\n");
    printf("***********************************************\n");
	printf("请输入您需要查询的用户名：");
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
		printf("错误：不存在该用户信息\n");
		SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		printf("3秒后自动跳转至管理员页面...\n");
		Sleep(3000);
		return;
	}
	else
	{
		int n;
		while (1)
		{
			printf("***********************************************\n");
			printf("用户%s的个人信息：\n", p->username);
			printf("用户名：");
			puts(p->username);
			printf("密码：");
			puts(p->scert);

			printf("当前借书数量：%d\n", p->bookcount);
			if (p->bookcount != 0)
			{
				printf("当前所借书目：\n");
				int i;
				for (i = 0; i < p->bookcount; i++)
					puts(p->booklist[i]);
			}
			printf("***********************************************");
			printf("\n输入0返回管理员页面!\n");
			scanf("%d", &n);
			if (n == 0) return;
			else
			{
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			    printf("错误：输入错误！");
			    Sleep(1500);
			    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			    system("cls");
			}
		}
	}
}

//读取文件
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
