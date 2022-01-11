#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

//structure declaration
typedef struct car
{
    char name[20];
    int no;
    struct node *next;
}car;
typedef struct c_details //for storing detail of customers who have given order
{
    char car_name[20];
    char name[20];
    char mob_no[10];
    struct c_details *next;
}c_details;

//function declarations
int customer_list(); //to create queue for customers
void load_customers_list();
car* load_car_list();
c_details* d_customer(); //to delete customer from queue
void display_customer(c_details*); // used to display information about sell
void last_sell(c_details *); // to display last sold car details
void all_sell();//stack
void s_details(c_details*); // to store the deleted customer in the stack from queue
car* cars_list(); //to create a car list invantory
void print(car*); //to print car available
void create(car*); //to store value in file
void store_customer_list();
c_details* peek_customer();
void store_sell_info();
int s_details_flag=0;
int search(car* ,char[]);
void c_queprint(c_details *);
void load_sell_info();

//global variable or pointer's declaration
car *head=NULL; //for the linked list of inventory
int c_que_flag=0;
c_details *c_front=NULL,*c_rear=NULL,*s_top=NULL; //c_front and c_rear are for the front and rear of customer queue and s_top tor stack which contains deleted customer details
FILE *car_fp,*customer_fp,*sell_fp; //file for storing car in invantory

