/*��¼����*/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int informationIn();//�ļ���Ϣ���뺯�� ��ÿ������������txt�д洢����������ṹ������� 
int autoNumberCaculater(char *strNumber);//��Ӳ�Ʒ�Զ���Ŵ����� 
int commendRegister();//ע��ʵ�ֺ��� 
int commendLogin();//��¼��֤���� 
double salesSum(int choosingNumber6,char *targetNumber);//�����ܶ���㺯��
int add(int choosingNumber2);//��¼������µĲ�Ʒ���Ƕ��������� 
int lookingFor(int choosingNumber2);//Ŀ�������ܶ��ѯ���� 
void bubbleSort(struct information4 sumSort[]);//ð������ 
int sort(int choosingNumber2);//�����ܶ������� 
void afterLogin();//��¼�������������ƺ��� 

/*��Ϣ��������*/
//����Ա��Ϣ����
struct information1{
	char number[10];
	char name[31];
	char sex[7];
	char schooling[31];
	char password[18];
}salesPerson[20],login;

//��Ʒ��Ϣ���� 
struct information2{
	char number[10];//������ȡ���Ŀ�����Ľڵ� 
	char name[31];
	double price;
	int stock;
}product[30];

//������Ϣ����
struct information3{
	char number[10];// ��ʽ:O001-O00X
	char salesPersonNumber[10];
	char productNumber[10]; 
	char salesDay[11];// ��ʽ:year-month-day xxxx-xx-xx ע�����Ʒ�Χ
	int salesAmount;
}order[100];

//����Ա�����۶��
struct information4{
	char number[10];
	char name[31];
	double sumSales;
}sumSort[30];

int main()
{	
	//���ṹ�������Ϣ����	
	if(informationIn()!=1){
		printf("		�ļ���Ϣδ���������룡�����ļ�·����\n");
		return 0; 
	}
	
	//ѡ��������� 
	int choosingNumber1; 
	
	//��¼������ʾ��� ,ȫ��������ھ������ۿ��ǣ�ÿ��ǰ���������ַ�\t 
	printf("		------��ӭ���� IG ����ϵͳ------\n");
	printf("		--(�ޣޡ�)--(�ޣޡ�)--(�ޣޡ�)--\n");
	
	//������Χ���� 
	while(1){
		printf("		0)�ڲ�����Ա��¼\n");
		printf("		1)������Աע��\n");
		printf("		2)�˳�ϵͳ\n\n");
		printf("		�������Ӧ��������Խ�����һ��:");
		
		scanf("%d",&choosingNumber1); 
		switch(choosingNumber1){
			//��¼����
			case 0:	
				if(commendLogin()==1){
					afterLogin(); 
				}else{
					printf("		�û��������벻��ȷ������\n\n"); 
				}	
				break;
			//ע�����
			case 1:
				if(commendRegister()==1){
					printf("		ע��ɹ���! ^v^\n\n");
				}else{
					printf("		ע��ʧ����! =_=\n");
					printf("		ʧ��ԭ���ڲ��û������Ѵ�����!\n\n");
				}
				break;
			//����ѡ�� �˳����� 
			case 2:
				printf("		��л����ʹ��!~~\n");
				return 0;
			default:
				printf("		��Ч��������ţ�\n");
				break;
		}
	} 
}

//�ļ���Ϣ���뺯�� 
//ÿ������������txt�д洢����������ṹ������� 
int informationIn(){
	//�����ļ�ָ�� 
	FILE *fp;
	//��������Ա��Ϣ 
	if((fp=fopen("Record of salesperson information.txt","r"))==NULL){
		printf("		����δ���������ļ� =_=!\n");
		exit(0);
	}
	int i=0;
	while (!feof(fp)){
		fscanf(fp,"%s%s%s%s%s",salesPerson[i].number,salesPerson[i].name,salesPerson[i].sex,salesPerson[i].schooling,salesPerson[i].password);
		i++;
	}
	if(fclose(fp)){
		printf("		����δ�������ر��ļ� =_=!\n");
		exit(0);
	}
	//�����Ʒ��Ϣ
	if((fp=fopen("Record of products` information.txt","r"))==NULL){
		printf("		����δ���������ļ� =_=!\n");
		exit(0);
	}
	i=0;
	while (!feof(fp)){
		fscanf(fp,"%s%s%lf%d",product[i].number,product[i].name,&product[i].price,&product[i].stock);
		i++;
	}
	if(fclose(fp)){
		printf("		����δ�������ر��ļ� =_=!\n");
		exit(0);
	}
	//���붩����Ϣ
	 if((fp=fopen("Record of order information.txt","r"))==NULL){
		printf("		����δ���������ļ� =_=!\n");
		exit(0);
	}
	i=0;
	while (!feof(fp)){
		fscanf(fp,"%s%s%s%s%d",order[i].number,order[i].salesPersonNumber,order[i].productNumber,order[i].salesDay,&order[i].salesAmount);
		i++;
	}
	if(fclose(fp)){
		printf("		����δ�������ر��ļ� =_=!\n");
		exit(0);
	}
	return 1;
} 

