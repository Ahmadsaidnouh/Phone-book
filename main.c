#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct
{
    int day,month,year;
} birth;
typedef struct
{
    char lstname[20];
    char fstname[20];
    birth date;
    char addrs[100];
    char phone[20];
    char email[100];
} person;
person pr[1000];
int i=0,x,saveflag=1;
void load()
{
    FILE *f=fopen("dict.txt","r");
    while(!feof(f))
    {
        //fscanf(f,"%[^,],%[^,],%d-%d-%d,%[^,],%[^,],%s\n",pr[i].lstname,pr[i].fstname,&pr[i].date.day,&pr[i].date.month,&pr[i].date.year,pr[i].addrs,pr[i].phone,pr[i].email);
        fscanf(f,"%[^,],",pr[i].lstname);
        fscanf(f,"%[^,],",pr[i].fstname);
        fscanf(f,"%d-%d-%d,",&pr[i].date.day,&pr[i].date.month,&pr[i].date.year);
        fscanf(f,"%[^,],",pr[i].addrs);
        fscanf(f,"%[^,],",pr[i].phone);
        fscanf(f,"%s\n",pr[i].email);
        i++;
    }
    fclose(f);
}
void query()
{
    char name[20];
    printf("Enter the Last Name of the contact to search for: ");
    scanf("%s",name);
    int x,a=1, flag=1,cm ;
    for(x=0; x<i; x++)
    {
        cm=strcmp(pr[x].lstname,name);
        if(cm==0)
        {
            flag=0;
            break;
        }
    }

    if(flag)
    {
        printf("\nNO CONTACT WITH SUCH LAST NAME FOUND.\n");
    }
    else
    {
        printf("\nPeople with last name \"%s\":\n\n",name);
        for( x=0; x<i; x++)
        {
            cm=strcmp(pr[x].lstname,name);
            if(!cm)
            {
                printf("Contact %d:\nFirstName: %s\nLastName: %s\nDayOfBirth: %d\nMonthOfBirth: %d\nYearOfBirth: %d\nAddress: %s\nPhone: %s\nEmail: %s\n\n",a,pr[x].fstname,pr[x].lstname,pr[x].date.day,pr[x].date.month,pr[x].date.year,pr[x].addrs,pr[x].phone,pr[x].email);
                a++;
            }
        }
    }


}
int validateDate(int day,int month,int year)
{
    int result=0;
    if(month==2 && day==29 && year%4!=0)
        result=1;
    else if(month==2 && day>29)
        result=1;
    else if((month==2 || month==4 || month==6 || month==9 || month==11) && (day==31))
        result=1;
    if(result==1)
        printf("\"%d-%d-%d\" is an Invalid Date. Enter a Valid Date again.\n",day,month,year);
    return result;
}
void addOrModify(char *s,int a)
{
    char name[20],domain[20];
    printf("\n%sLastname: ",s);
    scanf("%s",pr[a].lstname);
    printf("\n%sFirstname: ",s);
    scanf("%s",pr[a].fstname);

    do
    {
        printf("\n%sDay of Birth: ",s);
        do
        {
            scanf("%d",&pr[a].date.day);
            if(pr[a].date.day<1 || pr[a].date.day>31)
                printf("enter a valid day: ");

        }
        while(pr[a].date.day<1 || pr[a].date.day>31);
        printf("\n%sMonth of Birth:",s);
        do
        {
            scanf("%d",&pr[a].date.month);
            if(pr[a].date.month<1 || pr[a].date.month>12)
                printf("enter a valid month: ");
        }
        while(pr[a].date.month<1 || pr[a].date.month>12);
        printf("\n%sYear of Birth:",s);
        do
        {
            scanf("%d",&pr[a].date.year);
            if(pr[a].date.year<1)
                printf("enter a valid year: ");
        }
        while(pr[a].date.year<1);
    }
    while(validateDate(pr[a].date.day,pr[a].date.month,pr[a].date.year));
    printf("\n%sAddress: ",s);
    fgets(pr[a].addrs, 100, stdin);
    scanf("%99[^\n]%*c", pr[a].addrs);
    printf("\n%sPhone: ",s);
    scanf("%s",pr[a].phone);
    while(1)
    {
        char *ch=pr[a].phone;
        int flg=0;
        while(*ch!=0)
        {
            if(*ch<48||*ch>57)
            {
                flg=1;
                break;
            }
            ch++;
        }
        if(strlen(pr[a].phone)!=11 || flg==1)
        {
            printf("enter a valid number: ");
            scanf("%s",pr[a].phone);
        }
        else
            break;
    }
    printf("\n%sEmail in the form(name@domain.com): ",s);
    printf("\n\tname: ");
    scanf("%s",name);
    printf("\tdomain: ");
    scanf("%s",domain);
    strcat(name,"@");
    strcat(domain,".com");
    strcat(name,domain);
    strcpy(pr[a].email,name);
}
void print()
{
    for(int x=0; x<i; x++)
        printf("%s,%s,%d-%d-%d,%s,%s,%s\n",pr[x].lstname,pr[x].fstname,pr[x].date.day,pr[x].date.month,pr[x].date.year,pr[x].addrs,pr[x].phone,pr[x].email);
}
void add()
{
    int m;
    printf("How many Contacts you want to add?(enter a number): ");
    scanf("%d",&m);
    for(x=0; x<m; x++)
    {
        printf("\nMember %d",x+1);
        addOrModify("",x+i);
    }
    i=i+m;
    if(m)
        printf("\nContact(s) Added Successfully\n");
}
void Delete()
{
    person hold[1000];
    char lnm[20],fnm[20];
    int k,c;
    do
    {
        printf("Enter the Last Name of the Contact to be deleted: ");
        scanf("%s",lnm);
        printf("Enter the First Name of the Contact to be deleted: ");
        scanf("%s",fnm);
        c=0;
        for( k=0; k<i; k++)
        {
            int cmp1=strcmp(pr[k].lstname,lnm);
            int cmp2=strcmp(pr[k].fstname,fnm);
            if(!(cmp1==0 && cmp2==0))
            {
                hold[c]=pr[k];
                c++;
            }

        }
        if(c!=i)
        {
            for( k=0; k<c; k++)
                pr[k]=hold[k];
        }
        else
            printf("\nDeleting a Contact not existing. Check the Names and try again now.\n\n");
    }
    while(c==i);
    printf("\nContact Deleted Successfully\n");
    i=c;
}
void modify()
{
    char lnm[20],fnm[20];
    int x,cm;
    do
    {
        printf("Enter the Last Name of the Contact to modify:");
        scanf("%s",lnm);
        for(x=0; x<i; x++)
        {
            cm=strcmp(pr[x].lstname,lnm);
            if(!cm)
                break;
        }
        if(cm)
            printf("\nNo Contact with such Last Name. Check the Name and write again now.\n");
    }
    while(cm);
    printf("\nPeople with Last Name \"%s\":\n",lnm);
    char a[20][20];
    int cb=0;
    for(x=0; x<i; x++)
    {
        cm=strcmp(pr[x].lstname,lnm);
        if(!cm)
        {
            printf("\n%d)%s %s",cb+1,pr[x].fstname,pr[x].lstname);
            strcpy(a[cb],pr[x].fstname);
            cb++;
        }

    }
    if(cb!=1)
    {

        do
        {
            printf("\nEnter the First Name from the above Names:");
            scanf("%s",fnm);
            for(x=0; x<cb; x++)
            {
                cm=strcmp(a[x],fnm);
                if(!cm)
                    break;
            }
            if(cm)
                printf("\nNo Contact with such First Name. Check the Name and write again now.\n");
        }
        while(cm);
        printf("\n\nChosen name is: %s %s\n",fnm,lnm);
    }
    else
    {
        strcpy(fnm,a[0]);
        printf("\n\nChosen name is: %s %s\n",fnm,lnm);
    }
    for(x=0; x<i; x++)
    {
        if(!strcmp(pr[x].fstname,fnm) && !strcmp(pr[x].lstname,lnm))
            addOrModify("New ",x);
    }

}
int compareNames(const void *pa,const void *pb)
{
    const person *p1=pa;
    const person *p2=pb;
    return strcmp(p1->lstname,p2->lstname);
}
void sortByLName()
{
    printf("\nunsorted:\n");
    print();
    qsort(pr,i,sizeof(person),compareNames);
    printf("\nsorted:\n");
    print();
}
int compareDates(const void *a,const void *b)
{
    const person *p1=a;
    const person *p2=b;
    int day1=p1->date.day;
    int day2=p2->date.day;
    int month1=p1->date.month;
    int month2=p2->date.month;
    int year1=p1->date.year;
    int year2=p2->date.year;
    int indicator;
    if(year1<year2)
        indicator=-1;
    else if(year1>year2)
        indicator=1;
    else if(year1==year2)
    {
        if(month1<month2)
            indicator=-1;
        else if(month1>month2)
            indicator=1;
        else if(month1==month2)
        {
            if(day1<day2)
                indicator=-1;
            else if(day1>day2)
                indicator=1;
            else if(day1==day2)
                indicator=0;
        }


    }
    return indicator;
}
void sortByDOB()
{
    printf("\nunsorted:\n");
    print();
    qsort(pr,i,sizeof(person),compareDates);
    printf("\nsorted:\n");
    print();
}
void printSort()
{
    char sort[10];
    printf("Want to sort by \"Last Name(lstnm)\" or by \"Date of Birth(DOB)\"?\n(lstnm/DOB): ");
    do
    {
        scanf("%s",sort);
        if(strcmp(sort,"lstnm") && strcmp(sort,"DOB"))
            printf("Invalid entry. Enter again (lstnm/DOB):");
    }
    while(strcmp(sort,"lstnm") && strcmp(sort,"DOB"));

    if(!strcmp(sort,"lstnm"))
        sortByLName();
    else if(!strcmp(sort,"DOB"))
        sortByDOB();
}
void save()
{
    FILE *f=fopen("dict.txt","w");
    int x;
    for(x=0; x<i; x++)
    {
        //fscanf(f,"%[^,],%[^,],%d-%d-%d,%[^,],%[^,],%s\n",pr[i].lstname,pr[i].fstname,&pr[i].date.day,&pr[i].date.month,&pr[i].date.year,pr[i].addrs,pr[i].phone,pr[i].email);
        fprintf(f,"%s,",pr[x].lstname);
        fprintf(f,"%s,",pr[x].fstname);
        fprintf(f,"%d-%d-%d,",pr[x].date.day,pr[x].date.month,pr[x].date.year);
        fprintf(f,"%s,",pr[x].addrs);
        fprintf(f,"%s,",pr[x].phone);
        fprintf(f,"%s\n",pr[x].email);
    }
    fclose(f);
    printf("\nSaved Successfully\n");
}
void quit()
{
    char input[3];

    /*person tempr[1000];

    FILE *f=fopen("dict.txt","r");
    int tmpC=0,flag=0;

    while(!feof(f))
    {
        //fscanf(f,"%[^,],%[^,],%d-%d-%d,%[^,],%[^,],%s\n",pr[i].lstname,pr[i].fstname,&pr[i].date.day,&pr[i].date.month,&pr[i].date.year,pr[i].addrs,pr[i].phone,pr[i].email);
        fscanf(f,"%[^,],",tempr[tmpC].lstname);
        fscanf(f,"%[^,],",tempr[tmpC].fstname);
        fscanf(f,"%d-%d-%d,",&tempr[tmpC].date.day,&tempr[tmpC].date.month,&tempr[tmpC].date.year);
        fscanf(f,"%[^,],",tempr[tmpC].addrs);
        fscanf(f,"%[^,],",tempr[tmpC].phone);
        fscanf(f,"%s\n",tempr[tmpC].email);
        tmpC++;
    }
    fclose(f);
    if(tmpC!=i)
        printf("\nWarning: you have unsaved data that will be lost if you quit.\n");
    else if(tmpC==i)
    {
        for(x=0; x<i; x++)
        {
            if(strcmp(pr[x].fstname,tempr[x].fstname))
            {
                flag=1;
                break;
            }
            if(strcmp(pr[x].lstname,tempr[x].lstname))
            {
                flag=1;
                break;
            }
            if(pr[x].date.day!=tempr[x].date.day || pr[x].date.month!=tempr[x].date.month || pr[x].date.year!=tempr[x].date.year)
            {
                flag=1;
                break;
            }
            if(strcmp(pr[x].addrs,tempr[x].addrs))
            {
                flag=1;
                break;
            }
            if(strcmp(pr[x].phone,tempr[x].phone))
            {
                flag=1;
                break;
            }
            if(strcmp(pr[x].email,tempr[x].email))
            {
                flag=1;
                break;
            }
        }
        if(flag)
            printf("\nWarning: you have unsaved data that will be lost if you quit.\n");
    }*/
    if(saveflag!=1)
       printf("\nWarning: you have unsaved data that will be lost if you quit.\n");
    printf("\nAre you sure you want to quit?\n(y/n): ");
    do
    {
        scanf("%s",input);
        if(strcmp(input,"y") && strcmp(input,"n"))
            printf("Invalid input. Enter again (y/n): ");
    }
    while(strcmp(input,"y") && strcmp(input,"n"));

    if(!strcmp(input,"y"))
        exit(0);
}
void pause()
{
    getchar();
    printf("\nPress Enter to continue...");
    getchar();
}
int main()
{
    char entry[8][30]= {"Query(Search)","Add","Delete","Modify","Print(Sort)","Print(CurrentState)","Save","Quit"};
    int d,num,flag;
    load();
    while(1)
    {
        flag=1;
        system("@cls||clear");
        printf("Choose an operation from the menu below: \n");
        for(d=0; d<8; d++)
            printf("%d)%s\n",d+1,entry[d]);
        printf("(enter the number of the operation): ");
        do
        {
            scanf("%d",&num);
            for(d=1; d<9; d++)
            {
                if(d==num)
                {
                    flag=0;
                    break;
                }
            }
            if(flag)
                printf("Invalid input. Enter a number again: ");
        }
        while(flag);

        if(num==1)
        {
            printf("\nQuery:\n");
            query();
            pause();
        }
        else if(num==2)
        {
            printf("\nAdd:\n");
            add();
            saveflag=0;
            pause();
        }
        else if(num==3)
        {
            printf("\nDelete:\n");
            Delete();
            saveflag=0;
            pause();
        }
        else if(num==4)
        {
            printf("\nModify:\n");
            modify();
            saveflag=0;
            pause();
        }
        else if(num==5)
        {
            printf("\nPrint(Sort):\n");
            printSort();
            saveflag=0;
            pause();
        }
        else if(num==6)
        {
            printf("\nPrint(CurrentState):\n");
            print();
            pause();
        }
        else if(num==7)
        {
            save();
            saveflag=1;
            pause();
        }
        else if(num==8)
            quit();
    }
    return 0;

}
