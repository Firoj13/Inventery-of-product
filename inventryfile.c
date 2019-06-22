#include<stdio.h>
#include<string.h>

FILE *f;

int toString(char a[]) {
  int c, sign, offset, n;
  if (a[0] == '-') {  // Handle negative integers
    sign = -1;
  }
  if (sign == -1) {  // Set starting position to convert
    offset = 1;
  }
  else {
    offset = 0;
  }
  n = 0;
  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }
  if (sign == -1) {
    n = -n;
  }
  return n;
}

struct node{
	int id;
	char productname[50];
	int quantity;

	int cp;
	int sp;
//	FILE *f;
	struct node *link;
	
};
struct node *start=NULL;

struct node* createnode(){
	struct node *temp;
	temp=malloc(sizeof (struct node));
	return temp;
}
void insertnode(int id,char name[50],int quan,int cost,int sell){
	int i=0;
	struct node *temp,*t;
	temp=createnode();
	f = fopen("product.txt", "a+");
	
	temp->id=id;
	temp->quantity=quan;
	temp->cp=cost;
	temp->sp=sell;
	
	while(name[i]!=NULL) {
		temp->productname[i]=name[i];
		i++;
	}

	temp->link=NULL;
	if(start==NULL){
		start=temp;
	}
	else{
		t=start;
		while(t->link!=NULL){
			t=t->link;
		}
		t->link=temp;
	}
}
void saveToFile(int id,char name[50],int quan,int cost,int sell) {
	int i=0;
	fprintf(f, "%d|", id);
	while(name[i]!=NULL) {
		fprintf(f, "%c", name[i]);
		i++;
	}
	fprintf(f, "|");
	fprintf(f, "%d|", quan);
	fprintf(f, "%d|", cost);
	fprintf(f, "%d|", sell);
	fclose(f);
}
void deletenode(int id){
	struct node *r,*l=NULL;
	int f=0;
		r=start;
	if(r==NULL){
		printf("You don't have product to delete!");
	}
	else{
		while(r!=NULL){
			if(r->id==id){
				f=1;
				break;
			}
			l=r;
			r=r->link;
			}
			if(f==1){
				if(l!=NULL){
					l->link=r->link;
				}
				else{
					start=r->link;
				}
				free(r);
				printf("product with #%d Deleted!",id);
			}
			else{
				printf("\n Please enter valid Id!");
		}
	}
}
void viewlist(){
	int Sno=0;
	FILE *f;
	struct node *c;
	c=start;
	f=fopen("inventry.txt","a+");
	if(start==NULL){
		printf("Empty");
	}
	
	else{
		printf("Sno.\t");
		printf("product name\t");
		printf("Id\t");
		printf("Quantity\t");
		printf("cost$\t");
		printf("sell$\t\n");
		printf("--------------------------------------------------------------------------\n");	
		
		while(c!=NULL){
			Sno++;
			printf("%d\t",Sno);
			printf("%s\t\t",c->productname);
			printf("%d\t",c->id);
			printf("%d\t\t",c->quantity);
			printf("%d\t",c->cp);
			printf("%d\t\n",c->sp);
			printf("--------------------------------------------------------------------------\n");	
			c=c->link;
		fclose(f);
		}
	}
}

void stock(){
	struct node *c;
	int Sno=0;
	FILE *f;
	c=start;
	f=fopen("inventry.txt","a+");
	if(start==NULL){
		printf("Empty");
	}
	else{
		printf("**********************\n");
		printf("product managment\n");
		printf("**********************\n");
		printf("Sno.\t");
		printf("product name\t");
		printf("Id\t");
		printf("quantity\n");
		while(c!=NULL){
			Sno++;
			printf("%d\t",Sno);
			printf("%s \t\t",c->productname);
			printf("%d\t\t",c->id);
			printf("%d \t\n",c->quantity);
		printf("--------------------------------------------\n");
			c=c->link;
		fclose(f);
		}
	}
}