//�������Ϣ�Զ���Ŵ����� 
int autoNumberCaculater(char *strNumber){
	//�����ļ�ָ��
	FILE *fp; 
	//�Զ���Ŵ��� 
	if(strcmp(strNumber,"salesPerson")==0){
		if((fp=fopen("Record of salesPerson information.txt","r"))==NULL){
			printf("		����δ���������ļ� =_=!\n");
			exit(0);
		} 
	}
	else if(strcmp(strNumber,"product")==0){
		if((fp=fopen("Record of products` information.txt","r"))==NULL){
			printf("		����δ���������ļ� =_=!\n");
			exit(0);
		}  
	}
	else if(strcmp(strNumber,"order")==0){
		if((fp=fopen("Record of order information.txt","r"))==NULL){
			printf("		����δ���������ļ� =_=!\n");
			exit(0);
		} 
	}
	
	int index;//����ṹ�庯���±� 
	char menberNumber[10];//���ܲ����б�Ŵ��� 
	strcpy(menberNumber,"null");
	
	char a[31],b[31],c[31],d[31];//���������ַ��� 
	double e;//��������˫���ȸ����ͱ��� 
	int f;//�����������ͱ��� 

	//�����ļ������һ����� 
		if(strcmp(strNumber,"salesPerson")==0){
			while(!feof(fp)){
				fscanf(fp,"%s %s %s %s %s",menberNumber,a,b,c,d);
			}
		}
		else if(strcmp(strNumber,"product")==0){
			while(!feof(fp)){
				fscanf(fp,"%s %s %f %d",menberNumber,a,&e,&f);
			} 
		}
		else if(strcmp(strNumber,"order")==0){
			while(!feof(fp)){
				fscanf(fp,"%s %s %s %s %d",menberNumber,a,b,c,&f);
			} 
		}
	
	int autoNumber=0;//������ͻ����� 
	
	//��¼�������κ���Ϣ��¼ʱ 
	if(strcmp(menberNumber,"null")==0){
		if(strcmp(strNumber,"salesPeron")==0){
			strcpy(salesPerson[0].number,"E001");//��ע���б�Ϊ�գ����û����ΪE001 
		}
		else if(strcmp(strNumber,"product")==0){
			strcpy(product[0].number,"P001");//��ע���б�Ϊ�գ��˲�Ʒ���ΪP001 
		}
		else if(strcmp(strNumber,"order")==0){
			strcpy(order[0].number,"O001");//��ע���б�Ϊ�գ��˶������ΪO001 
		}
		return 0;
	}else{
		int digit;//��λȡ����� 
		char *p=menberNumber+1;
		 
		//�ַ��ͱ�����ͻ�
		for(;*p!='\0';p++){
			digit=*p-'0';
			autoNumber=autoNumber*10+digit;
		}
		autoNumber++;//ĩλע��Ա��ż�һλ���ڴ������û���� 
		//�ж�ע�����Ƿ�Խ�� 
		if(strcmp(strNumber,"salesPeron")==0){
			if(autoNumber>20)return 2;
		}
		if(strcmp(strNumber,"product")==0){
			if(autoNumber>30)return 2;
		}
		
		index=autoNumber-1;
		int i=0;
		
		//���ͱ���ַ��� 
		for(p=menberNumber+3;i<3;p--){
			digit=autoNumber%10;
			*p=digit+'0';
			autoNumber/=10;
			i++;
		} 
	}
	if(fclose(fp)){
		printf("		����δ�������ر��ļ� =_=!\n");
		exit(0);
	}
	//����ű�������Ӧ�ṹ������� 
	if(strcmp(strNumber,"salesPerson")==0){
		strcpy(salesPerson[index].number,menberNumber);
	}
	if(strcmp(strNumber,"product")==0){
		strcpy(product[index].number,menberNumber);
	}
	if(strcmp(strNumber,"order")==0){
		strcpy(order[index].number,menberNumber);
	}
	return index;
}

