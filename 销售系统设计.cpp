/*登录界面*/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int informationIn();//文件信息导入函数 ，每当程序启动将txt中存储的数据引入结构体变量中 
int autoNumberCaculater(char *strNumber);//添加产品自动编号处理函数 
int commendRegister();//注册实现函数 
int commendLogin();//登录验证函数 
double salesSum(int choosingNumber6,char *targetNumber);//销售总额计算函数
int add(int choosingNumber2);//登录后添加新的产品或是订单处理函数 
int lookingFor(int choosingNumber2);//目标销售总额查询函数 
void bubbleSort(struct information4 sumSort[]);//冒泡排序 
int sort(int choosingNumber2);//销售总额排序函数 
void afterLogin();//登录后程序主界面控制函数 

/*信息储存程序段*/
//销售员信息储存
struct information1{
	char number[10];
	char name[31];
	char sex[7];
	char schooling[31];
	char password[18];
}salesPerson[20],login;

//产品信息储存 
struct information2{
	char number[10];//用于提取更改库存量的节点 
	char name[31];
	double price;
	int stock;
}product[30];

//订单信息储存
struct information3{
	char number[10];// 格式:O001-O00X
	char salesPersonNumber[10];
	char productNumber[10]; 
	char salesDay[11];// 格式:year-month-day xxxx-xx-xx 注意限制范围
	int salesAmount;
}order[100];

//销售员总销售额储存
struct information4{
	char number[10];
	char name[31];
	double sumSales;
}sumSort[30];

int main()
{	
	//将结构体变量信息导入	
	if(informationIn()!=1){
		printf("		文件信息未能正常导入！请检查文件路径！\n");
		return 0; 
	}
	
	//选择操作变量 
	int choosingNumber1; 
	
	//登录界面提示语句 ,全局输出出于居中美观考虑，每行前两个缩进字符\t 
	printf("		------欢迎来到 IG 销售系统------\n");
	printf("		--(＾＾●)--(＾＾●)--(＾＾●)--\n");
	
	//程序外围操作 
	while(1){
		printf("		0)在册销售员登录\n");
		printf("		1)新销售员注册\n");
		printf("		2)退出系统\n\n");
		printf("		请输出相应命令序号以进行下一步:");
		
		scanf("%d",&choosingNumber1); 
		switch(choosingNumber1){
			//登录界面
			case 0:	
				if(commendLogin()==1){
					afterLogin(); 
				}else{
					printf("		用户名或密码不正确！！！\n\n"); 
				}	
				break;
			//注册界面
			case 1:
				if(commendRegister()==1){
					printf("		注册成功啦! ^v^\n\n");
				}else{
					printf("		注册失败辽! =_=\n");
					printf("		失败原因：在册用户数量已达上限!\n\n");
				}
				break;
			//结束选择 退出程序 
			case 2:
				printf("		感谢您的使用!~~\n");
				return 0;
			default:
				printf("		无效的命令序号！\n");
				break;
		}
	} 
}

//文件信息导入函数 
//每当程序启动将txt中存储的数据引入结构体变量中 
int informationIn(){
	//定义文件指针 
	FILE *fp;
	//导入销售员信息 
	if((fp=fopen("Record of salesperson information.txt","r"))==NULL){
		printf("		错误：未能正常打开文件 =_=!\n");
		exit(0);
	}
	int i=0;
	while (!feof(fp)){
		fscanf(fp,"%s%s%s%s%s",salesPerson[i].number,salesPerson[i].name,salesPerson[i].sex,salesPerson[i].schooling,salesPerson[i].password);
		i++;
	}
	if(fclose(fp)){
		printf("		错误：未能正常关闭文件 =_=!\n");
		exit(0);
	}
	//导入产品信息
	if((fp=fopen("Record of products` information.txt","r"))==NULL){
		printf("		错误：未能正常打开文件 =_=!\n");
		exit(0);
	}
	i=0;
	while (!feof(fp)){
		fscanf(fp,"%s%s%lf%d",product[i].number,product[i].name,&product[i].price,&product[i].stock);
		i++;
	}
	if(fclose(fp)){
		printf("		错误：未能正常关闭文件 =_=!\n");
		exit(0);
	}
	//导入订单信息
	 if((fp=fopen("Record of order information.txt","r"))==NULL){
		printf("		错误：未能正常打开文件 =_=!\n");
		exit(0);
	}
	i=0;
	while (!feof(fp)){
		fscanf(fp,"%s%s%s%s%d",order[i].number,order[i].salesPersonNumber,order[i].productNumber,order[i].salesDay,&order[i].salesAmount);
		i++;
	}
	if(fclose(fp)){
		printf("		错误：未能正常关闭文件 =_=!\n");
		exit(0);
	}
	return 1;
} 

