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


void execute(char *arglist[]){
    int pid,exitstatus;
    
    pid=fork();// create child process
    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            execvp(arglist[0],arglist);//change child process
            perror("execvp failed");
            exit(1);
        default:
            while(wait(&exitstatus)!=pid);//parent process wait
            //printf("child exited with status %d,%d\n",exitstatus>>8,exitstatus&0377);
    }
}

class Commands{
    
    char* connectors ;
    char * command[20];
    int count;
public:
    char* content;
    
    Commands(char* str)
    {
        //content
        content = str;
        
        //connector
        string c = ";&&||";
        int len1 = (int) c.length();
        connectors = new char[len1+1];
        strcpy(connectors,c.c_str());
        
//        cout<<content<<endl;
        //parse commands
        
    }
    
    void parse(){
        count = 0;
        char * p;
        p = strtok(content,connectors);
        
        while(p!= NULL)
        {
            command[count] = p;
            count++;
            p = strtok(NULL, connectors);
        }
//        cout<<count<<endl;
//        for(int i=0;i<count;i++)
//        {
//            cout<<command[i]<<endl;
//        }
    }
    
    void exec(){
        
        for(int i = 0;i<=count;i++)
        {
            char *arglist[20];
            char * p;
            p = strtok(command[i], " ");
            int num = 0;
            while(p!= NULL)
            {
                arglist[num] = p;
                num++;
                p = strtok(NULL, " ");
            }
            arglist[num] = NULL;
//            cout<<*arglist<<endl;
             execute(arglist);
        }
        
        
    }
};


class Command_lines{
    char* content;
    char* comment_connector;
public:
    Command_lines(string str){
        //content
        int len = (int)str.length();
        content =new char[len+1];
        strcpy(content,str.c_str());
        
        //comment_connector
        string c1 = "#";
        int len2 = (int) c1.length();
        comment_connector = new char[len2+1];
        strcpy(comment_connector,c1.c_str());
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
    while(1){
        cout<<"$";
        getline(cin,c);
        if(c=="exit")
            break;
        Command_lines cl(c);
        Commands cs = cl.parseCommands();
        cs.parse();
        cs.exec();
    }
    
}
