#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#define BASE_URL "www.chitkara.edu.in"
#define SEED_URL "http://www.chitkara.edu.in/"
#define Url_length 1000


 
struct node{
   int depth;
   char *url;
   int visited;
   int key;
   struct node *next;
   struct node *prev;
}*head=NULL;

struct keyword{
     char *word;
     int keys; 
     struct keyword *next;
     struct file *file_head;
}*head1=NULL,*hash_array1[100] = {NULL};

struct file{
     char *filename;
     int occur;
     int count;
     struct keyword *next;
     struct keyword *prev;
}*head2=NULL;


int hash_key(int str_len){
     int key1;
     key1 = str_len;
     return key1;    
}


//make a linklist for file names and no. of occurances of letters
/*struct filename* add_to_file_list(){
               struct filename *temppp;
               temppp=(struct keyword*) malloc(sizeof(struct keyword));
               if(head2==NULL){
                 struct filename
 } 



}*/

//making a linklist for words
struct keyword* add_to_wordlist(char *name,int key){
struct keyword *tempp;
     tempp = (struct keyword*) malloc(sizeof(struct keyword));
	memset(tempp,0,1);
     if(head1 == NULL){
     struct keyword* new_node1 = (struct keyword*) malloc(sizeof(struct keyword));
	memset(new_node1,0,1);
     new_node1->word = (char*)malloc(sizeof(char)*100);
     memset(new_node1->word,0,100);
     strcpy(new_node1->word,name);
     new_node1->file_head = NULL;
     new_node1->keys = key;
     new_node1->next = NULL;
     head1 = new_node1;
     return head1;
}
     else if(head1 !=NULL){
           tempp = head1;
           while(tempp->next != NULL&&tempp->keys != key){
               tempp = tempp->next;
}
         if(tempp->keys == key){
           while(tempp->next != NULL&&tempp->next->keys == key){
            tempp = tempp->next;
       }
       }
           struct keyword* new_node1 = (struct keyword*) malloc(sizeof(struct keyword));
		memset(new_node1,0,1);           
           new_node1->word = (char*)malloc(sizeof(char)*100);
           memset(new_node1->word,0,100);
           strcpy(new_node1->word,name);
           new_node1->file_head = NULL;
           new_node1->keys = key;
           new_node1->next = tempp->next;
           tempp->next = new_node1;
           return new_node1;           
}
}


//making a linklist for files
struct keyword* list_files(char *name,struct keyword *duphead){
struct file *tempp;
     tempp = (struct file*) malloc(sizeof(struct file));
     memset(tempp,0,1);
     if(duphead->file_head == NULL){
     struct file* new_node1 = (struct file*) malloc(sizeof(struct file));
      memset(new_node1,0,1);
     new_node1->filename = (char*)malloc(sizeof(char)*300);
     memset(new_node1->filename,0,300);
     strcpy(new_node1->filename,name);
     new_node1->count= 1;
     new_node1->next = NULL;
     duphead->file_head = new_node1;
}
     else if(duphead->file_head !=NULL){
           tempp = duphead->file_head;
           while(tempp->next != NULL){
               tempp = tempp->next;
}          
           if(strcmp(tempp->filename,name)!=0){
           struct file* new_node1 = (struct file*) malloc(sizeof(struct file));
           memset(new_node1,0,1);           
           new_node1->filename = (char*)malloc(sizeof(char)*300);
           memset(new_node1->filename,0,300);
           strcpy(new_node1->filename,name);
           new_node1->count= 1;
           new_node1->next = tempp->next;
           tempp->next = new_node1;
         }
            else{
                   tempp->count = tempp->count + 1;
}
                      
}
return duphead;
}

//making a linklist for urls.
struct node* make_a_linklist(int Depth,char *URL,int k){
     struct node *temp,*new_node,*temp1;
     temp1 =head;
     temp = (struct node*)malloc(sizeof(struct node));
      memset(temp,0,1);
     if(head == NULL){
     new_node = (struct node*)malloc(sizeof(struct node));
     memset(new_node,0,1);
     new_node->url = (char*)malloc(sizeof(char)*1000);
      memset(new_node->url,0,1000);
     new_node->depth = 0;
     strcpy(new_node->url,URL);
     new_node->visited = 0;
     new_node->next = NULL;
     new_node->prev = NULL;
     new_node->key = k;
     head = new_node;
     
}
    else if(head != NULL){
      temp = head;
       while(temp->key != k && temp->next != NULL){
             temp = temp->next;
} 
       if(temp->key == k){
           while(temp->next != NULL&&temp->next->key == k){
            temp = temp->next;
       }
       }
        new_node = (struct node*)malloc(sizeof(struct node));
        memset(new_node,0,1);
        new_node->url = (char*)malloc(sizeof(char)*1000);
        memset(new_node->url,0,1000);
        new_node->depth = Depth; 
        strcpy(new_node->url,URL);
        new_node->visited = 0; 
        new_node->key = k;
        new_node->next = temp->next;
        new_node->prev = temp;
        temp->next = new_node;
        if(new_node->next != NULL)
        new_node->next->prev = new_node;
}                 
}

