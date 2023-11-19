#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct emp{
		int eid;
		char name[50];
		char gender;
		char dept[50];
		
		struct answer{
				char a1[4];
				char a2[4];
				char a3[4];
				char a4[4];
				char a5[4];
		}ans;
};


void employee(int);
void bod();

int main(){
	char answ[4];
	
	printf("\n\n\n");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############            Welcome to SMART DOKO!!!              ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\t----------------------------------------------------------------------------");
	printf("\nThis voting system allows employees to put forward their opinions across the decision makers of the company");
	

	Doagain:
	printf("\n\nAre you an employee or not? If yes, type 'Yes' else type 'No'.\n");
	gets(answ);
	
	if((strcmp(answ,"yes") == 0) || (strcmp(answ,"Yes") == 0)){
		printf("\nProceeding towards the respective function, employee.\n");
			printf("\n\n\n\n\n");
    printf("\n\t\t\t      *-----------------------------------------------*\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                     ARE                   =");
    printf("\n\t\t\t        =                     YOU                   =");
    printf("\n\t\t\t        =                    READY                  =");
    printf("\n\t\t\t        =                     TO                    =");
    printf("\n\t\t\t        =                    VOTE??                 =");
    printf("\n\t\t\t        =*******************************************=");
		employee(5);
	}
	else if((strcmp(answ,"no") == 0) || (strcmp(answ,"No") == 0)){
		printf("\nProceeding towards the respective function, bod.\n");
		printf("\n\t\t\t  *-----------------------------------------------*\n");
    printf("\n\t\t\t        =*******************************************=");
    printf("\n\t\t\t        =                     THE                   =");
    printf("\n\t\t\t        =                   RESULTS                 =");
    printf("\n\t\t\t        =                     ARE                   =");
    printf("\n\t\t\t        =                     OUT                   =");
    printf("\n\t\t\t        =                   ALREADY                 =");
    printf("\n\t\t\t        =*******************************************=");
		bod();
	}
	else{
		printf("Invalid Option. Choose yes or no only");
		goto Doagain;
	}
return 0;
}

void employee(int emp_num){
	FILE *f,*g;
	
	char a1,a2,a3,a4,a5;
	struct emp e[emp_num],e_read[5]; // changes
	struct answer ans;
	
	f=fopen("Employeerecord.txt","w+");
	g=fopen("Answers.txt","w");
	
	int i,j,w,q,flag=0;
	char a;
	int dup_id[100];
	//int emp_num = 3; // number of employees
	
	printf("\nWe would like you to have your role in the decision making of the company by making your choices\n");
	printf("\nOnly %d employee representatives can vote.Thank you for your cooperation.\n\n",emp_num);
	
	for(i=0;i<emp_num;i++){
		
		printf("Enter eid:\n");
		scanf("%d%*c",&e[i].eid);
		
		printf("Enter name:\n");
		scanf("%[^\n]%*c",e[i].name);
		
		printf("Enter gender:\n");
		scanf("%c%*c",&e[i].gender);
		
		printf("Enter department:\n");
		scanf("%[^\n]",e[i].dept);
		
		printf("\n\n");
	
		fprintf(f,"%d\n%s\n%c\n%s\n\n",e[i].eid,e[i].name,e[i].gender,e[i].dept);
		
		//MCQs
		printf("Please answer the following with 'y' if you agree with the statement or 'n' if you don't:\n\n");
		
		printf("Our company, Smart doko, should work more on developing public relations by sending free products to celebrities and other popular individual on the internet.\n");
		scanf("%s%*c",e[i].ans.a1);
		
		printf("Smart doko should enhance the facilities of allowances.\n");
		scanf("%s%*c",e[i].ans.a2);
		
		printf("A 5 day working system has to be introduced with 8 working hours on work days.\n");
		scanf("%s%*c",e[i].ans.a3);
		
		printf("Smart doko should merge with the company, Daraz in the near future.\n");
		scanf("%s%*c",e[i].ans.a4);
		
		printf("Smart doko should bring in young influential speakers for the annual event.\n");
		scanf("%s%*c",e[i].ans.a5);
		
		printf("\n\n");
	}
	
	//validation part remaining
	int m = 0; // changes
	int dup_count = 0;
	
	rewind(f);

	while(m<emp_num){ // changes in the condition
		fscanf(f,"%d\n%s\n%c\n%s\n\n",&e_read[m].eid,&e_read[m].name,&e_read[m].gender,&e_read[m].dept); //changes
		m++;
	}

	// changes -------------------------------------
	// sorting in ascending order
	for(w=0;w<emp_num;w++){
		for(j=w+1;j<emp_num;j++){
			if(e[w].eid>e[j].eid){
				q=e[w].eid;
				e[w].eid=e[j].eid;
				e[j].eid=q;	
			}
		}
	}
	
	//checking the equality of adjacent elements of ordered id
	for(j=0; j<(emp_num-1); j++){
		if(e[j].eid == e[j+1].eid){
			 flag=1;
			 dup_id[dup_count]=e[j].eid;
			 dup_count++;
		}
	}
	FILE *c;
	c = fopen("valid_count.txt","w");
	fprintf(c,"%d",(5-(dup_count+1))); // 5 to be changed according to the number of employees
	
	fclose(c);
	
	// changes ------------------------------------------
	
	if(flag==1){
		printf("Found Multiple Entries for an ID"); // message changed
		
		FILE *h;
		
		h = fopen("Updatedlist.txt","w");
		
		for(i=0;i<emp_num;i++){
			int detect_flag = 0; // changes
			
			for(j=0;j<dup_count;j++){
				if(dup_id[j]==e_read[i].eid){
					detect_flag = 1; //changes
					break; // changes
				}
			}
			
			if(detect_flag == 0){ //changes
				fprintf(h,"%d\n%s\n%c\n%s\n\n",e_read[i].eid,e_read[i].name,e_read[i].gender,e_read[i].dept);
				fprintf(g,"%s\n%s\n%s\n%s\n%s\n\n",e[i].ans.a1,e[i].ans.a2,e[i].ans.a3,e[i].ans.a4,e[i].ans.a5);
			}
		}
		
		fclose(h);
	}
	else{
		for(i=0;i<emp_num;i++){
			fprintf(g,"%s\n%s\n%s\n%s\n%s\n\n",e[i].ans.a1,e[i].ans.a2,e[i].ans.a3,e[i].ans.a4,e[i].ans.a5);
		}
	}
	
	fclose(f);
	fclose(g);
	printf("\n\nThank you for the data entry!!\n");
	
	// for printing the retrieved structured data from Employeerecord -------
	
	/*int y = 0;
	while(y<emp_num){
		printf("\nid= %d",e_read[y].eid);
		printf("\ngender= %c",e_read[y].gender);
		printf("\nname = %s",e_read[y].name);
		printf("\ndept = %s",e_read[y].dept);
		y++;
	}*/
	
	// ------------------------------------------------------(means this block is evitable)
}

