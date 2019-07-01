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
    printf("                  ����Ա��¼>>\n\n");
    printf("***********************************************\n");
    printf("�������û�����\n");
    scanf("%s",username);
    printf("���������룺\n");
    scanf("%s",userpwd);
    if (strcmp(username,"root")==0&&strcmp(userpwd,"admin")==0)
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("��¼�ɹ���������ת���û����˵�...");
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
        Sleep(1500);
        admin_menu();
    }
    else
    {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("��¼ʧ�ܣ�����������û��������Ƿ���ȷ��");
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
    printf("                  �����ߵ�¼>>\n\n");
    printf("***********************************************\n");
    printf("�������û�����\n");
    scanf("%s",username);
    printf("���������룺\n");
    scanf("%s",userpwd);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("��¼�ɹ���������ת���û����˵�...");
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
    printf("                  ������ע��>>\n\n");
    printf("***********************************************\n");
    printf("�������û�����\n");
    scanf("%s",username);
    printf("���������룺\n");
    scanf("%s",userpwd);
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("ע��ɹ������ڹ���Աȷ��֮ǰ�����˺���ʱ�޷�ʹ�á�\n��ȴ�����Աȷ�ϡ���л������ϣ���������������˵���\n");
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
    printf("                 ͼ��¼��ϵͳ>>\n\n");
    printf("***********************************************\n");
    printf("������ͼ���ţ�\n");
    scanf("%s",p->book_num);
    printf("������������\n");
    scanf("%s",p->book_name);
    printf("������ͼ����������\n");
    scanf("%s",p->book_author);
    printf("ͼ�����������\n");
    scanf("%s",p->book_press);
    printf("������ͼ�����ʱ�䣺\n");
    scanf("%s",p->book_time);
    printf("������ͼ��ļ۸�\n");
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
    printf("ͼ����Ϣ����ɹ���Ҫ����¼����");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("<1>.����¼��   <2>.������һ��˵�\n");
    printf("***********************************************\n���������֣�");
    int key_input;
    scanf("%d",&key_input);
    switch (key_input)
    {
        case 1: book_login();break;
        case 2: admin_menu();break;
        default:
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("��������������1��2��");
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
    printf("\n               ͼ����Ϣ���\n\n");
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("���Եȣ�ϵͳ���ڴ���...\n");
    for (i=0;i<30;i++)
    {
        printf(">");
        Sleep(100);
    }
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("\n");
    printf("***********************************************\n");
    system("cls");
    printf("\n               ͼ����Ϣ���\n\n");
    printf("********************************************************\n");
    printf("���\t����\t������\t������\t����ʱ��\tͼ��۸�\n");
    printf("--------------------------------------------------------\n");
    while (p->next)
    {
        printf("%s\t%s\t%S\t%s\t%s\t%lf\n",p->book_num,p->book_name,p->book_author,p->book_press,p->book_time,p->book_price);
    }
    printf("********************************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("����ͼ�������ϡ��������������һ��˵���\n");
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
    printf("\n               ͼ����Ϣ��ѯ\n\n");
    printf("                               --Search by name\n");
    printf("********************************************************\n");
    printf("������ؼ��ʣ�");
    scanf("%s",words);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("���Եȣ�ϵͳ���ڴ���...\n");

    for (i=0;i<30;i++)
    {
        printf(">");
        Sleep(100);
    }
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("\n");
    printf("********************************************************\n");
    printf("���\t����\t������\t������\t����ʱ��\tͼ��۸�\n");
    printf("--------------------------------------------------------\n");
    printf("\n\n\n\n\n");
    printf("********************************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("����ͼ���ѯ��ϡ���������������˵���\n");
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
    printf("\n               ͼ����Ϣ��ѯ\n\n");
    printf("                             --Search by author\n");
    printf("***********************************************\n");
    printf("������ؼ��ʣ�");
    scanf("%s",words);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("���Եȣ�ϵͳ���ڴ���...\n");

    for (i=0;i<30;i++)
    {
        printf(">");
        Sleep(100);
    }
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("\n");
    printf("********************************************************\n");
    printf("���\t����\t������\t������\t����ʱ��\tͼ��۸�\n");
    printf("--------------------------------------------------------\n");
    printf("\n\n\n\n\n");
    printf("********************************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("����ͼ���ѯ��ϡ���������������˵���\n");
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
    printf("\n               ͼ����Ϣ��ѯ\n\n");
    printf("***********************************************\n");
    printf("|��������������ʽ����ѡ��                   |\n");
    printf("|      1 -------------- Search by name        |\n");
    printf("|      2 -------------- Search by author      |\n");
    printf("|      9 -------------- ������һ���˵�        |\n");
    printf("***********************************************\n");
    printf("���������֣�");
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
                printf("��������������1,2��9��");
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
    printf("                 ͼ����Ϣ�޸�>>\n\n");
    printf("***********************************************\n");
    printf("������ͼ���ţ�\n");
    scanf("%s",booknum);
    printf("��������������\n");
    scanf("%s",bookname);
    printf("��������ͼ����������\n");
    scanf("%s",bookauthor);
    printf("ͼ���µĳ���������\n");
    scanf("%s",bookpress);
    printf("������ͼ���µĳ���ʱ�䣺\n");
    scanf("%s",booktime);
    printf("������ͼ���µĵļ۸�\n");
    scanf("%lf",&bookprice);
    printf("***********************************************\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("ͼ����Ϣ����ɹ���Ҫ����¼����");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("<1>.�����޸�   <2>.������һ��˵�\n");
    printf("***********************************************\n���������֣�");
    int key_input;
    scanf("%d",&key_input);
    switch (key_input)
    {
        case 1: book_change();break;
        case 2: admin_menu();break;
        default:
            {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                printf("��������������1��2��");
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
    printf("ͼ����Ϣɾ���ɹ���Ҫ����ɾ����");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("<1>.����ɾ��   <2>.������һ��˵�\n");
    printf("***********************************************\n���������֣�");
    int key_input;
    scanf("%d",&key_input);
    switch (key_input)
    {
        case 1: book_del();break;
        case 2: admin_menu();break;
        default:
            {
                printf("��������������1��2��");
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
    printf("                 ͼ����Ϣɾ��>>\n\n");
    printf("***********************************************\n");
    printf("������ͼ���ţ�\n");
    scanf("%s",booknum);
    printf("��ѯ��ͼ�����Ϣ���£�\n");
    printf("���\t����\t������\t������\t����ʱ��\tͼ��۸�\n");
    printf("--------------------------------------------------------\n");
    printf("\n\n\n\n\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("ȷʵҪɾ���Ȿ�飿\n<1>.ɾ��   <2>.ȡ����������һ��˵�\n");
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
                printf("��������������1��2��");
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
    printf("                 ͼ��ȡ������>>\n\n");
    printf("***********************************************\n");
    printf("��������Ҫȡ�������ͼ���ţ�\n");
    scanf("%s",booknum);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("ȡ�����ĳɹ���������ת�����˵�...\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    Sleep(1500);
    if (auth) admin_menu();
    else user_menu();
}

void user_check()
{
    system("cls");
    printf("***********************************************\n\n");
    printf("                  ���������>>\n\n");
    printf("***********************************************\n");
    printf("�·��г�\n");
}

void exit_system()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("�����˳�ϵͳ�����Ժ�...\n");
    Sleep(1500);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("�˳��ɹ���");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    system("pause");
    printf("���ˣ������ϸ����˳�ս����--�ݶ�");//�ʵ�
    exit(0);
}

void user_menu()
{
    system("cls");
    int key_input;
    printf("\n              ��ӭʹ��ͼ�����ϵͳ\n\n");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("��ǰ��¼��ݣ�������\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("***********************************************\n");
    printf("|        1 -------------- ͼ����Ϣ���        |\n");
    printf("|        2 -------------- ͼ����Ϣ��ѯ        |\n");
    printf("|        3 -------------- ͼ��ȡ������        |\n");
    printf("|        9 -------------- �˳���¼            |\n");
    printf("|        0 -------------- �˳�ϵͳ            |\n");
    printf("***********************************************\n");
    printf("���������֣�");
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
                printf("��������������1~6��0��");
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
    printf("\n              ��ӭʹ��ͼ�����ϵͳ\n\n");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printf("��ǰ��¼��ݣ�ͼ��ݹ���Ա\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("***********************************************\n");
    printf("|        1 -------------- ͼ����Ϣ¼��        |\n");
    printf("|        2 -------------- ͼ����Ϣ���        |\n");
    printf("|        3 -------------- ͼ����Ϣ��ѯ        |\n");
    printf("|        4 -------------- ͼ����Ϣ�޸�        |\n");
    printf("|        5 -------------- ͼ����Ϣɾ��        |\n");
    printf("|        6 -------------- ���������          |\n");
    printf("|        9 -------------- �˳���¼            |\n");
    printf("|        0 -------------- �˳�ϵͳ            |\n");
    printf("***********************************************\n");
    printf("���������֣�");
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
                printf("��������������1~6��0��");
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
    printf("\n              ��ӭʹ��ͼ�����ϵͳ\n\n");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    printf("����δ��¼�����ȵ�¼��\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    printf("***********************************************\n");
    printf("|         1 -------------- �����ߵ�¼         |\n");
    printf("|         2 -------------- ������ע��         |\n");
    printf("|         3 -------------- ����Ա��¼         |\n");
    printf("|         0 -------------- �˳�ϵͳ           |\n");
    printf("***********************************************\n");
    printf("���������֣�");
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
                printf("��������������1~3��0��");
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