//checks if the directory chitkara search exists or not.
int testDir(char *dir)
{
  struct stat statbuf;
  if ( stat(dir, &statbuf) == -1 ) 
  {
    fprintf(stderr, "-----------------\n");
    fprintf(stderr, "Invalid directory\n");
    fprintf(stderr, "-----------------\n");
    return 0;
  }

  //Both check if there's a directory and if it's writable
  if ( !S_ISDIR(statbuf.st_mode) ) 
  {
    fprintf(stderr, "-----------------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
    fprintf(stderr, "-----------------------------------------------------\n");
    return 0;
  }

  if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR ) 
  {
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. It isn't writable\n");
    fprintf(stderr, "------------------------------------------\n");
    return 0;
  }
return 1;
}

//fetches a page and print the data in file temp.
int fetchpage(char *URL){
char urlbuffer[Url_length+1000] = {0};
strcat(urlbuffer,"wget ");
strcat(urlbuffer,URL);
strcat(urlbuffer," -O /home/administrator/chitkarasearch/temp.txt ");
system(urlbuffer);
return 1;
}

//fetches a page and print the data in file temp.
/*int spider(char *URL){
char urlbuffer[Url_length+1000] = {0};
strcat(urlbuffer,"wget --spider ");
strcat(urlbuffer,URL);
if(!system(urlbuffer))
return 1;
else 
return -1;
}*/

void NormalizeWord(char* word) {
  int i = 0;
  while (word[i]) {
      // NEW
    if (word[i] < 91 && word[i] > 64) // Bounded below so this funct. can run on all urls
      // /NEW
      word[i] += 32;
    i++;
  }
}

int NormalizeURL(char* URL) 
{
  int len = strlen(URL);
  if (len <= 1 )
    return 0;
  //! Normalize all URLs.
  if (URL[len - 1] == '/') 
  {
    URL[len - 1] = 0;
    len--;
  }
  int i, j;
  len = strlen(URL);
  //! Safe check.
  if (len < 2)
    return 0;
  //! Locate the URL's suffix.
  for (i = len - 1; i >= 0; i--)
    if (URL[i] =='.')
      break;
  for (j = len - 1; j >= 0; j--)
    if (URL[j] =='/')
      break;
  //! We ignore other file types.
  //! So if a URL link is to a file that are not in the file type of the following
  //! one of four, then we will discard this URL, and it will not be in the URL list.
  if ((j >= 7) && (i > j) && ((i + 2) < len)) 
  {
    if ((!strncmp((URL + i), ".htm", 4))
        ||(!strncmp((URL + i), ".HTM", 4))
        ||(!strncmp((URL + i), ".php", 4))
        ||(!strncmp((URL + i), ".jsp", 4))
        ) 
    {
      len = len; // do nothing.
    } 
    else 
    {
      return 0; // bad type
    }
  }
  return 1;
}


void removeWhiteSpace(char* html) 
{
  int i;
  char *buffer = malloc(strlen(html)+1), *p=malloc (sizeof(char)+1);
  memset(buffer,0,strlen(html)+1);
  for (i=0;html[i];i++) 
  {
    if(html[i]>32)
    {
      sprintf(p,"%c",html[i]);
      strcat(buffer,p);
    }
  }
  strcpy(html,buffer);
  free(buffer); free(p);
}

