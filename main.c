#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<math.h>

struct user_db
{
    char user_name[20];
    char user_pwd[20];
    int user_status;
    struct user_db *next;
}*user_head,*user_tail;

struct book_db
{
    char book_num[20];
    char book_name[20];
    char book_author[20];
    char book_press[20];
    char book_time[20];
    double book_price;
    int book_status;
    struct book_db *next;
}*book_head,*book_tail;

int user_count,book_count;

void main_menu();
void admin_login();
void admin_menu();
void user_register();
void book_login();
void book_explore(int auth);
void book_search(int auth);
void book_author_search(int auth);
void book_name_search(int auth);
void book_change();
void book_del();
void book_del_action();
void book_cancel(int auth);
void user_login();
void user_menu();
void user_check();
void exit_system();
void read_book_file();
void read_user_file();

void read_book_file()
{
	struct book_db *p;
	FILE *fp;

	p = book_head;
	fp = fopen("book.dat", "ab+");
	while (fread(p, sizeof(struct book_db), 1, fp))
	{
		if (p->next != NULL)
		{
			p = (struct book_db *)malloc(sizeof(struct book_db));

			book_tail->next = p;
			book_tail= p;
			book_tail->next = NULL;
		}
	}
}

void read_user_file()
{
    return;
}

void admin_login()
{
    system("cls");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    char username[20],userpwd[20];
    printf("***********************************************\n\n");
    printf("                  管理员登录>>\n\n");
    printf("***********************************************\n");
    printf("请输入用户名：\n");
    scanf("%s",username);
    printf("请输入密码：\n");
    scanf("%s",userpwd);
    if (strcmp(username,"root")==0&&strcmp(userpwd,"admin")==0)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("登录成功！即将跳转到用户主菜单...");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        Sleep(1500);
        admin_menu();
    }
    else
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("登录失败！请检查输入的用户名密码是否正确！");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        Sleep(1500);
        admin_login();
    }
}

void user_login()
{
    system("cls");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    char username[20],userpwd[20];
    printf("***********************************************\n\n");
    printf("                  借阅者登录>>\n\n");
    printf("***********************************************\n");
    printf("请输入用户名：\n");
    scanf("%s",username);
    printf("请输入密码：\n");
    scanf("%s",userpwd);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("登录成功！即将跳转到用户主菜单...");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    Sleep(1500);
    user_menu();
}

void user_register()
{
    system("cls");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    char username[20],userpwd[20];
    printf("***********************************************\n\n");
    printf("                  借阅者注册>>\n\n");
    printf("***********************************************\n");
    printf("请输入用户名：\n");
    scanf("%s",username);
    printf("请输入密码：\n");
    scanf("%s",userpwd);
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("注册成功！但在管理员确认之前，此账号暂时无法使用。\n请等待管理员确认。感谢您的配合！按任意键返回主菜单。\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("***********************************************\n");
    system("pause");
    main_menu();

}

void book_login()
{
    system("cls");
    struct book_db *p,*q;
    p = book_head;
    q = book_head;
    while (p->next)
    {
        p = p->next;
    }
    FILE *fp;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("***********************************************\n\n");
    printf("                 图书录入系统>>\n\n");
    printf("***********************************************\n");
    printf("请输入图书编号：\n");
    scanf("%s",p->book_num);
    printf("请输入书名：\n");
    scanf("%s",p->book_name);
    printf("请输入图书作者名：\n");
    scanf("%s",p->book_author);
    printf("图书出版社名：\n");
    scanf("%s",p->book_press);
    printf("请输入图书出版时间：\n");
    scanf("%s",p->book_time);
    printf("请输入图书的价格：\n");
    scanf("%lf",&p->book_price);
    p->book_status = 1;
    p->next = NULL;
    fp = fopen("book.dat","w");
    while (q!=NULL)
    {
        fwrite(q, sizeof(struct book_db), 1, fp);
		q = q->next;
    }
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("图书信息保存成功！要继续录入吗？");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("<1>.继续录入   <2>.返回上一层菜单\n");
    printf("***********************************************\n请输入数字：");
    int key_input;
    scanf("%d",&key_input);
    switch (key_input)
    {
        case 1: book_login();break;
        case 2: admin_menu();break;
        default:
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("错误：请输入数字1或2！");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                Sleep(1500);
                book_login();
            }
    }
}

