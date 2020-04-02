#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct information_node * wordIn(int *cnt);//文件内信息导入链表函数
struct information_node * newWordInsert(struct information_node *head,int *cnt_word);//新单词插入功能函数
void reciteWord(int choosingNumber2,int cnt_word,struct information_node *head);//单词复习功能函数
void choosingSort(int cnt_word,int choosingNumber3,struct information_node *sorting_word);//选择排序并输出序列表函数
void dataCount(int cnt_word,struct information_node * head);//技术数据表输出函数 
void word_output(int cnt_word,struct information_node *head );//链表已变更信息写入文件函数

//每个单词的信息 使用链表储存 
struct information_node{
	char wordName[20];//单词 
	char wordMean[40];//单词释义 
	int cnt_correct;//正确次数 
	int cnt_wrong;//错误次数
	int cnt_answer;//回答次数 
	struct information_node *next;//next指针 
}; 

int main()
{	
	int cnt_word=0;
	//定义并储存文件链表 
	struct information_node *tail=NULL;
	struct information_node *head=wordIn(&cnt_word);
	
	int choosingNumber1;//程序外围选择变量 
	int choosingNumber2;//单词背诵功能选择 
	int cnt_newWord;//录入新单词功能中新单词数量统计变量 
	
	//欢迎问候语行 
	printf("**********************************\n	滴水石穿\n**********************************\n\n"); 
	//目标功能菜单序列表
	while(1){
		printf("0 新的单词录入\n");
		printf("1 开始复习单词\n");
		printf("2 技术数据统计\n"); 
		printf("3 退出程序\n"); 
		printf("请输入目标功能序号：");
		//录入功能选择序号 
		scanf("%d",&choosingNumber1);
		printf("\n");
		//目标功能选择 
		switch(choosingNumber1){
			case 0:
				printf("功能：新的单词录入\n");
				cnt_newWord=0;
				head=newWordInsert(head,&cnt_newWord);
				printf("新的单词录入成功  本次录入新单词数量：%d个\n\n",cnt_newWord);
				cnt_word+=cnt_newWord;//单词总数加上新添加单词数 
				break;
			case 1:
				printf("功能：复习历史存入单词\n");
				printf("请选择复习方式 \n0)以汉答英\n1)以英答汉 ：");
				scanf("%d",&choosingNumber2); 
				printf("\n");
				reciteWord(choosingNumber2,cnt_word,head);
				break;
			case 2:
				printf("功能：技术数据统计如下\n");
				dataCount(cnt_word,head);
				break;
			case 3:
				printf("功能：退出程序\n");
				word_output(cnt_word,head);
				exit(0); 
		}
	}
} 

/*文件内信息导入链表函数
参数：单词总数变量地址 返回值：链表的头结点地址*/
struct information_node * wordIn(int *cnt){
	FILE *fp;
	*cnt=0;
	
	if((fp=fopen("单词库.txt","r"))==NULL){
		printf("单词储存文件不存在 即将新建文件！\n");
		return NULL;//如文件不存在 则新建文件 
	}
	
	struct information_node *head,*tail,*word;
	int size = sizeof(struct information_node);
	
	head=tail=NULL;
	//录入文件内信息 
	while(!feof(fp)){
		word=(struct information_node *)malloc(size);
		fscanf(fp,"%s%s%d%d%d",word->wordName,word->wordMean,&word->cnt_correct,&word->cnt_wrong,&word->cnt_answer);
		(*cnt)++;
		word->next=NULL;
		if(head==NULL){
			head=word;
		}else{
			tail->next=word;
		}
		tail=word;
	}
	(*cnt)--; 
	if(fclose(fp)){
		printf("关闭文件失败！");
		exit(0);
	}
	//返回链表头地址 
	return head;
}

/*新单词插入功能函数
参数：链表头结点　返回值：新插入的单词个数*/ 
struct information_node * newWordInsert(struct information_node *head,int *cnt_newWord){
	FILE *fp;//定义文件指针
	//新建移动、尾、新单词链表节点 
	struct information_node *p=head,*tail=NULL,*newWord=NULL;
	int size=sizeof(struct information_node);//动态申请空间准备 
	int first=1;//释义提示语 仅出现一次控制变量 
	