int GetNextURL(char* html, char* urlofthispage, char* result, int pos) 
{
  char c;
  int len, i, j;
  char* p1;  //!< pointer pointed to the start of a new-founded URL.
  char* p2;  //!< pointer pointed to the end of a new-founded URL.

  // NEW
  // Clean up \n chars
  if(pos == 0) {
    removeWhiteSpace(html);
  }
  // /NEW

  // Find the <a> <A> HTML tag.
  while (0 != (c = html[pos])) 
  {
    if ((c=='<') &&
        ((html[pos+1] == 'a') || (html[pos+1] == 'A'))) {
      break;
    }
    pos++;
  }
  //! Find the URL it the HTML tag. They usually look like <a href="www.abc.com">
  //! We try to find the quote mark in order to find the URL inside the quote mark.
  if (c) 
  {  
    // check for equals first... some HTML tags don't have quotes...or use single quotes instead
    p1 = strchr(&(html[pos+1]), '=');
    
    if ((!p1) || (*(p1-1) == 'e') || ((p1 - html - pos) > 10)) 
    {
      // keep going...
      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (*(p1+1) == '\"' || *(p1+1) == '\'')
      p1++;

    p1++;    

    p2 = strpbrk(p1, "\'\">");
    if (!p2) 
    {
      // keep going...
      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (*p1 == '#') 
    { // Why bother returning anything here....recursively keep going...

      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (!strncmp(p1, "mailto:",7))
      return GetNextURL(html, urlofthispage, result, pos+1);
    if (!strncmp(p1, "http", 4) || !strncmp(p1, "HTTP", 4)) 
    {
      //! Nice! The URL we found is in absolute path.
      strncpy(result, p1, (p2-p1));
      return  (int)(p2 - html + 1);
    } else {
      //! We find a URL. HTML is a terrible standard. So there are many ways to present a URL.
      if (p1[0] == '.') {
        //! Some URLs are like <a href="../../../a.txt"> I cannot handle this. 
	// again...probably good to recursively keep going..
	// NEW
        
        return GetNextURL(html,urlofthispage,result,pos+1);
	// /NEW
      }
      if (p1[0] == '/') {
        //! this means the URL is the absolute path
        for (i = 7; i < strlen(urlofthispage); i++)
          if (urlofthispage[i] == '/')
            break;
        strcpy(result, urlofthispage);
        result[i] = 0;
        strncat(result, p1, (p2 - p1));
        return (int)(p2 - html + 1);        
      } else {
        //! the URL is a absolute path.
        len = strlen(urlofthispage);
for (i = (len - 1); i >= 0; i--)
          if (urlofthispage[i] == '/')
            break;
        for (j = (len - 1); j >= 0; j--)
          if (urlofthispage[j] == '.')
              break;
        if (i == (len -1)) {
          //! urlofthis page is like http://www.abc.com/
            strcpy(result, urlofthispage);
            result[i + 1] = 0;
            strncat(result, p1, p2 - p1);
            return (int)(p2 - html + 1);
        }
        if ((i <= 6)||(i > j)) {
          //! urlofthis page is like http://www.abc.com/~xyz
          //! or http://www.abc.com
          strcpy(result, urlofthispage);
          result[len] = '/';
          strncat(result, p1, p2 - p1);
          return (int)(p2 - html + 1);
        }
        strcpy(result, urlofthispage);
        result[i + 1] = 0;
        strncat(result, p1, p2 - p1);
        return (int)(p2 - html + 1);
      }
    }
  }    
  return -1;
}



void save(struct node *tempNode,int m)//creating permanent File 
{
	char a;
	char ptr[500]={0};
	FILE *fp,*fr;
	char itostring[Url_length+300]={0};
	sprintf(itostring,"%d",m);
	strcat(ptr,"/home/administrator/chitkarasearch/");
	strcat(ptr,"file no");
	strcat(ptr,itostring);
	strcat(ptr,".txt");
	fp=fopen(ptr,"w");
	fr=fopen("/home/administrator/chitkarasearch/temp.txt","r");
	fprintf(fp,"%dn%dn%sn",tempNode->depth,tempNode->visited,tempNode->url);
	do
	{
		a=fgetc(fr);
		fputc(a,fp);
	}while(a!=EOF);
	fclose(fr);
	fclose(fp);
}

//creates a new file temp1 and copy the data of temp to temp1.
void create_new_file(char *url){
       FILE *ptr,*p;
       int pos = 0;
       char *result=NULL;
       char *t;
       t = "temp1.txt";
       p = fopen("/home/administrator/chitkarasearch/temp1.txt","w");
       ptr = fopen("/home/administrator/chitkarasearch/temp.txt","r");
       char a;
       do{ 
      a = getc(ptr);
      putc(a,p);
}while(a!=EOF); 
fclose(p);
fclose(ptr);             
}

//takes the text from file temp and takes the text in the string.
char* text_to_string(){
        char *buffer;
        FILE *pfile;
        long Lsize;
        pfile = fopen("/home/administrator/chitkarasearch/temp1.txt","rb");
        fseek(pfile,0,SEEK_END);
        Lsize = ftell(pfile);
        rewind(pfile);
        buffer=(char*)malloc(sizeof(char)*Lsize);
        fread(buffer,1,Lsize,pfile);
        fclose(pfile);
        return buffer;
}


void finding_links(int depth,char* dir,char* url){
       char *buf;
       long int pos=0;
       int k = (int) malloc(sizeof(int));
       int flag = (int) malloc(sizeof(int));
       struct node *hash_array[1000] = {NULL}; 
       struct node *ptr,*ptr1;
       k = hash_key(strlen(url));
       make_a_linklist(0,url,k);
       ptr = head;
        while(ptr != NULL){
               if(ptr->depth<depth && ptr->visited!=1){
                    //if(!spider(url))
                    fetchpage(ptr->url);
                    ptr->visited = 1;
                    ptr->key = hash_key(strlen(ptr->url));
                    k = hash_key(strlen(ptr->url));
                    char* htmlbuffer = text_to_string();
                    char *str = (char*) malloc(sizeof(char)*1000);
                    memset(str,0,1000);
                    int i=0; 
                    while(i != 10){
                          flag=0;   
                          pos = GetNextURL(htmlbuffer,ptr->url,str,pos+1);
                          ptr1 = head; 
                          while(ptr1 != NULL){
                              
                              if(strcmp(ptr1->url,str)==0){
                                   flag=1;
                                   break;
                          }
                           ptr1=ptr1->next;
                                                 
}
                        
                          if(flag == 0){
                          k = hash_key(strlen(str));
                          make_a_linklist(ptr->depth+1,str,k);
                          if(hash_array[k] == NULL){
                              hash_array[k] = ptr;
                              
                     }
} 
                        i++; 
                
}                
                 free(htmlbuffer);  
             }
 ptr = ptr->next; 
}
ptr = head;
}


//making files for all links.
void making_files(){
struct node *temp;
temp = head;
int count = 0;
while(temp->next != NULL){
 count++;
fetchpage(temp->url);
save(temp,count);
temp = temp->next;
}
}


//text to string for other files.
char* text_to_string1(int m){
        char *buffer1;
        char ptr[500]={0};
        FILE *pfile1;
        long Lsize1;
        char itostring[Url_length+300]={0};
        sprintf(itostring,"%d",m);
        strcat(ptr,"/home/administrator/chitkarasearch/");
        strcat(ptr,"file no");
        strcat(ptr,itostring);
        strcat(ptr,".txt");
        pfile1 = fopen(ptr,"r");
        fseek(pfile1,0,SEEK_END);
        Lsize1 = ftell(pfile1);
        rewind(pfile1);
        buffer1=(char*)malloc(sizeof(char)*Lsize1);
        fread(buffer1,1,Lsize1,pfile1);
        fclose(pfile1);
        return buffer1;
}


int get_next_word(char *htmlbuffer,char* res1,int pos1){
     char c;
     int len,i,j;
     char* p11;     //pointer pointed to the start of a new founded word.
     char* p22;    //pointer pointed to the end of a new founded word.
     c=htmlbuffer[pos1];
//find the <title> HTML tag.
while(c != '\0'){
        c=htmlbuffer[pos1];
       if((c=='>') && ((htmlbuffer[pos1-6] != '/') &&(htmlbuffer[pos1-5] == 't') && (htmlbuffer[pos1 - 4] == 'i')&&(htmlbuffer[pos1-3] == 't')&&(htmlbuffer[pos1-2] == 'l')&&(htmlbuffer[pos1-1] == 'e')))
{      
        break;
}
if((c=='"')&&((htmlbuffer[pos1-1] == '=')&&(htmlbuffer[pos1-2] == 'e')&&(htmlbuffer[pos1-3] == 'l')&&(htmlbuffer[pos1-4] == 't')&&(htmlbuffer[pos1-5] == 'i')&&(htmlbuffer[pos1-6] == 't'))){
break;
}
pos1++;
}
i=0;
if(c=='>'){
pos1++;
while(c!='<'){
c = htmlbuffer[pos1];
res1[i] = c;
pos1++;
i++;
}
}
if(c=='"'){
pos1++;
c = htmlbuffer[pos1];
while(c!='"'){
c = htmlbuffer[pos1];
res1[i] = c;
pos1++;
i++;
}
}
res1[i-1] = '\0';
return pos1;
}


//to implement the strpok1 function
void strpok1(char *res1,char*name){
      int flag=0;
      static int count=0;
      int key = 0;
     struct keyword* duphead = (struct keyword*) malloc(sizeof(struct keyword));
     memset(duphead,0,1);
     struct keyword* templ = (struct keyword*) malloc(sizeof(struct keyword));
     memset(templ,0,1);
     char* temp = (char*)malloc(sizeof(char)*100);
     memset(temp,0,100);
        temp=strtok(res1," ");
        templ = head1;
         while(templ != NULL && temp != '\0'){
              if(strcmp(temp,templ->word)==0){
              flag = 1;
              list_files(name,templ);
              break;
              }
              templ = templ->next;
           } 
         while(temp != '\0'){
             if(flag == 0){
             key = hash_key(strlen(temp));          
             duphead=add_to_wordlist(temp,key);
             if(hash_array1[key]==NULL)
             hash_array1[key] = duphead;
             list_files(name,duphead);
             }
             temp = strtok(NULL," ");
             flag = 0;
             templ = head1;
             while(templ != NULL && temp != '\0'){
              if(strcmp(temp,templ->word)==0){
              list_files(name,templ);
              flag = 1;
              break;
              }
              templ = templ->next;
           }     
}
templ = head1;

}


//gather words for indexer.
void gather_words(){
int i=0;
int pos1=0;
int j=1;
char itostring[Url_length+300]={0};
char *res1 = (char*)malloc(sizeof(char)*100);
memset(res1,0,100);
while(j<9){
char *file_name = (char*)malloc(sizeof(char)*100);
memset(file_name,0,100);
i=0;
char *htmlbuffer = text_to_string1(j);
sprintf(itostring,"%d",j);
strcat(file_name,"file no");
strcat(file_name,itostring);
puts(file_name);
while(i<12){
pos1 = get_next_word(htmlbuffer,res1,pos1+1);
strpok1(res1,file_name);
i++;
}
j++;
}
}



/*void printwordlist(){
struct keyword* temp;
temp = (struct keyword*) malloc (sizeof(struct keyword));
memset(temp,0,1);
temp = head1;
while(temp != NULL){
puts(temp->word);
temp = temp->next;
}
}*/

void printfilelist(){
struct file* temp;
struct keyword* temp1;
temp1 = (struct keyword*) malloc (sizeof(struct keyword));
memset(temp1,0,1);
temp = (struct file*) malloc (sizeof(struct file));
memset(temp,0,1);
temp1 = head1;
temp = temp1->file_head;
while(temp1 != NULL){
temp = temp1->file_head;
puts(temp1->word);
while(temp!=NULL){
puts(temp->filename);
printf("%d\n",temp->count);
temp = temp->next;
}
temp1 = temp1->next;
}
//while(temp != NULL){
//puts(temp->filename);
//temp = temp->next;
//}
}


//saving the files to hash table.
void save_hash_to_file(){
int i=0;
struct keyword *temppp[100]={NULL};
struct keyword *tempt=(struct keyword*) malloc (sizeof(struct keyword));
memset(tempt,0,1);
puts("............................");
puts(hash_array1[8]->word);
puts("............................");
FILE *f = fopen("/home/administrator/chitkarasearch/karan.txt","w");
for(i=1;i<100;i++){
if(hash_array1[i]!=NULL){
tempt = hash_array1[i];
puts("hello");
while(tempt->next != NULL&&tempt->keys == i ){
puts("jeejda");
fputs(tempt->word,f);
tempt = tempt->next;
}
}
}
fclose(f);
}


int main(int argc,char *argv[])
{ 
int i;
for(i = 1;i<argc;i++){
printf("arg%d:%s\n",i,argv[i]);
}
if(argc == 4){
if(*argv[1] == 49){
 if(testDir(argv[3])){
   if(fetchpage(argv[2]) == 1){
     create_new_file(argv[3]);
     int depth = *argv[1] - '0';
     finding_links(depth,argv[3],argv[2]);
     making_files();
     gather_words();
     //printwordlist();
     printfilelist();
     save_hash_to_file();  
}
}
}
}
return 0;
}