void book_explore(int auth)
{
    int i;
    struct book_db *p;
    p = book_head;
    system("cls");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("\n               图书信息浏览\n\n");
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("请稍等，系统正在处理...\n");
    for (i=0;i<30;i++)
    {
        printf(">");
        Sleep(100);
    }
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("\n");
    printf("***********************************************\n");
    system("cls");
    printf("\n               图书信息浏览\n\n");
    printf("********************************************************\n");
    printf("书号\t书名\t作者名\t出版社\t出版时间\t图书价格\n");
    printf("--------------------------------------------------------\n");
    while (p->next)
    {
        printf("%s\t%s\t%S\t%s\t%s\t%lf\n",p->book_num,p->book_name,p->book_author,p->book_press,p->book_time,p->book_price);
    }
    printf("********************************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("所有图书浏览完毕。按任意键返回上一层菜单。\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    system("pause");
    if (auth) admin_menu();
    else user_menu();
}

void book_name_search(int auth)
{
    system("cls");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    int i;
    char words[20];
    printf("\n               图书信息查询\n\n");
    printf("                               --Search by name\n");
    printf("********************************************************\n");
    printf("请输入关键词：");
    scanf("%s",words);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("请稍等，系统正在处理...\n");

    for (i=0;i<30;i++)
    {
        printf(">");
        Sleep(100);
    }
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("\n");
    printf("********************************************************\n");
    printf("书号\t书名\t作者名\t出版社\t出版时间\t图书价格\n");
    printf("--------------------------------------------------------\n");
    printf("\n\n\n\n\n");
    printf("********************************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("所有图书查询完毕。按任意键返回主菜单。\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    system("pause");
    if (auth) admin_menu();
    else user_menu();
}

void book_author_search(int auth)
{
    system("cls");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    int i;
    char words[20];
    printf("\n               图书信息查询\n\n");
    printf("                             --Search by author\n");
    printf("***********************************************\n");
    printf("请输入关键词：");
    scanf("%s",words);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("请稍等，系统正在处理...\n");

    for (i=0;i<30;i++)
    {
        printf(">");
        Sleep(100);
    }
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("\n");
    printf("********************************************************\n");
    printf("书号\t书名\t作者名\t出版社\t出版时间\t图书价格\n");
    printf("--------------------------------------------------------\n");
    printf("\n\n\n\n\n");
    printf("********************************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("所有图书查询完毕。按任意键返回主菜单。\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    system("pause");
    if (auth) admin_menu();
    else user_menu();
}

void book_search(int auth)
{
    int key_input;
    system("cls");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("\n               图书信息查询\n\n");
    printf("***********************************************\n");
    printf("|现有两种搜索方式，请选择：                   |\n");
    printf("|      1 -------------- Search by name        |\n");
    printf("|      2 -------------- Search by author      |\n");
    printf("|      9 -------------- 返回上一级菜单        |\n");
    printf("***********************************************\n");
    printf("请输入数字：");
    scanf("%d",&key_input);
    switch (key_input)
    {
        case 1: book_name_search(auth);break;
        case 2: book_author_search(auth);break;
        case 9:
            {
                if (auth) {admin_menu();break;}
                else {user_menu();break;}
            }
        default:
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("错误：请输入数字1,2或9！");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                Sleep(1500);
                book_search(auth);
            }
    }
}

void book_change()
{
    char bookname[20],bookauthor[20],bookpress[20],booktime[20],booknum[20];
    double bookprice;
    system("cls");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("***********************************************\n\n");
    printf("                 图书信息修改>>\n\n");
    printf("***********************************************\n");
    printf("请输入图书编号：\n");
    scanf("%s",booknum);
    printf("请输入新书名：\n");
    scanf("%s",bookname);
    printf("请输入新图书作者名：\n");
    scanf("%s",bookauthor);
    printf("图书新的出版社名：\n");
    scanf("%s",bookpress);
    printf("请输入图书新的出版时间：\n");
    scanf("%s",booktime);
    printf("请输入图书新的的价格：\n");
    scanf("%lf",&bookprice);
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("图书信息保存成功！要继续录入吗？");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("<1>.继续修改   <2>.返回上一层菜单\n");
    printf("***********************************************\n请输入数字：");
    int key_input;
    scanf("%d",&key_input);
    switch (key_input)
    {
        case 1: book_change();break;
        case 2: admin_menu();break;
        default:
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("错误：请输入数字1或2！");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                Sleep(1500);
                book_login();
            }
    }
}

void book_del_action(char *booknum)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("图书信息删除成功！要继续删除吗？");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("<1>.继续删除   <2>.返回上一层菜单\n");
    printf("***********************************************\n请输入数字：");
    int key_input;
    scanf("%d",&key_input);
    switch (key_input)
    {
        case 1: book_del();break;
        case 2: admin_menu();break;
        default:
            {
                printf("错误：请输入数字1或2！");
                Sleep(1500);
                book_login();
            }
    }
}