//main function
void main()
{
    c_details *temp=NULL,*clr=NULL;
    car *head=NULL; //for storing head of car inventory
   // c_details *c_front=NULL; //for queue of customers
    int a,s,n=0;
    while(1)
    {
        printf("=========================================\n");
        printf("Press 0 to load files\n");
        printf("=========================================\n\n");
        printf("Press 1 to add Car in Inventory\n");
        printf("Press 2 to take Order from Customer's\n");
        printf("Press 3 to Clear Order\n");
        printf("\n=========================================\n\n");
        printf("Press 4 to see last sold car information\n");
        printf("Press 5 to see all sell details\n");
        printf("\n=========================================\n\n");
        printf("Press 6 to view Car Inventory\n");
        printf("Press 7 to view Customer's Queue\n");
        printf("Press 8 to Clear Screen\n");
        printf("Press 9 to EXIT from program\n");
        printf("\n==========================================\n");
        scanf("%d",&a);
        printf("\n==========================================\n");
        switch(a)
            {
                case 0: if(n==0)
                        {
                            //n==0 to load file only for one time
                            head=load_car_list();
                            load_customers_list();
                            load_sell_info();
                            n=1;
                        }
                        printf("\n***Files Loaded Successfully***\n \n");break;
                case 1: head=cars_list();break;
                case 2: customer_list();break;
                case 3: if(c_front==NULL)
                        {
                            printf("\nNo. Customer available  in queue\n \n");
                        }
                        else
                        {
                            s=search(head,c_front->car_name);
                            if(s==0)
                            {
                                printf("Car Found\n");
                                temp=d_customer();
                                s_details(temp); //need to be resolved
                            }
                            else
                            {
                                printf("Car Not found in inventory\n Order Can't be delivered\n\n");
                                temp=d_customer();
                            }
                        }break;
                case 4: last_sell(s_top);break;
                case 5: all_sell();break;
                case 6: print(head);break;
                case 7: c_queprint(c_front);break;
                case 8: system("cls");/*system("clear")*/;break;
                case 9: exit(0);break;
                default: printf("\nInvalid Input\n");
        }
    }

}
int customer_list() //to create queue for customers WORK COMPLETED
{
    customer_fp=fopen("customerlist","r");
    c_details red,*new;
    new=NULL;
    if(customer_fp==NULL)
    {
        new=(c_details*)malloc(sizeof(c_details));
        printf("Enter Name of Car: ");
        fflush(stdin);
        scanf("%[^\n]s",new->car_name);
        printf("Enter Name: ");
        fflush(stdin);
        scanf("%[^\n]s",new->name);
        printf("Enter Phone No.: ");
        fflush(stdin);
        scanf("%[^\n]s",new->mob_no);
        new->next=NULL;
        c_front=new;
        c_rear=new;
    }
    else
    {
        if(c_front==NULL){
        while(fread(&red,sizeof(red),1,customer_fp)>0)
        {
                new=(c_details*)malloc(sizeof(c_details));
                strcpy(new->car_name,red.car_name);
                strcpy(new->name,red.name);
                strcpy(new->mob_no,red.mob_no);
                new->next=NULL;
                if(c_front==NULL)
                {
                    c_front=new;
                    c_rear=new;
                }
                else
                {
                    c_rear->next=new;
                    c_rear=new;
                }

        }
            c_que_flag=1;
        }
        new=(c_details*)malloc(sizeof(c_details));
        printf("Enter Name of Car: ");
        fflush(stdin);
        scanf("%[^\n]s",new->car_name);
        printf("Enter Name: ");
        fflush(stdin);
        scanf("%[^\n]s",new->name);
        printf("Enter Phone No.: ");
        fflush(stdin);
        scanf("%[^\n]s",new->mob_no);
        new->next=NULL;
        if(c_front==NULL)
        {
            c_front=new;
            c_rear=new;
        }
        else
        {
            c_rear->next=new;
            c_rear=new;
        }
    }
    fclose(customer_fp);
    store_customer_list();
    return 0;
}
c_details* d_customer() //to delete customers from queue WORK COMPLETED
{
    c_details *temp=c_front;
    if(c_front==NULL)
    {
        printf("No. Customer Found in the Queue\n");

    }
    else
    {
        c_front=c_front->next;
        temp->next=NULL;
        store_customer_list();
    }
    return temp;
}
void display_customer(c_details *head) // used to display information about sell WORK COMPLETED
{
    c_details *temp=head;
    if(temp==NULL)
    {
        printf("No. Customer is in the queue\n");
    }
    while(temp!=NULL)
    {
        printf("\n====================================\n");
        printf("Car Name: %s\n",temp->car_name);
        printf("Customer's Name: %s\n",temp->name);
        printf("Customer's Mob. No.: %s",temp->mob_no);
        printf("\n====================================\n");
        temp=temp->next;
    }
    free(temp);
}
void last_sell(c_details *s_top) //to display last sold car information WORK COMPLETED
{
    if(s_top==NULL)
    {
        printf("No car Sold Yet\n");
    }
    else
    {
        c_details *temp=s_top;
        printf("\n====================================\n");
        printf("Car Name: %s\n",temp->car_name);
        printf("Customer's Name: %s\n",temp->name);
        printf("Customer's Mob. No.: %s",temp->mob_no);
        printf("\n====================================\n");
    }
}
void all_sell()
{
    c_details *temp=s_top;
    if(s_top==NULL)
    {
        printf("No car Sold Yet\n");
    }
    else
    {
        while(temp!=NULL){
        printf("\n====================================\n");
        printf("Car Name: %s\n",temp->car_name);
        printf("Customer's Name: %s\n",temp->name);
        printf("Customer's Mob. No.: %s\n",temp->mob_no);
        printf("\n====================================\n");
        temp=temp->next;
    }}
}
void s_details(c_details *temp) //for storing sell details WORK COMPLETED
{
    c_details *temp1,*new;
    c_details list;
    sell_fp=fopen("sellinfo","r");
    if(sell_fp==NULL)
    {
        temp->next=s_top;
        s_top=temp;
        s_details_flag=1;
    }
    else
    {
        if(s_top==NULL)
        {
            while(fread(&list,sizeof(list),1,sell_fp)>0)
            {
                    new=(c_details*)malloc(sizeof(c_details));
                    strcpy(new->car_name,list.car_name);
                    strcpy(new->name,list.name);
                    strcpy(new->mob_no,list.mob_no);
                    new->next=s_top;
                    s_top=new;
            }
        }
        temp->next=s_top;
        s_top=temp;
    }
        store_sell_info();
}
void store_sell_info()
{
    c_details *temp=s_top;
    c_details list;
    sell_fp=fopen("sellinfo","w");
    while(temp!=NULL)
    {
        strcpy(list.car_name,temp->car_name);
        strcpy(list.name,temp->name);
        strcpy(list.mob_no,temp->mob_no);
        fwrite(&list,sizeof(list),1,sell_fp);
        temp=temp->next;
    }
    printf("Sell information Stored Successfully\n");
    fclose(sell_fp);
}
void create(car* head)
{
    car list,*temp=head;
    car_fp=fopen("node","w");
    while(temp!=NULL)
    {
        strcpy(list.name,temp->name);
        list.no=temp->no;
        fwrite(&list,sizeof(list),1,car_fp);
        temp=temp->next;
    }
    fclose(car_fp);
}
void store_customer_list()
{
    c_details *temp=c_front,list;
    customer_fp=fopen("customerlist","w");
    while(temp!=NULL)
    {
        strcpy(list.car_name,temp->car_name);
        strcpy(list.name,temp->name);
        strcpy(list.mob_no,temp->mob_no);
        fwrite(&list,sizeof(list),1,customer_fp);
        temp=temp->next;
    }
    printf("Customer's Queue Updated Successfully\n");
    fclose(customer_fp);

}
car* cars_list()
{
    car_fp=fopen("node","r");
    car red;
    car *head=NULL,*temp=NULL,*new=NULL;
    if(car_fp==NULL)
    {
        new=(car*)malloc(sizeof(car));
        printf("Enter Car Name: ");
        fflush(stdin);
        scanf("%[^\n]s",new->name);
        fflush(stdin);
        printf("Enter Quantity Avilabe: ");
        fflush(stdin);
        scanf("%d",&new->no);
        if(new->no<10)
        {
            printf("No. of Quantity Can't be less than10\n Please Quantity again\n");
            printf("Enter Quantity Avilabe: ");
            scanf("%d",&new->no);
        }
        new->next=NULL;
        head=new;
    }
    else
    {
        while(fread(&red,sizeof(red),1,car_fp)>0)
        {
                new=(car*)malloc(sizeof(car));
                strcpy(new->name,red.name);
                new->no=red.no;
                new->next=NULL;
                if(head==NULL)
                {
                    head=new;
                }
                else
                {
                    temp=head;
                    while(temp->next!=NULL)
                    {
                        temp=temp->next;
                    }
                    temp->next=new;
                }

        }
        new=(car*)malloc(sizeof(car));
        printf("Enter Car Name: ");
        fflush(stdin);
        scanf("%[^\n]s",new->name); //
        fflush(stdin);
        printf("Enter Quantity Avilabe: ");
        fflush(stdin);
        scanf("%d",&new->no);
        if(new->no<10)
        {
            printf("\nNo. of Quantity Can't be less than10\nPlease Quantity again\n\n");
            printf("Enter Quantity Avilabe: ");
            scanf("%d",&new->no);
        }
        new->next=NULL;
        temp=head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=new;
        temp=head;
    }
    fclose(car_fp);
    create(head);
    printf("Car Added Successfully\n");
    return (head);
}
void print(car* head)
{
    car *temp=head;
    printf("*********************************\n");
    printf("Name\t\t\tQuantity\n");
    printf("*********************************\n");
    while(temp!=NULL)
    {
        printf("%s",temp->name);
        printf("\t\t%d\n",temp->no);
        temp=temp->next;
    }
}
void load_customers_list()
{
    customer_fp=fopen("customerlist","r");
    c_details red,*new=NULL;
    if(c_front==NULL)
    {
        if(customer_fp==NULL)
        {
            printf("No. Customer is in Queue\n");
        }
        else
        {
            while(fread(&red,sizeof(red),1,customer_fp)>0)
            {
                new=(c_details*)malloc(sizeof(c_details));
                strcpy(new->car_name,red.car_name);
                strcpy(new->name,red.name);
                strcpy(new->mob_no,red.mob_no);
                new->next=NULL;
                if(c_front==NULL)
                {
                    c_front=new;
                    c_rear=new;
                }
                else
                {
                    c_rear->next=new;
                    c_rear=new;
                }

            }
        }
    }
    fclose(customer_fp);
}
car* load_car_list()
{
    car_fp=fopen("node","r");
    car red;
    car *temp=NULL,*new=NULL;
    if(car_fp==NULL)
    {
      printf("No. Car is Availabe in Invantory\n");
      return NULL;
    }
    else
    {
        while(fread(&red,sizeof(red),1,car_fp)>0)
        {
                new=(car*)malloc(sizeof(car));
                strcpy(new->name,red.name);
                new->no=red.no;
                new->next=NULL;
                if(head==NULL)
                {
                    head=new;
                }
                else
                {
                    temp=head;
                    while(temp->next!=NULL)
                    {
                        temp=temp->next;
                    }
                    temp->next=new;
                }
        }
        return (head);
    }
    fclose(car_fp);
}
int search(car *head,char car_name_d[])
{
    int j=0,k=1;
    car *temp=head;
    while(temp!=NULL)
    {
        if(strcmp(temp->name,car_name_d)==0)
        {
            j=0;
            if(j==0)
            {
                temp->no=temp->no-1;
                if(temp->no>0 && temp->no>=10)
                {
                    k=0;
                }
                else if((temp->no)<10)
                {
                    k=0;
                    printf("The No. Of Car Named %s have become less than 10\nPlease Report to Authority\n",temp->name);
                }
            }
            break;
        }
        else
        {
            j=1;
        }
        temp=temp->next;
    }
    create(head);
    return k;
}
c_details* peek_customer()
{
    if(c_front==NULL)
    {
        printf("All Orders have been cleared\n");
        return NULL;
    }
    else
    {
        c_details *temp=c_front;
        return temp;
    }
}
void c_queprint(c_details *front)
{
    c_details *temp;
    temp=front;
    if(temp==NULL)
    {
        printf("No Customer is avilable in the Queue\n");
    }
    else
    {
        while(temp!=NULL)
        {
            printf("\n====================================\n");
            printf("Car Name: %s\n",temp->car_name);
            printf("Customer's Name: %s\n",temp->name);
            printf("Customer's Mob. No.: %s\n",temp->mob_no);
            printf("\n====================================\n");
            temp=temp->next;
        }
    }
}
void load_sell_info()
{
    c_details *new;
    c_details list;
    sell_fp=fopen("sellinfo","r");
    if(s_top==NULL)
    {
        while(fread(&list,sizeof(list),1,sell_fp)>0)
        {
            new=(c_details*)malloc(sizeof(c_details));
            strcpy(new->car_name,list.car_name);
            strcpy(new->name,list.name);
            strcpy(new->mob_no,list.mob_no);
            new->next=s_top;
            s_top=new;
        }
    }
    fclose(sell_fp);
}
