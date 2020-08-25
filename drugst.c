/*AUTHORS: L. SUSHMA  P. TEJASWINI
PROJECT NAME: DRUG STORE MANAGEMENT*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	struct node *children[26];
	int is_end_of_word;
	int val;
	int price;
};
struct node* getNode()
{
	int i;
	struct node *p=(struct node*)malloc(sizeof(struct node));
	p->is_end_of_word=0;
	p->val=0;
	p->price=0;
	for(i=0;i<26;i++)
	p->children[i]=NULL;
	return p;
}
void insert(struct node *root,char key[],int v,int pric)
{
	struct node *q=root;
	int l,index;
	int len=strlen(key);
	for(l=0;l<len;l++)
	{
		index=(int)key[l]-(int)'a';
		if(!q->children[index]){
		q->children[index]=getNode();}
		q=q->children[index];
	}
	q->is_end_of_word=1;
	q->val=v;
	q->price=pric;
}
int search(struct node *root,char key[])
{
	int len,l,index;
	len=strlen(key);
	struct node *q=root;
	for(l=0;l<len;l++)
	{
	   index=key[l]-'a';
	   if(q->children[index]==NULL)
	   return 0;
	   q=q->children[index];	
	} 
	if(q!= NULL&&q->is_end_of_word)printf("drug: %s   \nquantity: %d\nprice: $%d\n",key,q->val,q->price);
	if(q->val==0)printf("*****OUT OF STOCK*******\n");
	return (q!= NULL&&q->is_end_of_word);
}
int update(struct node *root,char key[],int x)
{
	int len,l,index;
	len=strlen(key);
	struct node *q=root;
	for(l=0;l<len;l++)
	{
	   index=key[l]-'a';
	   if(q->children[index]==NULL)
	   return 0;
	   q=q->children[index];	
	} 
	if(q!= NULL&&q->is_end_of_word)
	{
		q->val=q->val-x;
		if(q->val<0)printf("***ERROR***\n");
		return q->val;
	}
}
int isLastNode( struct node *root)
{
	int i,flag=0;
	struct node *q;
	q=root;
	for(i=0;i<26;i++) 
		if(q->children[i])
		return 0;
	return q->val; 
} 
int suggestionsRec(struct node *root, char currPrefix[]) 
{ 
	int i,xx,yy;
	char letter;
	if (root->is_end_of_word) 
	{ 
		printf("\n%s\t",currPrefix);
		printf("quantity: %d   price: $%d\n",root->val,root->price);
		if(root->val==0)
		printf("\n***  %s OUT OF STOCK  ***\n",currPrefix);
	} 
	if (isLastNode(root)) 
		return root->val; 
	for(i=0;i<26;i++) 
	{ 
		if (root->children[i]) 
		{ 
			letter=('a'+i);
			xx=strlen(currPrefix);
			currPrefix[xx]=letter;
			currPrefix[xx+1]='\0';
			suggestionsRec(root->children[i],currPrefix); 
			yy=strlen(currPrefix);
			currPrefix[yy-1]='\0';
		} 
	} 
} 
int printAutoSuggestions(struct node* root, char query[]) 
{ 
	struct node *q=root; 
	char prefix[50];
	int level,index; 
	int n = strlen(query);
	for (level=0;level<n;level++) 
	{ 
		index = query[level]-'a'; 
		if (!q->children[index]) 
			return 0; 
		q = q->children[index]; 
	} 
	int isWord = (q->is_end_of_word== 1); 
	int isLast = isLastNode(q); 
	if (isWord && isLast) 
	{ 
	printf("%s\t",query);
	printf("quantity: %d     price: $%d\n\n",isLast,q->price);
		return -1; 
	} 
	if (!isLast) 
	{ 
	  strcpy(prefix,query); 
		suggestionsRec(q, prefix); 
		return 1; 
	} 
} 
int isEmpty(struct node* root) 
{ 
int i;
    for (i=0;i<26;i++) 
        if (root->children[i]) 
            return 0; 
    return 1; 
} 
struct node* r(struct node* root, char key[], int depth) 
{ 
    if (!root) 
        return NULL; 
    int len =strlen(key);
    if (depth == len) { 
        if (root->is_end_of_word) 
            root->is_end_of_word = 0; 
        if (isEmpty(root)) { 
            free(root);
			root = NULL; 
        } 
  
        return root; 
    }
	int index = key[depth] - 'a'; 
    root->children[index] =  
          r(root->children[index], key, depth + 1); 
   if (isEmpty(root) && root->is_end_of_word == 0) { 
        free(root);
		root = NULL; 
    } 
    return root; 
}
int js(int p[20],int d[20],int j[20],int n,int dmax,int tss[])
{
	int ts[20],i,pf,k;
	int x;
	for(i=1;i<=dmax;i++)
	{
		ts[i]=-1;
	}
	j[1]=1;
	//pf=p[1];
	ts[d[1]]=1;
	/*for(i=1;i<=dmax;i++)
	{
	printf("ts[%d]: %d\n",i,ts[i]);
	}*/
	pf=0;
	int mmm=0;
	for(i=1;i<=n;i++)
	{
		if(d[i]==0&&mmm<p[i])
		{
			ts[1]=i;
			pf=p[i];
			//printf("if  j%d: %d\n",i,p[i]);
			//printf("profit: %d\n",pf);
			break;
		}
	}
	if(ts[1]<0)
	pf=p[1];
	for(i=2;i<=n;i++)
	{
			if(ts[d[i]]==-1){
				ts[d[i]]=i;
				pf+=p[i];
				//printf("if  j%d: %d\n",i,p[i]);
				//printf("profit: %d\n",pf);
			}
			else
			{
				k=d[i]-1;
				while(k>0)
				{
					if(ts[k]==-1){
						//printf("else    j%d: %d\n",i,p[i]);
						//printf("profit: %d\n",pf);
						ts[k]=i;
						pf+=p[i];
						break;
					}
					k--;
				}
			}
			/*for(x=1;x<=dmax;x++)
			{
			printf("ts[%d]: %d\n",x,ts[x]);	
			}*/
	}
	for(x=1;x<=dmax;x++){
		//printf("ts[%d]: %d\n",x,ts[x]);
	tss[x]=ts[x];
	}
	//printf("profit: %d\n",pf);
	return pf; 
}
int updatereq(struct node *root,char key[],int quan,int* pp)
{
	int len,l,index;
	len=strlen(key);
	struct node *q=root;
	for(l=0;l<len;l++)
	{
	   index=key[l]-'a';
	   if(q->children[index]==NULL)
	   return 0;
	   q=q->children[index];	
	} 
	if(q!= NULL&&q->is_end_of_word)
	{
		q->val=q->val-quan;
		*pp=q->price;
	//	printf("pp: %d   price: %d\n",*pp,q->price);
		if(q->val<0)return -1;
		return q->val;
	}
}
void fr(struct node *root,char fname[],int ra[],int d[],int num)
{
	FILE *fp;
	char buff[500];
	int quan,x,pro;
	fp=fopen(fname,"r");
		ra[num]=0;
	if(fp!=NULL)
	{
		//printf("in if\n");
		fscanf(fp, "%s %d", buff,&quan);
		d[num]=quan;
		while(fscanf(fp, "%s %d", buff,&quan)!=EOF)
		{  
    		printf("%s %d\n", buff,quan );
			x=updatereq(root,buff,quan,&pro);
		//	printf("quan: %d   p: %d\n",quan,pro);
			if(x<0)
			{
				ra[num]=-1;
				return;
			}
			else
			{
				ra[num]+=pro*quan;
			}
    	}	
    }
	else
	{
		printf("an error in request file\n");
	}
	fclose(fp);
	return;	
}
void sort(int a[],int b[],char f[100][100],int n)
{
	int i,j,temp;
	char temps[100];
	for(i=1;i<=n;i++)
	{
		for(j=i+1;j<=n;j++)
		{
			if(a[i]<a[j])
			{
				temp=a[i];a[i]=a[j];a[j]=temp;
				temp=b[i];b[i]=b[j];b[j]=temp;
				strcpy(temps,f[i]);
				strcpy(f[i],f[j]);
				strcpy(f[j],temps);	
			}
		}
	}
}
int main() 
{ 
	struct node* root = getNode(); int tss[50];
	FILE *fp,*fp1,*fp2;
	char str[5000],ctr='a';int count=1,counter=0;
	int ch=0,i,flag=0,ppp,qqq;
	int x,xx,v;
	char alp[2000];
	srand(time(0)); 
	fp=fopen("D:\\pteja\\start\\drugnames1.txt", "r");
	fp1=fopen("D:\\pteja\\start\\drugquanti.txt","r");
	fp2=fopen("D:\\pteja\\start\\drugprice.txt","r");
	if ( fp == NULL ) 
    { 
        printf( "check the file is correct\n" ) ; 
    } 
    else
    { 
		while(ctr!='Z')
		{			
			i=0;
        	while ((ctr=fgetc(fp))!=' ') 
       		{
       			if(ctr=='Z'){
       				flag=1;
       				break;
				   }
       			str[i++]=ctr;
		  
    		}
    		str[i]='\0';
    		fscanf(fp1,"%d",&qqq);
    		fscanf(fp2,"%d",&ppp);
			insert(root,str,qqq,ppp);
			counter++;
			if(flag==1)break;
		}
		fclose(fp);
	}
	//printf("\n\ncounter: %d\n",counter);
	insert(root,"pencilin",0,89);
	int opt=1;
	printf("***********DRUG STORE****************\n1) TO CHECK THE STOCKS\n2) TO SUPPLY REQUESTS\n");
	scanf("%d",&v);
	if(v==1){
	printf("enter '1' to search a prefix of a drug\n\n");
	printf("enter '2' to update the no of items of drug\n\n");
	printf("enter '3' to add a new drug\n\n");
	printf("enter '4' to delete a drug\n\n");
	printf("enter '5' to search a drug present or not\n\n");
	printf("enter '-1' to quit\n\n");
    while(opt>0)
    {
    	printf("\nenter valid opt\n\n");scanf("%d",&opt);
		switch (opt)
		{	
    		case 1: printf("\nenter prefix of drug to search\n\n");
    				scanf("%s",alp);
    				int comp = printAutoSuggestions(root,alp); 
    				if(comp==0)printf("\nno such drug available\n");
    		
        		break;
    		case 2: printf("\nenter the drug to be updated\n");
    				scanf("%s",alp);
    				printf("\nthe val to update \n\nenter '0' to decrease the quantity \n\nenter '1' to increae the quantity \n");
    				scanf("%d",&xx);
    				scanf("%d",&ch);
    				if(xx==1)(ch=(-1)*ch);
    				x=search(root,alp);
					//printf("search: %d\n",x);
    				if(x<=0){
					printf("\nno such drug present in the store\n");
    				break;
    				}
    				else
					printf("%d\n",update(root,alp,ch));
        		break;
        	case 3: printf("\nnew drug to be added\n");
        			scanf("%s",alp);
        			printf("\nenter the quantity and price\n");
        			int pric;
        			scanf("%d%d",&ch,&pric);
        			if(search(root,alp)){
					printf("\nthe drug is already present in the store\n");
					break;
					}
        			insert(root,alp,ch,pric);
        		break;
        	case 4: printf("\nenter the drug to be removed\n");
        			scanf("%s",alp);
        			if(!search(root,alp))printf("no such drug is present\n");
        			else{
        				r(root,alp,0);
        				printf("the drug is removed\n");
					}
        		break;
        	case 5: printf("\nenter the drug to be searched\n");
        			scanf("%s",&alp);
        			x=search(root,alp);
        			if(x){
					//printf("drug is present\n");
					}
        			else printf("\nno such drug is avialable\n");
        		break;

   			default: if(opt!=-1)printf("\nno such opt there\n");
		}	
	}
}
 else if(v==2)
{
	printf("**************   START   OF   THE   DAY   *****************\n\n");
	int numreq,len,d[50],dmax,job[50],value;
	char filename[100],fnames[100][100];
	printf("enter how many req\n");
	scanf("%d",&numreq);
	int p[100];
	for(i=1;i<=numreq;i++)p[i]=0;
	for(i=1;i<=numreq;i++)
	{
	strcpy(filename,"D:\\\\pteja\\\\start\\\\file");
	len=strlen(filename);
	filename[len]='a'+i-1;
	filename[len+1]='.';filename[len+2]='t';	filename[len+3]='x';filename[len+4]='t';filename[len+5]='\0';
	len=strlen(filename);
	printf("\n\n%s\n\n",filename);
	fr(root,filename,p,d,i);
	strcpy(fnames[i],filename);
	}
	dmax=0;
	printf("\n\n\n\n");
	for(i=1;i<=numreq;i++)
	{
		//printf("profit: %d   d: %d\n",p[i],d[i]);
		if(dmax<d[i])dmax=d[i];
	}
	sort(p,d,fnames,numreq);
	//int flag1=0;
	printf("profit\t\t\t\tdeadline\t\t\tRequst fanme\t\t\t\t\t\n");
	printf("=========================================================================================\n");
	for(i=1;i<=numreq;i++)
	{
		if(d[i]==0)
		printf("%d\t\t\t\tEMERGENCY\t\t\t%s\n",p[i],fnames[i]);
		else
		printf("%d\t\t\t\t%d\t\t\t\t%s\n",p[i],d[i],fnames[i]);
		//if(dmax<d[i])dmax=d[i];
	}
	value=js(p,d,job,numreq,dmax,tss);
	int z;
	for( z=1;z<dmax;z++)
	{
		FILE *gp;
		gp=fopen(fnames[z],"a");
		if(gp)
		{
			fprintf(gp,"%s","YOUR ORDER IS PLACED:)\n");
		}
		else printf("error");
	}
	printf("=========================================================================================\n\n");
	printf("\n\n********** THE   GAINED   PROFIT   IS   $ %d *****************\n",value);
	FILE *hgr,*fof;
	int numb;
	char sstr[1000];
	hgr=fopen("D:\\pteja\\start\\resultfile.txt","w");
	fprintf(hgr,"********************** TODAY'S SALE ANALYSIS **************************\n");
	for(x=1;x<=dmax;x++){
		//printf("ts[%d]: %d\n",x,ts[x]);
		//tss[x]=ts[x];
		//printf("\ntss[%d]: %d\n",x,tss[x]);
		//printf("\n%s\n\n",fnames[tss[x]]);
		fprintf(hgr,"\n%s\n",fnames[tss[x]]);
		fof=fopen(fnames[tss[x]],"r");
		if(fof!=NULL)
		{
			//printf("in if\n");
			while(fscanf(fof,"%s %d",sstr,&numb)!=EOF)
			{
				//printf("loop\n");
				//printf("%s   %d\n",sstr,numb);
				fprintf(hgr,"%s %d\n",sstr,numb);	
			}
			strcpy(sstr,"\n************profit: $");
			fprintf(hgr,"%s %d",sstr,p[tss[x]]);
			strcpy(sstr,"***************\n");
			fprintf(hgr,"%s",sstr);
			fclose(fof);	
		}
		else
		{
			strcpy(sstr,"~~~~~~~~FREEE HOUR~~~~~~~~~~~\n");
			fprintf(hgr,"%s",sstr);
		}
	}
	strcpy(sstr,"\n=======================================\n");
	fprintf(hgr,"%s",sstr);
	strcpy(sstr," THE   GAINED   PROFIT   IS   $  ");
	fprintf(hgr,"%s",sstr);
	fprintf(hgr,"%d",value);
	strcpy(sstr,"\n");
	fprintf(hgr,"%s",sstr);
	strcpy(sstr,"=======================================\n");
	fprintf(hgr,"%s",sstr);
}
else{
	printf("\n\n************INVALID OPTION***********\n");
}
	return 0; 
}
