//
//  main.cpp
//  cs100HW3
//
//  Created by HuZhenyu on 16/2/1.
//  Copyright © 2016年 HuZhenyu. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <vector>
#include <stdlib.h> 

using namespace std;

bool compareStrandChar(char * c, string str)
{
    string s = c;
    if (s == str) {
        return true;
    }
    else{
        return false;
    }
    
}

bool contain(char * c, string t)
{
    string s = c;
    string::iterator ps = s.begin(), pt = t.begin(),
    send = s.end(), tend = t.end();
    while(ps != send && pt != tend)
        if(*ps++ == *pt)pt++;
    return (pt == tend)&& (s.size()<=4);
}

int execute(char *arglist[]){
    

    int pid, exitstatus,flag = 1;
    if(compareStrandChar(arglist[0],"test")||compareStrandChar(arglist[0],"["))
    {
        struct stat buf;
        char * f;
        char * path;
        if(compareStrandChar(arglist[1],"-f")||compareStrandChar(arglist[1],"-d")||compareStrandChar(arglist[1],"-e"))
        {
            f = arglist[1];
            path = arglist[2];
        }
        else
        {
            f = arglist[1];
            path = arglist[1];
        }
        //cout<<f<<endl;
        //cout<<path<<endl;
        if(lstat(path, &buf)<0)
        {
            cout<<"(False)"<<endl;
            return -1;
        }
        if (compareStrandChar(f,"-f")) {
            if(S_ISREG(buf.st_mode))
            {
                 cout<<"(True)"<<endl;
            }
            else
                cout<<"(False)"<<endl;
        }
        else if(compareStrandChar(f,"-d"))
        {
            if(S_ISDIR(buf.st_mode))
            {
                cout<<"(True)"<<endl;
            }
            else
                cout<<"(False)"<<endl;
        }
        else{
            if(S_ISREG(buf.st_mode)||S_ISDIR(buf.st_mode))
            {
                cout<<"(True)"<<endl;
            }
            else
                cout<<"(False)"<<endl;
        }
    }
    else{
    // create child process
    pid = fork();
    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            //change child process
            flag = execvp(arglist[0], arglist);
            perror("execvp failed");
            exit(1);
        default:
            //parent process wait
            while(wait(&exitstatus) != pid);
    }
    }
    return flag;
}

class Commands{
    
    char * connectors ;
    char * command[20];
    char con[100];
    int count;
    
public:
    char * content;
    
    Commands(char * str)
    {
        //content
        content = str;
        
        //connector
        string c = ";&&||";
        int len1 = (int) c.length();
        connectors = new char[len1+1];
        strcpy(connectors, c.c_str());
    }
    
    void SetContent(char * str)
    {
        //content
        content = str;
        
        //connector
        string c = ";&&||";
        int len1 = (int) c.length();
        connectors = new char[len1+1];
        strcpy(connectors, c.c_str());
        
    }
    
    int getlen(char * result)
    {
        int i = 0;
        while (result[i]!='\0'){
            i++;
        }
        return i;
    }
    
    string subs(string str,int reduce,char type)
    {
        string p = str;
        if(type == ';')
        {
            p = str.substr(reduce+1);
        }
        else if(type == '&' || type == '|')
        {
            p = str.substr(reduce+2);
        }
        return p;
    }
    
    //parse commands
    void parse(){
        
        count = 0;
        char * p;
        string tmpcontent = content;
        p = strtok(content, connectors);
        int p_len;
        char type;
        
        while(p!= NULL)
        {
            
            p_len = getlen(p);
            type = tmpcontent[p_len];
            con[count] = type;
            tmpcontent = subs(tmpcontent,p_len,type);
            command[count] = p;
            count++;
            p = strtok(NULL, connectors);
        }
    }
    
    int exec(){
        
        int flag = 0;
        int cmdflag = 1;
        
        for (int i = 0;i<=count-1;i++)
        {
            char * arglist[20];
            char * p;
            p = strtok(command[i], " ");
            int num = 0;
            while (p!= NULL)
            {
                arglist[num] = p;
                num++;
                p = strtok(NULL, " ");
            }
            arglist[num] = NULL;
            if(i>0){
                if(con[i-1] == '&')
                {
                    if(flag == -1)
                    {
                        continue;
                    }
                }
                if(con[i-1] == '|')
                {
                    if(flag != -1)
                        continue;
                }
            }
//            cout<<*arglist<<endl;
            flag = execute(arglist);
            if(i>0){
                if(con[i-1] == '|' && flag == 1)
                    cmdflag = 1;
                if (con[i-1] == '&' && flag == -1) {
                    cmdflag = -1;
                }
            }
        }
        return cmdflag;
    }
};

class PrecedenceCommands{
    
    char * content;
    char * connectors;
    char * command[20];
    char * con[10];
    int count;
    vector<Commands * > list;
    
public:
    PrecedenceCommands(char * str)
    {
        //content
        content = str;
        
        //connector
        string c = "()";
        int len1 = (int) c.length();
        connectors = new char[len1+1];
        strcpy(connectors, c.c_str());
    }
    void parse(){
        
        count = 0;
        char * p;
        string tmpcontent = content;
        p = strtok(content, connectors);
        
        while(p!= NULL)
        {
            command[count] = p;
            p = strtok(NULL, connectors);
            count++;
        }
    }
    void exec()
    {
        int flag = 0;
        char * arg[20];
        int num1 = 0;
        int num = 0;
        for (int i = 0;i<=count-1;i++)
        {
            if(contain(command[i], "&&")||contain(command[i], "||")||contain(command[i], ";"))
            {
                con[num1] = command[i];
                //cout<<con[num1]<<endl;
                num1++;
            }
            else
            {
                arg[num] = command[i];
                num++;
            }
        }
//        cout<<"here"<<endl;
        for (int j=0; j<num; j++) {
            if (j>0) {
                if(contain(con[j-1], "&&"))
                {
                    
                    if(flag == -1)
                    continue;
                }
                if(contain(con[j-1], "||"))
                {
                    if(flag != -1)
                    continue;
                }
            }
            //cout<<arg[j]<<endl;
            Commands cmds(arg[j]);
            cmds.parse();
            flag = cmds.exec();
        }
//    }
    }
};



class Command_lines{
    char * content;
    char * comment_connector;
public:
    Command_lines(string str){
        //content
        int len = (int) str.length();
        content = new char[len+1];
        strcpy(content, str.c_str());
        
        //comment_connector
        string c1 = "#";
        int len2 = (int) c1.length();
        comment_connector = new char[len2+1];
        strcpy(comment_connector, c1.c_str());
    };
    PrecedenceCommands parseCommands(){
        char * p;
        p = strtok(content, comment_connector);
        PrecedenceCommands pcd(p);
        return pcd;
        
    }
};



int main(int argc, const char * argv[]) {
    string c;
    while (1){
        cout << "$";
        getline(cin,c);
        if(c == "exit")
            break;
        int count1 = 0;
        int count2 = 0;
        string str = c;
        for(int i = 0;i<(int)str.size();i++)
        {
            if (str[i] == '(' )
                count1++;
            if (str[i] == ')')
                count2++;
        }
        if (count1!=count2) {
            cout<<"No match ( and )"<<endl;
            continue;
        }
        else
        {
        Command_lines cl(c);
        PrecedenceCommands pcs = cl.parseCommands();
        pcs.parse();
        pcs.exec();
        }
    }
    
}