void update(int id,int item,int price){
	int f=0;
	struct node *r;
	r=start;
	if(start==NULL){
		printf("Empty");
	}
	while(r!=NULL){
		if(r->id==id){
			f=1;
			break;
		}
		r=r->link;
	}
	if(f==1){
		r->quantity=r->quantity+item;
		printf("\nyour current quantity is %d:",r->quantity);
		r->sp=price;
		printf("\n price update:%d",r->sp);	
	}
}
void buy(int id,int item){
	struct node *r;
	int f=0;
	r=start;
	if(start==NULL){
		printf("Empty");
	}
	while(r!=NULL){
		if(r->id==id){
			f=1;
			break;
		}
		r=r->link;
	}
	if(f==1){
		if(r->quantity < item){
			printf("Out of stock");
		}
		else {
			r->quantity-=item;
			printf("sell is done");
		}
	}
	else  {
		printf("Unknown Product Id!");
	}
}
void main(){
	char t;
	int id;
	int item;
	int price;
	char productname[50];
	int quantity;
	int cp;
	int sp;
	int x;
	
	char old[1000], oName[50], temp[50];
	int i=0, oId, oQty, oCost, oSell, c=0, rec=1, l=0;
		
	f = fopen("product.txt", "r");
	fgets(old, 1000, f);
	while(old[i]!=NULL) {
		if(old[i]!='|') {
			temp[c] = old[i];
			c++;
		}
		else {
			c=0;
			if(rec==1) {
				oId = toString(temp);
				rec++;
			}
			else if(rec==2) {
				while(temp[l]!=NULL) {
					oName[l] = temp[l];					
					l++;	
				}
				rec++;
			}
			else if(rec==3) {
				oQty = toString(temp);
				rec++;
			}
			else if(rec==4) {
				oCost = toString(temp);
				rec++;
			}
			else if(rec==5) {
				oSell = toString(temp);
				rec++;
			}
			l=0;
			while(temp[l]!=NULL) {
				temp[l] = NULL;
				l++;
			}
			l=0;
		}
		i++;
		if(rec > 5) {
			insertnode(oId,oName,oQty,oCost,oSell);
			l=0;
			while(oName[l]!=NULL) {
				oName[l] = NULL;
				l++;
			}
			l=0;
			rec = 1;
			c=0;
		}
	}
	
	
	while(x!=7){
	printf("\n1.add information\n");

	printf("2.delete\n");
	
	printf("3.view\n");
	
	printf("4.Stock Managment\n");
	printf("5.update\n");
	printf("6.Buy\n");
	printf("7.Exit\n");
	printf("---------------------------\n");

	printf("Chose option:");
	scanf("%d",&x);
	
	switch (x){
		case 1:
				printf("1.product id:");
				scanf("%d",&id);
				scanf("%c",&t);
				printf("2.Enter product name:");
				gets(productname);
				printf("4.Enter product quantity:");
				scanf("%d",&quantity);
				printf("5.Enter cost price:");
				scanf("%d",&cp);
				printf("6.Enter selling price:");
				scanf("%d",&sp);
				insertnode(id,productname,quantity,cp,sp);
				saveToFile(id,productname,quantity,cp,sp);
				break;			
		case 2:
			printf("Enter delete Id: ");
			scanf("%d",&id);
			deletenode(id);
			break;
		case 3:
			viewlist();
			break;
		case 4:
			stock();
			break;
		case 5:
			printf("Enter Id:");
			scanf("%d",&id);
			printf("Enter item:");
			scanf("%d",&item);
			printf("Enter price");
			scanf("%d",&price);
			update(id,item,price);
			break;
		case 6:
			printf("Enter Id:");
			scanf("%d",&id);
			printf("Enter item:");
			scanf("%d",&item);
			buy(id,item);
			break;
		case 7:
			system("Exit");
			break;
		default:
			printf("Invalid option");
		}
	}
}
