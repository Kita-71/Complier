%{
    int count=0;//计数器
    char*yyval;//用于指向暂存字符串
    char*current;//当前正在打开的文件的文件名
    int offset=0;//当前文件的
    typedef struct files
    {
        char* name;
        int pos;
    }files;//用于记录待分析文件
    files f[10];//待分析文件栈
    int top=-1;//栈顶指针
%}

%%
#include("\x20"*)<.+> {
    //文件预处理操作
    int first=0;
    offset+=yyleng;
    for(int i=0;i<yyleng;i++)
    {
        if(yytext[i]=='<')
        {
            first=i;
            break;
        }
    }
    yyval = malloc(yyleng-first-1);
    memcpy(yyval, yytext + first+1, yyleng -first-2);
    yyval[yyleng -first-2]=0;
    
    //当前处理文件入栈，并退出
    top++;
    f[top].name=current;
    f[top].pos=offset;
    fclose(yyin);

    //新的文件作为当前处理的文件
    current=yyval;
    yyin=fopen(yyval,"r");
    offset=0;

    yyrestart(yyin);
}

int|void|NULL|if|else|while|for|return {
    //关键字
    count++;
    offset+=yyleng;
    printf("word_%d keyword:%s\n",count,yytext);
}

"+"|"-"|"*"|"/"|"="|"=="|"!="|"<"|"<="|">"|">=" {
    //运算符
    count++;
    offset+=yyleng;
    printf("word_%d operator:%s\n",count,yytext);
}


["!"|"<"|">"][^A-Za-z0-9|","|";"|"；"|"{"|"}"|"("|")"|"\""] {
    //运算符错误处理
    offset+=yyleng;
    printf("ERROR: %s is not define, do you mean '%c=' ?\n",yytext,*yytext);
}


","|";"|"；"|"{"|"}"|"("|")" {
    //界符
    count++;
    offset+=yyleng;
    printf("word_%d delimiter: %s\n", count, yytext);
}

[A-Za-z]([A-Za-z]|[0-9])* {
    //标识符,字母开头,接任意长度字母和数字
    count ++;
    offset+=yyleng;
	printf("word_%d identifier: %s\n", count, yytext);
}

[0-9]* {
    //整型常量
	count ++;
    offset+=yyleng;
	printf("word_%d int_constant: %s\n", count, yytext);
}

\"(\\\"|[^"]|\n)*\" {
    //字符串和界符"
    count++;
    offset+=yyleng;
    printf("word_%d delimiter: \"\n", count);
    count++;
    yyval = malloc(yyleng -1);
    memcpy(yyval, yytext + 1, yyleng - 2);
    yyval[yyleng - 2] = 0;
    printf("word_%d string_constant:%s\n", count,yyval);
    free(yyval);
    count++;
    printf("word_%d delimiter: \"\n", count);
}

"\x20"|"\x09"|"\x0d"|"\x0a" {
    offset+=yyleng;
    //空格x20、缩进x09、回车键x0d、换行x0a，什么都不做
}


. {
    //其他字符出错处理
    offset+=yyleng;
    printf("ERROR: %c is illegal\n",*yytext);
}

%%

int yywrap()
{
    printf("---------------file:%s done-----------------\n",current);
    count=0;
    fclose(yyin);
    if(top!=-1)
    {
        current=f[top].name;
        yyin=fopen(current,"r");
        //printf("%s\n",current);
        //printf("%d\n",f[top].pos);
        if(yyin==NULL)
        {
            printf("ERROR: can't find the input file:%s\n",current);
        }
        offset=f[top].pos;
        fseek(yyin,offset, SEEK_SET);
        top--;
        return 0;
    }
    return 1;
}

int main(int argc,char**argv)
{
    yyin= fopen("input.txt","r");
    current=malloc(sizeof("input.txt"));
    memcpy(current,"input.txt",sizeof("input.txt"));
    if(yyin==NULL)
    {
        printf("ERROR: can't find the input file");
        return 0;
    }
    yylex();
    return 0;
}
