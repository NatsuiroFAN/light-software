#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct information_node * wordIn(int *cnt);//�ļ�����Ϣ����������
struct information_node * newWordInsert(struct information_node *head,int *cnt_word);//�µ��ʲ��빦�ܺ���
void reciteWord(int choosingNumber2,int cnt_word,struct information_node *head);//���ʸ�ϰ���ܺ���
void choosingSort(int cnt_word,int choosingNumber3,struct information_node *sorting_word);//ѡ������������б���
void dataCount(int cnt_word,struct information_node * head);//�������ݱ�������� 
void word_output(int cnt_word,struct information_node *head );//�����ѱ����Ϣд���ļ�����

//ÿ�����ʵ���Ϣ ʹ�������� 
struct information_node{
	char wordName[20];//���� 
	char wordMean[40];//�������� 
	int cnt_correct;//��ȷ���� 
	int cnt_wrong;//�������
	int cnt_answer;//�ش���� 
	struct information_node *next;//nextָ�� 
}; 

int main()
{	
	int cnt_word=0;
	//���岢�����ļ����� 
	struct information_node *tail=NULL;
	struct information_node *head=wordIn(&cnt_word);
	
	int choosingNumber1;//������Χѡ����� 
	int choosingNumber2;//���ʱ��й���ѡ�� 
	int cnt_newWord;//¼���µ��ʹ������µ�������ͳ�Ʊ��� 
	
	//��ӭ�ʺ����� 
	printf("**********************************\n	��ˮʯ��\n**********************************\n\n"); 
	//Ŀ�깦�ܲ˵����б�
	while(1){
		printf("0 �µĵ���¼��\n");
		printf("1 ��ʼ��ϰ����\n");
		printf("2 ��������ͳ��\n"); 
		printf("3 �˳�����\n"); 
		printf("������Ŀ�깦����ţ�");
		//¼�빦��ѡ����� 
		scanf("%d",&choosingNumber1);
		printf("\n");
		//Ŀ�깦��ѡ�� 
		switch(choosingNumber1){
			case 0:
				printf("���ܣ��µĵ���¼��\n");
				cnt_newWord=0;
				head=newWordInsert(head,&cnt_newWord);
				printf("�µĵ���¼��ɹ�  ����¼���µ���������%d��\n\n",cnt_newWord);
				cnt_word+=cnt_newWord;//����������������ӵ����� 
				break;
			case 1:
				printf("���ܣ���ϰ��ʷ���뵥��\n");
				printf("��ѡ��ϰ��ʽ \n0)�Ժ���Ӣ\n1)��Ӣ�� ��");
				scanf("%d",&choosingNumber2); 
				printf("\n");
				reciteWord(choosingNumber2,cnt_word,head);
				break;
			case 2:
				printf("���ܣ���������ͳ������\n");
				dataCount(cnt_word,head);
				break;
			case 3:
				printf("���ܣ��˳�����\n");
				word_output(cnt_word,head);
				exit(0); 
		}
	}
} 

/*�ļ�����Ϣ����������
��������������������ַ ����ֵ�������ͷ����ַ*/
struct information_node * wordIn(int *cnt){
	FILE *fp;
	*cnt=0;
	
	if((fp=fopen("���ʿ�.txt","r"))==NULL){
		printf("���ʴ����ļ������� �����½��ļ���\n");
		return NULL;//���ļ������� ���½��ļ� 
	}
	
	struct information_node *head,*tail,*word;
	int size = sizeof(struct information_node);
	
	head=tail=NULL;
	//¼���ļ�����Ϣ 
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
		printf("�ر��ļ�ʧ�ܣ�");
		exit(0);
	}
	//��������ͷ��ַ 
	return head;
}

/*�µ��ʲ��빦�ܺ���
����������ͷ��㡡����ֵ���²���ĵ��ʸ���*/ 
struct information_node * newWordInsert(struct information_node *head,int *cnt_newWord){
	FILE *fp;//�����ļ�ָ��
	//�½��ƶ���β���µ�������ڵ� 
	struct information_node *p=head,*tail=NULL,*newWord=NULL;
	int size=sizeof(information_node);//��̬����ռ�׼�� 
	int first=1;//������ʾ�� ������һ�ο��Ʊ��� 
	
	//��β�����λ 
	if(head==NULL){
		//��Ԥ���ļ� ����׽ڵ㲻���� 
		tail=NULL;
	} else{
		//��Ԥ���ļ� �׽ڵ���� 
		while(p->next!=NULL){
			tail=p;
			p=p->next;
		}
	}
	