//ע��ʵ�ֺ��� 
int commendRegister(){
	printf("\n		----------������Աע�����-------------\n") ; 
	 
	//�����ļ�ָ��
	FILE *fp;  
	//�Զ����,����������¼�ı����±� 
	char strNumber[12];
	strcpy(strNumber,"salesPerson");
	int menberIndex=autoNumberCaculater(strNumber);
	//���û�д������Ա��Ϣ���� 
	if((fp=fopen("Record of salesPerson information.txt","a"))==NULL){
		printf("	 	����δ���������ļ�  =_=!\n");
		exit(0);
	}

	//���û����� 
	printf("		��ʾ�������û�����������30���ַ�֮�ڣ�����ռ2���ַ���\n");    
	printf("		�������µ�����Ա�û�����");
	scanf("%s",salesPerson[menberIndex].name);
	printf("\n"); 
	
	//���û��Ա�
	int sexnumber;
	printf("		0)����\n");
	printf("		1)Ů��\n\n");
	printf("		��������Ӧ�����ѡ�������Ա�:");
	
	scanf("%d",&sexnumber); 
	switch(sexnumber){
		case 0:strcpy(salesPerson[menberIndex].sex,"����");break;
		case 1:strcpy(salesPerson[menberIndex].sex,"Ů��");break;
	}
	printf("\n"); 
	
	//���û��ܽ����̶�
	int schoolingNumber;
	printf("		0)�о���ѧ��������\n");
	printf("		1)��ѧ���ƻ�ר��ѧ��\n");
	printf("		2)����ѧ��������\n\n");
	printf("		��������Ӧ�����ѡ������ѧ��:");
		
	scanf("%d",&schoolingNumber);
	switch(schoolingNumber){
		case 0:strcpy(salesPerson[menberIndex].schooling,"�о���ѧ��������");break;
		case 1:strcpy(salesPerson[menberIndex].schooling,"��ѧ���ƻ�ר��ѧ��");break;
		case 2:strcpy(salesPerson[menberIndex].schooling,"����ѧ��������");break;
	}
	printf("\n");
	
	//���û�����
	printf("		��ʾ���������볤������17���ַ��ڣ�����ռ2���ַ���\n");
	printf("		�������������� *_*:");
	scanf("%s",salesPerson[menberIndex].password);
	//�����������뱣֤��ȷ
	char str[18];
	while (1){
		printf("		��ȷ����������:");
		scanf("%s",str);
		if(strcmp(str,salesPerson[menberIndex].password)!=0){
			printf("		����������������벻һ�£�����\n");
		}
		else break;
	}
	printf("\n");
	//����Ϣ¼���ڴ洢�ļ��� 
	fprintf(fp,"%s %s %s %s %s\n",salesPerson[menberIndex].number,salesPerson[menberIndex].name,salesPerson[menberIndex].sex,salesPerson[menberIndex].schooling,salesPerson[menberIndex].password);
	if(fclose(fp)){
		printf("		����δ�������ر��ļ� =_=!\n");
		exit(0);
	}
	return 1;
}
	
//��¼��֤���� 
int commendLogin(){
	printf("\n		----------�ڲ�����Ա��¼����----------\n");
	
	//�����ļ�ָ��
	FILE *fp;  
	//�����û��������� 
	printf("		�����������û�����"); 
	scanf("%s",login.name);
	printf("		��������������:");
	scanf("%s",login.password);
	//��֤�û������������ȷ�� 
	if((fp=fopen("Record of salesPerson information.txt","r"))==NULL){
		printf("		����δ���������ļ� =_=!\n");
		exit(0);
	}

	char menberName[31];//�洢һ������Ա�û��� 
	char menberPassword[18];//�洢��Ӧ������Ա���� 
	char a[31],b[31],c[31];//�洢�����ַ��� 
	
	while(!feof(fp)){
		fscanf(fp,"%s%s%s%s%s",a,menberName,b,c,menberPassword);
		if(strcmp(menberName,login.name)==0){
			if(strcmp(menberPassword,login.password)==0){
				return 1;
			}
		}
	}
	return 2; 
}