//添加新信息自动编号处理函数 
int autoNumberCaculater(char *strNumber){
	//定义文件指针
	FILE *fp; 
	//自动编号处理 
	if(strcmp(strNumber,"salesPerson")==0){
		if((fp=fopen("Record of salesPerson information.txt","r"))==NULL){
			printf("		错误：未能正常打开文件 =_=!\n");
			exit(0);
		} 
	}
	else if(strcmp(strNumber,"product")==0){
		if((fp=fopen("Record of products` information.txt","r"))==NULL){
			printf("		错误：未能正常打开文件 =_=!\n");
			exit(0);
		}  
	}
	else if(strcmp(strNumber,"order")==0){
		if((fp=fopen("Record of order information.txt","r"))==NULL){
			printf("		错误：未能正常打开文件 =_=!\n");
			exit(0);
		} 
	}
	
	int index;//储存结构体函数下标 
	char menberNumber[10];//接受并进行编号处理 
	strcpy(menberNumber,"null");
	
	char a[31],b[31],c[31],d[31];//接受无用字符串 
	double e;//接受无用双精度浮点型变量 
	int f;//接受无用整型变量 

	//保存文件中最后一个编号 
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
	
	int autoNumber=0;//编号整型化储存 
	
	//记录表中无任何信息记录时 
	if(strcmp(menberNumber,"null")==0){
		if(strcmp(strNumber,"salesPeron")==0){
			strcpy(salesPerson[0].number,"E001");//如注册列表为空，此用户编号为E001 
		}
		else if(strcmp(strNumber,"product")==0){
			strcpy(product[0].number,"P001");//如注册列表为空，此产品编号为P001 
		}
		else if(strcmp(strNumber,"order")==0){
			strcpy(order[0].number,"O001");//如注册列表为空，此订单编号为O001 
		}
		return 0;
	}else{
		int digit;//高位取出编号 
		char *p=menberNumber+1;
		 
		//字符型编号整型化
		for(;*p!='\0';p++){
			digit=*p-'0';
			autoNumber=autoNumber*10+digit;
		}
		autoNumber++;//末位注册员编号加一位用于储存新用户编号 
		//判断注册数是否越界 
		if(strcmp(strNumber,"salesPeron")==0){
			if(autoNumber>20)return 2;
		}
		if(strcmp(strNumber,"product")==0){
			if(autoNumber>30)return 2;
		}
		
		index=autoNumber-1;
		int i=0;
		
		//整型编号字符化 
		for(p=menberNumber+3;i<3;p--){
			digit=autoNumber%10;
			*p=digit+'0';
			autoNumber/=10;
			i++;
		} 
	}
	if(fclose(fp)){
		printf("		错误：未能正常关闭文件 =_=!\n");
		exit(0);
	}
	//将序号保存在相应结构体变量中 
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

//注册实现函数 
int commendRegister(){
	printf("\n		----------新销售员注册界面-------------\n") ; 
	 
	//定义文件指针
	FILE *fp;  
	//自动编号,并计算此项记录的变量下标 
	char strNumber[12];
	strcpy(strNumber,"salesPerson");
	int menberIndex=autoNumberCaculater(strNumber);
	//新用户写入销售员信息表中 
	if((fp=fopen("Record of salesPerson information.txt","a"))==NULL){
		printf("	 	错误：未能正常打开文件  =_=!\n");
		exit(0);
	}

	//新用户名称 
	printf("		提示：您的用户名长度限于30个字符之内（汉字占2个字符）\n");    
	printf("		请输入新的销售员用户名：");
	scanf("%s",salesPerson[menberIndex].name);
	printf("\n"); 
	
	//新用户性别
	int sexnumber;
	printf("		0)男性\n");
	printf("		1)女性\n\n");
	printf("		请输入相应序号以选择您的性别:");
	
	scanf("%d",&sexnumber); 
	switch(sexnumber){
		case 0:strcpy(salesPerson[menberIndex].sex,"男性");break;
		case 1:strcpy(salesPerson[menberIndex].sex,"女性");break;
	}
	printf("\n"); 
	
	//新用户受教育程度
	int schoolingNumber;
	printf("		0)研究生学历及以上\n");
	printf("		1)大学本科或专科学历\n");
	printf("		2)高中学历及以下\n\n");
	printf("		请输入相应序号以选择您的学历:");
		
	scanf("%d",&schoolingNumber);
	switch(schoolingNumber){
		case 0:strcpy(salesPerson[menberIndex].schooling,"研究生学历及以上");break;
		case 1:strcpy(salesPerson[menberIndex].schooling,"大学本科或专科学历");break;
		case 2:strcpy(salesPerson[menberIndex].schooling,"高中学历及以下");break;
	}
	printf("\n");
	
	//新用户密码
	printf("		提示：您的密码长度限于17个字符内（汉字占2个字符）\n");
	printf("		请输入您的密码 *_*:");
	scanf("%s",salesPerson[menberIndex].password);
	//二次输入密码保证正确
	char str[18];
	while (1){
		printf("		请确认您的密码:");
		scanf("%s",str);
		if(strcmp(str,salesPerson[menberIndex].password)!=0){
			printf("		错误：两次输入的密码不一致！！！\n");
		}
		else break;
	}
	printf("\n");
	//将信息录入于存储文件中 
	fprintf(fp,"%s %s %s %s %s\n",salesPerson[menberIndex].number,salesPerson[menberIndex].name,salesPerson[menberIndex].sex,salesPerson[menberIndex].schooling,salesPerson[menberIndex].password);
	if(fclose(fp)){
		printf("		错误：未能正常关闭文件 =_=!\n");
		exit(0);
	}
	return 1;
}
	
//登录验证函数 
int commendLogin(){
	printf("\n		----------在册销售员登录界面----------\n");
	
	//定义文件指针
	FILE *fp;  
	//输入用户名与密码 
	printf("		请输入您的用户名："); 
	scanf("%s",login.name);
	printf("		请输入您的密码:");
	scanf("%s",login.password);
	//验证用户名与密码的正确性 
	if((fp=fopen("Record of salesPerson information.txt","r"))==NULL){
		printf("		错误：未能正常打开文件 =_=!\n");
		exit(0);
	}

	char menberName[31];//存储一项销售员用户名 
	char menberPassword[18];//存储相应的销售员密码 
	char a[31],b[31],c[31];//存储无用字符串 
	
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

//销售总额计算函数 
//参数choosingNumber2 0为以销售员编号 1为以产品编号 
//参数targetNumber 为目标编号 
double salesSum(int choosingNumber2,char *targetNumber){
	FILE *fp;
	//循环控制变量 
	int i,j;
	//销售额统计变量 
	double sum=0;
	//choosingNumber6==0时为查询单个销售员的销售额总和 
	if(choosingNumber2==0){
		if((fp=fopen("Record of order information.txt","r"))==NULL){
			printf("		未能正常打开文件\n"); 
		}
		
		char a[31],b[31],c[31],d[31];
		int e;
		
		int n=0;
		//确定订单记录总数 
		while(!feof(fp)){
			fscanf(fp,"%s%s%s%s%d",a,b,c,d,&e);
			n++;
		}
		for(i=0;i<n;i++){
			//寻找订单列表中目标销售员执行的订单 
			if(strcmp(targetNumber,order[i].salesPersonNumber)==0){
				for(j=0;;j++){
					//找到订单执行的商品信息并计入总和 
					if(strcmp(product[j].number,order[i].productNumber)==0){
						sum+=product[j].price*order[i].salesAmount;
						break;
					}
				}
			}
		}
		return sum; 
	//choosingNumber6==1时为查询单个产品的销售额总和 
	}else if(choosingNumber2==1){
		if((fp=fopen("Record of order information.txt","r"))==NULL){
			printf("		未能正常打开文件\n"); 
		}
		
		char a[31],b[31],c[31],d[31];
		int e;
		
		int n=0;
		//确定订单记录总数 
		while(!feof(fp)){ 
			fscanf(fp,"%s%s%s%s%d",a,b,c,d,&e);
			n++;
		}
		for(i=0;i<n;i++){
			//寻找订单列表中目标销售员执行的订单 
			if(strcmp(targetNumber,order[i].productNumber)==0){
				for(j=0;;j++){
					//找到订单执行的商品信息并计入总和 
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

//登录后添加新的产品或是订单处理函数 
int add(int choosingNumber3){
	FILE *fp;
	//添加新的产品信息 
	if(choosingNumber3==0){
		//自动编号,并计算此项记录的变量下标 
		char strNumber[12];
		strcpy(strNumber,"product");
		int productIndex=autoNumberCaculater(strNumber);
		
		//新产品写入产品信息表中 
		if((fp=fopen("Record of products` information.txt","a"))==NULL){
			printf("	 	错误：未能正常打开文件  =_=!\n");
			exit(0);
		}
		//输入新产品名称 
		printf("		提示：产品名称限制在30个字符之内（汉字占2个字符）\n") ;
		printf("		请输入新产品名称：");
		scanf("%s",product[productIndex].name);
		//输入新产品单价
		printf("		请输入新产品价格：");
		scanf("%lf",&product[productIndex].price);
		//输入新产品库存量
		printf("		请输入新产品库存量: "); 
		scanf("%d",&product[productIndex].stock); 
		
		fprintf(fp,"%s %s %.2f %d\n",product[productIndex].number,product[productIndex].name,product[productIndex].price,product[productIndex].stock);
		if(fclose(fp)){
			printf("	 	错误：未能正常关闭文件  =_=!\n");
			exit(0);
		}
		return 1; 
	}else if(choosingNumber3==1){
		//自动编号,并计算此项记录的变量下标 
		char strNumber[12];
		strcpy(strNumber,"order");
		int orderIndex=autoNumberCaculater(strNumber);
		
		//新订单写入订单信息表中 
		if((fp=fopen("Record of order information.txt","a"))==NULL){
			printf("	 	错误：未能正常打开文件  =_=!\n");
			exit(0);
		}
		//输入销售员编号 
		printf("		请输入执行销售员编号（Exxx）：");
		scanf("%s",order[orderIndex].salesPersonNumber);
		//销售员存在检验
		int i,flag=0;
		for(i=0;*(salesPerson[i].number)!='\0';i++){
			if(strcmp(salesPerson[i].number,order[orderIndex].salesPersonNumber)==0){
				flag=1;break;
			}
		}
		if(!flag){
			printf("		销售员不存在！！\n");
			return 0;
		}
		//输入出售产品编号 
		printf("		请输入出售产品编号(Pxxx)：");
		scanf("%s", order[orderIndex].productNumber);
		//产品存在检验
		flag=0;
		for(i=0;*(product[i].number)!='\0';i++){
			if(strcmp(product[i].number,order[orderIndex].productNumber)==0){
				flag=1;break;
			}
		}
		if(!flag){
			printf("		产品不存在！！\n");
			return 0;
		}
		//取出产品在结构体变量中的下标，用以减少库存 
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
				printf("		产品库存量为 0 !\n");
				return 0; 
			}
		}
		//输入订单执行时间 
		printf("		请输入订单执行时间（yyyy-mm-dd）: "); 
		scanf("%s", order[orderIndex].salesDay); 
		//输入订单销售数量 
		printf("		请输入产品出售数量: "); 
		scanf("%d", &order[orderIndex].salesAmount); 
		product[i].stock-=order[orderIndex].salesAmount; 
		//判断库存 
		if(product[i].stock<0){
			printf("		产品库存量不足！！\n");
			return 0;
		} 
		FILE *fp1;
		int j;
		//重写更改产品文件中的库存量
		if((fp1=fopen("Record of products` information.txt","w"))==NULL){
			printf("	 	错误：未能正常打开文件  =_=!\n");
			exit(0);
		}
		//将信息录入于存储文件中 
		for(j=0;*(product[j].number)!='\0';j++){
			fprintf(fp1,"%s %s %.2f %d\n",product[j].number,product[j].name,product[j].price,product[j].stock);
		} 
		if(fclose(fp1)){
			printf("		错误：未能正常关闭文件 =_=!\n");
			exit(0); 
		}	
		//将订单写入订单信息储存文件 
		fprintf(fp,"%s %s %s %s %d\n",order[orderIndex].number,order[orderIndex].salesPersonNumber,order[orderIndex].productNumber,order[orderIndex].salesDay,order[orderIndex].salesAmount);
		if(fclose(fp)){
			printf("	 	错误：未能正常关闭文件  =_=!\n");
			exit(0);
		}
		return 1; 
	}
}

//目标销售总额查询函数 
//参数choosingNumber4 2为以目标销售员总销售额 3为查询目标产品总销售额  
int lookingFor(int choosingNumber4){
	double sum=0;
	if(choosingNumber4==2){
		char salesPersonNumber[5];
		printf("		请输入销售员编号以查询其总销售额：");
		scanf("%s",salesPersonNumber);
		
		int i,flag=0;//销售员存在检验
		for(i=0;*(salesPerson[i].number)!='\0';i++){
			if(strcmp(salesPerson[i].number,salesPersonNumber)==0){
				flag=1;break;
			}
		}
		if(!flag){
			printf("		销售员不存在！！\n");
			return 0;
		}
		sum=salesSum(0,salesPersonNumber); 
		printf("		该销售员总销售额为：%.2f\n",sum);
		return 1;
	}else if(choosingNumber4==3){
		char productNumber[5];
		printf("		请输入产品编号以查询其总销售额：");
		scanf("%s",productNumber);
		
		int i,flag=0;//产品存在检验
		for(i=0;*(product[i].number)!='\0';i++){
			if(strcmp(product[i].number,productNumber)==0){
				flag=1;break;
			}
		}
		if(!flag){
			printf("		产品不存在！！\n");
			return 0;
		}
		sum=salesSum(1,productNumber); 
		printf("		该产品产生的总销售额为：%.2f\n",sum);
		return 1;
	}
}

//冒泡排序 
void bubbleSort(struct information4 sumSort[]){
	struct information4 temp;//交换变量 
	int i,j;//循环控制变量
	
	//找到sumSort终点
	for(i=0;*(sumSort[i].number)!='\0';i++); 
	int sumSortEnd=i;
	 
	//冒泡排序 
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

//定义销售总额排序函数 
//参数choosingNumber2 
//==4按销售额对销售员进行升序排序，输出排序结果 
//==5按销售额对产品进行降序排序，输出排序结果  
int sort(int choosingNumber5){
	int i,j;//循环控制变量 
	
	//输出销售员排序列表 
	if(choosingNumber5==4){
		for(i=0;*(salesPerson[i].number)!='\0';i++){
			strcpy(sumSort[i].number,salesPerson[i].number);
			strcpy(sumSort[i].name,salesPerson[i].name);
			sumSort[i].sumSales=salesSum(0,salesPerson[i].number);
		} 
		//冒泡排序 
		bubbleSort(sumSort);
		//输出列表
		printf("		-------------按销售额对销售员进行升序排序列表---------\n");
		for(i=0;*(sumSort[i].number)!='\0';i++);
		for(i-=1;i>=0;i--){
			printf("		%s  %s  %.2f\n",sumSort[i].number,sumSort[i].name,sumSort[i].sumSales);
		} 
		return 1;
	} 
	//输出产品排序列表
	if(choosingNumber5==5){
		for(i=0;*(product[i].number)!='\0';i++){
			strcpy(sumSort[i].number,product[i].number);
			strcpy(sumSort[i].name,product[i].name);
			sumSort[i].sumSales=salesSum(1,product[i].number);
		} 
		//冒泡排序 
		bubbleSort(sumSort);
		//输出列表
		printf("		-------------按销售额对产品进行降序排序列表--------\n");
		for(i=0;*(sumSort[i].number)!='\0';i++){
			printf("		%s  %s  %.2f\n",sumSort[i].number,sumSort[i].name,sumSort[i].sumSales);
		} 
		return 1;
	} 
}

//登录后程序主界面控制函数 
void afterLogin(){
	//登录成功问候语 
	printf("		---------欢迎！！^v^ ");
	printf("%s",login.name);
	printf("----------\n");
	
	//操作选择变量 
	int choosingNumber6;
	
	while (1){
		//操作菜单 
		printf("		0)添加新的产品信息\n");
		printf("		1)添加新的订单信息\n");
		printf("		2)查询某销售员的总销售额\n");
		printf("		3)查询某个产品产生的总销售额\n");
		printf("		4)查看以销售额为指标升序排序的销售员列表\n");
		printf("		5)查看以销售额为指标降序排序的产品列表\n"); 
		printf("		6)退出登录\n");
		printf("		7)退出系统\n\n");
		printf("		请输出相应命令序号以进行下一步:");
		
		scanf("%d",&choosingNumber6);
		switch(choosingNumber6){
			//添加新信息操作 
			case 0:case 1:
				if(add(choosingNumber6)==1){
					printf("		新的信息已成功添加！！~\n\n"); 
				}else{
					printf("		添加失败！！~\n\n");
				}
				break;
//			查询目标信息操作 
			case 2:case 3:	
				if(lookingFor(choosingNumber6)==1){
					printf("		查询目标信息如上所示↑\n\n"); 
				}else{
					printf("		目标信息显示失败！！\n\n"); 
				}
				break;
			//查看目标排序操作 
			case 4:case 5:
				if(sort(choosingNumber6)==1){
					printf("		目标信息列表如上所示↑\n\n"); 
				}else{
					printf("		列表显示失败！！\n\n"); 
				}break;
			//退出登录 
			case 6:
				return;
			//退出系统 
			case 7:
				printf("		感谢您的使用~~！");
				exit(0);
			default:
				printf("		无效的命令序号！\n");
				break;
		}
	}	
}