	//¼���µ���  
	if((fp=fopen("���ʿ�.txt","a"))==NULL){
		printf("���ʿ�����Ϣ����ʧ�ܣ�");
		exit(0); 
	} 
	printf("��¼���µĵ��� ÿ�������Իس���β\n���һ������¼�����ʱ�����뵥����commend_end�Խ����µ���¼�룡\n\n"); 
	while(1) {
		//�µ��ʲ��뼰�µ�����Ϣ��ȡ 
		//��̬����ÿ���½ڵ�Ŀռ� 
		newWord=(struct information_node*)malloc(size); 
		//¼���µĵ��� 
		printf("�������µ��ʣ�");
		scanf("%s",newWord->wordName);
//		gets(newWord->wordName); 
		//���뵥����Ϊcommend_end ��ֹ 
		if(strcmp(newWord->wordName,"commend_end")==0) {
			break;
		}
		//�µ�������������ʾ������һ�� 
		if(first==1){
			printf("�������ԷֺŸ��� �м䲻�ɴ��С� �� ���ɳ���40�ַ�\n");
			first=0;
		} 
		printf("�������µ������壺");
		scanf("%s",newWord->wordMean);
//		gets(newWord->wordMean); 
		//�µ���ͳ����Ϣ��ʼ��
		newWord->cnt_correct=0;newWord->cnt_wrong=0;newWord->cnt_answer=0; 
		//�µĵ��ʼ������� 
		newWord->next=NULL;
		if(head==NULL){
			head=newWord;//�½��Ϊ������׽ڵ� 
		}else{
			tail->next=newWord;//�½�����ǿ�����β�� 
		}
		//����β�ڵ�Ϊ�½ڵ� 
		tail=newWord;
		printf("�µ��ʣ�%s ����ɹ�\n\n",newWord->wordName); 
		//�µ�����++ 
		(*cnt_newWord)++;
		//���µĵ�����Ϣд���ļ���
		fprintf(fp,"%s %s %d %d %d\n",newWord->wordName,newWord->wordMean,newWord->cnt_correct,newWord->cnt_wrong,newWord->cnt_answer); 
	}
	//�ر��ļ�
	if(fclose(fp)){
		printf("δ�������ر��ļ���");
		exit(0); 
	} 
	return head;
} 

/*���ʸ�ϰ���ܺ���
��������ϰ����ѡ�����choosingNumber2,����ͷ���ڵ��ַ ����ֵ����*/
void reciteWord(int choosingNumber2,int cnt_word,struct information_node *head){
	//����ͳ�Ʊ��� ,ѭ�����Ʊ��� 
	int cnt_c=0,cnt_w=0,cnt_a=0,i; 
	//��������
//	const int CNT=cnt_word; 
	//�Ժ���Ӣ���з�ʽ 
	if(choosingNumber2==0){
		//��ʱ����Ϊ���� 
		srand((int)time(0));
		printf("�Ժ���Ӣ��ϰ�ʻ㷽ʽ ����commend_end�Խ�����ϰ\n\n");
		while(1){
			//ȡ���� 0~�������-1 ��Χ����������� 
			int random=rand()%cnt_word;
//			int random=rand()%4;//���� 
//			random=random==0?random:random-1;
			
			//ȡ�������ַ������ 
//			struct information_node *answer_word=head+random;
			struct information_node *answer_word=head;
			for(i=0;i<random;i++){
				answer_word=answer_word->next;
			}
			//����ش�ĵ���
			char answer[20];
			
			printf("���壺%s\n",answer_word->wordMean);
			scanf("%s",answer);
			if(strcmp(answer,answer_word->wordName)==0){
				printf("��ȷ��\n\n");
				cnt_c++;cnt_a++;
				//��ȷ������ش����+1 
				answer_word->cnt_answer++;answer_word->cnt_correct++; 
			}else if(strcmp(answer,"commend_end")==0){
				break;
			}else{
				printf("���� ��ȷ��Ϊ��%s\n\n",answer_word->wordName);
				cnt_w++;cnt_a++;
				//���������ش����+1 
				answer_word->cnt_answer++;answer_word->cnt_wrong++;  
			}
		}
		printf("���ܽ��� ���θ�ϰ %d �ʻ� ��ȷ��%d ����%d ��ȷ�ʣ�%.1f%%\n\n",cnt_a,cnt_c,cnt_w,100.0*cnt_c/cnt_a); 	
	}else if (choosingNumber2==1){
		//��ʱ����Ϊ���� 
		srand((int)time(0));
		printf("��Ӣ�𺺸�ϰ�ʻ㷽ʽ ����commend_end�Խ�������\n\n");
		while(1){
			//ȡ���� 0~�������-1 ��Χ����������� 
			int random=rand()%cnt_word;
//			random=random==0?random:random-1;
			
			//ȡ�������ַ������ 
//			struct information_node *answer_word=head+random;
			struct information_node *answer_word=head;
			for(i=0;i<random;i++){
				answer_word=answer_word->next;
			}
			//����ش������ 
			char answer[40];
			
			printf("���ʣ�%s\n",answer_word->wordName);
			scanf("%s",answer);cnt_a++;
			if(strcmp(answer,"commend_end")==0)break; 
			printf("���壺 %s\n\n",answer_word->wordMean);
		}
		printf("���ܽ��� ���θ�ϰ %d �ʻ�\n\n",cnt_a);
	}
}