//�����ܶ���㺯�� 
//����choosingNumber2 0Ϊ������Ա��� 1Ϊ�Բ�Ʒ��� 
//����targetNumber ΪĿ���� 
double salesSum(int choosingNumber2,char *targetNumber){
	FILE *fp;
	//ѭ�����Ʊ��� 
	int i,j;
	//���۶�ͳ�Ʊ��� 
	double sum=0;
	//choosingNumber6==0ʱΪ��ѯ��������Ա�����۶��ܺ� 
	if(choosingNumber2==0){
		if((fp=fopen("Record of order information.txt","r"))==NULL){
			printf("		δ���������ļ�\n"); 
		}
		
		char a[31],b[31],c[31],d[31];
		int e;
		
		int n=0;
		//ȷ��������¼���� 
		while(!feof(fp)){
			fscanf(fp,"%s%s%s%s%d",a,b,c,d,&e);
			n++;
		}
		for(i=0;i<n;i++){
			//Ѱ�Ҷ����б���Ŀ������Աִ�еĶ��� 
			if(strcmp(targetNumber,order[i].salesPersonNumber)==0){
				for(j=0;;j++){
					//�ҵ�����ִ�е���Ʒ��Ϣ�������ܺ� 
					if(strcmp(product[j].number,order[i].productNumber)==0){
						sum+=product[j].price*order[i].salesAmount;
						break;
					}
				}
			}
		}
		return sum; 
	//choosingNumber6==1ʱΪ��ѯ������Ʒ�����۶��ܺ� 
	}else if(choosingNumber2==1){
		if((fp=fopen("Record of order information.txt","r"))==NULL){
			printf("		δ���������ļ�\n"); 
		}
		
		char a[31],b[31],c[31],d[31];
		int e;
		
		int n=0;
		//ȷ��������¼���� 
		while(!feof(fp)){ 
			fscanf(fp,"%s%s%s%s%d",a,b,c,d,&e);
			n++;
		}
		for(i=0;i<n;i++){
			//Ѱ�Ҷ����б���Ŀ������Աִ�еĶ��� 
			if(strcmp(targetNumber,order[i].productNumber)==0){
				for(j=0;;j++){
					//�ҵ�����ִ�е���Ʒ��Ϣ�������ܺ� 
					if(strcmp(product[j].number,order[i].productNumber)==0){
						sum+=product[j].price*order[i].salesAmount;
						break;
					}
				}
			}
		}
		return sum; 
	}
}	