void bod(){
	int e_num;
	FILE *g=fopen("Answers.txt","r");
	
	FILE *c;
	c = fopen("valid_count.txt","r");
	
	fscanf(c,"%d",&e_num);
	
	fclose(c);
	
	int c1=0,c2=0,c3=0,c4=0,c5=0;
	struct emp e[e_num];
	struct answer ans;
	
	
	int i = 0;
	
	while(i<e_num){
	
		fscanf(g,"%s\n%s\n%s\n%s\n%s\n\n",&e[i].ans.a1,&e[i].ans.a2,&e[i].ans.a3,&e[i].ans.a4,&e[i].ans.a5);
		
		if(strcmp(e[i].ans.a1,"Y")==0 ||strcmp(e[i].ans.a1,"y")==0){
			c1++;
		}
		
		if(strcmp(e[i].ans.a2,"Y")==0 ||strcmp(e[i].ans.a2,"y")==0){
			c2++;
		}
		
		if(strcmp(e[i].ans.a3,"Y")==0 ||strcmp(e[i].ans.a3,"y")==0){
			c3++;
		}
		
		if(strcmp(e[i].ans.a4,"Y")==0 ||strcmp(e[i].ans.a4,"y")==0){
			c4++;
		}
		
		if(strcmp(e[i].ans.a5,"Y")==0 ||strcmp(e[i].ans.a5,"y")==0){
			c5++;
		}
		
		i++;
	}
	fclose(g);
	printf("\n\n\n\n According to the data survey by %d employees, the following insights have been taken:\n\n",e_num);
	
	
		printf("\n\nOur company, Smart doko, should work more on Corporate Social responsibility.\n The results of voting for this statement is %d out of %d.",c1,e_num);
		printf("\n\nSmart doko should enhance the facilities of allowances.\n The results of voting for this statement is %d out of %d.",c2,e_num);
		printf("\n\nA 5 day working system has to be introduced with 8 working hours on work days.\n The results of voting for this statement is %d out of %d.",c3,e_num);
		printf("\n\nSmart doko should merge with the company, Daraz in the near future.\n The results of voting for this statement is %d out of %d.",c4,e_num);
		printf("\n\nSmart doko should bring in young influential speakers for the annual event\n The results of voting for this statement is %d out of %d.",c5,e_num);
	
	
}