	//将尾结点正位 
	if(head==NULL){
		//无预置文件 如果首节点不存在 
		tail=NULL;
	} else{
		//有预置文件 首节点存在 
		while(p->next!=NULL){
			tail=p;
			p=p->next;
		}
	}
	
	//录入新单词  
	if((fp=fopen("单词库.txt","a"))==NULL){
		printf("单词库内信息导入失败！");
		exit(0); 
	} 
	printf("请录入新的单词 每个单词以回车结尾\n最后一个单词录入结束时请输入单词名commend_end以结束新单词录入！\n\n"); 
	while(1) {
		//新单词插入及新单词信息获取 
		//动态申请每个新节点的空间 
		newWord=(struct information_node*)malloc(size); 
		//录入新的单词 
		printf("请输入新单词：");
		scanf("%s",newWord->wordName);
//		gets(newWord->wordName); 
		//输入单词名为commend_end 终止 
		if(strcmp(newWord->wordName,"commend_end")==0) {
			break;
		}
		//新单词释义输入提示仅出现一次 
		if(first==1){
			printf("多释义以分号隔离 中间不可带有‘ ’ 不可超过40字符\n");
			first=0;
		} 
		printf("请输入新单词释义：");
		scanf("%s",newWord->wordMean);
//		gets(newWord->wordMean); 
		//新单词统计信息初始化
		newWord->cnt_correct=0;newWord->cnt_wrong=0;newWord->cnt_answer=0; 
		//新的单词加入链表 
		newWord->next=NULL;
		if(head==NULL){
			head=newWord;//新结点为链表的首节点 
		}else{
			tail->next=newWord;//新结点插入非空链表尾部 
		}
		//链表尾节点为新节点 
		tail=newWord;
		printf("新单词：%s 导入成功\n\n",newWord->wordName); 
		//新单词数++ 
		(*cnt_newWord)++;
		//将新的单词信息写入文件中
		fprintf(fp,"%s %s %d %d %d\n",newWord->wordName,newWord->wordMean,newWord->cnt_correct,newWord->cnt_wrong,newWord->cnt_answer); 
	}
	//关闭文件
	if(fclose(fp)){
		printf("未能正常关闭文件！");
		exit(0); 
	} 
	return head;
} 

/*单词复习功能函数
参数：复习类型选择变量choosingNumber2,链表头部节点地址 返回值：无*/
void reciteWord(int choosingNumber2,int cnt_word,struct information_node *head){
	//数据统计变量 ,循环控制变量 
	int cnt_c=0,cnt_w=0,cnt_a=0,i; 
	//常量储存
//	const int CNT=cnt_word; 
	//以汉答英背诵方式 
	if(choosingNumber2==0){
		//以时间作为种子 
		srand((int)time(0));
		printf("以汉答英复习词汇方式 输入commend_end以结束复习\n\n");
		while(1){
			//取链表 0~结点总数-1 范围内任意随机数 
			int random=rand()%cnt_word;
//			int random=rand()%4;//调试 
//			random=random==0?random:random-1;
			
			//取随机结点地址并储存 
//			struct information_node *answer_word=head+random;
			struct information_node *answer_word=head;
			for(i=0;i<random;i++){
				answer_word=answer_word->next;
			}
			//定义回答的单词
			char answer[20];
			
			printf("释义：%s\n",answer_word->wordMean);
			scanf("%s",answer);
			if(strcmp(answer,answer_word->wordName)==0){
				printf("正确！\n\n");
				cnt_c++;cnt_a++;
				//正确次数与回答次数+1 
				answer_word->cnt_answer++;answer_word->cnt_correct++; 
			}else if(strcmp(answer,"commend_end")==0){
				break;
			}else{
				printf("错误！ 正确答案为：%s\n\n",answer_word->wordName);
				cnt_w++;cnt_a++;
				//错误次数与回答次数+1 
				answer_word->cnt_answer++;answer_word->cnt_wrong++;  
			}
		}
		printf("功能结束 本次复习 %d 词汇 正确：%d 错误：%d 正确率：%.1f%%\n\n",cnt_a,cnt_c,cnt_w,100.0*cnt_c/cnt_a); 	
	}else if (choosingNumber2==1){
		//以时间作为种子 
		srand((int)time(0));
		printf("以英答汉复习词汇方式 输入commend_end以结束背诵\n\n");
		while(1){
			//取链表 0~结点总数-1 范围内任意随机数 
			int random=rand()%cnt_word;
//			random=random==0?random:random-1;
			
			//取随机结点地址并储存 
//			struct information_node *answer_word=head+random;
			struct information_node *answer_word=head;
			for(i=0;i<random;i++){
				answer_word=answer_word->next;
			}
			//定义回答的释义 
			char answer[40];
			
			printf("单词：%s\n",answer_word->wordName);
			scanf("%s",answer);cnt_a++;
			if(strcmp(answer,"commend_end")==0)break; 
			printf("释义： %s\n\n",answer_word->wordMean);
		}
		printf("功能结束 本次复习 %d 词汇\n\n",cnt_a);
	}
}

