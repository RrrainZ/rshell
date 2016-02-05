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

class Commands{
    char* content;
    char* type;
    char* parameters;
public:
    char* getType(string str){
        
        char* type;
        return type;
    }
    char* getParameters(string str){
        
        char* parameters;
        return parameters;
    }
    void exec(){
        
    }
};

class Comments{
    char* content;
public:
    void print(){
        
    }
};

class Command_lines{
    char* content;
    char** connectors;
public:
    Command_lines(string str){
        
    };
    Commands parseCommands(){
        Commands cd;
        return cd;
    }
    Comments parseComments(){
        Comments ct;
        return ct;
    }
};

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
            printf("child exited with status %d,%d\n",exitstatus>>8,exitstatus&0377);
    }
}

int main(int argc, const char * argv[]) {

    string c;
    while(c!="exit"){
        cin>>c;
        Command_lines cl(c);
    }
    
}