//��¼������µĲ�Ʒ���Ƕ��������� 
int add(int choosingNumber3){
	FILE *fp;
	//����µĲ�Ʒ��Ϣ 
	if(choosingNumber3==0){
		//�Զ����,����������¼�ı����±� 
		char strNumber[12];
		strcpy(strNumber,"product");
		int productIndex=autoNumberCaculater(strNumber);
		
		//�²�Ʒд���Ʒ��Ϣ���� 
		if((fp=fopen("Record of products` information.txt","a"))==NULL){
			printf("	 	����δ���������ļ�  =_=!\n");
			exit(0);
		}
		//�����²�Ʒ���� 
		printf("		��ʾ����Ʒ����������30���ַ�֮�ڣ�����ռ2���ַ���\n") ;
		printf("		�������²�Ʒ���ƣ�");
		scanf("%s",product[productIndex].name);
		//�����²�Ʒ����
		printf("		�������²�Ʒ�۸�");
		scanf("%lf",&product[productIndex].price);
		//�����²�Ʒ�����
		printf("		�������²�Ʒ�����: "); 
		scanf("%d",&product[productIndex].stock); 
		
		fprintf(fp,"%s %s %.2f %d\n",product[productIndex].number,product[productIndex].name,product[productIndex].price,product[productIndex].stock);
		if(fclose(fp)){
			printf("	 	����δ�������ر��ļ�  =_=!\n");
			exit(0);
		}
		return 1; 
	}else if(choosingNumber3==1){
		//�Զ����,����������¼�ı����±� 
		char strNumber[12];
		strcpy(strNumber,"order");
		int orderIndex=autoNumberCaculater(strNumber);
		
		//�¶���д�붩����Ϣ���� 
		if((fp=fopen("Record of order information.txt","a"))==NULL){
			printf("	 	����δ���������ļ�  =_=!\n");
			exit(0);
		}
		//��������Ա��� 
		printf("		������ִ������Ա��ţ�Exxx����");
		scanf("%s",order[orderIndex].salesPersonNumber);
		//����Ա���ڼ���
		int i,flag=0;
		for(i=0;*(salesPerson[i].number)!='\0';i++){
			if(strcmp(salesPerson[i].number,order[orderIndex].salesPersonNumber)==0){
				flag=1;break;
			}
		}
		if(!flag){
			printf("		����Ա�����ڣ���\n");
			return 0;
		}
		//������۲�Ʒ��� 
		printf("		��������۲�Ʒ���(Pxxx)��");
		scanf("%s", order[orderIndex].productNumber);
		//��Ʒ���ڼ���
		flag=0;
		for(i=0;*(product[i].number)!='\0';i++){
			if(strcmp(product[i].number,order[orderIndex].productNumber)==0){
				flag=1;break;
			}
		}
		if(!flag){
			printf("		��Ʒ�����ڣ���\n");
			return 0;
		}
		//ȡ����Ʒ�ڽṹ������е��±꣬���Լ��ٿ�� 
		while(1){
			flag=0;
			for(i=0;*(product[i].number)!='\0';i++){
				if(strcmp(order[orderIndex].productNumber,product[i].number)==0&&product[i].stock!=0){
					flag=1;
					break;
				}
			}
			if(flag)break;
			else{
				printf("		��Ʒ�����Ϊ 0 !\n");
				return 0; 
			}
		}
		//���붩��ִ��ʱ�� 
		printf("		�����붩��ִ��ʱ�䣨yyyy-mm-dd��: "); 
		scanf("%s", order[orderIndex].salesDay); 
		//���붩���������� 
		printf("		�������Ʒ��������: "); 
		scanf("%d", &order[orderIndex].salesAmount); 
		product[i].stock-=order[orderIndex].salesAmount; 
		//�жϿ�� 
		if(product[i].stock<0){
			printf("		��Ʒ��������㣡��\n");
			return 0;
		} 
		FILE *fp1;
		int j;
		//��д���Ĳ�Ʒ�ļ��еĿ����
		if((fp1=fopen("Record of products` information.txt","w"))==NULL){
			printf("	 	����δ���������ļ�  =_=!\n");
			exit(0);
		}
		//����Ϣ¼���ڴ洢�ļ��� 
		for(j=0;*(product[j].number)!='\0';j++){
			fprintf(fp1,"%s %s %.2f %d\n",product[j].number,product[j].name,product[j].price,product[j].stock);
		} 
		if(fclose(fp1)){
			printf("		����δ�������ر��ļ� =_=!\n");
			exit(0); 
		}	
		//������д�붩����Ϣ�����ļ� 
		fprintf(fp,"%s %s %s %s %d\n",order[orderIndex].number,order[orderIndex].salesPersonNumber,order[orderIndex].productNumber,order[orderIndex].salesDay,order[orderIndex].salesAmount);
		if(fclose(fp)){
			printf("	 	����δ�������ر��ļ�  =_=!\n");
			exit(0);
		}
		return 1; 
	}
}

//Ŀ�������ܶ��ѯ���� 
//����choosingNumber4 2Ϊ��Ŀ������Ա�����۶� 3Ϊ��ѯĿ���Ʒ�����۶�  
int lookingFor(int choosingNumber4){
	double sum=0;
	if(choosingNumber4==2){
		char salesPersonNumber[5];
		printf("		����������Ա����Բ�ѯ�������۶");
		scanf("%s",salesPersonNumber);
		
		int i,flag=0;//����Ա���ڼ���
		for(i=0;*(salesPerson[i].number)!='\0';i++){
			if(strcmp(salesPerson[i].number,salesPersonNumber)==0){
				flag=1;break;
			}
		}
		if(!flag){
			printf("		����Ա�����ڣ���\n");
			return 0;
		}
		sum=salesSum(0,salesPersonNumber); 
		printf("		������Ա�����۶�Ϊ��%.2f\n",sum);
		return 1;
	}else if(choosingNumber4==3){
		char productNumber[5];
		printf("		�������Ʒ����Բ�ѯ�������۶");
		scanf("%s",productNumber);
		
		int i,flag=0;//��Ʒ���ڼ���
		for(i=0;*(product[i].number)!='\0';i++){
			if(strcmp(product[i].number,productNumber)==0){
				flag=1;break;
			}
		}
		if(!flag){
			printf("		��Ʒ�����ڣ���\n");
			return 0;
		}
		sum=salesSum(1,productNumber); 
		printf("		�ò�Ʒ�����������۶�Ϊ��%.2f\n",sum);
		return 1;
	}
}