/*ѡ������������б���
���� �������������ṹ��������,��ʽѡ����� ����ֵ:��*/
void choosingSort(int cnt_word,int choosingNumber3,struct information_node *sorting_word) {
	int i,j;//ѭ�����Ʊ���
	int index_max;//�����ű���
	struct information_node temp;//�����ṹ����� 
	 
	for (i=0;i<cnt_word;i++){
		index_max=i;
		for(j=i;j<cnt_word;j++){
			if(choosingNumber3==0){//�Իش�������� 
				if(sorting_word[j].cnt_answer>sorting_word[index_max].cnt_answer){
					index_max=j;
				}
			}else if(choosingNumber3==1){//����ȷ�������� 
				if(sorting_word[j].cnt_correct>sorting_word[index_max].cnt_correct){
					index_max=j;
				}
			}else if(choosingNumber3==2){//�Դ���������� 
				if(sorting_word[j].cnt_wrong>sorting_word[index_max].cnt_wrong){
					index_max=j;
				}
			}else{//����ȷ������ 
				if(1.0*sorting_word[j].cnt_correct/sorting_word[j].cnt_answer>1.0*sorting_word[index_max].cnt_correct/sorting_word[index_max].cnt_answer){
					index_max=j;
				}
			}
		}
		//�ṹ���ڲ���Ϣ���� 
		temp=sorting_word[i];
		sorting_word[i]=sorting_word[index_max];
		sorting_word[index_max]=temp;
	}
	//����б���Ϣ 
	printf("         ����  	     ��ȷ����    �ش����      ��ȷ��\n"); 
	for(i=0;i<cnt_word;i++){
		printf("%15s %10d %10d %14.1f%%\n",sorting_word[i].wordName,sorting_word[i].cnt_correct,sorting_word[i].cnt_answer,100.0*sorting_word[i].cnt_correct/sorting_word[i].cnt_answer) ;
	}
}

/*�������ݱ��������
���� ����������������ͷ����ַ������ֵ����*/
void dataCount(int cnt_word,struct information_node * head){
	printf("0)�Իش��������\n");
	printf("1)����ȷ��������\n");
	printf("2)�Դ����������\n");
	printf("3)�Իش���ȷ�ʽ�������\n"); 
	printf("�����뼼���������б��������ݣ�");
	
	struct information_node sorting_word[cnt_word];	//��������洢��Ϣ�������� 
	struct information_node	*p=head;//�洢������ 
	int i,j,choosingNumber3;//ѭ�����Ʊ���,ѡ����� 
	//��������Ϣ¼��ṹ�������� 
	for(i=0;i<cnt_word;i++){
		sorting_word[i]=*p;//�洢�ڵ�
		p=p->next;//�ڵ��ƶ� 
	}
	scanf("%d",&choosingNumber3) ;//¼��ѡ����� 
	printf("\n"); 
	choosingSort(cnt_word,choosingNumber3,sorting_word) ;
	printf("\n�����Ϣ������\n\n"); 
}

/*�����ѱ����Ϣд���ļ�����
����������ͷ�ڵ��ַ �������� ����ֵ����*/ 
void word_output(int cnt_word,struct information_node *head ){
	FILE *fp;
	int i;//ѭ�����Ʊ��� 
	struct information_node *p=head;//�ڵ㴢��ָ�� 
	
	if((fp=fopen("���ʿ�.txt","w"))==NULL){
		printf("���ļ�ʧ�ܣ�");
		exit(0);
	} 
	for(i=0;i<cnt_word;i++){
		//���ڵ���Ϣд���ļ��� 
		fprintf(fp,"%s %s %d %d %d\n",p->wordName,p->wordMean,p->cnt_correct,p->cnt_wrong,p->cnt_answer);
		p=p->next;//�ڵ�����ƶ� 
	}
	if(fclose(fp)){
		printf("�ر��ļ�ʧ�ܣ�");
		exit(0);
	}
} 