/*选择排序并输出序列表函数
参数 ：单词总数，结构体数组名,方式选择变量 返回值:无*/
void choosingSort(int cnt_word,int choosingNumber3,struct information_node *sorting_word) {
	int i,j;//循环控制变量
	int index_max;//标记序号变量
	struct information_node temp;//交换结构体变量 
	 
	for (i=0;i<cnt_word;i++){
		index_max=i;
		for(j=i;j<cnt_word;j++){
			if(choosingNumber3==0){//以回答次数排序 
				if(sorting_word[j].cnt_answer>sorting_word[index_max].cnt_answer){
					index_max=j;
				}
			}else if(choosingNumber3==1){//以正确次数排序 
				if(sorting_word[j].cnt_correct>sorting_word[index_max].cnt_correct){
					index_max=j;
				}
			}else if(choosingNumber3==2){//以错误次数排序 
				if(sorting_word[j].cnt_wrong>sorting_word[index_max].cnt_wrong){
					index_max=j;
				}
			}else{//以正确率排序 
				if(1.0*sorting_word[j].cnt_correct/sorting_word[j].cnt_answer>1.0*sorting_word[index_max].cnt_correct/sorting_word[index_max].cnt_answer){
					index_max=j;
				}
			}
		}
		//结构体内部信息交换 
		temp=sorting_word[i];
		sorting_word[i]=sorting_word[index_max];
		sorting_word[index_max]=temp;
	}
	//输出列表信息 
	printf("         单词  	     正确次数    回答次数      正确率\n"); 
	for(i=0;i<cnt_word;i++){
		printf("%15s %10d %10d %14.1f%%\n",sorting_word[i].wordName,sorting_word[i].cnt_correct,sorting_word[i].cnt_answer,100.0*sorting_word[i].cnt_correct/sorting_word[i].cnt_answer) ;
	}
}

/*技术数据表输出函数
参数 ：单词总数，链表头结点地址　返回值：无*/
void dataCount(int cnt_word,struct information_node * head){
	printf("0)以回答次数排序\n");
	printf("1)以正确次数排序\n");
	printf("2)以错误次数排序\n");
	printf("3)以回答正确率进行排序\n"); 
	printf("请输入技术数据序列表排序依据：");
	
	struct information_node sorting_word[cnt_word];	//构造数组存储信息用以排序 
	struct information_node	*p=head;//存储链表结点 
	int i,j,choosingNumber3;//循环控制变量,选择变量 
	//将链表信息录入结构体数组中 
	for(i=0;i<cnt_word;i++){
		sorting_word[i]=*p;//存储节点
		p=p->next;//节点移动 
	}
	scanf("%d",&choosingNumber3) ;//录入选择变量 
	printf("\n"); 
	choosingSort(cnt_word,choosingNumber3,sorting_word) ;
	printf("\n输出信息表如上\n\n"); 
}

/*链表已变更信息写入文件函数
参数：链表头节点地址 单词总数 返回值：无*/ 
void word_output(int cnt_word,struct information_node *head ){
	FILE *fp;
	int i;//循环控制变量 
	struct information_node *p=head;//节点储存指针 
	
	if((fp=fopen("单词库.txt","w"))==NULL){
		printf("打开文件失败！");
		exit(0);
	} 
	for(i=0;i<cnt_word;i++){
		//将节点信息写入文件中 
		fprintf(fp,"%s %s %d %d %d\n",p->wordName,p->wordMean,p->cnt_correct,p->cnt_wrong,p->cnt_answer);
		p=p->next;//节点向后移动 
	}
	if(fclose(fp)){
		printf("关闭文件失败！");
		exit(0);
	}
} 