//ð������ 
void bubbleSort(struct information4 sumSort[]){
	struct information4 temp;//�������� 
	int i,j;//ѭ�����Ʊ���
	
	//�ҵ�sumSort�յ�
	for(i=0;*(sumSort[i].number)!='\0';i++); 
	int sumSortEnd=i;
	 
	//ð������ 
	for(i=1;i<sumSortEnd;i++){
		for(j=0;j<sumSortEnd-i;j++){
			 if(sumSort[j].sumSales<sumSort[j+1].sumSales){
				temp=sumSort[j];
				sumSort[j]=sumSort[j+1];
				sumSort[j+1]=temp; 
			 }
		}
	} 
}

//���������ܶ������� 
//����choosingNumber2 
//==4�����۶������Ա��������������������� 
//==5�����۶�Բ�Ʒ���н����������������  
int sort(int choosingNumber5){
	int i,j;//ѭ�����Ʊ��� 
	
	//�������Ա�����б� 
	if(choosingNumber5==4){
		for(i=0;*(salesPerson[i].number)!='\0';i++){
			strcpy(sumSort[i].number,salesPerson[i].number);
			strcpy(sumSort[i].name,salesPerson[i].name);
			sumSort[i].sumSales=salesSum(0,salesPerson[i].number);
		} 
		//ð������ 
		bubbleSort(sumSort);
		//����б�
		printf("		-------------�����۶������Ա�������������б�---------\n");
		for(i=0;*(sumSort[i].number)!='\0';i++);
		for(i-=1;i>=0;i--){
			printf("		%s  %s  %.2f\n",sumSort[i].number,sumSort[i].name,sumSort[i].sumSales);
		} 
		return 1;
	} 
	//�����Ʒ�����б�
	if(choosingNumber5==5){
		for(i=0;*(product[i].number)!='\0';i++){
			strcpy(sumSort[i].number,product[i].number);
			strcpy(sumSort[i].name,product[i].name);
			sumSort[i].sumSales=salesSum(1,product[i].number);
		} 
		//ð������ 
		bubbleSort(sumSort);
		//����б�
		printf("		-------------�����۶�Բ�Ʒ���н��������б�--------\n");
		for(i=0;*(sumSort[i].number)!='\0';i++){
			printf("		%s  %s  %.2f\n",sumSort[i].number,sumSort[i].name,sumSort[i].sumSales);
		} 
		return 1;
	} 
}

//��¼�������������ƺ��� 
void afterLogin(){
	//��¼�ɹ��ʺ��� 
	printf("		---------��ӭ����^v^ ");
	printf("%s",login.name);
	printf("----------\n");
	
	//����ѡ����� 
	int choosingNumber6;
	
	while (1){
		//�����˵� 
		printf("		0)����µĲ�Ʒ��Ϣ\n");
		printf("		1)����µĶ�����Ϣ\n");
		printf("		2)��ѯĳ����Ա�������۶�\n");
		printf("		3)��ѯĳ����Ʒ�����������۶�\n");
		printf("		4)�鿴�����۶�Ϊָ���������������Ա�б�\n");
		printf("		5)�鿴�����۶�Ϊָ�꽵������Ĳ�Ʒ�б�\n"); 
		printf("		6)�˳���¼\n");
		printf("		7)�˳�ϵͳ\n\n");
		printf("		�������Ӧ��������Խ�����һ��:");
		
		scanf("%d",&choosingNumber6);
		switch(choosingNumber6){
			//�������Ϣ���� 
			case 0:case 1:
				if(add(choosingNumber6)==1){
					printf("		�µ���Ϣ�ѳɹ���ӣ���~\n\n"); 
				}else{
					printf("		���ʧ�ܣ���~\n\n");
				}
				break;
//			��ѯĿ����Ϣ���� 
			case 2:case 3:	
				if(lookingFor(choosingNumber6)==1){
					printf("		��ѯĿ����Ϣ������ʾ��\n\n"); 
				}else{
					printf("		Ŀ����Ϣ��ʾʧ�ܣ���\n\n"); 
				}
				break;
			//�鿴Ŀ��������� 
			case 4:case 5:
				if(sort(choosingNumber6)==1){
					printf("		Ŀ����Ϣ�б�������ʾ��\n\n"); 
				}else{
					printf("		�б���ʾʧ�ܣ���\n\n"); 
				}break;
			//�˳���¼ 
			case 6:
				return;
			//�˳�ϵͳ 
			case 7:
				printf("		��л����ʹ��~~��");
				exit(0);
			default:
				printf("		��Ч��������ţ�\n");
				break;
		}
	}	
}
