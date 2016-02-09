//
//  main.cpp
//  cs100HW2
//
//  Created by HuZhenyu on 16/2/1.
//  Copyright © 2016年 HuZhenyu. All rights reserved.
//

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;


int execute(char *arglist[]){
    
    int pid, exitstatus,flag = 1;
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
            cout<<con[count]<<endl;
            tmpcontent = subs(tmpcontent,p_len,type);
            command[count] = p;
            count++;
            p = strtok(NULL, connectors);
        }
    }
    
    void exec(){
        int flag;
        for (int i = 0;i<=count;i++)
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
                        continue;
                }
                if(con[i-1] == '|')
                {
                    if(flag != -1)
                        continue;
                }
            }
            flag = execute(arglist);
        }
        
        
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
    Commands parseCommands(){
        char * p;
        p = strtok(content, comment_connector);
        Commands cd(p);
        return cd;
    }
};



int main(int argc, const char * argv[]) {
    
    string c;
    while (1){
        cout << "$";
        getline(cin,c);
        if(c == "exit")
            break;
        Command_lines cl(c);
        Commands cs = cl.parseCommands();
        cs.parse();
        cs.exec();
    }
    
}