void book_del()
{
    char booknum[20];
    system("cls");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("***********************************************\n\n");
    printf("                 图书信息删除>>\n\n");
    printf("***********************************************\n");
    printf("请输入图书编号：\n");
    scanf("%s",booknum);
    printf("查询到图书的信息如下：\n");
    printf("书号\t书名\t作者名\t出版社\t出版时间\t图书价格\n");
    printf("--------------------------------------------------------\n");
    printf("\n\n\n\n\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("确实要删除这本书？\n<1>.删除   <2>.取消并返回上一层菜单\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    int key_input2;
    scanf("%d",&key_input2);
    switch (key_input2)
    {
        case 1: book_del_action(booknum);break;
        case 2: admin_menu();break;
        default:
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("错误：请输入数字1或2！");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                Sleep(1500);
                book_del();
            }
    }
}

void book_cancel(int auth)
{
    char booknum[20];
    system("cls");
    printf("***********************************************\n\n");
    printf("                 图书取消借阅>>\n\n");
    printf("***********************************************\n");
    printf("请输入你要取消的书的图书编号：\n");
    scanf("%s",booknum);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("取消借阅成功！即将跳转到主菜单...\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    Sleep(1500);
    if (auth) admin_menu();
    else user_menu();
}

void user_check()
{
    system("cls");
    printf("***********************************************\n\n");
    printf("                  借阅者审核>>\n\n");
    printf("***********************************************\n");
    printf("下方列出\n");
}

void exit_system()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("正在退出系统，请稍后...\n");
    Sleep(1500);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("退出成功！");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    system("pause");
    printf("丢人！你马上给我退出战场！--凛冬");//彩蛋
    exit(0);
}

void user_menu()
{
    system("cls");
    int key_input;
    printf("\n              欢迎使用图书管理系统\n\n");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("当前登录身份：借阅者\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("***********************************************\n");
    printf("|        1 -------------- 图书信息浏览        |\n");
    printf("|        2 -------------- 图书信息查询        |\n");
    printf("|        3 -------------- 图书取消借阅        |\n");
    printf("|        9 -------------- 退出登录            |\n");
    printf("|        0 -------------- 退出系统            |\n");
    printf("***********************************************\n");
    printf("请输入数字：");
    scanf("%d",&key_input);
    switch (key_input)
    {
        case 1: book_explore(0);break;
        case 2: book_search(0);break;
        case 3: book_cancel(0);break;
        case 9: main_menu();break;
        case 0: exit_system();break;
        default:
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("错误：请输入数字1~6或0！");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                Sleep(1500);
                user_menu();
            }
    }
}

void admin_menu()
{
    system("cls");

    int key_input;
    printf("\n              欢迎使用图书管理系统\n\n");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("当前登录身份：图书馆管理员\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("***********************************************\n");
    printf("|        1 -------------- 图书信息录入        |\n");
    printf("|        2 -------------- 图书信息浏览        |\n");
    printf("|        3 -------------- 图书信息查询        |\n");
    printf("|        4 -------------- 图书信息修改        |\n");
    printf("|        5 -------------- 图书信息删除        |\n");
    printf("|        6 -------------- 借阅者审核          |\n");
    printf("|        9 -------------- 退出登录            |\n");
    printf("|        0 -------------- 退出系统            |\n");
    printf("***********************************************\n");
    printf("请输入数字：");
    scanf("%d",&key_input);
    switch (key_input)
    {
        case 1: book_login();break;
        case 2: book_explore(1);break;
        case 3: book_search(1);break;
        case 4: book_change();break;
        case 5: book_del();break;
        case 6: user_check();break;
        case 9: main_menu();break;
        case 0: exit_system();break;
        default:
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("错误：请输入数字1~6或0！");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                Sleep(1500);
                admin_menu();
            }
    }
}

void main_menu()
{
    system("cls");
    int key_input;
    printf("\n              欢迎使用图书管理系统\n\n");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("您还未登录，请先登录！\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("***********************************************\n");
    printf("|         1 -------------- 借阅者登录         |\n");
    printf("|         2 -------------- 借阅者注册         |\n");
    printf("|         3 -------------- 管理员登录         |\n");
    printf("|         0 -------------- 退出系统           |\n");
    printf("***********************************************\n");
    printf("请输入数字：");
    scanf("%d",&key_input);
    switch (key_input)
    {
        case 1: user_login();break;
        case 2: user_register();break;
        case 3: admin_login();break;
        case 0: exit_system();break;
        default:
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("错误：请输入数字1~3或0！");
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                Sleep(1500);
                main_menu();
            }
    }
}

int main()
{
    FILE *fp;

	user_head = (struct user_db *)malloc(sizeof(struct user_db));
	book_head = (struct book_db *)malloc(sizeof(struct book_db));

	//fp = fopen("user.dat", "a+");
	//user_count = fread(user_head, sizeof(struct user_db), 1, fp);
	//fclose(fp);
	//user_tail = user_head;
	//read_user_file();

	fp = fopen("book.dat", "a+");
	book_count = fread(book_head, sizeof(struct book_db), 1, fp);
	fclose(fp);
	book_tail = book_head;
	read_book_file();

    main_menu();
    return 0;
}
